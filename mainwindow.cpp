#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QComboBox>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

#include "Scheme.h"
#include <floydsetinTool.h>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QTimer>
using namespace cv;

cv::Mat MainWindow::img={};
cv::Mat MainWindow::img_resized={};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pBloadImage, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(ui->pBstartLayering, &QPushButton::clicked, this, &MainWindow::analyzeImage);

    connect(ui->pBsaveSchemeAs, &QPushButton::clicked, this, &MainWindow::saveAsScheme);
    connect(ui->pBsaveScheme, &QPushButton::clicked, this, &MainWindow::saveScheme);
    connect(ui->pbNewScheme, &QPushButton::clicked, this, &MainWindow::newScheme);
    connect(ui->pbOpenScheme, &QPushButton::clicked, this, &MainWindow::openScheme);

    connect(ui->dSBcAdjustmentCoefficient, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dSBcAdjustmentCoefficient);
    connect(ui->dSBmAdjustmentCoefficient, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dSBmAdjustmentCoefficient);
    connect(ui->dSByAdjustmentCoefficient, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dSByAdjustmentCoefficient);
    connect(ui->dSBkAdjustmentCoefficient, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dSBkAdjustmentCoefficient);
    connect(ui->hSColorSaturation, &QSlider::valueChanged, this, &MainWindow::colorSaturationChanged);

    connect(ui->cBblackLayering, &QCheckBox::toggled, this, &MainWindow::blackLayerChanged);




    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init() {

    floydsetin=new floydsetinTool();
    scheme=new Scheme();
    ImProcess=new ImProcessTool();
    // 创建保存图像的目录（如果它不存在）
    QString exeDir = QCoreApplication::applicationDirPath();
    exeDir.replace("\\", "/");

    imageSplitDirPath = exeDir + "/image_split";
    QDir().mkpath(imageSplitDirPath); // 如果目录已存在，mkpath 会直接返回 true

    inifile_Path = exeDir + "/ini" + "/config.ini";
    QDir().mkpath(exeDir + "/ini"); // 如果目录已存在，mkpath 会直接返回 true

    // 实例化QSettings对象，指向之前创建的配置文件
    QSettings settings(inifile_Path, QSettings::IniFormat);


    //*****************************************************************************************************
    scheme->schemePath= settings.value("schemePath", "").toString();


    if (settings.value("IsStartWithScheme", false).toBool()){
        ui->cbStartInScheme->setChecked(true);
        loadScheme(scheme->schemePath);}

}

void MainWindow::loadImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        imagePath = fileName;
        QImage img;
        img.load(fileName);
        QPixmap pixmap = QPixmap::fromImage(img);
        ui->lbOriginalImageDisplay->setPixmap(pixmap.scaled(ui->lbOriginalImageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // Load the source image
        OriginalImage = cv::imread(imagePath.toLocal8Bit().toStdString());
        ProcessImage=OriginalImage;
        ui->lbImageName->setText(imagePath);
    }
}

void MainWindow::analyzeImage() {

    if(scheme->schemePath==""||ui->leSchemeDameDisplay->text()==""){
        QMessageBox box(QMessageBox::Question,QStringLiteral("提示"),QStringLiteral("请先建立方案"));
        box.setStandardButtons (QMessageBox::Ok);
        box.exec ();
        return;}

    if (ProcessImage.empty()||ui->sBimageHeight->value()<=0||ui->sbGrayLevel->value()<=0){

        QMessageBox *box=new QMessageBox(QMessageBox::Question,QStringLiteral("提示"),QStringLiteral("请选择图像，灰度层级和图片高度要大于0"));

        box->setStandardButtons(QMessageBox::NoButton); // 禁用默认按钮
        // 使用 QTimer 设置1秒后自动关闭消息框
        QTimer::singleShot(1000,  box, [box]() {
            box->close();
            box->deleteLater();
        });
        // 打开消息框（非模态）
        box->open ();
        return;}


    bool  DrawLntype;
    floydsetin->lineDistanceC=ui->dsbLineDistanceC->value();
    floydsetin->lineDistanceM=ui->dsbLineDistanceM->value();
    floydsetin->lineDistanceY=ui->dsbLineDistanceY->value();
    floydsetin->lineDistanceK=ui->dsbLineDistanceK->value();
    double imageHeight=ui->sBimageHeight->value();
    int   grayLevel=ui->sbGrayLevel->value();
    bool blackLayer=ui->cBblackLayering->checkState();
    floydsetin->floydsetinTooLlineDistance=std::max({floydsetin->lineDistanceC, floydsetin->lineDistanceM, floydsetin->lineDistanceY, floydsetin->lineDistanceK});
    floydsetin->floysetinTooLimageHeight=imageHeight;

    vector<int> colorList;
    Mat img_cmyk,halftoneOut,mat_not,circleOrRect,processMat;

    ColorCorrection={{ui->sBccOriginal->value(),ui->sBcmOriginal->value(),ui->sBcyOriginal->value(),100},
                     {ui->sBmcOriginal->value(),ui->sBmmOriginal->value(),ui->sBmyOriginal->value(),100},
                     {ui->sBycOriginal->value(),ui->sBymOriginal->value(),ui->sByyOriginal->value(),100},
                     //{ui->sBkcOriginal->value(),ui->sBkmOriginal->value(),ui->sBkyOriginal->value(),100}
                    };
    floydsetin->solveLinear3x3(ColorCorrection);

    if(ui->cmbDrawLnType->currentIndex()==0){DrawLntype=true;}else { DrawLntype=false;}


    Mat ProcessImageBN;
    ProcessImageBN=ProcessImage;
    // Split CMYK channels
    img_cmyk.create(ProcessImage.rows, ProcessImage.cols, CV_8UC4);
    if(blackLayer){ProcessImageBN = Mat();bitwise_not(ProcessImage,ProcessImageBN);}
    ImProcess->splitCMYK(ProcessImageBN, img_cmyk);
    //ImProcess->rgbToCmyk(ProcessImageBN, img_cmyk);
    split(img_cmyk, vecCmykRgb);

    QLabel *cmykLabels[4] = {ui->lbOriginalImageDisplay_cORr, ui->lbOriginalImageDisplay_mORg, ui->lbOriginalImageDisplay_yORb, ui->lbOriginalImageDisplay_k};
    // 对于C, M, Y通道
    Contrast=vecCmykRgb;

    // 遍历CMYK通道
    for (int i = 0; i < 4; ++i) {


        Mat colorCmykChannel;
        ImProcess->processChannels(vecCmykRgb,colorCmykChannel,i);
        dSBcAdjustmentCoefficient(ui->dSBcAdjustmentCoefficient->value());
        dSBmAdjustmentCoefficient(ui->dSBmAdjustmentCoefficient->value());
        dSByAdjustmentCoefficient(ui->dSByAdjustmentCoefficient->value());
        dSBkAdjustmentCoefficient(ui->dSBkAdjustmentCoefficient->value());
        // 显示图像
        displayImage(colorCmykChannel, cmykLabels[i]);

    }
    // 合并Cyan, Magenta和Yellow通道生成一个CMY图像
    Mat Cmy;
    vector<Mat> cmyChannels = {
        vecCmykRgb[0] + vecCmykRgb[2],  // 合并Cyan和Yellow通道到Red
        vecCmykRgb[0] + vecCmykRgb[1],  // 合并Cyan和Magenta通道到Green
        vecCmykRgb[1] + vecCmykRgb[2]   // 合并Magenta和Yellow通道到Blue
    };

    // 对每个通道进行限制，确保值在0到255之间
    for (Mat &channel : cmyChannels) {
        cv::threshold(channel, channel, 255, 255, THRESH_TRUNC); // 限制最大值为255
    }

    // 合并通道
    merge(cmyChannels, Cmy);



    selcetLayre(colorList);
    if( colorList.empty()){
        QMessageBox box(QMessageBox::Question,QStringLiteral("提示"),QStringLiteral("选择要打印的图层"));
        box.setStandardButtons (QMessageBox::Ok);
        box.exec ();
        return;}


    QVector<double> lineDistance={floydsetin->lineDistanceC, floydsetin->lineDistanceM, floydsetin->lineDistanceY, floydsetin->lineDistanceK};
    for(const auto &intColor : colorList){

        processMat=NULL;
        processMat=vecCmykRgb[intColor];

        grayLevel=std::floor((grayLevel*floydsetin->floydsetinTooLlineDistance/lineDistance[intColor]));
        double density_factor=imageHeight/(lineDistance[intColor]*grayLevel);

        ImProcess->resizeImageWithLanczos4(processMat,processMat,density_factor);
        floydsetin->vectorSize=processMat.cols*processMat.rows*grayLevel*grayLevel;

        cv::flip(processMat,processMat,0);

        floydsetin->pltPathDxf=imageSplitDirPath+QString("/LayerColor %1 Matrix.dxf").arg(intColor);
        floydsetin->halftoneUsingline_doubelSizeGridWithErrorDiffusionAndMatrixTest(processMat, halftoneOut,grayLevel,DrawLntype,intColor,dataDenstyScaling,blackRange);

        cv::flip(processMat,processMat,0);
        cv::flip(halftoneOut,halftoneOut,0);

        // 将线段位置信息保存为 .plt 文件

    }
    QMessageBox box(QMessageBox::Question,QStringLiteral("提示"),QStringLiteral("矢量图生成完成"));
    box.setStandardButtons (QMessageBox::Ok);
    box.exec ();
}

void MainWindow::displayImage(const cv::Mat &image, QLabel *label) {
    cv::Mat rgb;
    cv::cvtColor(image, rgb, cv::COLOR_BGR2RGB);
    QImage qimg(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(qimg);
    label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}





void MainWindow::exportVectorImage() {


}

void MainWindow::exportGrayImage() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Gray Image", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        Mat grayImage;
        cvtColor(imread(imagePath.toLocal8Bit().toStdString()), grayImage, COLOR_BGR2GRAY);
        imwrite(fileName.toLocal8Bit().toStdString(), grayImage);
    }
}

void MainWindow::colorSaturationChanged(int index) {
    // 获取当前图像

    if (OriginalImage.empty()) {
        return;
    }


    ImProcess->colorSaturation(OriginalImage,ProcessImage,index);

    ui->lbColorSaturationDisplay->setText(QString("% %1").arg(index));
    // 显示调整后的图像
    displayImage(ProcessImage, ui->lbOriginalImageDisplay);

}

void MainWindow::blackLayerChanged(bool checked) {
    // 获取当前图像

    blackLayer=checked;


}



void MainWindow::loadScheme(const QString &filePath) {


    scheme->loadScheme(filePath, imagePath,grayLevel, halftoneGridType, DrawLnType, colorlayereType,
                       dsbLineDistanceC,  dsbLineDistanceM,  dsbLineDistanceY,  dsbLineDistanceK,imageHeight, blackLayer,dataDenstyScaling,blackRange,colorSaturationList,colorLayerList,ColorCorrection);

    ui->hSColorSaturation->setValue(colorSaturationList[0]);
    ui->lbColorSaturationDisplay->setText(QString::number(colorSaturationList[0]));
    ui->dSBcAdjustmentCoefficient->setValue(colorSaturationList[1]);
    ui->dSBmAdjustmentCoefficient->setValue(colorSaturationList[2]);
    ui->dSByAdjustmentCoefficient->setValue(colorSaturationList[3]);
    ui->dSBkAdjustmentCoefficient->setValue(colorSaturationList[4]);
    ui->sbGrayLevel->setValue(grayLevel);
    ui->cBblackLayering->setChecked(blackLayer);
    ui->dsbLineDistanceC->setValue(dsbLineDistanceC);
    ui->dsbLineDistanceM->setValue(dsbLineDistanceM);
    ui->dsbLineDistanceY->setValue(dsbLineDistanceY);
    ui->dsbLineDistanceK->setValue(dsbLineDistanceK);

    ui->leSchemeDameDisplay->setText(scheme->schemePath);

    ui->sBimageHeight->setValue(imageHeight);
    ui->cmbDrawLnType->setCurrentIndex(DrawLnType);

    // 设置各个 QCheckBox 的状态
    ui->cBSelectCorR->setCheckState(colorLayerList[0] ? Qt::Checked : Qt::Unchecked);
    ui->cBSelectMorG->setCheckState(colorLayerList[1] ? Qt::Checked : Qt::Unchecked);
    ui->cBSelectYorB->setCheckState(colorLayerList[2] ? Qt::Checked : Qt::Unchecked);
    ui->cBSelectK->setCheckState(colorLayerList[3] ? Qt::Checked : Qt::Unchecked);

    ui->dsbLineDistanceC->setValue(dsbLineDistanceC);
    ui->dsbLineDistanceM->setValue(dsbLineDistanceM);
    ui->dsbLineDistanceY->setValue(dsbLineDistanceY);
    ui->dsbLineDistanceK->setValue(dsbLineDistanceK);

    QVector<QVector<QSpinBox*>> ColorCorrectionUi={{ui->sBccOriginal,ui->sBcmOriginal,ui->sBcyOriginal},
                                                   {ui->sBmcOriginal,ui->sBmmOriginal,ui->sBmyOriginal},
                                                   {ui->sBycOriginal,ui->sBymOriginal,ui->sByyOriginal},
                                                   //{ui->sBkcOriginal,ui->sBkmOriginal,ui->sBkyOriginal,ui->sBkkOriginal}
                                                  };





    // 假设有一个与ColorCorrection相同维度的QVector<QVector<int>> matrixToShow，其中保存了需要显示的值
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ColorCorrectionUi[i][j]->setValue(ColorCorrection[i][j]);
        }
    }


    ui->lbImageName->setText(imagePath);
    if (!imagePath.isEmpty()) {
        OriginalImage = cv::imread(imagePath.toLocal8Bit().toStdString());
        ProcessImage = OriginalImage;

        // Process the image (assuming colorSaturation modifies ProcessImage)
        ImProcess->colorSaturation(OriginalImage, ProcessImage, colorSaturationList[0]);

        // Convert cv::Mat (ProcessImage) to QImage
        QImage img((const unsigned char*) ProcessImage.data, ProcessImage.cols, ProcessImage.rows, ProcessImage.step, QImage::Format_RGB888);

        // Convert BGR to RGB (since OpenCV loads images in BGR format)
        QImage imgRGB = img.rgbSwapped();

        // Convert QImage to QPixmap and display
        QPixmap pixmap = QPixmap::fromImage(imgRGB);
        ui->lbOriginalImageDisplay->setPixmap(pixmap.scaled(ui->lbOriginalImageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }


}

void MainWindow::saveAsScheme() {

    if(scheme->schemePath==""||ui->leSchemeDameDisplay->text()==""){
        QMessageBox box(QMessageBox::Question,QStringLiteral("提示"),QStringLiteral("请先建立方案"));
        box.setStandardButtons (QMessageBox::Ok);
        box.exec ();
        return;}

    QString fileName = QFileDialog::getSaveFileName(this, "Save Scheme As", "", "Scheme Files (*.json)");
    if (!fileName.isEmpty()) {
        colorSaturationList = {
            static_cast<double>(ui->hSColorSaturation->value()),
            ui->dSBcAdjustmentCoefficient->value(),
            ui->dSBmAdjustmentCoefficient->value(),
            ui->dSByAdjustmentCoefficient->value(),
            ui->dSBkAdjustmentCoefficient->value()
        };

        colorLayerList = {
            ui->cBSelectCorR->isChecked(),
            ui->cBSelectMorG->isChecked(),
            ui->cBSelectYorB->isChecked(),
            ui->cBSelectK->isChecked()
        };

        ColorCorrection={{ui->sBccOriginal->value(),ui->sBcmOriginal->value(),ui->sBcyOriginal->value()},
                         {ui->sBmcOriginal->value(),ui->sBmmOriginal->value(),ui->sBmyOriginal->value()},
                         {ui->sBycOriginal->value(),ui->sBymOriginal->value(),ui->sByyOriginal->value()},
                        };

        scheme->saveCurrentScheme(fileName, imagePath, ui->sbGrayLevel->value(), halftoneGridType , ui->cmbDrawLnType->currentIndex()
                                  , "cmyk"  ,ui->dsbLineDistanceC->value(),ui->dsbLineDistanceM->value(),ui->dsbLineDistanceY->value(),
                                  ui->dsbLineDistanceK->value(),ui->sBimageHeight->value()
                                  ,ui->cBblackLayering->isChecked(), ui->dsbLineDistanceC->value(),0,colorSaturationList,colorLayerList,ColorCorrection);
        scheme->setSchemePath(fileName);
    }
    save_setting("IsStartWithScheme",ui->cbStartInScheme->isChecked());
    save_setting("schemePath",scheme->schemePath);

}

void MainWindow::saveScheme() {
    if(scheme->schemePath==""||ui->leSchemeDameDisplay->text()==""){
        QMessageBox box(QMessageBox::Question,QStringLiteral("提示"),QStringLiteral("请先建立方案"));
        box.setStandardButtons (QMessageBox::Ok);
        box.exec ();
        return;}
    if (!scheme->getSchemePath().isEmpty()) {
        colorSaturationList = {
            static_cast<double>(ui->hSColorSaturation->value()),
            ui->dSBcAdjustmentCoefficient->value(),
            ui->dSBmAdjustmentCoefficient->value(),
            ui->dSByAdjustmentCoefficient->value(),
            ui->dSBkAdjustmentCoefficient->value()
        };

        QVector<bool> colorLayerList = {
            ui->cBSelectCorR->isChecked(),
            ui->cBSelectMorG->isChecked(),
            ui->cBSelectYorB->isChecked(),
            ui->cBSelectK->isChecked()
        };
        ColorCorrection={{ui->sBccOriginal->value(),ui->sBcmOriginal->value(),ui->sBcyOriginal->value()},
                         {ui->sBmcOriginal->value(),ui->sBmmOriginal->value(),ui->sBmyOriginal->value()},
                         {ui->sBycOriginal->value(),ui->sBymOriginal->value(),ui->sByyOriginal->value()},
                        };

        scheme->saveCurrentScheme(scheme->getSchemePath(), imagePath,  ui->sbGrayLevel->value(),0 , ui->cmbDrawLnType->currentIndex()
                                  , "cmyk"  ,ui->dsbLineDistanceC->value(),ui->dsbLineDistanceM->value(),ui->dsbLineDistanceY->value(),
                                  ui->dsbLineDistanceK->value(),ui->sBimageHeight->value()
                                  ,ui->cBblackLayering->isChecked(), 0,0,colorSaturationList,colorLayerList,ColorCorrection);
    } else {
        saveAsScheme();
    }
    save_setting("IsStartWithScheme",ui->cbStartInScheme->isChecked());
    save_setting("schemePath",scheme->schemePath);

}

void MainWindow::openScheme() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Scheme", "", "Scheme Files (*.json)");
    if (!fileName.isEmpty()) {
        scheme->setSchemePath(fileName);
        loadScheme(fileName);
        ui->leSchemeDameDisplay->setText(scheme->schemePath);
    }
}

void MainWindow::newScheme() {
    QString fileName = QFileDialog::getSaveFileName(this, "New Scheme", "", "Scheme Files (*.json)");
    if (!fileName.isEmpty()) {
        scheme->resetScheme();  // 重置方案
        scheme->setSchemePath(fileName);  // 设置方案路径

        // 设置默认值
        ui->hSColorSaturation->setValue(1.0);
        ui->cBblackLayering->setChecked(false);
        ui->sbGrayLevel->setValue(3);
        ui->dsbLineDistanceC->setValue(1.0);
        ui->dsbLineDistanceM->setValue(1.0);
        ui->dsbLineDistanceY->setValue(1.0);
        ui->dsbLineDistanceK->setValue(1.0);

        imagePath.clear();
        //loadImage();  // 清空图像显示
        int grayLevel=3;
        double dsbLineDistanceC=0.01;
        double dsbLineDistanceM=0.01;
        double dsbLineDistanceY=0.01;
        double dsbLineDistanceD=0.01;
        double imageHeight=25;
        double dataDenstyScaling=1;
        int BlackRange=grayLevel;
        // 创建并保存空白方案文件
        scheme->saveCurrentScheme(fileName, imagePath,grayLevel, 1, 1,"CMYK", dsbLineDistanceC,dsbLineDistanceM,dsbLineDistanceY,dsbLineDistanceD,
                                  imageHeight,false,dataDenstyScaling,BlackRange,{1.0,1.0,1.0,1.0,1.0},{true,true,true,true},{{100,0,0},{0,100,0},{0,0,100}});
        ui->leSchemeDameDisplay->setText(scheme->schemePath);
    }
}








void MainWindow::save_setting(const QString &key, const QVariant &value) {


    // 在inifile文件夹中新建一个ini文件
    QSettings settings(inifile_Path ,QSettings::IniFormat);

    // 以键值对的形式写入数据
    settings.setValue(key, value);
}





void MainWindow::dSBcAdjustmentCoefficient(double value){

    if(Contrast.empty()){return;}
    ImProcess->adjustContrast(Contrast[0], vecCmykRgb[0] , value, 0);
    displayImage(vecCmykRgb[0], ui->lbOriginalImageDisplay_cORr);

}

void MainWindow::dSBmAdjustmentCoefficient(double value){

    if(Contrast.empty()){return;}
    ImProcess->adjustContrast(Contrast[1], vecCmykRgb[1] , value, 0);
    displayImage(vecCmykRgb[1], ui->lbOriginalImageDisplay_mORg);


}

void MainWindow::dSByAdjustmentCoefficient(double value){

    if(Contrast.empty()){return;}
    ImProcess->adjustContrast(Contrast[2], vecCmykRgb[2] , value, 0);
    displayImage(vecCmykRgb[2], ui->lbOriginalImageDisplay_yORb);


}

void MainWindow::dSBkAdjustmentCoefficient(double value){

    if(Contrast.empty()||Contrast[3].empty()){return;}
    ImProcess->adjustContrast(Contrast[3], vecCmykRgb[3] , value, 0);
    displayImage(vecCmykRgb[3], ui->lbOriginalImageDisplay_k);


}





void MainWindow::halftoneGridTypeChanged(int index){

    halftoneGridType=index;


}




void  MainWindow::selcetLayre(vector<int> &color){



    if (ui->cBSelectCorR->isChecked()){          color.push_back(0);    }

    if (ui->cBSelectMorG->isChecked()) {    color.push_back(1);    }

    if (ui->cBSelectYorB->isChecked()) {    color.push_back(2);    }

    if (ui->cBSelectK->isChecked()) {    color.push_back(3);    }


}

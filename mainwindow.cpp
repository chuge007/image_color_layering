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

    connect(ui->pBdisplayImage1, &QPushButton::clicked, this, &MainWindow::pBdisplayImage1);
    connect(ui->pBdisplayImage2, &QPushButton::clicked, this, &MainWindow::pBdisplayImage2);
    connect(ui->pBdisplayImage3, &QPushButton::clicked, this, &MainWindow::pBdisplayImage3);
    connect(ui->pBdisplayImage4, &QPushButton::clicked, this, &MainWindow::pBdisplayImage4);

    connect(ui->pBsaveSchemeAs, &QPushButton::clicked, this, &MainWindow::saveAsScheme);
    connect(ui->pBsaveScheme, &QPushButton::clicked, this, &MainWindow::saveScheme);
    connect(ui->pbNewScheme, &QPushButton::clicked, this, &MainWindow::newScheme);
    connect(ui->pbOpenScheme, &QPushButton::clicked, this, &MainWindow::openScheme);

    //    connect(ui->pBexportVectorDiagram, &QPushButton::clicked, this, &MainWindow::exportVectorImage);
    //    connect(ui->pBexportGrayScaleImage, &QPushButton::clicked, this, &MainWindow::exportGrayImage);
    //connect(ui->dSBcolorSaturation, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::colorSaturationChanged);
    connect(ui->hSColorSaturation, &QSlider::valueChanged, this, &MainWindow::colorSaturationChanged);
    connect(ui->cBblackLayering, &QCheckBox::toggled, this, &MainWindow::blackLayerChanged);
    connect(ui->cmbColorLayerdType,
            QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::colorLayerChanged);
    connect(ui->cbGridType,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::halftoneGridTypeChanged);
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

    if (ProcessImage.empty()){return;}

    double lineDisdance;
    bool  DrawLntype;
    double lineDistance_f=ui->dsbLineDistance->value();
    double imageHeight=ui->sBimageHeight->value();
    int   grayLevel=ui->sbGrayLevel->value();

    double pixelHeight=lineDistance_f*grayLevel;

    qDebug()<<"pixelHeight   "<<(pixelHeight);

    double density_factor=imageHeight/(lineDistance_f*grayLevel);


    qDebug()<<"density_factor   "<<density_factor;

    floydsetin->lines={};
    floydsetin->linesSegments={};

    if(ui->cmbDrawLnType->currentIndex()==0){DrawLntype=true;}else { DrawLntype=false;}


    vector<int> colorList;
    Mat img_cmyk,halftoneOut,mat_not,processMat,circleOrRect;

    if (ui->cmbColorLayerdType->currentText()=="CMYK"){
        // Split CMYK channels
        img_cmyk.create(ProcessImage.rows, ProcessImage.cols, CV_8UC4);
        ImProcess->splitCMYK(ProcessImage, img_cmyk);
        split(img_cmyk, vecCmykRgb);}
    else {
        // Split RGB channels
        split(ProcessImage, vecCmykRgb);
    }


    if(selcetLayre(colorList)==(-1)){
        QMessageBox box(QMessageBox::Question,QStringLiteral("提示"),QStringLiteral("选择要打印的图层"));
        box.setStandardButtons (QMessageBox::Ok);
        box.exec ();
        return;}

    for(const auto &intColor : colorList){

        processMat=vecCmykRgb[intColor];


        ImProcess->resizeImageWithLanczos4(processMat,processMat,density_factor);

        qDebug()<<"processMat   "<<processMat.cols;

        {
            //circleOrRect=processMat;
            //if (halftoneGridType==0){floydsetin->halftoneUsingCircles_doubelSizeGrid(processMat, circleOrRect, gridSize_f,256);}
            //else {floydsetin->halftoneUsingRect_doubelSizeGrid(processMat, circleOrRect, gridSize_f,256);}

            //floydsetin_16(src);
            //floydsetin->halftone(ProcessImage,halftone_mat,gridSize);
            //floydsetin->floydSteinbergHalftoneUsingPointNum(processMat, halftone_mat, gridSize);

            //floydsetin->halftoneUsingCircles(processMat, halftone_mat, gridSize);
            //floydsetin->halftoneWithCirclesDoubelSizeGridTest(processMat, circle, gridSize_f,density_factor);
            //bitwise_not(processMat,processMat);
            //floydsetin->halftoneUsingCircles_doubelSizeGrid(processMat, processMat, 3,256);
        }

        cv::flip(processMat,processMat,0);

        {
            //floydsetin->halftoneUsingline_doubelSizeGrid_savePat(processMat,floydsetin->lines, gridSize_f,true);
            //floydsetin->halftoneUsingline_doubelSizeGrid(circle, halftone_mat,floydsetin->lines, gridSize_f*0.5,true);
            //floydsetin->halftoneUsingLineWithErrorDiffusion(circle, halftone_mat,floydsetin->lines, gridSize_f,true);
        }
        floydsetin->halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(processMat, halftoneOut,lineDisdance,imageHeight,pixelHeight,grayLevel,DrawLntype);
        cv::flip(processMat,processMat,0);
        cv::flip(halftoneOut,halftoneOut,0);

        // 将线段位置信息保存为 .plt 文件
        floydsetin->mergeLineSegments(floydsetin->lines,floydsetin->linesSegments,DrawLntype);
        QString pltPath=imageSplitDirPath+QString("/LayerColor %1 .plt").arg(intColor);
        floydsetin->saveAsPlt(pltPath.toStdString(), floydsetin->linesSegments);


        if (ui->cmbColorLayerdType->currentText()=="CMYK"){

            // Display and save CMYK channels
            QLabel *cmykLabels[4] = {ui->lbOriginalImageDisplay_cORr, ui->lbOriginalImageDisplay_mORg, ui->lbOriginalImageDisplay_yORb, ui->lbOriginalImageDisplay_k};
            for (int i = 0; i < 4; ++i) {
                std::vector<Mat> channels = {Mat::zeros(ProcessImage.size(), CV_8UC1), Mat::zeros(ProcessImage.size(), CV_8UC1), Mat::zeros(ProcessImage.size(), CV_8UC1)};
                if (i < 3) {
                    channels[i] = vecCmykRgb[i]; // Set the respective channel
                } else {
                    channels = {vecCmykRgb[i], vecCmykRgb[i], vecCmykRgb[i]}; // Set all channels to K for black channel
                }
                Mat colorCmykChannel;
                merge(channels, colorCmykChannel);
                displayImage(vecCmykRgb[i], cmykLabels[i]);
                QString fileName = QString("CMYK_%1.png").arg(i);
                QString filePath = imageSplitDirPath + "/" + fileName;
                cv::imwrite(filePath.toStdString(), vecCmykRgb[i]);
            }

        }else {

            // Display and save RGB channels
            QLabel *rgbLabels[3] = {ui->lbOriginalImageDisplay_cORr, ui->lbOriginalImageDisplay_mORg, ui->lbOriginalImageDisplay_yORb};
            for (int i = 0; i < 3; ++i) {
                //std::vector<Mat> channels = {Mat::zeros(src.size(), CV_8UC1), Mat::zeros(src.size(), CV_8UC1), Mat::zeros(src.size(), CV_8UC1)};
                //channels[i] = vecRgb[i]; // Set the respective channel
                //Mat colorRgbChannel;
                //merge(channels, colorRgbChannel);
                displayImage(vecCmykRgb[i], rgbLabels[i]);
                QString fileName = QString("RGB_%1.png").arg(i);
                QString filePath = imageSplitDirPath + "/" + fileName;
                cv::imwrite(filePath.toStdString(), vecCmykRgb[i]);
            }
        }


        //        QString halftone_fileName = QString("halftoneOut.png").arg(intColor);
        //        QString halftone_filePath = imageSplitDirPath + "/" + halftone_fileName;
        //        cv::imwrite(halftone_filePath.toStdString(),halftoneOut);


        QString circle_fileName = QString("circleOrRect.png").arg(intColor);
        QString circle_filePath = imageSplitDirPath + "/" + circle_fileName;
        cv::imwrite(circle_filePath.toStdString(),processMat);

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



void MainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save As", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        cv::imwrite(fileName.toLocal8Bit().toStdString(), imread(imagePath.toLocal8Bit().toStdString()));
    }
}

void MainWindow::save() {
    if (!imagePath.isEmpty()) {
        cv::imwrite(imagePath.toLocal8Bit().toStdString(), imread(imagePath.toLocal8Bit().toStdString()));
    }
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
    Mat src = cv::imread(imagePath.toLocal8Bit().toStdString());
    if (src.empty()) {
        return;
    }

    // 转换到灰度图像
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // 调整黑色层次
    if (checked) {
        for (int i = 0; i < gray.rows; ++i) {
            for (int j = 0; j < gray.cols; ++j) {
                gray.at<uchar>(i, j) = saturate_cast<uchar>(gray.at<uchar>(i, j) * 1.5);
            }
        }
    }

    // 显示调整后的图像
    displayImage(gray, ui->lbOriginalImageDisplay);
}



void MainWindow::loadScheme(const QString &filePath) {


    scheme->loadScheme(filePath, imagePath,grayLevel, halftoneGridType, DrawLnType, colorlayereType,
                       pixelGridHeight,imageHeight, blackLayer,colorSaturationLIst,colorLayerList);

    ui->hSColorSaturation->setValue(colorSaturationLIst[0]);
    ui->lbColorSaturationDisplay->setText(QString::number(colorSaturationLIst[0]));
    ui->dSBcAdjustmentCoefficient->setValue(colorSaturationLIst[1]);
    ui->dSBmAdjustmentCoefficient->setValue(colorSaturationLIst[2]);
    ui->dSByAdjustmentCoefficient->setValue(colorSaturationLIst[3]);
    ui->dSBkAdjustmentCoefficient->setValue(colorSaturationLIst[4]);
    ui->sbGrayLevel->setValue(grayLevel);
    ui->cBblackLayering->setChecked(blackLayer);
    ui->dsbLineDistance->setValue(pixelGridHeight);
    ui->leSchemeDameDisplay->setText(scheme->schemePath);
    ui->cmbColorLayerdType->setCurrentText(colorlayereType);
    ui->sBimageHeight->setValue(imageHeight);
    ui->cbGridType->setCurrentIndex(halftoneGridType);
    ui->cmbDrawLnType->setCurrentIndex(DrawLnType);

    // 设置各个 QCheckBox 的状态
    ui->cBSelectCorR->setCheckState(colorLayerList[0] ? Qt::Checked : Qt::Unchecked);
    ui->cBSelectMorG->setCheckState(colorLayerList[1] ? Qt::Checked : Qt::Unchecked);
    ui->cBSelectYorB->setCheckState(colorLayerList[2] ? Qt::Checked : Qt::Unchecked);
    ui->cBSelectK->setCheckState(colorLayerList[3] ? Qt::Checked : Qt::Unchecked);


    ui->lbImageName->setText(imagePath);
    if (!imagePath.isEmpty()) {
        QImage img;
        img.load(imagePath);
        QPixmap pixmap = QPixmap::fromImage(img);
        ui->lbOriginalImageDisplay->setPixmap(pixmap.scaled(ui->lbOriginalImageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // Load the source image
        OriginalImage = cv::imread(imagePath.toLocal8Bit().toStdString());
        ProcessImage=OriginalImage;
    }
}

void MainWindow::saveAsScheme() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Scheme As", "", "Scheme Files (*.json)");
    if (!fileName.isEmpty()) {
        QVector<double> colorSaturationList = {
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

        QVector <double> colorSaturationLIst{static_cast<double>(ui->hSColorSaturation->value(), ui->dSBcAdjustmentCoefficient->value(),ui->dSBmAdjustmentCoefficient->value(),ui->dSByAdjustmentCoefficient->value()),ui->dSBmAdjustmentCoefficient->value(),ui->dSBkAdjustmentCoefficient->value()};
        scheme->saveCurrentScheme(fileName, imagePath, ui->sbGrayLevel->value(), halftoneGridType , ui->cmbDrawLnType->currentIndex()
                                  , ui->cmbColorLayerdType->currentText()  ,ui->dsbLineDistance->value(),ui->sBimageHeight->value()
                                  ,ui->cBblackLayering->isChecked(), colorSaturationLIst,colorLayerList);
        scheme->setSchemePath(fileName);
    }
    save_setting("IsStartWithScheme",ui->cbStartInScheme->isChecked());
    save_setting("schemePath",scheme->schemePath);

}

void MainWindow::saveScheme() {

    if (!scheme->getSchemePath().isEmpty()) {
        QVector<double> colorSaturationList = {
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
        scheme->saveCurrentScheme(scheme->getSchemePath(), imagePath,  ui->sbGrayLevel->value(),ui->cbGridType->currentIndex() , ui->cmbDrawLnType->currentIndex()
                                  , ui->cmbColorLayerdType->currentText()  ,ui->dsbLineDistance->value(),ui->sBimageHeight->value()
                                  ,ui->cBblackLayering->isChecked(), colorSaturationLIst,colorLayerList);
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
        ui->dsbLineDistance->setValue(1.0);
        imagePath.clear();
        //loadImage();  // 清空图像显示

        // 创建并保存空白方案文件
        scheme->saveCurrentScheme(fileName, imagePath,1, 1, 1,"CMYK", 1.0,1.0,false,{1.0,1.0,1.0,1.0,1.0},{true,true,true,true});
        ui->leSchemeDameDisplay->setText(scheme->schemePath);
    }
}








void MainWindow::save_setting(const QString &key, const QVariant &value) {


    // 在inifile文件夹中新建一个ini文件
    QSettings settings(inifile_Path ,QSettings::IniFormat);

    // 以键值对的形式写入数据
    settings.setValue(key, value);
}



void MainWindow::colorLayerChanged(){


}



void MainWindow::pBdisplayImage1(){

    if (vecCmyk.empty()||vecRgb.empty()){return;}


    if(ui->cmbColorLayerdType->currentText()=="CMYK"){

        namedWindow("image",cv::WINDOW_NORMAL);
        // 设置鼠标回调函数
        //img=vecCmyk[2];
        cv::setMouseCallback("image", onMouse, nullptr);
        imshow("image",vecCmyk[0]);
    }else {

        namedWindow("image");
        cv::setMouseCallback("image", onMouse, nullptr);
        imshow("image",vecRgb[0]);
    }

}


void MainWindow::pBdisplayImage2(){

    if (vecCmyk.empty()||vecRgb.empty()){return;}
    if(ui->cmbColorLayerdType->currentText()=="CMYK"){

        namedWindow("image",cv::WINDOW_NORMAL);
        // 设置鼠标回调函数
        //img=vecCmyk[2];
        cv::setMouseCallback("image", onMouse, nullptr);
        imshow("image",vecCmyk[1]);
    }else {

        namedWindow("image");
        cv::setMouseCallback("image", onMouse, nullptr);
        imshow("image",vecRgb[1]);
    }

}

void MainWindow::pBdisplayImage3(){

    if (vecCmyk.empty()||vecRgb.empty()){return;}

    if(ui->cmbColorLayerdType->currentText()=="CMYK"){

        namedWindow("image",cv::WINDOW_NORMAL);
        // 设置鼠标回调函数
        //img=vecCmyk[2];
        cv::setMouseCallback("image", onMouse, nullptr);
        //imshow("image",vecCmyk[2]);
    }else {

        namedWindow("image");
        //cv::setMouseCallback("image", onMouse, nullptr);
        imshow("image",vecRgb[2]);
    }

}

void MainWindow::pBdisplayImage4(){

    if (vecCmyk.empty()||vecRgb.empty()){return;}

    if(ui->cmbColorLayerdType->currentText()=="CMYK"){

        namedWindow("image",cv::WINDOW_NORMAL);
        // 设置鼠标回调函数
        //img=vecCmyk[2];
        //cv::setMouseCallback("image", onMouse, nullptr);
        imshow("image",vecCmyk[3]);
    }else {

        //namedWindow("image");
        //cv::setMouseCallback("image", onMouse, nullptr);
        imshow("image",vecRgb[3]);
    }
}


// 鼠标回调函数
void MainWindow::onMouse(int event, int x, int y, int flags, void* userdata) {

    cv::Mat img_resized;
    double scaleFactor = 1.0;
    const double scaleStep = 0.1;
    if (event == cv::EVENT_MOUSEWHEEL) {
        if (flags > 0) {  // 滚轮向上滚动，放大图像
            scaleFactor += scaleStep;
        } else if (flags < 0) {  // 滚轮向下滚动，缩小图像
            scaleFactor -= scaleStep;
            if (scaleFactor < scaleStep) {
                scaleFactor = scaleStep;  // 防止缩放因子过小
            }
        }
        cv::resize(img, img_resized, cv::Size(), scaleFactor, scaleFactor);
        cv::imshow("image", img_resized);
    }
}


void MainWindow::halftoneGridTypeChanged(int index){

    halftoneGridType=index;


}












int MainWindow::selcetLayre(vector<int> &color){



    if (ui->cBSelectCorR->isChecked()){          color.push_back(0);    }
    else if (ui->cBSelectMorG->isChecked()) {    color.push_back(1);    }
    else if (ui->cBSelectYorB->isChecked()) {    color.push_back(2);    }
    else if (ui->cBSelectK->isChecked()) {    color.push_back(3);    }
    else {

        return -1;
    }



}
//    namedWindow("CMYK_C");
//    namedWindow("CMYK_M");
//    namedWindow("CMYK_Y");
//    namedWindow("CMYK_K");
//    namedWindow("CMYK");
//    namedWindow("halftone_mat");
//    imshow("CMYK_C",vecCmyk[0]);
//    imshow("CMYK_M",vecCmyk[1]);
//    imshow("CMYK_Y",vecCmyk[2]);
//    imshow("CMYK_K",vecCmyk[3]);
//    imshow("CMYK",img_cmyk);
//    imshow("halftone_mat",halftone_mat_not);

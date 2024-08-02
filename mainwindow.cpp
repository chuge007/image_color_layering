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

    connect(ui->pBexportVectorDiagram, &QPushButton::clicked, this, &MainWindow::exportVectorImage);
    connect(ui->pBexportGrayScaleImage, &QPushButton::clicked, this, &MainWindow::exportGrayImage);
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


    cbColorLayerdType= settings.value("cbColorLayerdType", "").toString();
    scheme->schemePath= settings.value("schemePath", "").toString();
    halftoneGridType= settings.value("halftoneGridType", "").toInt();
    ui->cbGridType->setCurrentIndex(halftoneGridType);


    if (settings.value("IsStartWithScheme", false).toBool()){
        ui->cbStartInScheme->setChecked(true);
        loadScheme(scheme->schemePath);}


    if (settings.value("cbColorLayerdType", "CMYK").toString()=="CMYK"){

        ui->lbOriginalImageDisplay_r->setEnabled(false);
        ui->lbOriginalImageDisplay_r->setEnabled(false);
        ui->lbOriginalImageDisplay_r->setEnabled(false);

        ui->lbColor1->setText("C");
        ui->lbColor2->setText("M");
        ui->lbColor3->setText("Y");
        ui->lbColor4->setText("K");

    }else {

        ui->lbOriginalImageDisplay_r->setEnabled(true);
        ui->lbOriginalImageDisplay_r->setEnabled(true);
        ui->lbOriginalImageDisplay_r->setEnabled(true);


        ui->lbColor1->setText("R");
        ui->lbColor2->setText("G");
        ui->lbColor3->setText("B");

    }



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

    if (ProcessImage.empty()){return;};


    float gridSize_f=ui->dSBpixelGridheight->value();
    int   which_layer,density_factor=1;
    selcetLayre(which_layer);

    Mat img_cmyk,halftone_mat,mat_not,processMat,circleOrRect;


    img_cmyk.create(ProcessImage.rows, ProcessImage.cols, CV_8UC4);


    //bitwise_not(ProcessImage,ProcessImage);
    // Split CMYK channels
    ImProcess->splitCMYK(ProcessImage, img_cmyk);
    split(img_cmyk, vecCmyk);
    // Split RGB channels
    split(ProcessImage, vecRgb);


    processMat=vecCmyk[which_layer];

    bitwise_not(processMat,processMat);


    if (halftoneGridType==0){floydsetin->halftoneUsingCircles_doubelSizeGrid(processMat, circleOrRect, gridSize_f,500);}
    else {floydsetin->halftoneUsingRect_doubelSizeGrid(processMat, circleOrRect, gridSize_f,500);}

    //floydsetin_16(src);
    //floydsetin->halftone(ProcessImage,halftone_mat,gridSize);
    //floydsetin->floydSteinbergHalftoneUsingPointNum(processMat, halftone_mat, gridSize);

    //floydsetin->halftoneUsingCircles(processMat, halftone_mat, gridSize);
    //floydsetin->halftoneWithCirclesDoubelSizeGridTest(processMat, circle, gridSize_f,density_factor);



    cv::flip(circleOrRect,circleOrRect,0);
    //floydsetin->halftoneUsingline_doubelSizeGrid_savePat(processMat,floydsetin->lines, gridSize_f,true);
    //floydsetin->halftoneUsingline_doubelSizeGrid(circle, halftone_mat,floydsetin->lines, gridSize_f*0.5,true);
    //floydsetin->halftoneUsingLineWithErrorDiffusion(circle, halftone_mat,floydsetin->lines, gridSize_f,true);
    floydsetin->halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(circleOrRect, halftone_mat, gridSize_f,true);
    cv::flip(circleOrRect,circleOrRect,0);
    cv::flip(halftone_mat,halftone_mat,0);

    // 将线段位置信息保存为 .plt 文件
    QString pltPath=imageSplitDirPath+"/line.plt";
    floydsetin->saveAsPlt(pltPath.toStdString(), floydsetin->lines);





    // Display and save CMYK channels
    QLabel *cmykLabels[4] = {ui->lbOriginalImageDisplay_c, ui->lbOriginalImageDisplay_m, ui->lbOriginalImageDisplay_y, ui->lbOriginalImageDisplay_k};
    for (int i = 0; i < 4; ++i) {
        std::vector<Mat> channels = {Mat::zeros(ProcessImage.size(), CV_8UC1), Mat::zeros(ProcessImage.size(), CV_8UC1), Mat::zeros(ProcessImage.size(), CV_8UC1)};
        if (i < 3) {
            channels[i] = vecCmyk[i]; // Set the respective channel
        } else {
            channels = {vecCmyk[i], vecCmyk[i], vecCmyk[i]}; // Set all channels to K for black channel
        }
        Mat colorCmykChannel;
        merge(channels, colorCmykChannel);
        displayImage(vecCmyk[i], cmykLabels[i]);
        QString fileName = QString("CMYK_%1.png").arg(i);
        QString filePath = imageSplitDirPath + "/" + fileName;
        cv::imwrite(filePath.toStdString(), vecCmyk[i]);
    }



    // Display and save RGB channels
    QLabel *rgbLabels[3] = {ui->lbOriginalImageDisplay_b, ui->lbOriginalImageDisplay_g, ui->lbOriginalImageDisplay_r};
    for (int i = 0; i < 3; ++i) {
        //std::vector<Mat> channels = {Mat::zeros(src.size(), CV_8UC1), Mat::zeros(src.size(), CV_8UC1), Mat::zeros(src.size(), CV_8UC1)};
        //channels[i] = vecRgb[i]; // Set the respective channel
        //Mat colorRgbChannel;
        //merge(channels, colorRgbChannel);
        displayImage(vecRgb[i], rgbLabels[i]);
        QString fileName = QString("RGB_%1.png").arg(i);
        QString filePath = imageSplitDirPath + "/" + fileName;
        cv::imwrite(filePath.toStdString(), vecRgb[i]);
    }




    //    displayImage(img_cmyk,ui->lbOriginalImageDisplay_cmyk);
    QString fileName = QString("CMYK.png");
    QString filePath = imageSplitDirPath + "/" + fileName;
    cv::imwrite(filePath.toStdString(),img_cmyk);

    QString halftone_fileName = "halftone_mat.png";
    QString halftone_filePath = imageSplitDirPath + "/" + halftone_fileName;
    cv::imwrite(halftone_filePath.toStdString(),halftone_mat);


    QString circle_fileName = "circle_mat.png";
    QString circle_filePath = imageSplitDirPath + "/" + circle_fileName;
    cv::imwrite(circle_filePath.toStdString(),circleOrRect);

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



void MainWindow::saveCurrentScheme(const QString &filePath) {
    scheme->saveCurrentScheme(filePath, imagePath, ui->hSColorSaturation->value(), ui->cBblackLayering->isChecked(), ui->dSBpixelGridheight->value());
}

void MainWindow::loadScheme(const QString &filePath) {
    double colorSaturation, pixelGridHeight;
    bool blackLayer;
    scheme->loadScheme(filePath, imagePath, colorSaturation, blackLayer, pixelGridHeight);

    ui->hSColorSaturation->setValue(colorSaturation);
    ui->cBblackLayering->setChecked(blackLayer);
    ui->dSBpixelGridheight->setValue(pixelGridHeight);
    ui->leSchemeDameDisplay->setText(scheme->schemePath);
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
        scheme->saveCurrentScheme(fileName, imagePath, ui->hSColorSaturation->value(), ui->cBblackLayering->isChecked(), ui->dSBpixelGridheight->value());
        scheme->setSchemePath(fileName);
    }
    save_setting("IsStartWithScheme",ui->cbStartInScheme->isChecked());
    save_setting("schemePath",scheme->schemePath);
    save_setting("imagePath",imagePath);
    save_setting("cbColorLayerdType",ui->cBblackLayering->text());
    save_setting("halftoneGridType",halftoneGridType);
}

void MainWindow::saveScheme() {
    if (!scheme->getSchemePath().isEmpty()) {
        scheme->saveCurrentScheme(scheme->getSchemePath(), imagePath, ui->hSColorSaturation->value(), ui->cBblackLayering->isChecked(), ui->dSBpixelGridheight->value());
    } else {
        saveAsScheme();
    }
    save_setting("IsStartWithScheme",ui->cbStartInScheme->isChecked());
    save_setting("schemePath",scheme->schemePath);
    save_setting("imagePath",imagePath);
    save_setting("cbColorLayerdType",ui->cBblackLayering->text());
    save_setting("halftoneGridType",halftoneGridType);
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
        ui->dSBpixelGridheight->setValue(1.0);
        imagePath.clear();
        //loadImage();  // 清空图像显示

        // 创建并保存空白方案文件
        scheme->saveCurrentScheme(fileName, imagePath, 1.0, false, 1.0);
        ui->leSchemeDameDisplay->setText(scheme->schemePath);
    }
}


void MainWindow::selcetLayre(int& layer){


    if(ui->cBSelectC->isChecked()){layer=0;}

    else if(ui->cBSelectM->isChecked()){layer=1;}

    else if(ui->cBSelectY->isChecked()){layer=2;}

    else if(ui->cBSelectK->isChecked()){layer=3;}

    else {
        layer=0;
    }

}





void MainWindow::save_setting(const QString &key, const QVariant &value) {


    // 在inifile文件夹中新建一个ini文件
    QSettings settings(inifile_Path ,QSettings::IniFormat);

    // 以键值对的形式写入数据
    settings.setValue(key, value);
}



void MainWindow::colorLayerChanged(){


    if (ui->cmbColorLayerdType->currentText()=="CMYK"){

        ui->lbOriginalImageDisplay_r->setEnabled(false);
        ui->lbOriginalImageDisplay_g->setEnabled(false);
        ui->lbOriginalImageDisplay_b->setEnabled(false);

        ui->lbColor1->setText("C");
        ui->lbColor2->setText("M");
        ui->lbColor3->setText("Y");
        ui->lbColor4->setText("K");

    }else {

        ui->lbOriginalImageDisplay_r->setEnabled(true);
        ui->lbOriginalImageDisplay_g->setEnabled(true);
        ui->lbOriginalImageDisplay_b->setEnabled(true);

        ui->lbColor1->setText("R");
        ui->lbColor2->setText("G");
        ui->lbColor3->setText("B");
    }


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

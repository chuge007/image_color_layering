#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include "Scheme.h"
#include <floydsetinTool.h>
#include <improcesstool.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadImage();
    void analyzeImage();

    void exportVectorImage();
    void exportGrayImage();
    void colorSaturationChanged(int index);
    void blackLayerChanged(bool checked);
    void colorLayerChanged();
    void halftoneGridTypeChanged(int index);
    void pBdisplayImage1();
    void pBdisplayImage2();
    void pBdisplayImage3();
    void pBdisplayImage4();

    void dSBcAdjustmentCoefficient(double value);
    void dSBmAdjustmentCoefficient(double value);
    void dSByAdjustmentCoefficient(double value);
    void dSBkAdjustmentCoefficient(double value);

    void saveAsScheme();
    void saveScheme();
    void openScheme();
    void newScheme();

private:
    Ui::MainWindow *ui;

    QString imageSplitDirPath;
    QString inifile_Path;
    QString imagePath;
    QString colorlayereType;


    cv::Mat OriginalImage;
    cv::Mat ProcessImage;
    //cv::Mat processMat;
    std::vector<Mat> vecRgb, vecCmyk,vecCmykRgb,Contrast;

    floydsetinTool* floydsetin;
    Scheme* scheme;
    ImProcessTool* ImProcess;

    bool IsStartWithScheme;
    bool blackLayer;
    int  DrawLnType;
    int halftoneGridType;
    int gridImageSort;
    int grayLevel;
    int blackRange;
    double dataDenstyScaling;
    double imageHeight;
    double pixelGridHeight;
    //double colorSaturation;
    QVector<QVector<int>> ColorCorrection;
    QVector <double> colorSaturationList;
    QVector <bool>   colorLayerList;
    static cv::Mat img, img_resized;
    static void  onMouse(int event, int x, int y, int flags, void* userdata);
private:

    void init();
    void displayImage(const cv::Mat &image, QLabel *label);
    void selcetLayre(vector<int> &color);
    void loadScheme(const QString &filePath);
    void save_setting(const QString &key, const QVariant &value);
};

#endif // MAINWINDOW_H

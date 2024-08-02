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
    void saveAs();
    void save();
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

    void saveAsScheme();
    void saveScheme();
    void openScheme();
    void newScheme();

private:
    Ui::MainWindow *ui;

    QString imageSplitDirPath;
    QString inifile_Path;
    QString imagePath;
    QString cbColorLayerdType;


    cv::Mat OriginalImage;
    cv::Mat ProcessImage;
    std::vector<Mat> vecRgb, vecCmyk;

    floydsetinTool* floydsetin;
    Scheme* scheme;
    ImProcessTool* ImProcess;

    bool IsStartWithScheme;
    int halftoneGridType;


    static cv::Mat img, img_resized;
    static void  onMouse(int event, int x, int y, int flags, void* userdata);
private:

    void init();
    void displayImage(const cv::Mat &image, QLabel *label);
    void saveCurrentScheme(const QString &filePath);
    void loadScheme(const QString &filePath);
    void selcetLayre(int& layer);
    void save_setting(const QString &key, const QVariant &value);
};

#endif // MAINWINDOW_H

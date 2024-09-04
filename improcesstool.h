#ifndef IMPROCESSTOOL_H
#define IMPROCESSTOOL_H

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class ImProcessTool
{
public:
    ImProcessTool();
    void splitCMYK(cv::Mat &image, cv::Mat &cmyk);
    void splitCMYKT(const Mat& src, Mat& dst);
    void rgbToCmyk(const Mat &rgbImage, Mat &cmykImage) ;
    void colorSaturation(Mat &img,Mat &out,int index);
    void adjustContrast(const cv::Mat& src,  cv::Mat& dst ,double alpha, int beta) ;
    void resizeImageWithLanczos4(const cv::Mat& inputImage, cv::Mat& outputImage,double targetHeight);

    void processChannels(const vector<Mat>& vecCmykRgb, Mat& colorCmykChannel ,int i);
};

#endif // IMPROCESSTOOL_H

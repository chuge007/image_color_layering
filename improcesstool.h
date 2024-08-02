#ifndef IMPROCESSTOOL_H
#define IMPROCESSTOOL_H

#include <opencv2/opencv.hpp>
using namespace cv;
class ImProcessTool
{
public:
    ImProcessTool();
    void splitCMYK(cv::Mat &image, cv::Mat &cmyk);
    void colorSaturation(Mat &img,Mat &out,int index);
};

#endif // IMPROCESSTOOL_H

#include "improcesstool.h"
#include <opencv2/opencv.hpp>

using namespace cv;

ImProcessTool::ImProcessTool()
{

}


void  ImProcessTool::splitCMYK(Mat &image, Mat &cmyk) {
    if (!image.data) {
        std::cout << "Miss Data" << std::endl;
        return ;
    }
    int nl = image.rows; //行数
    int nc = image.cols; //列数
    if (image.isContinuous()) { //没有额外的填补像素
        nc = nc * nl;
        nl = 1; //It is now a 1D array
    }
    //对于连续图像，本循环只执行1次
    for (int i = 0; i < nl; i++) {
        uchar *data = image.ptr<uchar>(i);
        uchar *dataCMYK = cmyk.ptr<uchar>(i);
        for (int j = 0; j < nc; j++) {
            uchar b = data[3 * j];
            uchar g = data[3 * j + 1];
            uchar r = data[3 * j + 2];
            uchar c = 255 - r;
            uchar m = 255 - g;
            uchar y = 255 - b;
            uchar k = std::min(std::min(c, m), y);
            //            dataCMYK[4 * j] = c - k;
            //            dataCMYK[4 * j + 1] = m - k;
            //            dataCMYK[4 * j + 2] = y - k;
            //            dataCMYK[4 * j + 3] = k;

            dataCMYK[4 * j] = c;
            dataCMYK[4 * j + 1] = m;
            dataCMYK[4 * j + 2] = y;
            dataCMYK[4 * j + 3] = k;


        }
    }

}


void ImProcessTool::colorSaturation(Mat &img,Mat &out,int index){


    // 转换到HSV色彩空间
    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);

    // 调整饱和度
    for (int i = 0; i < hsv.rows; ++i) {
        for (int j = 0; j < hsv.cols; ++j) {
            hsv.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(hsv.at<Vec3b>(i, j)[1] * (1.0 + index / 10.0));
        }
    }

    // 转换回BGR色彩空间
    Mat adjusted;
    cvtColor(hsv, adjusted, COLOR_HSV2BGR);
    out=adjusted;





}


// 调整灰度图对比度的函数
void ImProcessTool::adjustContrast(const cv::Mat& src,  cv::Mat& dst ,double alpha, int beta) {

    // alpha: 对比度因子 (1.0 保持原始对比度, <1.0 降低对比度, >1.0 增加对比度)
    // beta: 亮度调整值
    dst.release();
    src.convertTo(dst, -1, alpha, beta);

}


void ImProcessTool::resizeImageWithLanczos4(const cv::Mat& inputImage, cv::Mat& outputImage,double targetHeight) {
    // 检查输入图像是否为空
        if (inputImage.empty()) {
            std::cerr << "输入图像为空，无法处理！" << std::endl;
            return;
        }

        // 计算缩放因子
        double scaleFactor = static_cast<double>(targetHeight) / inputImage.rows;

        // 计算新的尺寸，保持纵横比
        int newWidth = static_cast<int>(inputImage.cols * scaleFactor);
        int newHeight = static_cast<int>(targetHeight); // 直接使用目标高度

        // 使用 Lanczos4 插值方法进行缩放
        cv::resize(inputImage, outputImage, cv::Size(newWidth, newHeight), 0, 0, cv::INTER_LANCZOS4);
}






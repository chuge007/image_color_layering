#include "improcesstool.h"
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;
ImProcessTool::ImProcessTool()
{

}


void  ImProcessTool::splitCMYK(Mat &image, Mat &cmyk) {
    if(!image.data){
        std::cout<<"Miss Data"<<std::endl;
        //return -1;
    }
    int nl = image.rows;	//行数
    int nc = image.cols;	//列数
    if(image.isContinuous()){	//没有额外的填补像素
        nc = nc*nl;
        nl = 1;					//It is now a 1D array
    }
    //对于连续图像，本循环只执行1次
    for(int i=0;i<nl;i++){
        uchar *data = image.ptr<uchar>(i);
        uchar *dataCMYK = cmyk.ptr<uchar>(i);
        for(int j = 0;j < nc;j++){
            uchar b = data[3*j];
            uchar g = data[3*j+1];
            uchar r = data[3*j+2];
            uchar c = 255 - r;
            uchar m = 255 - g;
            uchar y = 255 - b;
            uchar k = min(min(c,m),y);
            //            dataCMYK[4*j] = c - k;
            //            dataCMYK[4*j+1] = m  - k;
            //            dataCMYK[4*j+2] = y  - k;
            //            dataCMYK[4*j+3] = k;

            dataCMYK[4*j] = c ;
            dataCMYK[4*j+1] = m  ;
            dataCMYK[4*j+2] = y  ;
            dataCMYK[4*j+3] = k;


            // 转换 CMYK 值到 0-100 范围
            dataCMYK[4 * j]     = static_cast<uchar>(c * 100.0f / 255.0f); // C 值
            dataCMYK[4 * j + 1] = static_cast<uchar>(m * 100.0f / 255.0f); // M 值
            dataCMYK[4 * j + 2] = static_cast<uchar>(y * 100.0f / 255.0f); // Y 值
            dataCMYK[4 * j + 3] = static_cast<uchar>(k * 100.0f / 255.0f); // K 值
        }
    }
    return ;

}


// Convert BGR to CMYK
void ImProcessTool::splitCMYKT(const Mat& src, Mat& dst) {
    // Check if the image is valid and has three channels
    if (src.empty() || src.channels() != 3) {
        std::cout << "Invalid input image" << std::endl;
        return;
    }

    // Allocate memory for the CMYK image
    dst.create(src.size(), CV_8UC4);

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            Vec3b bgr = src.at<Vec3b>(y, x);
            Vec4b cmyk;

            // Convert from BGR to RGB
            Vec3b rgb;
            rgb[2] = bgr[0]; // B
            rgb[1] = bgr[1]; // G
            rgb[0] = bgr[2]; // R

            // Convert from RGB to CMY
            cmyk[0] = 255 - rgb[2]; // Cyan
            cmyk[1] = 255 - rgb[1]; // Magenta
            cmyk[2] = 255 - rgb[0]; // Yellow

            // Calculate Black (K)
            uchar k = min(rgb[0], min(rgb[1], rgb[2]));
            cmyk[0] -= k; // Subtract black from cyan
            cmyk[1] -= k; // Subtract black from magenta
            cmyk[2] -= k; // Subtract black from yellow
            cmyk[3] = k;  // Black

            // Clamp values between 0 and 255
            cmyk[0] = min(max(cmyk[0], (uchar)0), (uchar)255);
            cmyk[1] = min(max(cmyk[1], (uchar)0), (uchar)255);
            cmyk[2] = min(max(cmyk[2], (uchar)0), (uchar)255);
            cmyk[3] = min(max(cmyk[3], (uchar)0), (uchar)255);

            // Store the CMYK value
            dst.at<Vec4b>(y, x) = cmyk;
        }
    }
}

void ImProcessTool::rgbToCmyk(const Mat &rgbImage, Mat &cmykImage) {
    if (!rgbImage.data) {
        std::cerr << "Image data missing" << std::endl;
        return;
    }

    int rows = rgbImage.rows;
    int cols = rgbImage.cols;

    // Ensure cmykImage is of type CV_8UC4 to handle integer values
    if (cmykImage.type() != CV_8UC4) {
        cmykImage.create(rgbImage.size(), CV_8UC4);
    }

    for (int i = 0; i < rows; ++i) {
        const uchar* src = rgbImage.ptr<uchar>(i);
        uchar* dst = cmykImage.ptr<uchar>(i);

        for (int j = 0; j < cols; ++j) {
            float b = src[3 * j] / 255.0f;
            float g = src[3 * j + 1] / 255.0f;
            float r = src[3 * j + 2] / 255.0f;

            float k = 1.0f - std::max({r, g, b});
            float c = (1.0f - r - k) / (1.0f - k);
            float m = (1.0f - g - k) / (1.0f - k);
            float y = (1.0f - b - k) / (1.0f - k);

            if (k == 1.0f) {
                c = 0.0f;
                m = 0.0f;
                y = 0.0f;
            }

            // Convert CMYK values to 0-100 range
            dst[4 * j]     = static_cast<uchar>(c * 100.0f);  // C value as integer
            dst[4 * j + 1] = static_cast<uchar>(m * 100.0f);  // M value as integer
            dst[4 * j + 2] = static_cast<uchar>(y * 100.0f);  // Y value as integer
            dst[4 * j + 3] = static_cast<uchar>(k * 100.0f);  // K value as integer
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



void ImProcessTool::processChannels(const vector<Mat>& vecCmykRgb, Mat& colorCmykChannel ,int i) {
    float PixelRange=255.0f/100;
    // Check that vecCmykRgb has the correct number of channels
    if (vecCmykRgb.size() != 4) {
        cerr << "Error: vecCmykRgb should have 4 channels (C, M, Y, K)" << endl;
        return;
    }


    Mat cmykChannel = vecCmykRgb[i] * PixelRange; // Scale CMYK values

    // Convert to CV_8UC1 if necessary
    cmykChannel.convertTo(cmykChannel, CV_8UC1);

    if (i == 0) { // Cyan
        // Cyan is mapped to Green and Blue channels
        Mat green = cmykChannel.clone();
        Mat blue = cmykChannel.clone();
        vector<Mat> channels = {blue,green,Mat::zeros(cmykChannel.size(), CV_8UC1)};
        merge(channels, colorCmykChannel);
    } else if (i == 1) { // Magenta
        // Magenta is mapped to Red and Blue channels
        Mat red = cmykChannel.clone();
        Mat blue = cmykChannel.clone();
        vector<Mat> channels = {blue, Mat::zeros(cmykChannel.size(), CV_8UC1),red};
        merge(channels, colorCmykChannel);
    } else if (i == 2) { // Yellow
        // Yellow is mapped to Red and Green channels
        Mat red = cmykChannel.clone();
        Mat green = cmykChannel.clone();
        vector<Mat> channels = { Mat::zeros(cmykChannel.size(), CV_8UC1),green ,red};
        merge(channels, colorCmykChannel);
    } else { // Black
        // Black is mapped to all channels as black
        Mat black = Mat::zeros(cmykChannel.size(), CV_8UC1);
        vector<Mat> channels = {black, black, black};
        merge(channels, colorCmykChannel);
    }

}


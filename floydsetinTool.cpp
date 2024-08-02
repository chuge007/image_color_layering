
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mainwindow.h>
#include <floydsetinTool.h>

using namespace cv;
using namespace std;



uchar floydsetinTool::findfit(uchar p_param)
{
    //0,16,32,
    uchar m = p_param / 16;
    uchar n = p_param % 16;
    if (n <=8)
    {
        return m*16;
    }
    else
    {
        return (m + 1)*16;
    }
}

int floydsetinTool::findfitInt(int pixel_value, int levels) {
    // 量化为指定级别的灰度级别，默认为16级
    int step = 255 / (levels - 1);
    return round(pixel_value / step) * step;
}


void floydsetinTool::fun1(Mat img)
{
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_dst;
    int len = sizeof(ushort);
    int len1 = sizeof(uchar);
    for (int i = 0; i < height; i++)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_dst = dst.ptr<uchar>(i);
        for (int j = 0; j < width; ++j)
        {
            p_dst[j] = (p_img[j] - minv) / (maxv - minv) * 255;
            p_dst[j] = p_dst[j] / 64;
            p_dst[j] = p_dst[j] * 64;
            //cout << (int)p_dst[j] << "  ";
            /*	if (p_dst[j] > 192)
            {
                p_dst[j] = 255;
            }
            else if(p_dst[j] > 128)
            {
                p_dst[j] = 128;
            }
            else if (p_dst[j] > 64)
            {
                p_dst[j] = 64;
            }
            else
            {
                p_dst[j] = 0;
            }*/
            //p_dst[j] = p_img[j*3/2];
            //下面是失真较大的转换方法
            //int temp = img.at<ushort>(i, j);
            //dst.at<uchar>(i, j) = temp;
        }
    }
    //   dst = img;
    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("2", 0);
    cv::resizeWindow("2", 192 * 3, 216 * 3);
    imshow("2", dst);
    imwrite("E:\\4.jpg", dst);
}


void floydsetinTool::fun2(Mat img)
{
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_dst;
    int len = sizeof(ushort);
    int len1 = sizeof(uchar);
    for (int i = 0; i < height; i++)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_dst = dst.ptr<uchar>(i);
        for (int j = 0; j < width; ++j)
        {
            p_dst[j] = (p_img[j] - minv) / (maxv - minv) * 255;
            if (p_dst[j] > 192)
            {
                p_dst[j] = 255;
            }
            else if(p_dst[j] > 128)
            {
                p_dst[j] = 128;
            }
            else if (p_dst[j] > 64)
            {
                p_dst[j] = 64;
            }
            else
            {
                p_dst[j] = 0;
            }
        }
    }
    //   dst = img;
    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("3", 0);
    cv::resizeWindow("3", 192 * 3, 216 * 3);
    imshow("3", dst);
    imwrite("E:\\4.jpg", dst);
}


void floydsetinTool::fun3(Mat img)
{
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_dst;
    int len = sizeof(ushort);
    int len1 = sizeof(uchar);
    for (int i = 0; i < height; i++)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_dst = dst.ptr<uchar>(i);
        for (int j = 0; j < width; ++j)
        {
            p_dst[j] = (p_img[j] - minv) / (maxv - minv) * 255;
            p_dst[j] = p_dst[j] & 0B11000000;
        }
    }
    //   dst = img;
    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("4", 0);
    cv::resizeWindow("4", 192 * 3, 216 * 3);
    imshow("4", dst);
    imwrite("E:\\4.jpg", dst);
}

//误差扩散法1
void floydsetinTool::floydsetin(Mat img)
{
    double a = 0.4375;
    double b = 0.1875;
    double c = 0.3125;
    double d = 0.0625;
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    dst = img;
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_lw;
    uchar* p_dst;
    int tep = 0;
    int err = 0;
    for (int i = 0; i < height-2;++i)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址

        p_lw = img.ptr<uchar>(i+1);
        p_dst = dst.ptr<uchar>(i);
        for (int j = 2; j < width-2; ++j)
        {
            if (p_img[j] > 128)
            {
                tep = 255;
            }
            else
            {
                tep = 0;
            }
            err = p_img[j] - tep;
            p_dst[j + 1] += err * a;
            p_lw[j - 1] += err * b;
            p_lw[j] += err * c;
            p_lw[j + 1] += err * d;
        }
    }

    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("5", 0);
    cv::resizeWindow("5", 192 * 3, 216 * 3);
    imshow("5", dst);
    imwrite("E:\\5.jpg", dst);
}

//误差扩散法2灰阶
void floydsetinTool::floydsetin_2(Mat img)
{
    double a = 0.4375;
    double b = 0.1875;
    double c = 0.3125;
    double d = 0.0625;
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    //dst = img;
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_lw;
    uchar* p_dst;
    int tep = 0;
    int err = 0;
    for (int i = 0; i < height - 2; ++i)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_lw = img.ptr<uchar>(i + 1);
        p_dst = dst.ptr<uchar>(i);
        for (int j = 2; j < width - 2; ++j)
        {
            if (p_img[j] > 128)
            {
                p_dst[j] = 255;
                tep = 255;
            }
            else
            {
                p_dst[j] = 0;
                tep = 0;
            }
            err = p_img[j] - tep;
            p_dst[j + 1] += err * a;
            p_lw[j - 1] += err * b;
            p_lw[j] += err * c;
            p_lw[j + 1] += err * d;
        }
    }

    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("2灰阶", 0);
    cv::resizeWindow("2灰阶", 192 * 3, 216 * 3);
    imshow("2灰阶", dst);
    imwrite("E:\\2灰阶.jpg", dst);
}

//误差扩散法2灰阶
void floydsetinTool::my2(Mat img)
{
    double a = 0.4375;
    double b = 0.1875;
    double c = 0.3125;
    double d = 0.0625;
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    //dst = img;
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_lw;
    uchar* p_dst;
    int tep = 0;
    int err = 0;
    for (int i = 0; i < height - 2; ++i)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_lw = img.ptr<uchar>(i + 1);
        p_dst = dst.ptr<uchar>(i);
        for (int j = 2; j < width - 2; ++j)
        {
            if (p_img[j] > 127)
            {
                p_dst[j] = 255;
                tep = 255;
            }
            else
            {
                p_dst[j] = 0;
                tep = 0;
            }
        }
    }

    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("my2灰阶", 0);
    cv::resizeWindow("my2灰阶", 192 * 3, 216 * 3);
    imshow("my2灰阶", dst);
    imwrite("E:\\my2灰阶.jpg", dst);
}

//误差扩散法4灰阶
void floydsetinTool::floydsetin_4(Mat img)
{
    double a = 0.4375;
    double b = 0.1875;
    double c = 0.3125;
    double d = 0.0625;
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    //dst = img;
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_lw;
    uchar* p_dst;
    int tep = 0;
    int err = 0;
    for (int i = 0; i < height - 2; ++i)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_lw = img.ptr<uchar>(i + 1);
        p_dst = dst.ptr<uchar>(i);
        for (int j = 2; j < width - 2; ++j)
        {
            if (p_img[j] > 192)
            {
                p_dst[j] = 192;
                tep = 192;
            }
            else if (p_img[j] > 128)
            {
                p_dst[j] = 128;
                tep = 128;
            }
            else if (p_img[j] > 64)
            {
                p_dst[j] = 64;
                tep = 64;
            }
            else
            {
                p_dst[j] = 0;
                tep = 0;
            }
            err = p_img[j] - tep;
            p_dst[j + 1] += err * a;
            p_lw[j - 1] += err * b;
            p_lw[j] += err * c;
            p_lw[j + 1] += err * d;
        }
    }

    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("4灰阶", 0);
    cv::resizeWindow("4灰阶", 192 * 3, 216 * 3);
    imshow("4灰阶", dst);
    imwrite("E:\\4灰阶.jpg", dst);
}

//误差扩散法8灰阶
void floydsetinTool::floydsetin_8(Mat img)
{
    double a = 0.4375;
    double b = 0.1875;
    double c = 0.3125;
    double d = 0.0625;
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    //dst = img;
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_lw;
    uchar* p_dst;
    int tep = 0;
    int err = 0;
    for (int i = 0; i < height - 2; ++i)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_lw = img.ptr<uchar>(i + 1);
        p_dst = dst.ptr<uchar>(i);
        for (int j = 2; j < width - 2; ++j)
        {
            if (p_img[j] > 224)
            {
                p_dst[j] = 224;
                tep = 224;
            }
            else if (p_img[j] > 192)
            {
                p_dst[j] = 192;
                tep = 192;
            }
            else if (p_img[j] > 160)
            {
                p_dst[j] = 160;
                tep = 160;
            }
            else if (p_img[j] > 128)
            {
                p_dst[j] = 128;
                tep = 128;
            }
            else if (p_img[j] > 96)
            {
                p_dst[j] = 96;
                tep = 96;
            }
            else if (p_img[j] > 64)
            {
                p_dst[j] = 64;
                tep = 64;
            }
            else if (p_img[j] > 32)
            {
                p_dst[j] = 32;
                tep = 32;
            }
            else
            {
                p_dst[j] = 0;
                tep = 0;
            }
            err = p_img[j] - tep;
            p_dst[j + 1] += err * a;
            p_lw[j - 1] += err * b;
            p_lw[j] += err * c;
            p_lw[j + 1] += err * d;
        }
    }

    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("8灰阶", 0);
    cv::resizeWindow("8灰阶", 192 * 3, 216 * 3);
    imshow("8灰阶", dst);
    imwrite("E:\\8灰阶.jpg", dst);
}

//误差扩散法16灰阶
void floydsetinTool::floydsetin_16(Mat img)
{
    double a = 0.4375;
    double b = 0.1875;
    double c = 0.3125;
    double d = 0.0625;
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    //dst = img;
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_lw;
    uchar* p_dst;
    int tep = 0;
    int err = 0;
    for (int i = 0; i < height - 2; ++i)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_lw = img.ptr<uchar>(i + 1);
        p_dst = dst.ptr<uchar>(i);
        for (int j = 2; j < width - 2; ++j)
        {
            for (int m = 15; m >= 0; --m)
            {
                if (p_img[j] > 16*m)
                {
                    p_dst[j] = 16 * m;
                    tep = 16 * m;
                    break;
                }
            }

            err = p_img[j] - tep;
            p_dst[j + 1] += err * a;
            p_lw[j - 1] += err * b;
            p_lw[j] += err * c;
            p_lw[j + 1] += err * d;
        }
    }

    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("16灰阶", 0);
    cv::resizeWindow("16灰阶", 192 * 3, 216 * 3);
    imshow("16灰阶", dst);
    imwrite("E:\\16灰阶.jpg", dst);
}

//误差扩散法16灰阶
void floydsetinTool::floydsetin_16_001(Mat img)
{
    double a = 0.4375;
    double b = 0.1875;
    double c = 0.3125;
    double d = 0.0625;
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    //dst = img;
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_lw;
    uchar* p_dst;
    int tep = 0;
    int err = 0;
    for (int i = 0; i < height - 2; ++i)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_lw = img.ptr<uchar>(i + 1);
        p_dst = dst.ptr<uchar>(i);
        for (int j = 2; j < width - 2; ++j)
        {
            /*for (int m = 15; m >= 0; --m)
            {
                if (p_img[j] > 16 * m)
                {
                    p_dst[j] = 16 * m;
                    tep = 16 * m;
                    break;
                }
            }*/
            int te = findfit(p_img[j]);
            p_dst[j] = te;
            tep = te;

            err = p_img[j] - tep;
            p_dst[j + 1] += err * a;
            p_lw[j - 1] += err * b;
            p_lw[j] += err * c;
            p_lw[j + 1] += err * d;
        }
    }

    DWORD End_time = GetTickCount(); //计时结束
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("16灰阶_001", 0);
    cv::resizeWindow("16灰阶_001", 192 * 3, 216 * 3);
    imshow("16灰阶_001", dst);
    imwrite("E:\\16灰阶_001.jpg", dst);
}
//误差扩散法n灰阶
void floydsetinTool::floydsetin_16(Mat img , int m)
{
    if (m <= 0)
    {
        return;
    }
    double a = 0.4375;
    double b = 0.1875;
    double c = 0.3125;
    double d = 0.0625;
    DWORD Start_time = GetTickCount(); //计时开始
    int width = img.cols;//图片宽度
    int height = img.rows;//图片高度
    Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
    //dst = img;
    double minv = 0.0, maxv = 0.0;
    double* minp = &minv;
    double* maxp = &maxv;
    minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值
    int t = CV_8UC1;
    //用指针访问像素，速度更快
    uchar* p_img;
    uchar* p_lw;
    uchar* p_dst;
    int tep = 0;
    int err = 0;
    int step = 256 / m;
    for (int i = 0; i < height - 2; ++i)
    {
        p_img = img.ptr<uchar>(i);//获取每行首地址
        p_lw = img.ptr<uchar>(i + 1);
        p_dst = dst.ptr<uchar>(i);
        for (int j = 2; j < width - 2; ++j)
        {
            for (; m >= 0; --m)
            {
                if (p_img[j] > step * (m-1))
                {
                    p_dst[j] = step * (m)-1;
                    tep = step * (m)-1;
                    if (m == 0)
                    {
                        p_dst[j] = 0;
                        tep = 0;
                    }
                    break;
                }
            }

            err = p_img[j] - tep;
            p_dst[j + 1] += err * a;
            p_lw[j - 1] += err * b;
            p_lw[j] += err * c;
            p_lw[j + 1] += err * d;
        }
    }

    DWORD End_time = GetTickCount(); //计时结束
    //imwrite(MainWindow::imagePath.toLocal8Bit().toStdString(), dst);
    cout << "Time used：" << End_time - Start_time << " ms" << '\n';
    namedWindow("灰阶", 0);
    cv::resizeWindow("灰阶", 192 * 3, 216 * 3);
    imshow("灰阶", dst);

}


void floydsetinTool::halftone( Mat& src, Mat& dst, int cell_size) {
    // 将图像转换为灰度图
        Mat gray;
        cvtColor(src, gray, COLOR_BGR2GRAY);

        // 获取图像尺寸
        int h = gray.rows;
        int w = gray.cols;

        // 创建一个与原图像相同大小的空白图像
        dst = Mat::zeros(h, w, CV_8UC1);

        // 遍历图像，分割成网格
        for (int i = 0; i < h; i += cell_size) {
            for (int j = 0; j < w; j += cell_size) {
                // 确保ROI不会超出图像边界
                int grid_width = min(cell_size, w - j);
                int grid_height = min(cell_size, h - i);

                // 获取当前网格中的像素值
                Rect grid(j, i, grid_width, grid_height);
                Mat roi = gray(grid);
                Scalar avg_color = mean(roi);

                // 根据平均亮度决定网格中填充的点数
                int radius = static_cast<int>((avg_color[0] / 255.0) * (min(grid_width, grid_height) / 2));
                Point center(j + grid_width / 2, i + grid_height / 2);

                // 绘制圆形
                circle(dst, center, radius, Scalar(255), FILLED);
            }
        }
}


void floydsetinTool::floydSteinbergHalftoneUsingPointNum(Mat& src, Mat& dst, int cell_size) {
    // 将图像转换为灰度图
    Mat gray=src;
    //cvtColor(src, gray, COLOR_BGR2GRAY);

    // 创建一个输出图像矩阵
    dst = Mat::zeros(gray.size(), CV_8UC1);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 遍历图像的每个像素
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // 当前像素的原始值
            int old_pixel = gray.at<uchar>(y, x);
            // 计算在当前网格中的位置
            int grid_x = (x / cell_size) * cell_size + cell_size / 2;
            int grid_y = (y / cell_size) * cell_size + cell_size / 2;

            // 将像素值量化为 0 或 255
            int new_pixel = (old_pixel > 127) ? 255 : 0;
            // 设置量化后的像素值（只在网格中心进行半色调处理）
            if (x == grid_x && y == grid_y) {
                dst.at<uchar>(y, x) = new_pixel;
            } else {
                dst.at<uchar>(y, x) = 0; // 非网格中心点保持黑色
            }

            // 计算误差
            int quant_error = old_pixel - new_pixel;

            // 将误差扩散到邻近像素
            if (x + 1 < cols) gray.at<uchar>(y, x + 1) += quant_error * 7 / 16;
            if (y + 1 < rows) {
                if (x > 0) gray.at<uchar>(y + 1, x - 1) += quant_error * 3 / 16;
                gray.at<uchar>(y + 1, x) += quant_error * 5 / 16;
                if (x + 1 < cols) gray.at<uchar>(y + 1, x + 1) += quant_error * 1 / 16;
            }
        }
    }
}


void floydsetinTool::halftoneUsingCircles(Mat& src, Mat& dst, int cell_size) {
    Mat gray;

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 创建一个与原图像相同大小的空白图像
    dst = Mat::zeros(gray.size(), CV_8UC3);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 遍历图像的每个像素
    for (int y = 0; y < rows; y += cell_size) {
        for (int x = 0; x < cols; x += cell_size) {
            // 确保ROI不会超出图像边界
            int grid_width = min(cell_size, cols - x);
            int grid_height = min(cell_size, rows - y);

            // 获取当前网格中的像素区域
            Rect grid(x, y, grid_width, grid_height);
            Mat roi = gray(grid);

            // 计算当前网格的平均灰度值
            Scalar avg_color = mean(roi);

            // 根据平均灰度值决定圆的半径
            int radius = static_cast<int>((avg_color[0] / 255.0) * (min(grid_width, grid_height) / 2));

            // 绘制圆形
            Point center(x + grid_width / 2, y + grid_height / 2);
            circle(dst, center, radius, Scalar(255, 255, 255), FILLED); // 白色圆形

            // 计算量化误差
            int new_pixel_value = (radius > 0) ? 255 : 0; // 如果有圆，表示为白色
            int quant_error = gray.at<uchar>(y, x) - new_pixel_value;

            // 将误差扩散到邻近像素
            if (x + 1 < cols) gray.at<uchar>(y, x + 1) += quant_error * 7 / 16;
            if (y + 1 < rows) {
                if (x > 0) gray.at<uchar>(y + 1, x - 1) += quant_error * 3 / 16;
                gray.at<uchar>(y + 1, x) += quant_error * 5 / 16;
                if (x + 1 < cols) gray.at<uchar>(y + 1, x + 1) += quant_error * 1 / 16;
            }
        }
    }
}



void floydsetinTool::halftoneUsingRect(Mat& src, Mat& dst, int cell_size) {
    Mat gray;

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 创建一个与原图像相同大小的空白图像
    dst = Mat::zeros(gray.size(), CV_8UC3);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 遍历图像的每个像素
    for (int y = 0; y < rows; y += cell_size) {
        for (int x = 0; x < cols; x += cell_size) {
            // 确保ROI不会超出图像边界
            int grid_width = min(cell_size, cols - x);
            int grid_height = min(cell_size, rows - y);

            // 获取当前网格中的像素区域
            Rect grid(x, y, grid_width, grid_height);
            Mat roi = gray(grid);

            // 计算当前网格的平均灰度值
            Scalar avg_color = mean(roi);

            // 根据平均灰度值决定正方形的边长
            int square_size = static_cast<int>((avg_color[0] / 255.0) * min(grid_width, grid_height));

            // 绘制正方形
            Point top_left(x + (grid_width - square_size) / 2, y + (grid_height - square_size) / 2);
            Point bottom_right(top_left.x + square_size, top_left.y + square_size);
            rectangle(dst, top_left, bottom_right, Scalar(255, 255, 255), FILLED); // 白色正方形

            // 计算量化误差
            int new_pixel_value = (square_size > 0) ? 255 : 0; // 如果有正方形，表示为白色
            int quant_error = gray.at<uchar>(y, x) - new_pixel_value;

            // 将误差扩散到邻近像素
            if (x + 1 < cols) gray.at<uchar>(y, x + 1) += quant_error * 7 / 16;
            if (y + 1 < rows) {
                if (x > 0) gray.at<uchar>(y + 1, x - 1) += quant_error * 3 / 16;
                gray.at<uchar>(y + 1, x) += quant_error * 5 / 16;
                if (x + 1 < cols) gray.at<uchar>(y + 1, x + 1) += quant_error * 1 / 16;
            }
        }
    }
}



void floydsetinTool::halftoneUsingRect_doubelSizeGrid(Mat& src, Mat& dst, float cell_size, int num_levels) {
    Mat gray;

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 创建一个与原图像相同大小的空白图像
    dst = Mat::zeros(gray.size(), CV_8UC3);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 定义灰度层级划分
    vector<int> rect_sizes(num_levels);
    for (int i = 0; i < num_levels; i++) {
        rect_sizes[i] = static_cast<int>((min(cell_size / 2, cell_size / 2) / num_levels) * (i + 1));
    }

    // 定义误差扩散矩阵 (Jarvis, Judice, and Ninke Dithering)
    vector<vector<double>> diffusion_matrix = {
        {0, 0, 0, 7.0 / 48, 5.0 / 48},
        {3.0 / 48, 5.0 / 48, 7.0 / 48, 5.0 / 48, 3.0 / 48},
        {1.0 / 48, 3.0 / 48, 5.0 / 48, 3.0 / 48, 1.0 / 48}
    };

    // 遍历图像的每个像素
    for (float y = 0; y < rows; y += cell_size) {
        for (float x = 0; x < cols; x += cell_size) {
            // 计算当前网格的实际宽度和高度
            int grid_width = min(static_cast<int>(cell_size), cols - static_cast<int>(x));
            int grid_height = min(static_cast<int>(cell_size), rows - static_cast<int>(y));

            // 获取当前网格中的像素区域
            Rect grid(static_cast<int>(x), static_cast<int>(y), grid_width, grid_height);
            Mat roi = gray(grid);

            // 计算当前网格的平均灰度值
            Scalar avg_color = mean(roi);

            // 根据平均灰度值决定正方形的边长
            int size_index = static_cast<int>((avg_color[0] / 255.0) * (num_levels - 1));
            int square_size = rect_sizes[size_index];

            // 确保正方形的大小不超过网格大小
            square_size = min(square_size, min(grid_width, grid_height));

            // 绘制正方形
            Point top_left(static_cast<int>(x) + (grid_width - square_size) / 2,
                           static_cast<int>(y) + (grid_height - square_size) / 2);
            Point bottom_right(top_left.x + square_size, top_left.y + square_size);
            rectangle(dst, top_left, bottom_right, Scalar(255, 255, 255), FILLED); // 白色正方形

            // 计算量化误差
            int new_pixel_value = (square_size > 0) ? 255 : 0; // 如果有正方形，表示为白色
            int quant_error = static_cast<int>(avg_color[0]) - new_pixel_value;

            // 将误差扩散到邻近像素
            for (int dy = 0; dy < diffusion_matrix.size(); ++dy) {
                for (int dx = -2; dx <= 2; ++dx) {
                    int new_y = static_cast<int>(y) + dy;
                    int new_x = static_cast<int>(x) + dx;
                    if (new_x >= 0 && new_x < cols && new_y < rows) {
                        gray.at<uchar>(new_y, new_x) = saturate_cast<uchar>(gray.at<uchar>(new_y, new_x) + quant_error * diffusion_matrix[dy][dx + 2]);
                    }
                }
            }
        }
    }
}






void floydsetinTool::halftoneUsingCircles_doubelSizeGrid(Mat& src, Mat& dst, float cell_size, int num_levels) {
    Mat gray;

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 创建一个与原图像相同大小的空白图像
    dst = Mat::zeros(gray.size(), CV_8UC3);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 定义灰度层级划分
    vector<int> radius_levels(num_levels);
    for (int i = 0; i < num_levels; i++) {
        radius_levels[i] = static_cast<int>((min(cell_size / 2, cell_size / 2) / num_levels) * (i + 1));
    }

    // 遍历图像，分割为网格并绘制圆形
    for (float y = 0; y < rows; y += cell_size) {
        for (float x = 0; x < cols; x += cell_size) {
            // 计算当前网格的实际宽度和高度
            int grid_width = min(static_cast<int>(cell_size), cols - static_cast<int>(x));
            int grid_height = min(static_cast<int>(cell_size), rows - static_cast<int>(y));

            // 获取当前网格中的像素区域
            Rect grid(static_cast<int>(x), static_cast<int>(y), grid_width, grid_height);
            Mat roi = gray(grid);

            // 计算当前网格的平均灰度值
            Scalar avg_color = mean(roi);

            // 根据平均灰度值决定圆的半径（使用灰度层次）
            int radius_index = static_cast<int>((avg_color[0] / 255.0) * (num_levels - 1));
            int radius = radius_levels[radius_index];

            // 确保圆的半径不超过网格的一半，避免圆形叠加
            radius = min(radius, min(grid_width, grid_height) / 2);

            // 绘制圆形，确保圆形在网格内居中且不叠加
            if (radius > 0) {
                Point center(static_cast<int>(x) + grid_width / 2, static_cast<int>(y) + grid_height / 2);
                circle(dst, center, radius, Scalar(255, 255, 255), FILLED); // 白色圆形
            }
        }
    }
}


void floydsetinTool::halftoneWithCirclesDoubelSizeGridTest(Mat& src, Mat& dst, float cell_size, int density_factor) {
    Mat gray;

        // 检查图像的通道数，如果是彩色图像则转换为灰度图
        if (src.channels() == 3) {
            cvtColor(src, gray, COLOR_BGR2GRAY);
        } else {
            gray = src;
        }

        // 创建一个与原图像相同大小的空白图像
        dst = Mat::zeros(gray.size(), CV_8UC3);

        // 获取图像尺寸
        int rows = gray.rows;
        int cols = gray.cols;

        // 定义Jarvis, Judice, and Ninke扩散矩阵
        vector<vector<double>> diffusion_matrix = {
            {0, 0, 0, 7.0/48, 5.0/48},
            {3.0/48, 5.0/48, 7.0/48, 5.0/48, 3.0/48},
            {1.0/48, 3.0/48, 5.0/48, 3.0/48, 1.0/48}
        };

        // 遍历图像，应用误差扩散并绘制圆形
        for (int y = 0; y < rows - 2; ++y) {
            for (int x = 2; x < cols - 2; ++x) {
                // 当前像素的量化值
                int old_pixel = gray.at<uchar>(y, x);
                int new_pixel = round(old_pixel / 255.0) * 255;  // 简单的二值化
                gray.at<uchar>(y, x) = new_pixel;

                // 计算误差
                int quant_error = old_pixel - new_pixel;

                // 将误差扩散到相邻像素
                for (int dy = 0; dy < diffusion_matrix.size(); ++dy) {
                    for (int dx = -2; dx <= 2; ++dx) {
                        int new_y = y + dy;
                        int new_x = x + dx;
                        if (new_x >= 0 && new_x < cols && new_y < rows) {
                            gray.at<uchar>(new_y, new_x) = saturate_cast<uchar>(gray.at<uchar>(new_y, new_x) + quant_error * diffusion_matrix[dy][dx + 2]);
                        }
                    }
                }
            }
        }

        // 绘制圆形
        for (float y = 0; y < rows; y += cell_size) {
            for (float x = 0; x < cols; x += cell_size) {
                // 计算当前网格的实际宽度和高度
                int grid_width = min(static_cast<int>(cell_size), cols - static_cast<int>(x));
                int grid_height = min(static_cast<int>(cell_size), rows - static_cast<int>(y));

                // 获取当前网格中的像素区域
                Rect grid(static_cast<int>(x), static_cast<int>(y), grid_width, grid_height);
                Mat roi = gray(grid);

                // 计算当前网格的平均灰度值
                Scalar avg_color = mean(roi);

                // 根据平均灰度值决定圆的半径
                int radius = static_cast<int>((avg_color[0] / 255.0) * (min(grid_width, grid_height) / density_factor));

                // 绘制圆形，确保圆形在网格内居中
                Point center(static_cast<int>(x) + grid_width / 2,
                             static_cast<int>(y) + grid_height / 2);
                if (radius > 0) {
                    circle(dst, center, radius, Scalar(255, 255, 255), FILLED); // 白色圆形
                }
            }
        }
}


void floydsetinTool::halftoneUsingline_doubelSizeGrid(Mat& src, Mat& dst,vector<LineSegment>& lines, float cell_size, bool horizontal_lines) {
    Mat gray;

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 创建一个与原图像相同大小的空白图像
    dst = Mat::zeros(gray.size(), CV_8UC3);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 遍历图像，分割为网格
    for (float y = 0; y < rows; y += cell_size) {
        for (float x = 0; x < cols; x += cell_size) {
            // 计算当前网格的实际宽度和高度
            int grid_width = min(static_cast<int>(cell_size), cols - static_cast<int>(x));
            int grid_height = min(static_cast<int>(cell_size), rows - static_cast<int>(y));

            // 获取当前网格中的像素区域
            Rect grid(static_cast<int>(x), static_cast<int>(y), grid_width, grid_height);
            Mat roi = gray(grid);

            // 计算当前网格的平均灰度值
            Scalar avg_color = mean(roi);

            // 根据平均灰度值确定线段的数量或密度
            int num_lines = static_cast<int>((avg_color[0] / 255.0) * grid_height);

            // 绘制线段
            for (int i = 0; i < num_lines; ++i) {
                if (horizontal_lines) {
                    // 绘制水平线
                    int line_y = static_cast<int>(y) + i * (grid_height / num_lines);
                    line(dst, Point(static_cast<int>(x), line_y),
                         Point(static_cast<int>(x) + grid_width, line_y), Scalar(255, 255, 255));
                    lines.push_back({Point(static_cast<int>(x), line_y), Point(static_cast<int>(x) + grid_width, line_y)});

                } else {
                    // 绘制垂直线
                    int line_x = static_cast<int>(x) + i * (grid_width / num_lines);
                    line(dst, Point(line_x, static_cast<int>(y)),
                         Point(line_x, static_cast<int>(y) + grid_height), Scalar(255, 255, 255));
                    lines.push_back({Point(line_x, static_cast<int>(y)), Point(line_x, static_cast<int>(y) + grid_height)});

                }
            }

            // 计算量化误差
            int new_pixel_value = (num_lines > 0) ? 255 : 0; // 如果有线段，表示为白色
            int quant_error = avg_color[0] - new_pixel_value;

            // 扩散误差到相邻网格
            if (static_cast<int>(x + cell_size) < cols) gray.at<uchar>(static_cast<int>(y), static_cast<int>(x + cell_size)) += quant_error * 7 / 16;
            if (static_cast<int>(y + cell_size) < rows) {
                if (static_cast<int>(x) > 0) gray.at<uchar>(static_cast<int>(y + cell_size), static_cast<int>(x - cell_size)) += quant_error * 3 / 16;
                gray.at<uchar>(static_cast<int>(y + cell_size), static_cast<int>(x)) += quant_error * 5 / 16;
                if (static_cast<int>(x + cell_size) < cols) gray.at<uchar>(static_cast<int>(y + cell_size), static_cast<int>(x + cell_size)) += quant_error * 1 / 16;
            }
        }
    }
}



void floydsetinTool::halftoneUsingline_doubelSizeGrid_savePat(Mat& src, vector<LineSegment>& lines, float cell_size, bool horizontal_lines) {
    Mat gray;

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 遍历图像，分割为网格
    for (float y = 0; y < rows; y += cell_size) {
        for (float x = 0; x < cols; x += cell_size) {
            // 计算当前网格的实际宽度和高度
            int grid_width = min(static_cast<int>(cell_size), cols - static_cast<int>(x));
            int grid_height = min(static_cast<int>(cell_size), rows - static_cast<int>(y));

            // 获取当前网格中的像素区域
            Rect grid(static_cast<int>(x), static_cast<int>(y), grid_width, grid_height);
            Mat roi = gray(grid);

            // 计算当前网格的平均灰度值
            Scalar avg_color = mean(roi);

            // 根据平均灰度值确定线段的数量或密度
            int num_lines = static_cast<int>((avg_color[0] / 255.0) * grid_height);

            // 保存线段信息
            for (int i = 0; i < num_lines; ++i) {
                if (horizontal_lines) {
                    // 保存水平线段
                    int line_y = static_cast<int>(y) + i * (grid_height / num_lines);
                    lines.push_back({Point(static_cast<int>(x), line_y), Point(static_cast<int>(x) + grid_width, line_y)});
                } else {
                    // 保存垂直线段
                    int line_x = static_cast<int>(x) + i * (grid_width / num_lines);
                    lines.push_back({Point(line_x, static_cast<int>(y)), Point(line_x, static_cast<int>(y) + grid_height)});
                }
            }
        }
    }
}



void floydsetinTool::halftoneUsingLineWithErrorDiffusion(Mat& src, Mat& dst,vector<LineSegment>& lines, float cell_size, bool horizontal_lines) {
    Mat gray;

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 创建一个与原图像相同大小的空白图像
    dst = Mat::zeros(gray.size(), CV_8UC3);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 遍历图像，分割为网格
    for (float y = 0; y < rows; y += cell_size) {
        for (float x = 0; x < cols; x += cell_size) {
            // 计算当前网格的实际宽度和高度
            int grid_width = min(static_cast<int>(cell_size), cols - static_cast<int>(x));
            int grid_height = min(static_cast<int>(cell_size), rows - static_cast<int>(y));

            // 获取当前网格中的像素区域
            Rect grid(static_cast<int>(x), static_cast<int>(y), grid_width, grid_height);
            Mat roi = gray(grid);

            // 计算当前网格的平均灰度值
            Scalar avg_color = mean(roi);

            // 根据平均灰度值确定线段的数量或密度
            int num_lines = static_cast<int>((avg_color[0] / 255.0) * grid_height);


            // 保存线段信息并绘制线段
            for (int i = 0; i < num_lines; ++i) {
                if (horizontal_lines) {
                    // 保存水平线段
                    int line_y = static_cast<int>(y) + i * (grid_height / num_lines);
                    lines.push_back({Point(static_cast<int>(x), line_y), Point(static_cast<int>(x) + grid_width, line_y)});
                    line(dst, Point(static_cast<int>(x), line_y),
                         Point(static_cast<int>(x) + grid_width, line_y), Scalar(255, 255, 255));
                } else {
                    // 保存垂直线段
                    int line_x = static_cast<int>(x) + i * (grid_width / num_lines);
                    lines.push_back({Point(line_x, static_cast<int>(y)), Point(line_x, static_cast<int>(y) + grid_height)});
                    line(dst, Point(line_x, static_cast<int>(y)),
                         Point(line_x, static_cast<int>(y) + grid_height), Scalar(255, 255, 255));
                }
            }

            // 计算量化误差并扩散到相邻网格
            int new_pixel_value = (num_lines > 0) ? 255 : 0;  // 假设每条线段代表的灰度值为255
            int quant_error = avg_color[0] - new_pixel_value;

            if (x + cell_size < cols) gray.at<uchar>(static_cast<int>(y), static_cast<int>(x + cell_size)) += quant_error * 7 / 16;
            if (y + cell_size < rows) {
                if (x > 0) gray.at<uchar>(static_cast<int>(y + cell_size), static_cast<int>(x - cell_size)) += quant_error * 3 / 16;
                gray.at<uchar>(static_cast<int>(y + cell_size), static_cast<int>(x)) += quant_error * 5 / 16;
                if (x + cell_size < cols) gray.at<uchar>(static_cast<int>(y + cell_size), static_cast<int>(x + cell_size)) += quant_error * 1 / 16;
            }
        }
    }
}



void floydsetinTool::halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(Mat& src, Mat& dst, float cell_size, bool horizontal_lines) {
    Mat gray;

       // 检查图像的通道数，如果是彩色图像则转换为灰度图
       if (src.channels() == 3) {
           cvtColor(src, gray, COLOR_BGR2GRAY);
       } else {
           gray = src;
       }

       // 创建一个与原图像相同大小的空白图像
       dst = Mat::zeros(gray.size(), CV_8UC3);

       // 获取图像尺寸
       int rows = gray.rows;
       int cols = gray.cols;

       // 定义误差扩散的权重 (Jarvis, Judice, and Ninke Dithering)
       vector<vector<double>> diffusion_matrix = {
           {0, 0, 0, 7.0/48, 5.0/48},
           {3.0/48, 5.0/48, 7.0/48, 5.0/48, 3.0/48},
           {1.0/48, 3.0/48, 5.0/48, 3.0/48, 1.0/48}
       };

       // 遍历图像，应用误差扩散
       for (int y = 0; y < rows - 2; ++y) {
           for (int x = 2; x < cols - 2; ++x) {
               // 当前像素的量化值
               int old_pixel = gray.at<uchar>(y, x);
               int new_pixel = findfitInt(old_pixel, 16);  // 64级量化
               gray.at<uchar>(y, x) = new_pixel;

               // 计算误差
               int quant_error = old_pixel - new_pixel;

               // 将误差扩散到相邻像素
               for (int dy = 0; dy < diffusion_matrix.size(); ++dy) {
                   for (int dx = -2; dx <= 2; ++dx) {
                       int new_y = y + dy;
                       int new_x = x + dx;
                       if (new_x >= 0 && new_x < cols && new_y < rows) {
                           gray.at<uchar>(new_y, new_x) = saturate_cast<uchar>(gray.at<uchar>(new_y, new_x) + quant_error * diffusion_matrix[dy][dx + 2]);
                       }
                   }
               }
           }
       }

       // 根据量化后的灰度图像绘制线段
       for (float y = 0; y < rows; y += cell_size) {
           for (float x = 0; x < cols; x += cell_size) {
               // 计算当前网格的实际宽度和高度
               int grid_width = min(static_cast<int>(cell_size), cols - static_cast<int>(x));
               int grid_height = min(static_cast<int>(cell_size), rows - static_cast<int>(y));

               // 获取当前网格中的像素区域
               Rect grid(static_cast<int>(x), static_cast<int>(y), grid_width, grid_height);
               Mat roi = gray(grid);

               // 计算当前网格的平均灰度值
               Scalar avg_color = mean(roi);

               // 根据平均灰度值确定线段的数量或密度
               int num_lines = static_cast<int>((avg_color[0] / 255.0) * grid_height);

               // 绘制线段，考虑灰度调整线宽
               int line_thickness = 1;  // 根据灰度调整线宽
               for (int i = 0; i < num_lines; ++i) {
                   if (horizontal_lines) {
                       // 绘制水平线
                       int line_y = static_cast<int>(y) + i * (grid_height / num_lines);
                       lines.push_back({Point(static_cast<int>(x), line_y), Point(static_cast<int>(x) + grid_width, line_y)});
                       line(dst, Point(static_cast<int>(x), line_y),
                            Point(static_cast<int>(x) + grid_width, line_y), Scalar(255, 255, 255), line_thickness);
                   } else {
                       // 绘制垂直线
                       int line_x = static_cast<int>(x) + i * (grid_width / num_lines);
                       lines.push_back({Point(line_x, static_cast<int>(y)), Point(line_x, static_cast<int>(y) + grid_height)});
                       line(dst, Point(line_x, static_cast<int>(y)),
                            Point(line_x, static_cast<int>(y) + grid_height), Scalar(255, 255, 255), line_thickness);
                   }
               }
           }
       }
}



void floydsetinTool::saveAsPlt(const string& filename, const vector<LineSegment>& lines) {
    ofstream plt_file(filename);
    if (!plt_file.is_open()) {
        cerr << "无法打开文件" << filename << endl;
        return;
    }

    // 写入PLT格式头部信息 (简化版本)
    plt_file << "IN;\n";  // Initialize
    plt_file << "SP1;\n";  // Select pen 1

    // 写入线段数据
    for (const auto& line : lines) {
        plt_file << "PU" << line.start.x << "," << line.start.y << ";\n";  // Move to start point
        plt_file << "PD" << line.end.x << "," << line.end.y << ";\n";      // Draw to end point
    }

    plt_file << "PU0,0;\n";  // Pen up and move to origin
    plt_file << "SP0;\n";  // End plotting
    plt_file.close();
}

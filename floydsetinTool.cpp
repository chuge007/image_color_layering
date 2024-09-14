
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mainwindow.h>
#include <floydsetinTool.h>
#include <algorithm>
#include <Qdebug.h>
#include <Qvector>
using namespace cv;
using namespace std;





//*****************************************************************************************************************************************************************
void floydsetinTool::scaleLineNum(int &lineNum,double scale){

    lineNum*=scale;


}
bool floydsetinTool::solveLinear3x3(const QVector<QVector<int>>& coefficients) {
    // 检查输入矩阵是否为 3x4
    if (coefficients.size() != 3) {
        qDebug() << "Invalid matrix size. Expected 3 rows.";
        return false;
    }
    for (const auto& row : coefficients) {
        if (row.size() != 4) {
            qDebug() << "Invalid matrix size. Each row should have 4 columns.";
            return false;
        }
    }

    // 创建 OpenCV 的 A 矩阵和 b 向量
    cv::Mat A(3, 3, CV_64F);
    cv::Mat bMat(3, 1, CV_64F);

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            A.at<double>(i, j) = static_cast<double>(coefficients[i][j]);
        }
        bMat.at<double>(i, 0) = static_cast<double>(coefficients[i][3]);
    }

    // 打印系数矩阵和常数向量（可选，用于调试）
    /*
    std::cout << "Matrix A:\n" << A << std::endl;
    std::cout << "Vector b:\n" << bMat << std::endl;
    */

    // 使用 OpenCV 解方程组
    cv::Mat x;
    bool solved = cv::solve(A, bMat, x, cv::DECOMP_LU); // 你也可以使用其他分解方法，如 DECOMP_SVD

    if (solved) {
        // 提取解
        ColorCorrectionA = x.at<double>(0, 0);
        ColorCorrectionB = x.at<double>(1, 0);
        ColorCorrectionC = x.at<double>(2, 0);

        qDebug() << "ColorCorrectionA:" << ColorCorrectionA;
        qDebug() << "ColorCorrectionB:" << ColorCorrectionB;
        qDebug() << "ColorCorrectionC:" << ColorCorrectionC;
        return true;
    } else {
        qDebug() << "The system has no unique solution.";
        return false;
    }
}
//*****************************************************************************************************************************************************************


//// 生成点的分布顺序，确保尽可能有间隔
std::vector<std::pair<int, int>> floydsetinTool::generateDistributedOrder(int gridSize) {
    std::vector<std::pair<int, int>> order;

    // 优先填充“棋盘”位置，即坐标为(奇,奇)或(偶,偶)的点
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
                order.emplace_back(i, j);
            }
        }
    }

    // 然后填充其余的点，确保尽量均匀分布
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if ((i % 2 != j % 2)) {
                order.emplace_back(i, j);
            }
        }
    }

    return order;
}

std::vector<std::vector<int>> floydsetinTool::generatePatternMatrix(int gridSize, int numPoints) {
    numPoints = clamp(numPoints, 0, gridSize*gridSize);
    std::vector<std::vector<int>> pattern(gridSize, std::vector<int>(gridSize, 0));

    // 获取分布顺序
    std::vector<std::pair<int, int>> fillOrder = generateDistributedOrder(gridSize);

    // 根据分布顺序填充指定数量的点
    for (int i = 0; i < numPoints; ++i) {
        int x = fillOrder[i].first;
        int y = fillOrder[i].second;
        pattern[x][y] = 1;
    }

    return pattern;
}

////像素网格划分，模式法,误差扩散，小网格位置用矩阵分散
void floydsetinTool::halftoneUsingline_doubelSizeGridWithErrorDiffusionAndMatrixTest(Mat& src, Mat& dst, double &line_distance, double imageHeight,  int grayLevel, bool horizontal_lines,int layer,double dataDenstyScaling,int blackRange) {
    Mat gray;
    float resize = 1;
    int gridSize = grayLevel;
    int totalLines = (gridSize * gridSize)+1;  // 5*5 + 1 = 26 个灰度等级
    float maxPixelValue=100.0f;
    int BlackRange= gridSize * gridSize-blackRange;
    double pixelHeight=line_distance*grayLevel;
    double ColorCorrection;
    floydsetinTooLlineDistance=line_distance;
    floydsetinTooLgrayLevel=grayLevel;
    floysetinTooLimageHeight=imageHeight;

    if(layer==0){
        linesCR={};
        linesSegments={};
        ColorCorrection=ColorCorrectionA;}
    else if (layer==1) {
        linesMG={};
        linesSegments={};
        ColorCorrection=ColorCorrectionB;
    } else if (layer==2) {
        linesYB={};
        linesSegments={};
        ColorCorrection=ColorCorrectionC;
    }
    else if (layer==3) {
        linesK={};
        linesSegments={};
        ColorCorrection=1;
    }
    vector<vector<LineSegment>>lineVector={linesCR,linesCR,linesYB,linesK};
    vector<LineSegment>  *lines=&lineVector[layer];

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 创建一个与原图像相同大小的空白图像
    dst = Mat::zeros(gray.size(), CV_8UC1);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 计算像素的实际物理尺寸（毫米）
    double pixel_height_mm = pixelHeight;
    double pixel_width_mm = pixelHeight;  // 假设图像宽度与高度的比例相同

    // 初始化误差扩散矩阵
    std::vector<std::vector<double>> error_diffusion(rows, std::vector<double>(cols, 0.0));

    // 根据量化后的灰度图像绘制线段
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {

            // 获取当前像素的灰度值并添加误差扩散的值
            double pixel_value = static_cast<float>(gray.at<uchar>(y, x)) + error_diffusion[y][x];

            // 限制 pixel_value 在 0 到 255 之间
            pixel_value = min(max(pixel_value, 0.0), maxPixelValue);

            float fractionalPart = (pixel_value / (maxPixelValue / totalLines)) - std::floor(pixel_value / (maxPixelValue / totalLines));

            // 计算灰度等级索引，选择对应的矩阵
            int gray_index = static_cast<int>(pixel_value / (maxPixelValue/totalLines)) + std::ceil(fractionalPart);

            //gray_index*=ColorCorrection;
            //scaleLineNum(gray_index,1.3);
            int drawLine=(gridSize * gridSize)-gray_index;
            // 生成对应的矩阵
            auto pattern = generatePatternMatrix(gridSize, drawLine);

            // 计算当前像素的量化误差
            double quant_error = pixel_value - ((maxPixelValue / totalLines) *
                                                (
                                                    static_cast<int>(pixel_value / (maxPixelValue / totalLines)) +
                                                    std::ceil(fractionalPart)
                                                    ));
            // 误差扩散：将误差扩散到周围像素
            //            if (x + 1 < cols) error_diffusion[y][x + 1] += quant_error * 7 / 16.0;
            //            if (y + 1 < rows) {
            //                if (x > 0) error_diffusion[y + 1][x - 1] += quant_error * 3 / 16.0;
            //                error_diffusion[y + 1][x] += quant_error * 5 / 16.0;
            //                if (x + 1 < cols) error_diffusion[y + 1][x + 1] += quant_error * 1 / 16.0;
            //            }

            // 误差扩散：将误差扩散到周围像素 (Stucki)
            if (x + 1 < cols) error_diffusion[y][x + 1] += quant_error * 8 / 42.0;
            if (x + 2 < cols) error_diffusion[y][x + 2] += quant_error * 4 / 42.0;
            if (y + 1 < rows) {
                if (x - 2 >= 0) error_diffusion[y + 1][x - 2] += quant_error * 2 / 42.0;
                if (x - 1 >= 0) error_diffusion[y + 1][x - 1] += quant_error * 4 / 42.0;
                error_diffusion[y + 1][x] += quant_error * 8 / 42.0;
                if (x + 1 < cols) error_diffusion[y + 1][x + 1] += quant_error * 4 / 42.0;
                if (x + 2 < cols) error_diffusion[y + 1][x + 2] += quant_error * 2 / 42.0;
            }
            if (y + 2 < rows) {
                if (x - 1 >= 0) error_diffusion[y + 2][x - 1] += quant_error * 2 / 42.0;
                error_diffusion[y + 2][x] += quant_error * 4 / 42.0;
                if (x + 1 < cols) error_diffusion[y + 2][x + 1] += quant_error * 2 / 42.0;
            }

            // 为了避免过多的误差累积，限制扩散误差的范围
            error_diffusion[y][x] = (error_diffusion[y][x] < -maxPixelValue) ? -maxPixelValue :
                                                                               ((error_diffusion[y][x] > maxPixelValue) ? maxPixelValue : error_diffusion[y][x]);
            // 使用生成的矩阵绘制线段
            for (int i = 0; i < gridSize; ++i) {
                for (int j = 0; j < gridSize; ++j) {
                    if (pattern[i][j] == 1) {

                        if(horizontal_lines){
                            // 计算线段的起始和终止位置（物理坐标）
                            double start_x_mm = x * pixel_width_mm + j * (pixel_width_mm / gridSize);
                            double start_y_mm = y * pixel_height_mm + i * (pixel_height_mm / gridSize);
                            double end_x_mm = start_x_mm + (horizontal_lines ? (pixel_width_mm / gridSize) : 0);
                            double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (pixel_height_mm / gridSize));
                            // 绘制线段
                            linesSegments.push_back({Point2f(start_x_mm * resize, start_y_mm * resize),
                                                     Point2f(end_x_mm * resize, end_y_mm * resize)});
                        }
                        else {

                            double start_x_mm = x * pixel_width_mm + i * (pixel_width_mm / gridSize);
                            double start_y_mm = y * pixel_height_mm + j * (pixel_height_mm / gridSize);
                            double end_x_mm = start_x_mm + (horizontal_lines ? (pixel_width_mm / gridSize) : 0);
                            double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (pixel_height_mm / gridSize));
                            // 绘制线段
                            linesSegments.push_back({Point2f(start_x_mm * resize, start_y_mm * resize),
                                                     Point2f(end_x_mm * resize, end_y_mm * resize)});
                        }

                    }
                }
            }
        }
    }
    mergeLineSegmentsT(linesSegments,lines,horizontal_lines);
    saveAsPlt(pltPathPlt.toStdString(), lines);
    saveAsDxf(pltPathDxf.toStdString(), lines,horizontal_lines);
}


//像素网格划分，模式法,误差扩散
void floydsetinTool::halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(Mat& src, Mat& dst, double &line_distance, double imageHeight,  int grayLevel, bool horizontal_lines,int layer,double dataDenstyScaling,int blackRange) {
    Mat gray;
    float resize = 40;
    int totalLines = grayLevel * grayLevel + 1;  // 量化后的灰度等级
    float maxPixelValue=100;
    int BlackRange= grayLevel * grayLevel-blackRange;
    double pixelHeight=line_distance*grayLevel;
    double ColorCorrection;



    if(layer==0){
        linesCR={};
        linesSegments={};
        ColorCorrection=ColorCorrectionA;}
    else if (layer==1) {
        linesMG={};
        linesSegments={};
        ColorCorrection=ColorCorrectionB;
    } else if (layer==2) {
        linesYB={};
        linesSegments={};
        ColorCorrection=ColorCorrectionC;
    }
    vector<vector<LineSegment>>lineVector={linesCR,linesCR,linesYB,linesK};
    vector<LineSegment>  *lines=&lineVector[layer];

    // 检查图像的通道数，如果是彩色图像则转换为灰度图
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // 创建一个与原图像相同大小的空白图像
    dst = Mat::zeros(gray.size(), CV_8UC1);

    // 获取图像尺寸
    int rows = gray.rows;
    int cols = gray.cols;

    // 计算像素的实际物理尺寸（毫米）
    double pixel_height_mm = pixelHeight;
    double pixel_width_mm = pixelHeight;  // 假设图像宽度与高度的比例相同



    // 初始化误差扩散矩阵
    std::vector<std::vector<double>> error_diffusion(rows, std::vector<double>(cols, 0.0));

    // 根据量化后的灰度图像绘制线段
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {

            // 获取当前像素的灰度值并添加误差扩散的值
            double pixel_value = static_cast<float>(gray.at<uchar>(y, x)) + error_diffusion[y][x];

            // 限制 pixel_value 在 0 到 255 之间
            pixel_value = min(max(pixel_value, 0.0), maxPixelValue);

            float fractionalPart = static_cast<int>(pixel_value / (maxPixelValue/totalLines)) + std::ceil(fractionalPart);

            // 计算灰度等级索引，线条数量与灰度值成反比
            int gray_index = static_cast<int>(pixel_value / (maxPixelValue/totalLines)) + std::ceil(fractionalPart);

            int num_lines_to_draw=(grayLevel * grayLevel)-gray_index;
            // 计算当前像素的量化误差
            double quant_error =  pixel_value - ((maxPixelValue / totalLines) *
                                                 (
                                                     static_cast<int>(pixel_value / (maxPixelValue / totalLines)) +
                                                     std::ceil(fractionalPart)
                                                     ));
            // 误差扩散：将误差扩散到周围像素
//            if (x + 1 < cols) error_diffusion[y][x + 1] += quant_error * 7 / 16.0;
//            if (y + 1 < rows) {
//                if (x > 0) error_diffusion[y + 1][x - 1] += quant_error * 3 / 16.0;
//                error_diffusion[y + 1][x] += quant_error * 5 / 16.0;
//                if (x + 1 < cols) error_diffusion[y + 1][x + 1] += quant_error * 1 / 16.0;
//            }
            if (x + 1 < cols) error_diffusion[y][x + 1] += quant_error * 8 / 42.0;
            if (x + 2 < cols) error_diffusion[y][x + 2] += quant_error * 4 / 42.0;
            if (y + 1 < rows) {
                if (x - 2 >= 0) error_diffusion[y + 1][x - 2] += quant_error * 2 / 42.0;
                if (x - 1 >= 0) error_diffusion[y + 1][x - 1] += quant_error * 4 / 42.0;
                error_diffusion[y + 1][x] += quant_error * 8 / 42.0;
                if (x + 1 < cols) error_diffusion[y + 1][x + 1] += quant_error * 4 / 42.0;
                if (x + 2 < cols) error_diffusion[y + 1][x + 2] += quant_error * 2 / 42.0;
            }
            if (y + 2 < rows) {
                if (x - 1 >= 0) error_diffusion[y + 2][x - 1] += quant_error * 2 / 42.0;
                error_diffusion[y + 2][x] += quant_error * 4 / 42.0;
                if (x + 1 < cols) error_diffusion[y + 2][x + 1] += quant_error * 2 / 42.0;
            }
            // 将每个像素划分为更小的网格，并绘制线段
            int grid_size = grayLevel;  // 根据 grayLevel 来划分网格
            for (int i = 0; i < num_lines_to_draw; ++i) {
                if(horizontal_lines){
                    int grid_row = i / grid_size;
                    int grid_col = i % grid_size;

                    // 计算线段的起始和终止位置（物理坐标）
                    double start_x_mm = x * pixel_width_mm + grid_col * (pixel_width_mm / grid_size);
                    double start_y_mm = y * pixel_height_mm + grid_row * (pixel_height_mm / grid_size);
                    double end_x_mm = start_x_mm + (horizontal_lines ? (pixel_width_mm / grid_size) : 0);
                    double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (pixel_height_mm / grid_size));

                    // 绘制线段
                    linesSegments.push_back({Point2f(start_x_mm * resize, start_y_mm * resize),
                                             Point2f(end_x_mm * resize, end_y_mm * resize)});
                }else
                {

                    int grid_col = i / grid_size;
                    int grid_row = i % grid_size;

                    // 计算线段的起始和终止位置（物理坐标）
                    double start_x_mm = x * pixel_width_mm + grid_col * (pixel_width_mm / grid_size);
                    double start_y_mm = y * pixel_height_mm + grid_row * (pixel_height_mm / grid_size);
                    double end_x_mm = start_x_mm + (horizontal_lines ? (pixel_width_mm / grid_size) : 0);
                    double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (pixel_height_mm / grid_size));

                    // 绘制线段
                    linesSegments.push_back({Point2f(start_x_mm * resize, start_y_mm * resize),
                                             Point2f(end_x_mm * resize, end_y_mm * resize)});

                }
            }
        }
    }

    //mergeLineSegmentsT(linesSegments,lines,horizontal_lines);
    //saveAsPlt(pltPath.toStdString(), lines);
    mergeLineSegmentsT(linesSegments,lines,horizontal_lines);
    saveAsDxf(pltPathDxf.toStdString(), lines,horizontal_lines);
}



void floydsetinTool::saveAsDxf(const string& filename, const vector<LineSegment>* lines,bool horizontal_lines) {
    std::ofstream dxf_file(filename);
    if (!dxf_file.is_open()) {
        std::cerr << "无法打开文件" << filename << std::endl;
        return;
    }

    // 写入DXF文件头部信息
    dxf_file << "0\nSECTION\n";
    dxf_file << "2\nHEADER\n";
    dxf_file << "0\nENDSEC\n";
    dxf_file << "0\nSECTION\n";
    dxf_file << "2\nTABLES\n";
    dxf_file << "0\nENDSEC\n";
    dxf_file << "0\nSECTION\n";
    dxf_file << "2\nBLOCKS\n";
    dxf_file << "0\nENDSEC\n";
    dxf_file << "0\nSECTION\n";
    dxf_file << "2\nENTITIES\n";

    //    dxf_file << "0\nPOINT\n";
    //    dxf_file << "8\n0\n";         // 使用默认图层 "0"
    //    dxf_file << "10\n" << 0 << "\n";  // X coordinate of start point
    //    dxf_file << "20\n" << 0 << "\n";  // Y coordinate of start point
    //    dxf_file << "30\n0.0\n";  // Z coordinate of start point (optional, usually 0)
    //    dxf_file << "11\n" << 0 << "\n";  // X coordinate of end point
    //    dxf_file << "21\n" << 0 << "\n";  // Y coordinate of end point
    //    dxf_file << "31\n0.0\n";  // Z coordinate of end point (optional, usually 0)


    vector<vector<double>>markPoint={
        {-1*(1.5),std::ceil(floysetinTooLimageHeight/2.0f),1},
        {std::ceil(floysetinTooLimageHeight)+1.5,std::ceil(floysetinTooLimageHeight/2.0f),1},
        {std::ceil(floysetinTooLimageHeight/2.0f),-1.5,1},
        {std::ceil(floysetinTooLimageHeight/2.0f),std::ceil(floysetinTooLimageHeight)+1.5,1}};

    // Write circles
    for (const auto& point : markPoint) {
        double x = point[0];
        double y = point[1];
        double radius = point[2];

        dxf_file << "0\nCIRCLE\n";
        dxf_file << "8\n0\n"; // Layer (0 for default layer)
        dxf_file << "10\n" << x << "\n"; // Center X
        dxf_file << "20\n" << y << "\n"; // Center Y
        dxf_file << "30\n0.0\n"; // Center Z (2D circle, Z = 0)
        dxf_file << "40\n" << radius << "\n"; // Radius
    }
    // 写入线段数据
    for (const auto& line : *lines) {

        //qDebug()<<"floy"<<floydsetinTooLlineDistance;
        //qDebug()<<"fabs(line.end.x-line.start.x)"<<fabs(line.end.x-line.start.x);
        if(fabs(line.end.x-line.start.x)-floydsetinTooLlineDistance<=0.001){
            //          dxf_file << "0\nLINE\n";
            //          dxf_file << "8\n0\n";  // Layer 0
            //qDebug()<<"fa";
            dxf_file << "0\nPOINT\n";
            dxf_file << "8\n0\n";         // 使用默认图层 "0"
            dxf_file << "10\n" << line.start.x << "\n";  // X coordinate of start point
            dxf_file << "20\n" << line.start.y << "\n";  // Y coordinate of start point
            dxf_file << "30\n0.0\n";  // Z coordinate of start point (optional, usually 0)
            dxf_file << "11\n" << line.start.x << "\n";  // X coordinate of end point
            dxf_file << "21\n" << line.start.y << "\n";  // Y coordinate of end point
            dxf_file << "31\n0.0\n";  // Z coordinate of end point (optional, usually 0)
        }else {

            dxf_file << "0\nLINE\n";
            dxf_file << "8\n0\n";  // Layer 0
            dxf_file<< "10\n"<<line.start.x<<"\n";
            dxf_file<<"20\n"<<line.start.y<<"\n";
            dxf_file<<"30\n0.0\n";
            dxf_file << "11\n" << line.end.x << "\n";  // X coordinate of end point
            dxf_file << "21\n" << line.end.y << "\n";  // Y coordinate of end point
            dxf_file << "31\n0.0\n";  // Z coordinate of end point (optional, usually 0)
        }


    }


    // 结束DXF文件
    dxf_file << "0\nENDSEC\n";
    dxf_file << "0\nSECTION\n";
    dxf_file << "2\nOBJECTS\n";
    dxf_file << "0\nENDSEC\n";
    dxf_file << "0\nEOF\n";

    dxf_file.close();
}



void floydsetinTool::saveAsPlt(const string& filename, const vector<LineSegment>* lines) {

    float resize = 40;
    ofstream plt_file(filename);
    if (!plt_file.is_open()) {
        cerr << "无法打开文件" << filename << endl;
        return;
    }

    // 写入PLT格式头部信息 (简化版本)
    plt_file << "IN;\n";  // Initialize
    plt_file << "SP1;\n";  // Select pen 1

    // 写入线段数据
    for (const auto& line : *lines) {
        plt_file << "PU" << line.start.x*resize << "," << line.start.y*resize << ";\n";  // Move to start point
        plt_file << "PD" << line.end.x*resize << "," << line.end.y*resize << ";\n";      // Draw to end point
    }

    plt_file << "PU0,0;\n";  // Pen up and move to origin
    plt_file << "SP0;\n";  // End plotting
    plt_file.close();
}





template <typename T>
T floydsetinTool::clamp(T &value, T min_value, T max_value) {
    if (value < min_value) value= min_value;
    if (value > max_value) value= max_value;
    return value;
}



void floydsetinTool::mergeLineSegmentsT(const vector<LineSegment>& input_lines, vector<LineSegment>* merged_lines, bool is_horizontal) {
    if (input_lines.empty()) return;

    // 先按线段的起点排序：根据水平线或垂直线的不同类型，选择排序方式
    vector<LineSegment> sorted_lines = input_lines;
    if (is_horizontal) {
        // 对于水平线段，按y排序，如果y相同则按x排序
        sort(sorted_lines.begin(), sorted_lines.end(), [](const LineSegment& a, const LineSegment& b) {
            if (a.start.y == b.start.y) {
                return a.start.x < b.start.x;
            }
            return a.start.y < b.start.y;
        });
    } else {
        // 对于垂直线段，按x排序，如果x相同则按y排序
        sort(sorted_lines.begin(), sorted_lines.end(), [](const LineSegment& a, const LineSegment& b) {
            if (a.start.x == b.start.x) {
                return a.start.y < b.start.y;
            }
            return a.start.x < b.start.x;
        });
    }
    bool reverse_direction = false;    // 控制相邻行或列之间的方向
    LineSegment* current_line = new LineSegment(sorted_lines[0]);
    vector<LineSegment> modell_data_collet;
    //svector<LineSegment> modell_data_out;

    for (size_t i = 1; i < sorted_lines.size(); ++i) {
        const auto& line = sorted_lines[i];

        if (is_horizontal) {
            // 处理水平线段的合并情况
            if (current_line->start.y == current_line->end.y && current_line->start.y == line.start.y) {
                if (current_line->end.x >= line.start.x) {
                    current_line->end.x = max(current_line->end.x, line.end.x);
                } else {

                    if (reverse_direction) {

                        // 手动交换 start 和 end 的数值
                        swap(current_line->start.x, current_line->end.x);
                        //swap(current_line->start.y, current_line->end.y);

                        modell_data_collet.push_back(*current_line);
                        *current_line = line;
                    }else {
                        merged_lines->push_back(*current_line);
                        *current_line = line;
                    }




                }
            } else {
                if (reverse_direction){

                    swap(current_line->start.x, current_line->end.x);
                    modell_data_collet.push_back(*current_line);
                    sort(modell_data_collet.begin(), modell_data_collet.end(), [](const LineSegment& a, const LineSegment& b) {
                        if (a.start.y == b.start.y) {
                            return a.start.x > b.start.x;
                        }
                        return a.start.y < b.start.y;
                    });
                    merged_lines->insert(merged_lines->end(), modell_data_collet.begin(), modell_data_collet.end());
                    modell_data_collet={};
                    *current_line = line;
                }
                else {
                    merged_lines->push_back(*current_line);;
                    *current_line = line;
                }


                reverse_direction=!reverse_direction;



            }
        } else {
            // 处理垂直线段的合并情况
            if (current_line->start.x == current_line->end.x && current_line->start.x == line.start.x) {
                if (current_line->end.y >= line.start.y) {
                    current_line->end.y = max(current_line->end.y, line.end.y);
                } else {
                    if (reverse_direction) {

                        // 手动交换 start 和 end 的数值
                        swap(current_line->start.y, current_line->end.y);

                        modell_data_collet.push_back(*current_line);
                        *current_line = line;
                    }else {
                        merged_lines->push_back(*current_line);
                        *current_line = line;
                    }

                }
            } else {
                if(reverse_direction){
                    swap(current_line->start.y, current_line->end.y);
                    modell_data_collet.push_back(*current_line);
                    sort(modell_data_collet.begin(), modell_data_collet.end(), [](const LineSegment& a, const LineSegment& b) {
                        if (a.start.x == b.start.x) {
                            return a.start.y > b.start.y;
                        }
                        return a.start.x < b.start.x;
                    });
                    merged_lines->insert(merged_lines->end(), modell_data_collet.begin(), modell_data_collet.end());
                    modell_data_collet={};
                    *current_line = line;
                }
                else {
                    merged_lines->push_back(*current_line);;
                    *current_line = line;
                }
            }
        }
    }

    // 添加最后一个线段
    merged_lines->push_back(*current_line);
    delete current_line;
}



void floydsetinTool::mergeLineSegments(const vector<LineSegment>& input_lines, vector<LineSegment>& merged_lines, bool is_horizontal) {
    if (input_lines.empty()) return;

    // 先按线段的起点排序：根据水平线或垂直线的不同类型，选择排序方式
    vector<LineSegment> sorted_lines = input_lines;
    if (is_horizontal) {
        // 对于水平线段，按y排序，如果y相同则按x排序
        sort(sorted_lines.begin(), sorted_lines.end(), [](const LineSegment& a, const LineSegment& b) {
            if (a.start.y == b.start.y) {
                return a.start.x < b.start.x;
            }
            return a.start.y < b.start.y;
        });
    } else {
        // 对于垂直线段，按x排序，如果x相同则按y排序
        sort(sorted_lines.begin(), sorted_lines.end(), [](const LineSegment& a, const LineSegment& b) {
            if (a.start.x == b.start.x) {
                return a.start.y < b.start.y;
            }
            return a.start.x < b.start.x;
        });
    }

    LineSegment* current_line = new LineSegment(sorted_lines[0]);

    for (size_t i = 1; i < sorted_lines.size(); ++i) {
        const auto& line = sorted_lines[i];

        if (is_horizontal) {
            // 处理水平线段的合并情况
            if (current_line->start.y == current_line->end.y && current_line->start.y == line.start.y) {
                if (current_line->end.x >= line.start.x) {
                    current_line->end.x = max(current_line->end.x, line.end.x);
                } else {
                    merged_lines.push_back(*current_line);
                    *current_line = line;
                }
            } else {
                merged_lines.push_back(*current_line);
                *current_line = line;
            }
        } else {
            // 处理垂直线段的合并情况
            if (current_line->start.x == current_line->end.x && current_line->start.x == line.start.x) {
                if (current_line->end.y >= line.start.y) {
                    current_line->end.y = max(current_line->end.y, line.end.y);
                } else {
                    merged_lines.push_back(*current_line);
                    *current_line = line;
                }
            } else {
                merged_lines.push_back(*current_line);
                *current_line = line;
            }
        }
    }

    // 添加最后一个线段
    merged_lines.push_back(*current_line);
    delete current_line;
}

// 计算行列式
//double floydsetinTool::determinant(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
//    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
//}

// 解三元一次方程组的函数
//bool floydsetinTool::solveLinear3x3(const QVector<QVector<int>>& coefficients) {
//    if (coefficients.size() != 4 || coefficients[0].size() != 4) {
//        qDebug() << "Invalid matrix size";
//        return false;
//    }

//    // Extract coefficients and constants
//    double a1 = coefficients[0][0];
//    double b1 = coefficients[0][1];
//    double c1 = coefficients[0][2];
//    double d1 = coefficients[0][3];

//    double a2 = coefficients[1][0];
//    double b2 = coefficients[1][1];
//    double c2 = coefficients[1][2];
//    double d2 = coefficients[1][3];

//    double a3 = coefficients[2][0];
//    double b3 = coefficients[2][1];
//    double c3 = coefficients[2][2];
//    double d3 = coefficients[2][3];

//    // Solve the system using Cramer's rule
//    double det = a1 * (b2 * c3 - b3 * c2)
//            - b1 * (a2 * c3 - a3 * c2)
//            + c1 * (a2 * b3 - a3 * b2);

//    if (det == 0) {
//        qDebug() << "The system has no unique solution.";
//        return false;
//    }

//    double detX = d1 * (b2 * c3 - b3 * c2)
//            - b1 * (d2 * c3 - d3 * c2)
//            + c1 * (d2 * b3 - d3 * b2);

//    double detY = a1 * (d2 * c3 - d3 * c2)
//            - d1 * (a2 * c3 - a3 * c2)
//            + c1 * (a2 * d3 - a3 * d2);

//    double detZ = a1 * (b2 * d3 - b3 * d2)
//            - b1 * (a2 * d3 - a3 * d2)
//            + d1 * (a2 * b3 - a3 * b2);

//    ColorCorrectionA = detX / det;
//    ColorCorrectionB = detY / det;
//    ColorCorrectionC = detZ / det;
//    qDebug()<<"ColorCorrectionA"<<ColorCorrectionA<<"  "<<detX;
//    qDebug()<<"ColorCorrectionB"<<ColorCorrectionB<<"  "<<detY;
//    qDebug()<<"ColorCorrectionC"<<ColorCorrectionC<<"  "<<detZ;
//    return true;
//}

//void floydsetinTool::halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(Mat& src, Mat& dst, double &line_distance, double imageHeight, double pixelHeight, int grayLevel, bool horizontal_lines) {
//    Mat gray;
//    float resize = 40;
//    int matrixSize =grayLevel;  // 计算矩阵的尺寸 2^grayLevel

//    // 检查图像的通道数，如果是彩色图像则转换为灰度图
//    if (src.channels() == 3) {
//        cvtColor(src, gray, COLOR_BGR2GRAY);
//    } else {
//        gray = src;
//    }

//    // 创建一个与原图像相同大小的空白图像
//    dst = Mat::zeros(gray.size(), CV_8UC1);

//    // 获取图像尺寸
//    int rows = gray.rows;
//    int cols = gray.cols;

//    // 生成 Bayer 矩阵
//    vector<vector<int>> bayerMatrix = generateBayerMatrix(grayLevel);
//    qDebug()<<bayerMatrix;
//    qDebug()<<"\n\n\n\n\n\n\n\n\n\n\n\n";
//    // 根据量化后的灰度图像绘制线段
//    for (int y = 0; y < rows; ++y) {
//        for (int x = 0; x < cols; ++x) {

//            // 获取当前像素的灰度值
//            double pixel_value = static_cast<float>(gray.at<uchar>(y, x));
//            double threshold = (pixel_value / 255.0) * (matrixSize * matrixSize);  // 确定灰度值对应的阈值

//            // 将每个像素划分为更小的网格，并根据 Bayer 矩阵决定绘制线段
//            for (int grid_row = 0; grid_row < matrixSize; ++grid_row) {
//                for (int grid_col = 0; grid_col < matrixSize; ++grid_col) {
//                    int bayer_value = bayerMatrix[grid_row][grid_col];
//                    if (bayer_value < threshold) {
//                        // 计算线段的起始和终止位置（物理坐标）
//                        double start_x_mm = x * pixelHeight + grid_col * (pixelHeight / matrixSize);
//                        double start_y_mm = y * pixelHeight + grid_row * (pixelHeight / matrixSize);
//                        double end_x_mm = start_x_mm + (horizontal_lines ? (pixelHeight / matrixSize) : 0);
//                        double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (pixelHeight / matrixSize));

//                        // 绘制线段
//                        lines.push_back({Point2f(start_x_mm * resize, start_y_mm * resize),
//                                         Point2f(end_x_mm * resize, end_y_mm * resize)});
//                    }
//                }
//            }
//        }
//    }
//}

//// 递归生成 Bayer 矩阵
//vector<vector<int>> floydsetinTool::generateBayerMatrix(int size) {
//    if (size == 2) {
//            // 基本的 2x2 Bayer 矩阵
//            return {{0, 2},
//                    {3, 1}};
//        }

//        // 生成前一层的 Bayer 矩阵
//        vector<vector<int>> prevMatrix = generateBayerMatrix(size / 2);
//        int prevSize = prevMatrix.size();  // 前一层矩阵的大小
//        vector<vector<int>> matrix(size, vector<int>(size));

//        // 填充当前层的 Bayer 矩阵
//        for (int y = 0; y < prevSize; ++y) {
//            for (int x = 0; x < prevSize; ++x) {
//                int value = prevMatrix[y][x];
//                matrix[y][x] = 4 * value;
//                matrix[y][x + prevSize] = 4 * value + 2;
//                matrix[y + prevSize][x] = 4 * value + 3;
//                matrix[y + prevSize][x + prevSize] = 4 * value + 1;
//            }
//        }

//        return matrix;
//}





//像素网格划分，模式法
//void floydsetinTool::halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(Mat& src, Mat& dst, double &line_distance, double imageHeight, double pixelHeight, int grayLevel, bool horizontal_lines) {
//    Mat gray;
//    float resize = 40;
//    int totalLines = grayLevel * grayLevel + 1;  // 最大的线条数量

//    // 检查图像的通道数，如果是彩色图像则转换为灰度图
//    if (src.channels() == 3) {
//        cvtColor(src, gray, COLOR_BGR2GRAY);
//    } else {
//        gray = src;
//    }

//    // 创建一个与原图像相同大小的空白图像
//    dst = Mat::zeros(gray.size(), CV_8UC1);

//    // 获取图像尺寸
//    int rows = gray.rows;
//    int cols = gray.cols;

//    // 计算像素的实际物理尺寸（毫米）
//    double pixel_height_mm = pixelHeight;
//    double pixel_width_mm = pixelHeight;  // 假设图像宽度与高度的比例相同

//    // 根据量化后的灰度图像绘制线段
//    for (int y = 0; y < rows; ++y) {
//        for (int x = 0; x < cols; ++x) {

//            // 获取当前像素的灰度值
//            double pixel_value = static_cast<float>(gray.at<uchar>(y, x));

//            // 限制 pixel_value 在 0 到 255 之间
//            pixel_value = min(max(pixel_value, 0.0), 255.0);

//            // 计算灰度等级索引，线条数量与灰度值成反比
//            int num_lines_to_draw = static_cast<int>((1.0f - (pixel_value / 255.0f)) * totalLines);

//            // 将每个像素划分为更小的网格，并绘制线段
//            int grid_size = grayLevel;  // 根据 grayLevel 来划分网格
//            for (int i = 0; i < num_lines_to_draw; ++i) {
//                int grid_row = i / grid_size;
//                int grid_col = i % grid_size;

//                // 计算线段的起始和终止位置（物理坐标）
//                double start_x_mm = x * pixel_width_mm + grid_col * (pixel_width_mm / grid_size);
//                double start_y_mm = y * pixel_height_mm + grid_row * (pixel_height_mm / grid_size);
//                double end_x_mm = start_x_mm + (horizontal_lines ? (pixel_width_mm / grid_size) : 0);
//                double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (pixel_height_mm / grid_size));

//                // 绘制线段
//                lines.push_back({Point2f(start_x_mm * resize, start_y_mm * resize),
//                                 Point2f(end_x_mm * resize, end_y_mm * resize)});
//            }
//        }
//    }
//}







//比实际的线间距控制少0.2，最后的替换
//void floydsetinTool::halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(Mat& src, Mat& dst, double &line_distance,double imageHeight , double LineDistance, int grayLevel,bool horizontal_lines) {
//    Mat gray;
//    std::vector<double> linDs;
//    float resize = 40;
//    line_distance=line_distance-0.02;
//    // 检查图像的通道数，如果是彩色图像则转换为灰度图
//    if (src.channels() == 3) {
//        cvtColor(src, gray, COLOR_BGR2GRAY);
//    } else {
//        gray = src;
//    }

//    // 创建一个与原图像相同大小的空白图像
//    dst = Mat::zeros(gray.size(), CV_8UC1);

//    // 获取图像尺寸
//    int rows = gray.rows;
//    int cols = gray.cols;

//    // 计算像素的实际物理尺寸（毫米）
//    double pixel_height_mm = LineDistance;
//    double pixel_width_mm = LineDistance;  // 假设图像宽度与高度的比例相同

//    // 根据量化后的灰度图像绘制线段
//    for (int y = 0; y < rows; ++y) {
//        for (int x = 0; x < cols; ++x) {

//            // 获取当前像素的灰度值
//            uchar pixel_value = gray.at<uchar>(y, x);

//            // 将灰度值映射到0到grayLevel之间的整数值
//            int pattern_index = static_cast<int>((1.0f - pixel_value / 255.0f) * grayLevel);
//            pattern_index = min(pattern_index, grayLevel - 1); // 确保pattern_index在合理范围内

//            // 根据pattern_index确定线段的数量和长度
//            int num_lines = pattern_index;
//            double line_length_factor = pixel_value / 255.0f; // 线段长度根据灰度值变化

//            for (int i = 0; i < num_lines; ++i) {
//                if (horizontal_lines) {
//                    // 计算水平线的实际物理坐标和长度（毫米）
//                    double line_y_mm = y * pixel_height_mm + i * (pixel_height_mm / num_lines);
//                    double line_length = pixel_width_mm * (1.0 - line_length_factor); // 线段长度与灰度值成反比
//                    lines.push_back({Point2f(x * pixel_width_mm * resize, line_y_mm * resize), Point2f((x * pixel_width_mm + line_length) * resize, line_y_mm * resize)});
//                } else {
//                    // 计算垂直线的实际物理坐标和长度（毫米）
//                    double line_x_mm = x * pixel_width_mm + i * (pixel_width_mm / num_lines);
//                    double line_length = pixel_height_mm * (1.0 - line_length_factor); // 线段长度与灰度值成反比
//                    lines.push_back({Point2f(line_x_mm * resize, y * pixel_height_mm * resize), Point2f(line_x_mm * resize, (y * pixel_height_mm + line_length) * resize)});
//                }
//            }
//        }
//    }
//}
//void floydsetinTool::halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(Mat& src, Mat& dst, double &line_distance, double imageHeight, double pixelHeight, int grayLevel, bool horizontal_lines) {
//    Mat gray;
//    float resize = 40;
//    int matrixSize = grayLevel;

//    // 检查图像的通道数，如果是彩色图像则转换为灰度图
//    if (src.channels() == 3) {
//        cvtColor(src, gray, COLOR_BGR2GRAY);
//    } else {
//        gray = src;
//    }

//    // 创建一个与原图像相同大小的空白图像
//    dst = Mat::zeros(gray.size(), CV_8UC1);

//    // 获取图像尺寸
//    int rows = gray.rows;
//    int cols = gray.cols;

//    // 生成 Bayer 矩阵
//    vector<vector<int>> bayerMatrix = generateBayerMatrix(matrixSize);

//    // 创建误差矩阵
//    Mat errorMatrix = Mat::zeros(rows, cols, CV_32F);

//    // 根据量化后的灰度图像绘制线段
//    for (int y = 0; y < rows; ++y) {
//        for (int x = 0; x < cols; ++x) {
//            // 获取当前像素的灰度值，并加上误差扩散的值
//            double pixel_value = static_cast<float>(gray.at<uchar>(y, x)) + errorMatrix.at<float>(y, x);
//            double threshold = (pixel_value / 255.0) * (matrixSize * matrixSize);  // 确定灰度值对应的阈值

//            // 计算误差
//            double quant_error = pixel_value - threshold;

//            // Floyd-Steinberg 误差扩散
//            if (x + 1 < cols) errorMatrix.at<float>(y, x + 1) += quant_error * 7 / 16.0;
//            if (y + 1 < rows) {
//                if (x > 0) errorMatrix.at<float>(y + 1, x - 1) += quant_error * 3 / 16.0;
//                errorMatrix.at<float>(y + 1, x) += quant_error * 5 / 16.0;
//                if (x + 1 < cols) errorMatrix.at<float>(y + 1, x + 1) += quant_error * 1 / 16.0;
//            }

//            // 将每个像素划分为更小的网格，并根据 Bayer 矩阵决定绘制线段
//            for (int grid_row = 0; grid_row < matrixSize; ++grid_row) {
//                for (int grid_col = 0; grid_col < matrixSize; ++grid_col) {
//                    int bayer_value = bayerMatrix[grid_row][grid_col];
//                    if (bayer_value < threshold) {
//                        // 计算线段的起始和终止位置（物理坐标）
//                        double start_x_mm = x * pixelHeight + grid_col * (pixelHeight / matrixSize);
//                        double start_y_mm = y * pixelHeight + grid_row * (pixelHeight / matrixSize);
//                        double end_x_mm = start_x_mm + (horizontal_lines ? (pixelHeight / matrixSize) : 0);
//                        double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (pixelHeight / matrixSize));

//                        // 绘制线段
//                        // lines.push_back({Point2f(start_x_mm * resize, start_y_mm * resize),
//                        //                  Point2f(end_x_mm * resize, end_y_mm * resize)});
//                    }
//                }
//            }
//        }
//    }
//}

//// 递归生成 Bayer 矩阵
//vector<vector<int>> floydsetinTool::generateBayerMatrix(int size) {
//    if (size == 2) {
//        // 基本的 2x2 Bayer 矩阵
//        return {{0, 2},
//                {3, 1}};
//    }

//    // 生成前一层的 Bayer 矩阵
//    vector<vector<int>> prevMatrix = generateBayerMatrix(size / 2);
//    int prevSize = prevMatrix.size();  // 前一层矩阵的大小
//    vector<vector<int>> matrix(size, vector<int>(size));

//    // 填充当前层的 Bayer 矩阵
//    for (int y = 0; y < prevSize; ++y) {
//        for (int x = 0; x < prevSize; ++x) {
//            int value = prevMatrix[y][x];
//            matrix[y][x] = 4 * value;
//            matrix[y][x + prevSize] = 4 * value + 2;
//            matrix[y + prevSize][x] = 4 * value + 3;
//            matrix[y + prevSize][x + prevSize] = 4 * value + 1;
//        }
//    }

//    return matrix;
//}


//*****************************************************************************************************************************************************************

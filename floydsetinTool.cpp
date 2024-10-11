
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>
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



//像素网格划分，模式法,误差扩散，小网格位置用矩阵分散
void floydsetinTool::halftoneUsingline_doubelSizeGridWithErrorDiffusionAndMatrixTest(Mat& src, Mat& dst,  int grayLevel, bool horizontal_lines,int layer,double dataDenstyScaling,int blackRange) {
    Mat gray;
    double resize = 1;
    int totalLines;  // 5*5 + 1 = 26 个灰度等级
    double maxPixelValue=100.0;
    double maxError=50;
    double pixelHeight;
    double ColorCorrection;
    double line_distance;
    double offsetLine_distance=0;

    if(layer==0){
        line_distance=lineDistanceC;
        pixelHeight=lineDistanceC*grayLevel;
        totalLines=grayLevel*grayLevel+1;
        linesCR={};
        linesSegments={};
        ColorCorrection=ColorCorrectionA;}
    else if (layer==1) {
        line_distance=lineDistanceM;
        pixelHeight=lineDistanceM*grayLevel;
        totalLines=grayLevel*grayLevel+1;
        linesMG={};
        linesSegments={};
        ColorCorrection=ColorCorrectionB;
    } else if (layer==2) {
        line_distance=lineDistanceY;
        pixelHeight=lineDistanceY*grayLevel;
        totalLines=grayLevel*grayLevel+1;
        linesYB={};
        linesSegments={};
        ColorCorrection=ColorCorrectionC;
    }
    else if (layer==3) {
        line_distance=lineDistanceK;
        pixelHeight=lineDistanceK*grayLevel;
        totalLines=grayLevel*grayLevel+1;
        linesK={};
        linesSegments={};
        ColorCorrection=1;
    }
    vector<vector<LineSegment>>lineVector={linesCR,linesCR,linesYB,linesK};
    vector<LineSegment>  *lines=&lineVector[layer];
    floydsetinTooLlineSegments=line_distance;
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
            double pixel_value = static_cast<double>(gray.at<uchar>(y, x)) + error_diffusion[y][x];

            // 限制 pixel_value 在 0 到 255 之间
            pixel_value = std::min(std::max(pixel_value, 0.0), maxPixelValue);

            double fractionalPart = (pixel_value / (maxPixelValue / totalLines)) - std::floor(pixel_value / (maxPixelValue / totalLines));

            fractionalPart = std::max(fractionalPart, 0.0);

            // 计算灰度等级索引，选择对应的矩阵
            int gray_index = (std::floor(pixel_value / (maxPixelValue/totalLines)) + std::ceil(fractionalPart))-1;

            gray_index*=ColorCorrection;

            int drawLine=(grayLevel * grayLevel)-gray_index;

            // 生成对应的矩阵
            auto pattern = generatePatternMatrix(grayLevel, drawLine);

            // 计算当前像素的量化误差
            double quant_error = pixel_value - ((maxPixelValue / totalLines) *
                                                (
                                                    gray_index
                                                    ));

            if (x + 1 < cols)
                error_diffusion[y][x + 1] += quant_error * 7.0 / 16.0;
            if (y + 1 < rows) {
                if (x - 1 >= 0)
                    error_diffusion[y + 1][x - 1] += quant_error * 3.0 / 16.0;
                error_diffusion[y + 1][x] += quant_error * 5.0 / 16.0;
                if (x + 1 < cols)
                    error_diffusion[y + 1][x + 1] += quant_error * 1.0 / 16.0;
            }


            // 为了避免过多的误差累积，限制扩散误差的范围
            error_diffusion[y][x] = (error_diffusion[y][x] < -maxError) ? -maxError :
                                                                          ((error_diffusion[y][x] > maxError) ? maxError : error_diffusion[y][x]);
            // 使用生成的矩阵绘制线段
            for (int i = 0; i < grayLevel; ++i) {
                for (int j = 0; j < grayLevel; ++j) {
                    if (pattern[i][j] == 1) {

                        if(horizontal_lines){

                            // 计算线段的起始和终止位置（物理坐标）
                            double start_x_mm = x * pixel_width_mm + j * (line_distance)+offsetLine_distance;
                            double start_y_mm = y * pixel_height_mm + i * (line_distance)+offsetLine_distance;
                            double end_x_mm = start_x_mm + (horizontal_lines ? (0) : 0);
                            double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (0));
                            // 绘制线段
                            linesSegments.push_back({Point2f(start_x_mm * resize, start_y_mm * resize),
                                                     Point2f(end_x_mm * resize, end_y_mm * resize)});
                        }
                        else {

                            double start_x_mm = x * pixel_width_mm + i * (line_distance)+offsetLine_distance;
                            double start_y_mm = y * pixel_height_mm + j * (line_distance)+offsetLine_distance;
                            double end_x_mm = start_x_mm + (horizontal_lines ? (0) : 0);
                            double end_y_mm = start_y_mm + (horizontal_lines ? 0 : (0));
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
    //saveAsPlt(pltPathPlt.toStdString(), lines);
    saveAsDxf(pltPathDxf.toStdString(), lines,horizontal_lines);
}



//********************************************************************************************************


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

    double gap = 2.0;  // 1毫米的间隙
    double adjustedHeight = floysetinTooLimageHeight + gap;  // 调整后的总直径

    // 确定带有间隙的矩形的四个顶点
    vector<vector<double>> markPoint = {
        {0-gap, 0-gap, 1},  // 左下角
        {std::ceil(adjustedHeight ), 0-gap, 1},   // 右下角
        {std::ceil(adjustedHeight ), std::ceil(adjustedHeight ), 1},    // 右上角
        {0-gap, std::ceil(adjustedHeight), 1}    // 左上角
    };

    // 写入带间隙的矩形（用线连接）
    for (size_t i = 0; i < markPoint.size(); ++i) {
        double x1 = markPoint[i][0];
        double y1 = markPoint[i][1];
        double x2 = markPoint[(i + 1) % markPoint.size()][0];  // 下一个点
        double y2 = markPoint[(i + 1) % markPoint.size()][1];

        dxf_file << "0\nLINE\n";
        dxf_file << "8\n0\n";  // Layer (0 for default layer)
        dxf_file << "10\n" << x1 << "\n";  // 起点X
        dxf_file << "20\n" << y1 << "\n";  // 起点Y
        dxf_file << "30\n0.0\n";  // 起点Z
        dxf_file << "11\n" << x2 << "\n";  // 终点X
        dxf_file << "21\n" << y2 << "\n";  // 终点Y
        dxf_file << "31\n0.0\n";  // 终点Z
    }
    // 写入线段数据
    for (const auto& line : *lines) {

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
                if ((std::abs(current_line->end.x - line.start.x)-floydsetinTooLlineSegments)<=0.0001) {
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
                if ( (std::abs(current_line->end.y - line.start.y)-floydsetinTooLlineDistance)<=0.001) {
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






//*****************************************************************************************************************************************************************

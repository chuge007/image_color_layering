#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Qvector>

// 定义命名空间
using namespace cv;
using namespace std;


class floydsetinTool{

struct LineSegment {
    Point2d start;
    Point2d end;
};

enum direction {
    R = 1,  // right
    D,      // down
    L,      // left
    U,      // up
    END     // 结束标志
};

public:
    // 保存线段位置信息
    vector<LineSegment> lines;
    vector<LineSegment> linesSegments;
    void mergeLineSegments(const vector<LineSegment>& input_lines, vector<LineSegment>& merged_lines,bool is_horizontal);
    void mergeLineSegmentsT(const vector<LineSegment>& input_lines, vector<LineSegment>& merged_lines, bool is_horizontal);
    void saveAsPlt(const string& filename, const vector<LineSegment>& lines);

    template <typename T> T clamp(T value, T min_value, T max_value);
    // 函数声明
    std::vector<std::pair<int, int>> generateDistributedOrder(int gridSize);
    std::vector<std::vector<int>> generatePatternMatrix(int gridSize, int numPoints);

    std::vector<std::vector<int>> generateBayerMatrix(int n);


    double ColorCorrectionA;
    double ColorCorrectionB;
    double ColorCorrectionC;
    //double determinant(double a, double b, double c, double d, double e, double f, double g, double h, double i) ;
    bool   solveLinear3x3(const QVector<QVector<int>>& coefficients);





    uchar findfit(uchar p_param);

    int   findfitInt(int pixel_value,int levels);

    void fun1(Mat img);

    void fun2(Mat img);

    void fun3(Mat img);

    void floydsetin(Mat img);

    void floydsetin_2(Mat img);

    void my2(Mat img);

    void floydsetin_4(Mat img);

    void floydsetin_8(Mat img);

    void floydsetin_16(Mat img);

    void floydsetin_16_001(Mat img);

    void floydsetin_16(Mat img, int m);

    void halftone( Mat& src, Mat& dst, int cell_size);

    void floydSteinbergHalftoneUsingPointNum(Mat& src, Mat& dst, int cell_size);

    void halftoneUsingRect(Mat& src, Mat& dst, int cell_size);

    void halftoneUsingCircles(Mat& src, Mat& dst, int cell_size);

    void halftoneUsingRect_doubelSizeGrid(Mat& src, Mat& dst, double cell_size, int num_levels);

    void halftoneUsingCircles_doubelSizeGrid(Mat& src, Mat& dst, double cell_size,int num_levels);

    void halftoneUsingline_doubelSizeGrid(Mat& src, Mat& dst,vector<LineSegment>& lines, double cell_size, bool horizontal_lines = true);

    void halftoneUsingline_doubelSizeGrid_savePat(Mat& src, vector<LineSegment>& lines, double cell_size, bool horizontal_lines = true);

    void halftoneUsingLineWithErrorDiffusion(Mat& src, Mat& dst,vector<LineSegment>& lines, double cell_size, bool horizontal_lines = true);

    void halftoneWithCirclesDoubelSizeGridTest(Mat& src, Mat& dst, double cell_size, int density_factor);



    void halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(Mat& src, Mat& dst,double &line_distance,double imageHeight ,double LineDistance,int grayLevel, bool horizontal_lines = true);

    void halftoneUsingline_doubelSizeGridWithErrorDiffusionAndMatrixTest(Mat& src, Mat& dst,double &line_distance,double imageHeight ,double LineDistance,int grayLevel, bool horizontal_lines ,int layer);



};
#endif // IMAGE_PROCESSING_H

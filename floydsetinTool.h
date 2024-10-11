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
    vector<LineSegment> linesCR;
    vector<LineSegment> linesMG;
    vector<LineSegment> linesYB;
    vector<LineSegment> linesK;
    vector<LineSegment> linesSegments;

    double floydsetinTooLlineDistance;
    double floydsetinTooLgrayLevel;
    double floysetinTooLimageHeight;
    double floydsetinTooLlineSegments;
    double StepDistance;
    int    vectorSize;

    void mergeLineSegmentsT(const vector<LineSegment>& input_lines, vector<LineSegment>* merged_lines, bool is_horizontal);

    void saveAsPlt(const string& filename, const vector<LineSegment>* lines);
    void saveAsDxf(const string& filename, const vector<LineSegment>* lines,bool horizontal_lines);

    template <typename T> T clamp(T &value, T min_value, T max_value);
    // 函数声明
    std::vector<std::pair<int, int>> generateDistributedOrder(int gridSize);
    std::vector<std::vector<int>> generatePatternMatrix(int gridSize, int numPoints);


    QString pltPathPlt;
    QString pltPathDxf;
    double ColorCorrectionA;
    double ColorCorrectionB;
    double ColorCorrectionC;
    double lineDistanceC;
    double lineDistanceM;
    double lineDistanceY;
    double lineDistanceK;
    //double determinant(double a, double b, double c, double d, double e, double f, double g, double h, double i) ;
    bool   solveLinear3x3(const QVector<QVector<int>>& coefficients);
    void   scaleLineNum(int &lineNum,double scale);


    void halftoneUsingline_doubelSizeGridWithErrorDiffusionAndMatrixTest(Mat& src, Mat& dst,int grayLevel, bool horizontal_lines ,int layer,double dataDenstyScaling,int blackRange);


};
#endif // IMAGE_PROCESSING_H

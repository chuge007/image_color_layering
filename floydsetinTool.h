﻿#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>


// 定义命名空间
using namespace cv;
using namespace std;


class floydsetinTool{

struct LineSegment {
    Point start;
    Point end;
};

public:
    // 保存线段位置信息
    vector<LineSegment> lines;
    vector<LineSegment> linesSegments;
    void mergeLineSegments(const vector<LineSegment>& input_lines, vector<LineSegment>& merged_lines,bool is_horizontal);
    // 函数声明
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

    void halftoneUsingRect_doubelSizeGrid(Mat& src, Mat& dst, float cell_size, int num_levels);

    void halftoneUsingCircles_doubelSizeGrid(Mat& src, Mat& dst, float cell_size,int num_levels);

    void halftoneUsingline_doubelSizeGrid(Mat& src, Mat& dst,vector<LineSegment>& lines, float cell_size, bool horizontal_lines = true);

    void halftoneUsingline_doubelSizeGrid_savePat(Mat& src, vector<LineSegment>& lines, float cell_size, bool horizontal_lines = true);

    void halftoneUsingLineWithErrorDiffusion(Mat& src, Mat& dst,vector<LineSegment>& lines, float cell_size, bool horizontal_lines = true);

    void halftoneWithCirclesDoubelSizeGridTest(Mat& src, Mat& dst, float cell_size, int density_factor);

    void halftoneUsingline_doubelSizeGridWithErrorDiffusionTest(Mat& src, Mat& dst,float &line_distance,float imageHeight ,float cell_size,int grayLevel, bool horizontal_lines = true);

    void saveAsPlt(const string& filename, const vector<LineSegment>& lines);

};
#endif // IMAGE_PROCESSING_H

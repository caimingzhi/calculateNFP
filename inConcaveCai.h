//
// Created by Admin on 2023/9/7.
//

#ifndef CALCULATENFP_INCONCAVECAI_H
#define CALCULATENFP_INCONCAVECAI_H

#include <cmath>
#include <vector>
#include <algorithm>
#include "cfloat"
#include "geometry.h"

#define EPSILON 0.000001

using namespace std;

//二维double矢量
//struct  Point
//{
//    double x, y;
//
//    Point()
//    {
//        x = 0.0;
//        y = 0.0;
//    }
//    Point(double dx, double dy)
//    {
//        x = dx;
//        y = dy;
//    }
//    void Set(double dx, double dy)
//    {
//        x = dx;
//        y = dy;
//    }
//};

//判断点在线段上
bool IsPointOnLine(double px0, double py0, double px1, double py1, double px2, double py2);

//判断两线段相交
bool IsIntersect(double px1, double py1, double px2, double py2, double px3, double py3, double px4, double py4);

//判断点在多边形内
bool Point_In_Polygon_2D(double x, double y, vector<Point> &POL);


//int main2()
//{
//    //定义一个多边形（六边形）
//    vector<Point> POL;
//    POL.push_back(Point(268.28, 784.75));
//    POL.push_back(Point(153.98, 600.60));
//    POL.push_back(Point(274.63, 336.02));
//    POL.push_back(Point(623.88, 401.64));
//    POL.push_back(Point(676.80, 634.47));
//    POL.push_back(Point(530.75, 822.85));
//    POL.push_back(Point(268.28, 784.75));				//将起始点放入尾部，方便遍历每一条边
//
//    //
//    if (Point_In_Polygon_2D(407.98, 579.43, POL))
//    {
//        cout << "点（407.98, 579.43）在多边形内" << endl;
//    }
//    else
//    {
//        cout << "点（407.98, 579.43）在多边形外" << endl;
//    }
//
//    //
//    if (Point_In_Polygon_2D(678.92, 482.07, POL))
//    {
//        cout << "点（678.92, 482.07）在多边形内" << endl;
//    }
//    else
//    {
//        cout << "点（678.92, 482.07）在多边形外" << endl;
//    }
//
//    return 0;
//}
#endif //CALCULATENFP_INCONCAVECAI_H

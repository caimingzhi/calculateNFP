//
// Created by Admin on 2023/9/7.
//

#ifndef CALCULATENFP_CUCKOO_H
#define CALCULATENFP_CUCKOO_H

#include "geometry.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#define M_PI  3.14159265358979323846
class CuckooSearch {
public:
    std::pair<std::vector<double>, std::vector<double>> getCuckoosLevy(int num, std::pair<double, double> best) {
        double beta = 1.5;
        double sigma_u = (std::tgamma(1 + beta) * std::sin(M_PI * beta / 2) / (
                std::tgamma((1 + beta) / 2) * beta * std::pow(2, (beta - 1) / 2))) / beta;
        double sigma_v = 1;
        double x0 = best.first;
        double y0 = best.second;
        double x_delta = 0;
        double y_delta = 0; 
        std::vector<double> resX;
        std::vector<double> resY;

        for (int i = 0; i < num * 10; ++i) {
            double u = getRandomNormal(0, sigma_u);
            double v = getRandomNormal(0, sigma_v);
            double s = u / (std::fabs(v) * std::pow(std::fabs(v), 1 / beta));
            x_delta += s;

            u = getRandomNormal(0, sigma_u);
            v = getRandomNormal(0, sigma_v);
            s = u / (std::fabs(v) * std::pow(std::fabs(v), 1 / beta));
            y_delta += s;

            resX.push_back(x_delta);
            resY.push_back(y_delta);

        }

        double minX = *std::min_element(resX.begin(), resX.end());
        double maxX = *std::max_element(resX.begin(), resX.end());
        double minY = *std::min_element(resY.begin(), resY.end());
        double maxY = *std::max_element(resY.begin(), resY.end());

        double x_zoom = W / (maxX - minX);
        double y_zoom = H / (maxY - minY);

        std::vector<double> Levy_x;
        std::vector<double> Levy_y;

        for (int i = 0; i < resX.size(); ++i) {
            Levy_x.push_back(resX[i] * x_zoom + x0);
            Levy_y.push_back(resY[i] * y_zoom + y0);
        }

        // 随机选择num个点
        std::vector<int> indices;
        for (int i = 0; i < num * 10; ++i) {
            indices.push_back(i);
        }

        std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device()()));

        std::vector<double> choiceX;
        std::vector<double> choiceY;

        for (int i = 0; i < num; ++i) {
            choiceX.push_back(Levy_x[indices[i]]);
            choiceY.push_back(Levy_y[indices[i]]);
        }

        return std::make_pair(choiceX, choiceY);
    }

private:
    double W = 45.0; // 你的W值
    double H = 60.0; // 你的H值

    double getRandomNormal(double mean, double stddev) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> distribution(mean, stddev);
        return distribution(gen);
    }

};

class CuckooSearch1
{
public:
    vector<Point> getCuckooLevy( int num, Point startPoint , vector<Point> ifp )
    {
        double beta = 1.5;
        double sigma_u = (std::tgamma(1 + beta) * std::sin(M_PI * beta / 2) / (
                std::tgamma((1 + beta) / 2) * beta * std::pow(2, (beta - 1) / 2))) / beta;
        double sigma_v = 1;
        double x0 = startPoint.x;
        double y0 = startPoint.y;
        double x_delta = 0;
        double y_delta = 0;
        vector<double> resX;
        vector<double> resY;
        for (int i = 0; i < 10 * num; ++i) {
            double u = getRandomNormal(0, sigma_u);
            double v = getRandomNormal(0, sigma_v);
            double s = u / (std::fabs(v) * std::pow(std::fabs(v), 1 / beta));
            x_delta += s;

            u = getRandomNormal(0, sigma_u);
            v = getRandomNormal(0, sigma_v);
            s = u / (std::fabs(v) * std::pow(std::fabs(v), 1 / beta));
            y_delta += s;

            resX.emplace_back( x_delta );
            resY.emplace_back( y_delta );

//            resX.push_back({x_delta, y_delta});
//            resY.push_back({x_delta, y_delta});
        }

        double minX = *std::min_element(resX.begin(), resX.end());
        double maxX = *std::max_element( resX.begin(), resX.end());
        double minY = *std::min_element( resY.begin(), resY.end());
        double maxY = *std::max_element( resY.begin(), resY.end());

        width = ifp[1].x - ifp[0].x;
        height = ifp[1].y - ifp[0].y;

        double x_zoom = width / ( maxX - minX );
        double y_zoom = height / ( maxY - minY );
/*

        double x_zoom = ( ifp[1].x - ifp[0].x ) / ( maxX - minX );
        double y_zoom = ( ifp[1].y - ifp[0].y ) / ( maxY - minY );
*/


        std::vector<double> Levy_x;
        std::vector<double> Levy_y;

        for (int i = 0; i < resX.size(); ++i) {
            auto thisX = resX[i] * x_zoom + x0;
            thisX -= ifp[0].x;
            if ( thisX < 0 )
            {
                auto diffX =  thisX - ::floor( thisX/width ) * width;
                thisX = width + diffX;
            }

            if ( thisX > width )
            {
                thisX = thisX - ::floor( thisX/width ) * width;
            }

            thisX += ifp[0].x;


            auto thisY = resY[i] * y_zoom + y0;

            thisY -= ifp[0].y;
            if ( thisY < 0  )
            {
                auto diffY =  thisY - ::floor( thisY/height ) * height;
                thisY = height + diffY;
            }

            if ( thisY > height )
            {
                thisY = thisY - ::floor( thisY/height ) * height;
            }
            thisY += ifp[0].y;

            Levy_x.emplace_back( thisX );
            Levy_y.emplace_back( thisY );
        }

        vector<int> indices;
        for (int i = 0; i < num; ++i) {
            indices.emplace_back(i);
        }

        std::shuffle( indices.begin(), indices.end(), std::mt19937( std::random_device()() ) );
        vector<Point> resultPoint;
        for (int i = 0; i < num; ++i) {
            resultPoint.emplace_back( Levy_x[ indices[i] ], Levy_y[ indices[i] ] );
        }
        return resultPoint;

    }
    CuckooSearch1( double width, double height)
    {
        this->width = width;
        this->height = height;
    }
private:
    double width;
    double height;

    double getRandomNormal( double mean, double stddev )
    {
        random_device rd;
        mt19937  gen( rd() );
        normal_distribution<double> distribution( mean, stddev );
        return distribution( gen );
    }
};



#endif //CALCULATENFP_CUCKOO_H

//
// Created by Admin on 2023/9/14.
//
#include "geometry.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#ifndef CALCULATENFP_CUCKOOBETA_H
#define CALCULATENFP_CUCKOOBETA_H

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
//            double s = u / (std::fabs(v) * std::pow(std::fabs(v), 1 / beta));
            double s = 0.01 * u /  std::pow(std::fabs(v), 1 / beta);
            x_delta += s;

            u = getRandomNormal(0, sigma_u);
            v = getRandomNormal(0, sigma_v);
            s = u / (std::fabs(v) * std::pow(std::fabs(v), 1 / beta));
            y_delta += s;

            resX.emplace_back( x_delta );
            resY.emplace_back( y_delta );

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

    vector<Point> generateCuckoo( int num,  vector<Point> ifp )
    {
        std::random_device rd;
        std::mt19937 gen(rd());  // 使用Mersenne Twister引擎

        // 创建一个分布，指定生成的范围为[1, 4]
        std::uniform_real_distribution<double> distributionx(ifp[0].x, ifp[1].x);
        std::uniform_real_distribution<double> distributiony(ifp[0].y, ifp[1].y);

        vector<Point> resultPoint;
        for (int i = 0; i < 10; i++) {
            double x = distributionx(gen);
            double y = distributiony(gen);
            resultPoint.emplace_back(x, y);
        }
        return resultPoint;

    }

    vector<Point> CuckooSearchLocal( vector<Point> ifp , vector<Point> originalPoints, int bestPointIndex  )
    {

        double alpha = 0.01;
        std::random_device rd;
        std::mt19937 gen(rd());  // 使用Mersenne Twister引擎
        auto originalPointsCopy = originalPoints;
        double threshold = 0.3;

        width = ifp[1].x - ifp[0].x;
        height = ifp[1].y - ifp[0].y;

        // 创建一个分布，指定生成的范围为[1, 4]
        std::uniform_real_distribution<double> distributionx(0, 1);
        for (int i = 0; i < originalPoints.size(); ++i) {
            if ( i == bestPointIndex )
                continue;
            if ( distributionx(gen) < threshold )
            {
                shuffle( originalPointsCopy.begin(), originalPointsCopy.end(), std::mt19937( std::random_device()() ) );
                double x = originalPoints[i].x + alpha * (originalPointsCopy[0].x - originalPointsCopy[1].x);
                double y = originalPoints[i].y + alpha *(originalPointsCopy[0].y - originalPointsCopy[1].y);
                double thisx = x - ifp[0].x;
                double thisy = y - ifp[0].y;
                if ( thisx < 0 )
                {
                    auto diffX =  thisx - ::floor( thisx/width ) * width;
                    thisx = width + diffX;
                }
                if ( thisx > width )
                {
                    thisx = thisx - ::floor( thisx/width ) * width;
                }
                thisx += ifp[0].x;

                if ( thisy < 0 )
                {
                    auto diffY =  thisy - ::floor( thisy/height ) * height;
                    thisy = height + diffY;
                }
                if ( thisy > height )
                {
                    thisy = thisy - ::floor( thisy/height ) * height;
                }
                thisy += ifp[0].y;

                originalPoints[i].x = thisx;
                originalPoints[i].y = thisy;
            }
        }

        return originalPoints;

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



#endif //CALCULATENFP_CUCKOOBETA_H

//
// Created by Admin on 2023/8/31.
//
#include "caculateDepth.h"


double getDepth(Point pointTarget, Direction entryDirection, vector<LineSegment> &lineNFP) {
//    Point pointTarget( 0, 3 );
    if ( entryDirection.x != 0 )
    {
        int fullFlag = 0;
        double pointToEdgeDistance = INT64_MAX;
        for( auto thisLine : lineNFP )
        {
            if ( thisLine.theDirection.y == 0 ) continue;
            if( thisLine.startPoint.y <= pointTarget.y && pointTarget.y <= thisLine.endPoint.y || pointTarget.y >= thisLine.endPoint.y && pointTarget.y <= thisLine.startPoint.y)
            {
//                cout << endl << thisLine.startPoint.x << " " << thisLine.startPoint.y << " , " << thisLine.endPoint.x << " " << thisLine.endPoint.y << endl;
                fullFlag++;
                double interPointx = ( pointTarget.y - thisLine.startPoint.y ) * ( thisLine.theDirection.x / thisLine.theDirection.y ) + thisLine.startPoint.x;

                if ( pointTarget.y == thisLine.startPoint.y || pointTarget.y == thisLine.endPoint.y )
                {
                    interPointx =  pointTarget.y == thisLine.startPoint.y ? thisLine.startPoint.x : thisLine.endPoint.x;
                }

                if ( interPointx < pointTarget.x  && entryDirection.x > 0 )
                {
                    // from left to right
                    return pointTarget.x - interPointx;
                }
                if( interPointx > pointTarget.x && entryDirection.x < 0 )
                {
                    // from right to left
                    return  interPointx - pointTarget.x;
                }
//                cout << " the interPointx is : " << interPointx << endl;
//                double distance = pointTarget.x > interPointx ? pointTarget.x - interPointx : interPointx - pointTarget.x;
//                if ( pointToEdgeDistance > distance )
//                {
//                    pointToEdgeDistance = distance;
//                }
                if ( fullFlag == 4 )
                {
                    break;
                }

            }
        }

//        cout << " the distance from point to boundary paralleling to x-axis is : " << pointToEdgeDistance << endl;
    }

    if ( entryDirection.y != 0 )
    {
        double pointToEdgeDistance = INT64_MAX;
        int fullFlag = 0;

        for( auto thisLine : lineNFP )
        {
            if ( thisLine.theDirection.x == 0 ) continue;
            if( thisLine.startPoint.x <= pointTarget.x && pointTarget.x <= thisLine.endPoint.x || pointTarget.x >= thisLine.endPoint.x && pointTarget.x <= thisLine.startPoint.x)
            {
                fullFlag++;
                double interPointy = ( pointTarget.x - thisLine.startPoint.x ) * ( thisLine.theDirection.y / thisLine.theDirection.x ) + thisLine.startPoint.y;
                if ( pointTarget.x == thisLine.startPoint.x || pointTarget.x == thisLine.endPoint.x )
                {
                    interPointy =  pointTarget.x == thisLine.startPoint.x ? thisLine.startPoint.y : thisLine.endPoint.y;
                }

                if ( interPointy < pointTarget.y  && entryDirection.y > 0 )
                {
                    // from the bottom up
                    return pointTarget.y - interPointy ;
                }
                if ( interPointy > pointTarget.y  && entryDirection.y < 0 )
                {
                    // from the top to bottom
                    return interPointy - pointTarget.y ;
                }
//                cout << " the interPointy is : " << interPointy << endl;
//                double distance = pointTarget.y > interPointy ? pointTarget.y - interPointy : interPointy - pointTarget.y;
//                if ( pointToEdgeDistance > distance )
//                {
//                    pointToEdgeDistance = distance;
//                }
                if ( fullFlag == 4 )
                {
                    break;
                }
            }
        }


//        cout << " the distance from point to boundary paralleling to y-axis is : " << pointToEdgeDistance << endl;
    }

    return INT64_MAX;
}


double
calculateFitness(int targetIndex, vector<Direction> &allDirection, vector<double> allAngular, Direction movingPosition,
                 vector<vector<NFPset>> &allNFP) {
    double totalFitness = 0;
    double polygonMovingAng = allAngular[targetIndex];
    for (int i = 0; i < allDirection.size(); ++i) {
        if ( i == targetIndex )
            continue;
        Point relativePosition = movingPosition - allDirection[i];
        double polygonFixedAng = allAngular[i];
        int relativeIndex = ( polygonFixedAng / 90 ) * 4 + ( polygonMovingAng / 90 + 1) - 1;
        auto pointNfp = allNFP[i][targetIndex].nfpSeqence[relativeIndex].pointNfp;
        if ( Point_In_Polygon_2D( relativePosition.x, relativePosition.y, pointNfp ) )
        {
            auto & lineNFP = allNFP[i][targetIndex].nfpSeqence[relativeIndex].lineSeq;
            auto thisDepth = getDepthleast( relativePosition, lineNFP );
            totalFitness += thisDepth;

        }
    }

    return totalFitness;

}

double
calculateFitnessRotateable(int targetIndex, vector<Direction> &allDirection, vector<double> allAngular, Direction movingPosition,
                 vector<vector<NFPset>> &allNFP, double rotationAngle) {
    double totalFitness = 0;
    double polygonMovingAng = rotationAngle;
    for (int i = 0; i < allDirection.size(); ++i) {
        if ( i == targetIndex )
            continue;
        Point relativePosition = movingPosition - allDirection[i];
        double polygonFixedAng = allAngular[i];
        int relativeIndex = ( polygonFixedAng / 90 ) * 4 + ( polygonMovingAng / 90 + 1) - 1;
        auto pointNfp = allNFP[i][targetIndex].nfpSeqence[relativeIndex].pointNfp;
        if ( Point_In_Polygon_2D( relativePosition.x, relativePosition.y, pointNfp ) )
        {
            auto & lineNFP = allNFP[i][targetIndex].nfpSeqence[relativeIndex].lineSeq;
            auto thisDepth = getDepthleast( relativePosition, lineNFP );
            totalFitness += thisDepth;

        }
    }

    return totalFitness;

}


//todo
double
calFitnessRotateAndPenalty( int targetIndex,
                            vector<Direction> &allDirection,
                            vector<double> allAngular,
                            Direction movingPosition,
                            vector<vector<NFPset>> &allNFP,
                            double rotationAngle,
                            vector<vector<double>> &penalty,
                            double & maxFitness,
                            vector<double> & newUij )
 {
    double totalFitness = 0;
    double polygonMovingAng = rotationAngle;
    for (int i = 0; i < allDirection.size(); ++i) {
        if ( i == targetIndex )
            continue;
        Point relativePosition = movingPosition - allDirection[i];
        double polygonFixedAng = allAngular[i];
        int relativeIndex = ( polygonFixedAng / 90 ) * 4 + ( polygonMovingAng / 90 + 1) - 1;
        auto pointNfp = allNFP[i][targetIndex].nfpSeqence[relativeIndex].pointNfp;

        if ( Point_In_Polygon_2D( relativePosition.x, relativePosition.y, pointNfp ) )
        {
            auto & lineNFP = allNFP[i][targetIndex].nfpSeqence[relativeIndex].lineSeq;
            auto thisDepth = getDepthleast( relativePosition, lineNFP );
//            totalFitness += thisDepth;

            if ( thisDepth > maxFitness )
            {
                maxFitness = thisDepth;
            }
            double uij = penalty[i][targetIndex] + ( thisDepth / maxFitness );
            newUij[i] = uij;
            totalFitness += uij * thisDepth;

        }

    }

    return totalFitness;
}


double getDepthleast(Point pointTarget, vector<LineSegment> &lineNFP) {

    double leastDistance = INT64_MAX;
    vector<Direction> allDirection{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int i = 0; i < allDirection.size(); ++i) {
        auto thisDepth = getDepth( pointTarget, allDirection[i], lineNFP );
        if ( thisDepth < leastDistance )
        {
            leastDistance = thisDepth;
        }
    }

    return leastDistance;
}




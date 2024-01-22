//
// Created by Admin on 2023/8/31.
//
#include "geometry.h"
#include "inConcaveCai.h"
vector <LineSegment> getLineSegment(vector <PointEdge> thePointEdge, Point referencePoint, bool isFit) {
    vector<LineSegment> theLineSegment;
    if ( isFit )
    {
        for( auto & thisPointEdge : thePointEdge )
        {
            Point startingPoint = referencePoint + ( thisPointEdge.movingPoint - thisPointEdge.touchPoint );
            Point endPoint = referencePoint + ( thisPointEdge.movingPoint - thisPointEdge.touchPoint ) + thisPointEdge.thisEdge.edgeDirect;
            Direction thisDirection = thisPointEdge.thisEdge.edgeDirect;
            LineSegment thisLinesegment( startingPoint, endPoint, thisDirection );
            theLineSegment.emplace_back( thisLinesegment );
        }
    } else
    {
        for( auto & thisPointEdge : thePointEdge )
        {
            Point startingPoint = referencePoint + (thisPointEdge.touchPoint - thisPointEdge.movingPoint );
            Point endPoint = referencePoint + (thisPointEdge.touchPoint - thisPointEdge.movingPoint ) + thisPointEdge.thisEdge.edgeReverseDirect;
            Direction thisDirection = thisPointEdge.thisEdge.edgeReverseDirect;
            LineSegment thisLinesegment( startingPoint, endPoint, thisDirection );
            theLineSegment.emplace_back( thisLinesegment );
        }
    }
    return theLineSegment;
}

double calculateAngelReverse(Edge edgeFist, Edge edgeSecond) {

    auto x1 = edgeFist.edgeDirect.x;
    auto x2 = edgeSecond.edgeDirect.x;
    auto y1 = edgeFist.edgeDirect.y;
    auto y2 = edgeSecond.edgeDirect.y;
    y1 = -y1;
    x1 = -x1;
    double dotProduct = x1 * x2 + y1 * y2;
    double normA = sqrt(x1 * x1 + y1 * y1);
    double normB = sqrt(x2 * x2 + y2 * y2);
    double cosTheta = dotProduct / (normA * normB);
    double radians = acos(cosTheta);
    double degrees = radians * (180.0 / M_PI);
    if ( -y2*x1 + y1*x2 < 0 )
//        if ( y2*x1 - y1*x2 < 0 )
    {
        return 360 - degrees;
    } else
    {
        return degrees;
    }
}

bool inConcave(const vector<Point> &Points, Point p) {
    int count = 0;
    int length = Points.size();
    int i = 0;
    while (i != length - 1) {

        auto p1 = Points[i];
        auto p2 = Points[i + 1];
        if((p1.x == p2.x and p1.x== p.x) and ((p.y <=p1.y and p.y>=p2.y) or (p.y <=p2.y and p.y>=p1.y)))
            return true;
        else if ((p1.y == p2.y and p1.y == p.y) and ((p.x <=p1.x and p.x>=p2.x) or (p.x <=p2.x and p.x>=p1.x)))
            return true;
        else {
            double k = (p2.y - p1.y) / (p2.x - p1.x);
            double b = -k * p1.x + p1.y;
            double res = p.y - k*p.x - b;
            if(abs(res)<1e-7)
                return true;
        }
        if(!(p1.x < p.x and p2.x < p.x)) {
            if ((p1.y - p.y) * (p2.y - p.y) < 0)
                count += 1;
            else if ((p1.y == p.y and p2.y < p.y) or (p2.y == p.y and p1.y < p.y))
                count += 1;
        }
        i++;
    }
    if(count % 2 ==0)
        return false;
    else return true;

}



vector<LineSegment> generateNFP(Polygon thePolyFixed, Polygon thePolyMoving) {

    auto polyFixedTrack = thePolyFixed.countAngel(thePolyMoving );
    auto polyMovingTrack = thePolyMoving.countAngel(thePolyFixed );
    Point referencePoint = thePolyMoving.topPoint;
    auto lineSegmentMoving = getLineSegment(polyMovingTrack, referencePoint, true );
    auto lineSegmentFixed = getLineSegment(polyFixedTrack, referencePoint, false );

    set<Point> pointSet1;
    lineSegmentFixed.insert( lineSegmentFixed.end(), lineSegmentMoving.begin(), lineSegmentMoving.end() );

    for (int i = 0; i < lineSegmentFixed.size(); ++i) {
        for (int j = 0 ; j < lineSegmentFixed.size(); ++j) {
            LineRelation thisLineRelation( lineSegmentFixed[i], lineSegmentFixed[j] );
            auto interFlag = thisLineRelation.interSection();
            auto thisSet01 = thisLineRelation.passSetPoint01();
            auto thisSet02 = thisLineRelation.passSetPoint02();
            lineSegmentFixed[i].addNewPoint( thisSet01 );
            lineSegmentFixed[j].addNewPoint( thisSet02 );
        }
    }

    set<LineSegment> allLineSeg;
    for (int i = 0; i < lineSegmentFixed.size(); ++i) {
        auto lineSeti = lineSegmentFixed[i].getBreakPoint( );
        for( auto & thisLine : lineSeti )
        {
            allLineSeg.insert( thisLine );
        }
    }


    Point beginPoint = allLineSeg.begin()->startPoint;
    LineSegment beginLine = *allLineSeg.begin();
    for( auto theLine : allLineSeg )
    {
        if ( theLine.startPoint < beginPoint )
        {
            beginPoint = theLine.startPoint;
            beginLine = theLine;
        }
    }


    vector<LineSegment> changePoint;
    LineSegment loopLine = beginLine;
    vector<LineSegment> lineNFP;
    lineNFP.emplace_back( beginLine );
    int ii = 0;
    while( loopLine.endPoint != beginPoint )
    {
        vector<LineSegment> tmpLine;
        vector<double> lineAngel;
        for( auto thisLine : allLineSeg )
        {
            if ( loopLine.endPoint == thisLine.startPoint )
            {
                tmpLine.emplace_back( thisLine );
                auto thisAngel = calculateAngelReverse( loopLine.lineToEdge(), thisLine.lineToEdge() );
                lineAngel.emplace_back( thisAngel );
            }
        }

          if ( tmpLine.size() != 1 )

        {
            auto maxElement = max_element( lineAngel.begin(), lineAngel.end() );
            int maxIndex = distance( lineAngel.begin(), maxElement );
            loopLine = tmpLine.at( maxIndex );
        } else
        {
            loopLine = tmpLine.at(0);
        }
        lineNFP.emplace_back( loopLine );
    }

    return lineNFP;
}




void rotatePolygon(vector<Point> &polyGon, double angel) {

    for( auto & thisPoint : polyGon )
    {
        if ( angel == 90 )
        {
            Point p1( thisPoint.x * COS90 - thisPoint.y * SIN90,
                      thisPoint.x * SIN90 + thisPoint.y * COS90 );
            thisPoint = p1;
        }
        if ( angel == 180 )
        {
            Point p1( thisPoint.x * COS180 - thisPoint.y * SIN180,
                      thisPoint.x * SIN180 + thisPoint.y * COS180 );
            thisPoint = p1;
        }
        if ( angel == 270 )
        {
            Point p1( thisPoint.x * COS270 - thisPoint.y * SIN270,
                      thisPoint.x * SIN270 + thisPoint.y * COS270 );
            thisPoint = p1;
        }

    }
}

vector<Point> extractPoints(vector<LineSegment> lineNFP) {
    vector<Point> points;
    for( auto & thisLine : lineNFP )
    {
        points.emplace_back( thisLine.startPoint );
    }

    return points;
}



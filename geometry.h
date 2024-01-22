//
// Created by Admin on 2023/8/31.
//


#include "list"
#include <cmath>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include "algorithm"
#include "set"
#include "cmath"
//#include "inConcaveCai.h"
#define M_PI 3.14159265358979323846
#define COS90 0
#define COS180 (-1)
#define COS270 0

#define SIN90 1
#define SIN180 0
#define SIN270 (-1)


#ifndef CALCULATENFP_GEOMETRY_H
#define CALCULATENFP_GEOMETRY_H
using namespace std;


class Point
{
public:
    double x;
    double y;
    Point(){
        x = 0;
        y = 0;
    };
    Point( double x1, double y1 )
    {
        x = x1;
        y = y1;
    }

    Point movingDirection( Point direction )
    {
        Point newPoint = *this + direction;
        return newPoint;
    }

    void Set(double dx, double dy)
    {
        x = dx;
        y = dy;
    }

    void printPoint()
    {
        cout << x << " " << y << endl;
    }
    Point operator + ( Point otherPoint )
    {
        Point resultPoint;
        resultPoint.x = this -> x + otherPoint.x;
        resultPoint.y = this -> y + otherPoint.y;
        return resultPoint;
    }
    Point operator - ( Point otherPoint )
    {
        Point resultPoint;
        resultPoint.x = this -> x - otherPoint.x;
        resultPoint.y = this -> y - otherPoint.y;
        return resultPoint;
    }
    bool operator < ( const Point & otherPoint ) const
    {
        if ( this -> y != otherPoint.y )
        {
            return this -> y < otherPoint.y;
        } else
        {
            return this -> x < otherPoint.x;
        }
    }
    bool operator == ( const Point & otherPoint ) const
    {
        return this -> x == otherPoint.x and this -> y == otherPoint.y;
    }
    bool operator != ( const Point & otherPoint ) const
    {
        return !( *this == otherPoint );
    }
};

typedef Point Direction;
typedef vector<Point> IFP;
class Edge
{
public:
    Point pointBegin;
    Point pointEnd;
    Direction edgeDirect;
    Direction edgeReverseDirect;
    Edge(){};
    Edge( Point pointFirst, Point pointSecond )
    {
        pointBegin = pointFirst;
        pointEnd = pointSecond;
        edgeDirect = Point( pointSecond.x - pointFirst.x, pointSecond.y - pointFirst.y);
        edgeReverseDirect = Point( pointFirst.x - pointSecond.x, pointFirst.y - pointSecond.y);
    };
    void printEdgeBegin()
    {
        cout << " 头端点：" << pointBegin.x << " , " << pointBegin.y << " 尾端点：" << pointEnd.x << " , " << pointEnd.y << endl;
    }
};


class Angel
{
public:
    double angels;
    Edge inGoingEdge;
    Edge outGoingEdge;
    Angel( double thisAngel , Edge inGoingEdge1, Edge outGoingEdge1 )
    {
        angels = thisAngel;
        inGoingEdge = inGoingEdge1;
        outGoingEdge = outGoingEdge1;
    }
    Angel(){};
};


class PointEdge
{
public:
    Point touchPoint;
    Point movingPoint;
    Edge thisEdge;
    PointEdge(Point staticP, Point movingP, Edge thisE )
    {
        touchPoint = staticP;
        movingPoint = movingP;
        thisEdge = thisE;
    }

};



class LineSegment
{
private:
    void setBreakPoint ( )
    {
        breakPoint.clear();
        vector<double> lengths;
        vector<Point> cachePointCopy;
        for( auto thePoint : cachePoint )
        {
            if ( thePoint == startPoint or thePoint == endPoint )
                continue;
            cachePointCopy.emplace_back( thePoint );
        }
        for (int i = 0; i < cachePointCopy.size(); ++i) {
            lengths.emplace_back( getEdgeLength(startPoint, cachePointCopy[i] ));
        }
        auto lengthsCopy = lengths;
        vector<int> index;
        std::sort(lengthsCopy.begin(), lengthsCopy.end(),
                  []( double a, double b ){ return a < b; });
        for (int i = 0; i < lengthsCopy.size(); ++i) {
            for (int j = 0; j < lengths.size(); ++j) {
                if ( lengthsCopy[i] == lengths[j] )
                {
                    index.emplace_back( i );
                }
            }
        }

//        cout << " the size of index is " << index.size() << endl;

        breakPoint.emplace_back( startPoint );
        for (int i = 0; i < index.size(); ++i) {
            breakPoint.emplace_back( cachePointCopy[i] );
        }

        breakPoint.emplace_back( endPoint );

    }
public:
    Point startPoint;
    Point endPoint;
    Direction theDirection;
    set<Point> cachePoint;
//    set<Point> cachePointCopy;
    vector<Point> breakPoint;
    LineSegment(){};
    LineSegment ( Point stPoint, Point theDirect, Direction thisDirection )
    {
        startPoint = stPoint;
        endPoint = theDirect;
        theDirection = thisDirection;
    }
    void addNewPoint( set<Point> thisSet )
    {
        for ( auto & thisPoint : thisSet ) {

            cachePoint.insert( thisPoint );
        }
    }


    vector<LineSegment> getBreakPoint( )
    {
        setBreakPoint();
        vector<LineSegment> thisLineSegment;
        for (int i = 0; i < breakPoint.size() - 1; ++i) {
            thisLineSegment.emplace_back( LineSegment( breakPoint[i], breakPoint[i+1],
                                                       Direction( breakPoint[i+1].x - breakPoint[i].x,
                                                                  breakPoint[i+1].y - breakPoint[i].y ) ));

        }

        return thisLineSegment;
    }



    double getEdgeLength( Point & p1, Point & p2 )
    {
        double length = (p2.y - p1.y) * (p2.y - p1.y) + ( p2.x - p1.x)*( p2.x - p1.x);
        return length;
    }

    Edge lineToEdge( )
    {
        Edge thisEdge( startPoint, endPoint );
        return thisEdge;
    }

    bool operator < ( const LineSegment& otherLineSegment ) const
    {
        if ( this -> startPoint < otherLineSegment.startPoint )
        {
            return true;
        } else if ( this -> startPoint == otherLineSegment.startPoint )
        {
            return this -> endPoint < otherLineSegment.endPoint;
        } else
        {
            return false;
        }
    }

};


class LineRelation
{
private:
    bool isCommonLine( )
    {
        double slope1 = (seg1.startPoint.y - seg1.endPoint.y)*(seg2.startPoint.x - seg2.endPoint.x);
        double slope2 = (seg2.startPoint.y - seg2.endPoint.y)*(seg1.startPoint.x - seg1.endPoint.x);
        double differ = abs(slope1 - slope2);
        if ( differ < 1e-6 )
        {
            return true;
        } else
        {
            return false;
        }
    }

    bool inside(double x1,double y1,double x2,double y2,double xk,double yk){
        return (xk>=min(x1,x2)&&xk<=max(x1,x2)&&yk>=min(y1,y2)&&yk<=max(y1,y2));
    }
public:
    LineSegment seg1;
    LineSegment seg2;
    vector<LineSegment> cacheLine;
    set<Point> pointSet01;
    set<Point> pointSet02;

    LineRelation( LineSegment seg01, LineSegment seg02)
    {
        seg1 = seg01;
        seg2 = seg02;
    }


    bool lineInsideTest( )
    {

//        auto thePointSetSize = pointSet.size();
//        cout << " the originalSet size is " << originalSet.size() << endl;
        auto insideOrNot01 = inside( seg1.startPoint.x, seg1.startPoint.y, seg1.endPoint.x, seg1.endPoint.y, seg2.startPoint.x, seg2.startPoint.y);
        if ( insideOrNot01 )
        {
            pointSet01.insert( seg2.startPoint );
        }
        auto insideOrNot02 = inside( seg1.startPoint.x, seg1.startPoint.y, seg1.endPoint.x, seg1.endPoint.y, seg2.endPoint.x, seg2.endPoint.y);
        if ( insideOrNot02 )
        {
            pointSet01.insert( seg2.endPoint );
        }
        auto insideOrNot03 = inside( seg2.startPoint.x, seg2.startPoint.y, seg2.endPoint.x, seg2.endPoint.y, seg1.startPoint.x, seg1.startPoint.y);
        if ( insideOrNot03 )
        {
            pointSet02.insert( seg1.startPoint );
        }
        auto insideOrNot04 = inside( seg2.startPoint.x, seg2.startPoint.y, seg2.endPoint.x, seg2.endPoint.y, seg1.endPoint.x, seg1.endPoint.y);
        if ( insideOrNot04 )
        {
            pointSet02.insert( seg1.endPoint );
        }
        return  pointSet01.size() != 0 or pointSet02.size() != 0;
//        return thePointSetSize != pointSet.size();

    }


    bool interSection()
    {
        set<Point> originalSet;
        originalSet.insert( seg1.startPoint );
        originalSet.insert( seg1.endPoint );
        originalSet.insert( seg2.startPoint );
        originalSet.insert( seg2.endPoint );
/*
        if ( originalSet.size() <= 3 )
        {
//            cacheLine.emplace_back(seg1);
//            cacheLine.emplace_back(seg2);
            return false;
        }
*/

        double x1 = seg1.startPoint.x;
        double y1 = seg1.startPoint.y;
        double x2 = seg1.endPoint.x;
        double y2 = seg1.endPoint.y;
        double x3 = seg2.startPoint.x;
        double y3 = seg2.startPoint.y;
        double x4 = seg2.endPoint.x;
        double y4 = seg2.endPoint.y;

        if ( isCommonLine() )
        {
            return lineInsideTest();
        } else
        {
            double t1 = (double)((x3-x1)*(y4-y3)-(y3-y1)*(x4-x3))/((x2-x1)*(y4-y3)-(x4-x3)*(y2-y1));
            double t2 = (double)((x1-x3)*(y2-y1)+(y3-y1)*(x2-x1))/((x4-x3)*(y2-y1)-(x2-x1)*(y4-y3));
            if(t1>=0&&t1<=1.0&&t2>=0&&t2<=1.0)
            {
                auto newPointx = (double)(x1+t1*(x2-x1));
                auto newPointy = double(y1+t1*(y2-y1));
                Point thisPoint( newPointx, newPointy );
                pointSet01.insert( thisPoint );
                pointSet02.insert( thisPoint );
                return true;
            } else
            {
                return false;
            }
        }
    }

//    void printNewPoint( )
//    {
//        for( auto& thisPoint : pointSet )
//        {
//            cout << " this new point with x valued " << thisPoint.x << " y valued " << thisPoint.y << endl;
//        }
//    }

    set<Point> passSetPoint01( )
    {
        return pointSet01;
    }
    set<Point> passSetPoint02( )
    {
        return pointSet02;
    }


};

class Polygon
{

private:
    void rotatePointSeq(vector<Point> &polyGon, double angel) {
        auto thisDirection = movingLenght( angel );
        for( auto & thisPoint : polyGon )
        {
            if ( angel == 90 )
            {
                Point p1( thisPoint.x * COS90 - thisPoint.y * SIN90,
                          thisPoint.x * SIN90 + thisPoint.y * COS90 );
                p1 = p1 + thisDirection;
                thisPoint = p1;
            }
            if ( angel == 180 )
            {
                Point p1( thisPoint.x * COS180 - thisPoint.y * SIN180,
                          thisPoint.x * SIN180 + thisPoint.y * COS180 );
                p1 = p1 + thisDirection;
                thisPoint = p1;
            }
            if ( angel == 270 )
            {
                Point p1( thisPoint.x * COS270 - thisPoint.y * SIN270,
                          thisPoint.x * SIN270 + thisPoint.y * COS270 );
                p1 = p1 + thisDirection;
                thisPoint = p1;
            }

        }
    }

    void setTopPoint( )
    {
        topPoint = polyPoint[0];
        for ( auto & thisPoint : polyPoint ) {
            if ( topPoint.y < thisPoint.y )
            {
                topPoint = thisPoint;
            }
        }
    }

    void setRectangleBottomPoint( )
    {
        double bottomx = INT64_MAX;
        double bottomy = INT64_MAX;
        for ( auto & thisPoint : polyPoint )
        {
            if( thisPoint.x < bottomx )
            {
                bottomx = thisPoint.x;
            }
            if( thisPoint.y < bottomy )
            {
                bottomy = thisPoint.y;
            }
        }
        rectBottomPoint = Point( bottomx, bottomy );
        realBottomPointxy = Point( bottomx, bottomy );
    }

    double calculateAngel( Edge edgeFist, Edge edgeSecond )
    {

        auto x1 = edgeFist.edgeDirect.x;
        auto x2 = edgeSecond.edgeDirect.x;
        auto y1 = edgeFist.edgeDirect.y;
        auto y2 = edgeSecond.edgeDirect.y;

        double dotProduct = x1 * x2 + y1 * y2;
        double normA = sqrt(x1 * x1 + y1 * y1);
        double normB = sqrt(x2 * x2 + y2 * y2);
        double cosTheta = dotProduct / (normA * normB);
        double radians = acos(cosTheta);
        double degrees = radians * ( 180.0 / M_PI );
        if ( y2*x1 - y1*x2 < 0 )
        {
            return 360 - degrees;
        } else
        {
            return degrees;
        }
    }

    double calculateAngelReverse( Edge edgeFist, Edge edgeSecond )
    {

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
        {
            return 360 - degrees;
        } else
        {
            return degrees;
        }
    }

    void setTopPoint( Point origPoint )
    {
        topPoint = origPoint;
    }
    void setRectangleBottomPoint( Point origPoint )
    {
        rectBottomPoint = origPoint;
    }
    void setHeightAndWidth( )
    {
        double x_mini = INT64_MAX;
        double x_max  = 0;
        double y_mini = INT64_MAX;
        double y_max  = 0;
        for (int i = 0; i < polyPoint.size(); ++i) {
            if ( x_mini > polyPoint[i].x )
            {
                x_mini = polyPoint[i].x;
            }
            if ( x_max < polyPoint[i].x )
            {
                x_max = polyPoint[i].x;
            }
            if ( y_mini > polyPoint[i].y )
            {
                y_mini = polyPoint[i].y;
            }
            if( y_max < polyPoint[i].y )
            {
                y_max = polyPoint[i].y;
            }
            height = y_max - y_mini;
            width = x_max - x_mini;
        }
    }



public:
    vector<Edge> polyEdge;
    vector<Point> polyPoint;
    vector<Angel> polyAngel;
    string polyId;
    Point topPoint;
    Point rectBottomPoint;
    Point realBottomPointxy;
    vector<Direction> directionSet{{-1, 0}, { 1, 0}, { 0, 1 }, { 0, -1 }};
    vector<Point> topPointRotateSeq;
    Direction movedDirection;
    double height;
    double width;
    double leftestX;
    double leftestX90;
    Polygon( vector<Point> otherPolyPoint )
    {
        polyPoint = otherPolyPoint;
        for (int i = 0; i < otherPolyPoint.size() - 1; ++i) {
            auto thisEdge = Edge( otherPolyPoint[i], otherPolyPoint[i+1] );
            polyEdge.emplace_back( thisEdge );
        }
        auto lastestEdge = Edge( otherPolyPoint[otherPolyPoint.size() - 1 ], otherPolyPoint[0] );
        polyEdge.emplace_back( lastestEdge );

        for (int i = 0; i < polyEdge.size() - 1 ; ++i) {
            auto angel = calculateAngelReverse( polyEdge[i], polyEdge[i+1] );
            auto thisAngel = Angel( angel, polyEdge[i], polyEdge[i+1] );
            polyAngel.emplace_back( thisAngel );
        }
        auto xAngel = calculateAngelReverse(  polyEdge[polyEdge.size() - 1 ], polyEdge[0]  );
        polyAngel.emplace_back( xAngel, polyEdge[polyEdge.size() - 1 ], polyEdge[0] );
        setTopPoint();
        generateTopSeq();
        setRectangleBottomPoint();
        setHeightAndWidth();
        movedDirection = Point( 0, 0);
        leftestX = realBottomPointxy.x + width;
        leftestX90 = leftestX + (height - width )/2;
    }

    Polygon(){};

    void generateTopSeq()
    {
        topPointRotateSeq.emplace_back(topPoint );
        topPointRotateSeq.emplace_back(this ->rotatePoint(topPoint, 90 ));
        topPointRotateSeq.emplace_back(this ->rotatePoint(topPoint, 180 ));
        topPointRotateSeq.emplace_back(this ->rotatePoint(topPoint, 270 ));
    }

    vector<PointEdge> countAngel(Polygon otherPolygon )
    {
        vector<PointEdge> segmentLine;
        int i = 0;
        for ( auto thisAngel : polyAngel )
        {
            for( auto otherEdge : otherPolygon.polyEdge )
            {
                auto alphaAngel = calculateAngel(  otherEdge, thisAngel.outGoingEdge );
//                if ( alphaAngel - thisAngel.angels >= 180 or alphaAngel == 180 )
                if ( (alphaAngel >= 180 and alphaAngel <= 360 - thisAngel.angels ) or alphaAngel == 180 )
                {
                    PointEdge thisPointAndEdge(thisAngel.inGoingEdge.pointEnd, otherEdge.pointBegin, otherEdge );
                    segmentLine.emplace_back( thisPointAndEdge );
                }
            }
        }
        return segmentLine;
    }

    IFP getINP ( double outWidth, double outHeight  )
    {
        Point topRightPoint( outWidth - width, outHeight - height );
        Point bottomLeftPoint( 0, 0 );
        Direction bottomleftDirection = bottomLeftPoint - realBottomPointxy;
        Direction topRightDirection = topRightPoint - realBottomPointxy;
        Point topRight = topPoint + topRightDirection;
        Point bottomLeft = topPoint +  bottomleftDirection;
        IFP ifp;
        ifp.emplace_back( bottomLeft );
        ifp.emplace_back( topRight );
        return ifp;
    }

    void printAngel( )
    {
        int i = 1;
        for( auto thisAngel : polyAngel )
        {
            cout << "The angle of the " << i++ << " is " << thisAngel.angels << endl;
        }
    }

    void setId( string otherId )
    {
        polyId = otherId;
    }

    Point rotatePoint( Point origPoint, double angel )
    {

        auto direction = movingLenght( angel );
        auto thisPoint = origPoint;

        if ( angel == 90 )
        {
            Point p1( thisPoint.x * COS90 - thisPoint.y * SIN90,
                      thisPoint.x * SIN90 + thisPoint.y * COS90 );
            p1 = p1 + direction;
            thisPoint = p1;
        }
        if ( angel == 180 )
        {
            Point p1( thisPoint.x * COS180 - thisPoint.y * SIN180,
                      thisPoint.x * SIN180 + thisPoint.y * COS180 );
            p1 = p1 + direction;
            thisPoint = p1;
        }
        if ( angel == 270 )
        {
            Point p1( thisPoint.x * COS270 - thisPoint.y * SIN270,
                      thisPoint.x * SIN270 + thisPoint.y * COS270 );
            p1 = p1 + direction;
            thisPoint = p1;
        }
        return thisPoint;
    }

    // angular adjustment
    Direction movingLenght( double angel )
    {

        Point origRectBottomPoint;
        double diffX;
        double diffY;
        auto thisPoint = rectBottomPoint;
        if ( angel == 90 )
        {
            diffX = ( height + width ) / 2;
            diffY = ( height - width ) / 2;
            origRectBottomPoint = Point( rectBottomPoint.x + diffX, rectBottomPoint.y + diffY );

            Point p1( thisPoint.x * COS90 - thisPoint.y * SIN90,
                      thisPoint.x * SIN90 + thisPoint.y * COS90 );
            thisPoint = p1;
        }
        if ( angel == 180 )
        {
            diffX = width;
            diffY = height;
            origRectBottomPoint = Point( rectBottomPoint.x + diffX, rectBottomPoint.y + diffY );

            Point p1( thisPoint.x * COS180 - thisPoint.y * SIN180,
                      thisPoint.x * SIN180 + thisPoint.y * COS180 );
            thisPoint = p1;
        }
        if ( angel == 270 ) {
            diffX = ( width - height ) / 2;
            diffY = ( height + width ) / 2;
            origRectBottomPoint = Point( rectBottomPoint.x + diffX, rectBottomPoint.y + diffY );
            Point p1(thisPoint.x * COS270 - thisPoint.y * SIN270,
                     thisPoint.x * SIN270 + thisPoint.y * COS270);
            thisPoint = p1;
        }

        Direction thisDirection = Point( origRectBottomPoint.x - thisPoint.x, origRectBottomPoint.y - thisPoint.y );
        return thisDirection;

    }

    double findAngle( double otherWidth, double otherHeight )
    {
        if( otherWidth == height || otherHeight == width )
        {
            return 90;
        } else
        {
            return 0;
        }
    }
    // rotate polygon with a sequence of angel ( 0 180 270 )

    Polygon rotatePolygonInside( double angel )
    {
        if ( angel == 0 )
        {
            return *this;
        }
        vector<Point> tmpPointSeq = polyPoint;
        rotatePointSeq( tmpPointSeq, angel );
        auto rotatePolygon = Polygon( tmpPointSeq );
        auto rotateTopPoint = rotatePoint( topPoint, angel );
/*
        auto thisPoint = topPoint;
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
        }*/
        rotatePolygon.setTopPoint( rotateTopPoint );
        auto rotateRectangleBottomPoint = rotatePoint( rectBottomPoint, angel );
        rotatePolygon.setRectangleBottomPoint( rotateRectangleBottomPoint );
        rotatePolygon.setId(polyId);

        return rotatePolygon;

    }

    Polygon movePolygonInside( Direction movingLength )
    {
        vector<Point> tmpPointSeq = polyPoint;
        for (int i = 0; i < tmpPointSeq.size(); ++i) {
            tmpPointSeq[i] = tmpPointSeq[i] + movingLength;
        }
        auto movePolygon = Polygon( tmpPointSeq );
        movePolygon.setId(polyId);
//        movePolygon.setRectangleBottomPoint( rectBottomPoint + movingLength );
//        movePolygon.setTopPoint( topPoint + movingLength );
        return movePolygon;
    }

};

class NFP
{
public:
    vector<Point> pointNfp;
    vector<LineSegment> lineSeq;
    Point referencePoint;
    IFP ifp;
    NFP( vector<LineSegment> lineSequence )
    {
        lineSeq = lineSequence;
        for( auto & thisline : lineSequence )
        {
            pointNfp.emplace_back( thisline.startPoint );
        }
    }
    void setReferencePoint( Point thisReferencePoint )
    {
        referencePoint = thisReferencePoint;
    }

    NFP(){};
    void addIFP( IFP thisIFP )
    {
        ifp = thisIFP;
    }
};

// including all possible NFP between a fixed polygon and a moving polygon
class NFPset
{
public:
    vector<NFP> nfpSeqence;
    NFPset( NFP thisNFP )
    {
        nfpSeqence.emplace_back( thisNFP );
    }
    NFPset(){};
    void addNFP( NFP thisNFP )
    {
        nfpSeqence.emplace_back( thisNFP );
    }
    void clear( )
    {
        nfpSeqence.clear();
    }

    NFP getNFP( int index )
    {
        return nfpSeqence[index];
    }

};

vector<LineSegment> getLineSegment( vector<PointEdge> thePointEdge, Point referencePoint, bool isFit );

double calculateAngelReverse( Edge edgeFist, Edge edgeSecond );

bool inConcave(const vector<Point> &Points, Point p);
vector<Point> extractPoints(vector<LineSegment> lineNFP);
vector<LineSegment> generateNFP( Polygon thePolyFixed, Polygon thePolyMoving );
void rotatePolygon( vector<Point> & polyGon , double angel );
double getDepthleast(Point pointTarget, vector<LineSegment> &lineNFP);

//todo



#endif //CALCULATENFP_GEOMETRY_H

//#include <iostream>
#include "list"
#include <cmath>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include "algorithm"
#include "set"
#include "cmath"
#include "caculateDepth.h"
#include <string>
#include "cuckooBeta.h"
//#include "cuckoo.h"
#include "sstream"
#include "inConcaveCai.h"
#define M_PI 3.14159265358979323846
//


using namespace std;
#include "geometry.h"
#include "SkyLine.h"

void savePolygon( Polygon thisPolygon , string path )
{
    std::ofstream outPutFile( path , std::ios::app );
    if (!outPutFile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    for( auto theLine : thisPolygon.polyEdge )
    {
        outPutFile <<  theLine.pointBegin.x << " " << theLine.pointBegin.y << " " << theLine.pointEnd.x << " " << theLine.pointEnd.y << endl;
    }
    outPutFile.close();
}
void savePolygonSet( vector<Polygon> polygonSet , string path , Point targetPoint )
{
    std::ofstream outPutFile( path );
    if (!outPutFile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    for (int i = 0; i < polygonSet.size(); ++i) {
        for( auto theLine : polygonSet[i].polyEdge )
        {
            outPutFile <<  theLine.pointBegin.x << " " << theLine.pointBegin.y << " " << theLine.pointEnd.x << " " << theLine.pointEnd.y << endl;
        }
    }
    outPutFile << targetPoint.x << " " << targetPoint.y << " " << targetPoint.x  << " " << targetPoint.y << endl;
    outPutFile.close();
}


void savePoint(vector<Point>  thisPolygon , string path , Point targetPoint )
{
    std::ofstream outPutFile( path  );
    if (!outPutFile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    for (int i = 0; i < thisPolygon.size(); ++i) {
        if ( i != thisPolygon.size() - 1 )
        {
            outPutFile << thisPolygon[i].x << " " << thisPolygon[i].y << " " << thisPolygon[i+1].x << " " << thisPolygon[i+1].y << endl;
        } else
        {
            outPutFile << thisPolygon[0].x << " " << thisPolygon[0].y << " " << thisPolygon[thisPolygon.size() - 1].x << " " << thisPolygon[thisPolygon.size() - 1].y << endl;

        }
    }
    outPutFile << targetPoint.x << " " << targetPoint.y << " " << targetPoint.x  << " " << targetPoint.y << endl;

    outPutFile.close();
}

void saveLine( vector<LineSegment> thisLineSegment , string path )
{
    std::ofstream outPutFile( path , std::ios::app );
    if (!outPutFile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    for( auto theLine : thisLineSegment )
    {
        outPutFile << theLine.startPoint.x << " " << theLine.startPoint.y << " " << theLine.endPoint.x << " " << theLine.endPoint.y << endl;
    }
    outPutFile.close();
}
void saveLine( vector<LineSegment> thisLineSegment , string path , Point targetPoint )
{
    std::ofstream outPutFile( path , ios::app );
    if (!outPutFile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    for( auto theLine : thisLineSegment )
    {
        outPutFile << theLine.startPoint.x << " " << theLine.startPoint.y << " " << theLine.endPoint.x << " " << theLine.endPoint.y << endl;
    }
    outPutFile << targetPoint.x << " " << targetPoint.y << " " << targetPoint.x << " " << targetPoint.y << endl;
    outPutFile.close();
}

void savePolygonSlide( Polygon thisPolygon , string path )
{
    std::ofstream outPutFile( path , std::ios::app );
    if (!outPutFile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    for( auto theLine : thisPolygon.polyEdge )
    {
        outPutFile <<  theLine.pointBegin.x + 10 << " " << theLine.pointBegin.y << " " << theLine.pointEnd.x + 10 << " " << theLine.pointEnd.y << endl;
    }
    outPutFile.close();

}

void savePolygon( Polygon thisPolygon , string path , Point targetPoint )
{
    std::ofstream outPutFile( path , ios::app );
    if (!outPutFile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    for( auto theLine : thisPolygon.polyEdge )
    {
        outPutFile <<  theLine.pointBegin.x  << " " << theLine.pointBegin.y << " " << theLine.pointEnd.x  << " " << theLine.pointEnd.y << endl;
    }
    outPutFile << targetPoint.x  << " " << targetPoint.y << " " << targetPoint.x << " " << targetPoint.y << endl;
    outPutFile.close();

}


NFPset getNFPSet( Polygon polygon1, Polygon polygon2 , double outerContainWidth, double outerContainHeight)
{
    vector<double> angelSeq{ 0, 90, 180, 270 };
    NFPset thisSet;
    for (int i = 0; i < angelSeq.size(); ++i) {
        for (int j = 0; j < angelSeq.size(); ++j) {
            auto lineNFP = generateNFP( polygon1.rotatePolygonInside( angelSeq[i] ), polygon2.rotatePolygonInside( angelSeq[j] ) );
            auto thisRotatePolyGon = polygon2.rotatePolygonInside( angelSeq[j] );
            IFP thiNFP = thisRotatePolyGon.getINP( outerContainWidth, outerContainHeight );
            NFP thisNFP(lineNFP);
            thisNFP.addIFP( thiNFP );
            thisNFP.setReferencePoint( polygon2.rotatePolygonInside( angelSeq[j] ).topPoint );
            thisSet.addNFP( thisNFP );
        }
    }
    return thisSet;
}

vector<Polygon> readDate()
{
    std::ifstream inputFile("E:\\myNewReposity\\testLib\\calculateNFP\\fu.txt");

    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
//        return 1;
    }

    std::vector<std::vector<double>> data;

    std::string line;
    int step = 0;
    vector<double> datax;
    vector<double> datay;
    while (std::getline(inputFile, line)) {
        std::vector<double> row;
        std::vector<double> tempData;
        string num1;
        step++;
        for( char thisC : line )
        {
            if ( thisC != ' ' )
            {
                num1 += thisC;
            } else
            {
                row.emplace_back( stod(num1) );
                num1.clear();
            }
        }
        row.emplace_back( stod(num1) );
        if ( step % 2 == 0 )
        {
            datay = row;
            for (int i = 0; i < row.size(); ++i) {
                tempData.emplace_back( datax [i] );
                tempData.emplace_back( datay [i] );
                datax.clear();
                datay.clear();
            }
            data.push_back(tempData);

        } else
        {
            datax = row;
        }

    }
    inputFile.close();
    vector<vector<Point>> pointSet;
    int index = 0;
    for (const auto& row : data) {
        vector<Point> thisPolygon;
        for (int i = 0; i < row.size(); ++i) {
            if ( ( i+1 ) % 2 == 1 )
            {
                thisPolygon.emplace_back(  row[i], row[i+1] );
            }
        }
        pointSet.emplace_back( thisPolygon );
    }


    vector<Polygon> sourcePolygonSet;
    for (int i = 0; i < pointSet.size(); ++i) {
        Polygon thisPolygon( pointSet[i] );
        thisPolygon.setId( to_string(i) );
        sourcePolygonSet.emplace_back( thisPolygon );

    }
    return sourcePolygonSet;
}


int main() {


   auto sourcePolygonSet = readDate();
    vector<Item> myItemVector;
    for (int i = 0; i < sourcePolygonSet.size(); ++i) {
        Item thisItem( sourcePolygonSet[i].polyId, sourcePolygonSet[i].width, sourcePolygonSet[i].height );
        myItemVector.emplace_back( thisItem );
    }

    double outerContainWidth  = 40.5;
    double outerContainHeight = 39;
    SkyLinePacking skyLinePack(true, outerContainWidth, outerContainHeight, myItemVector );
    auto thisSolution = skyLinePack.packing();
    auto placeItemList = thisSolution.getPlaceItemList();


    ofstream ploygonFile("E:\\myNewReposity\\testLib\\calculateNFP\\coordinates01.txt");
    if (!ploygonFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    // initialize the set of polygon in the solution, which will be saved int the linset.
    for ( auto it = placeItemList.begin(); it != placeItemList.end(); ++it )
    {
        Polygon thisPolyGon;
        Point bottomPoint;
        bool isRot = false;
        if ( it -> isRot() )
        {
            thisPolyGon =  sourcePolygonSet[stoi(it -> getName())].rotatePolygonInside( 90 );
            bottomPoint = Point( it -> getX() + it -> getW() , it -> getY() );
            isRot = true;
        } else
        {
            thisPolyGon =  sourcePolygonSet[stoi(it -> getName())];
            bottomPoint = Point( it -> getX() , it -> getY() );
        }
        Direction movingLength = bottomPoint - thisPolyGon.rectBottomPoint;
        auto thisPolygon = thisPolyGon.movePolygonInside( movingLength );
        sourcePolygonSet[stoi(it -> getName())] = thisPolygon;
        for( auto theLine : thisPolygon.polyEdge )
        {
            ploygonFile <<  theLine.pointBegin.x  << " " << theLine.pointBegin.y << " " << theLine.pointEnd.x << " " << theLine.pointEnd.y << endl;
        }

    }



    // 记录最右边的坐标


    vector<vector<double>> allleftestX;

    cout << " 原理容器最大的宽度为 " << outerContainWidth << endl;
    for (int i = 0; i < sourcePolygonSet.size(); ++i) {
        vector<double> thisLeftestx;
//        cout << " 靠右的坐标为 " << sourcePolygonSet[i].leftestX <<  endl;
        thisLeftestx.emplace_back( sourcePolygonSet[i].leftestX );
        thisLeftestx.emplace_back( sourcePolygonSet[i]. leftestX90 );
        allleftestX.emplace_back(thisLeftestx);

    }

    vector<double> angelSeq{ 0, 90, 180, 270 };
    vector<Direction> orientation{{ 1, 0}, {-1, 0}, { 0, 1}, { 0, -1} };
    vector<Direction> memoryPathDirection( sourcePolygonSet.size() );
    vector<double> rotationAngle( sourcePolygonSet.size() );
    for (int i = 0; i < rotationAngle.size(); ++i) {
        rotationAngle[i] = 0;
    }

    double shrinkRate = 0.8;

    double newOuterContainWidth = outerContainWidth * shrinkRate;

    auto newPolygonSet = sourcePolygonSet;
    for (int i = 0; i < allleftestX.size(); ++i) {
        if (allleftestX[i][0] > newOuterContainWidth )
        {
            cout << " 第 " << i << " 需要向左移动 " << allleftestX[i][0] - newOuterContainWidth << endl;
            Direction rightDirection = Point(newOuterContainWidth - allleftestX[i][0], 0 );
            memoryPathDirection[i] = rightDirection;
            newPolygonSet[i] = newPolygonSet[i].movePolygonInside( rightDirection );
        }
    }

    string thisString2 = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates02.txt";
    savePolygonSet( newPolygonSet, thisString2, Point(0, 0) );



    vector<vector<NFPset>> allNFP;
    for (int i = 0; i < sourcePolygonSet.size(); ++i) {
        vector<NFPset> nfpAssembly;
        NFPset thisSet;
        for (int j = 0; j < sourcePolygonSet.size(); ++j)
        {
            if ( i == j )
            {
                NFP thisNFP;
                thisSet.addNFP( thisNFP );
                nfpAssembly.emplace_back( thisSet );
                thisSet.clear();
                continue;
            }
            for (int k = 0; k < angelSeq.size(); ++k) {
                for (int l = 0; l < angelSeq.size(); ++l) {
                    auto lineNFP = generateNFP( sourcePolygonSet[i].rotatePolygonInside( angelSeq[k] ), sourcePolygonSet[j].rotatePolygonInside( angelSeq[l] ));
                    auto thisRotatePolyGonMoving = sourcePolygonSet[j].rotatePolygonInside( angelSeq[l] );
                    auto thisRotatePolyGonFixed = sourcePolygonSet[i].rotatePolygonInside( angelSeq[k] );
                    IFP thiNFP = thisRotatePolyGonMoving.getINP( outerContainWidth, outerContainHeight );
                    NFP thisNFP(lineNFP);
                    thisNFP.addIFP( thiNFP );
                    thisNFP.setReferencePoint( sourcePolygonSet[j].rotatePolygonInside( angelSeq[l] ).topPoint );

/*                    // testingF
                    auto topPoint = sourcePolygonSet[j].rotatePolygonInside( angelSeq[l] ).topPoint;
                    string thisPath = "E:\\myNewReposity\\testLib\\calculateNFP\\PointSeq.txt";
//                    savePolygon(thisRotatePolyGon, thisPath, topPoint );
                    saveLine( lineNFP, thisPath, topPoint );
                    cout << topPoint.x << " " << topPoint.y << endl;

                    savePolygon(thisRotatePolyGonMoving, thisPath, topPoint.movingDirection(Point(1,3)) );
                    savePolygon(thisRotatePolyGonFixed, thisPath, thisRotatePolyGonFixed.topPoint );
                    const char* pythonScript = "python E:\\myNewReposity\\testLib\\calculateNFP\\drawLine.py";
                    auto pointSeq = extractPoints( lineNFP);
                    if ( Point_In_Polygon_2D(topPoint.x, topPoint.y, pointSeq  ))
                    {
                        getDepth(topPoint, Direction(1, 0), lineNFP );
                        cout << " the angular is " << angelSeq[k] << " " << angelSeq[l] << endl;
                        cout << i << " " << j << " " << k << " " << l << endl;
                        cout << topPoint.x << " " << topPoint.y << endl;
                        int result = system( pythonScript );
                        auto lineNFP = generateNFP( sourcePolygonSet[i], sourcePolygonSet[j]);
                        auto thisRotatePolyGonMoving = sourcePolygonSet[j];
                        auto thisRotatePolyGonFixed = sourcePolygonSet[i];
                        auto topPoint = sourcePolygonSet[j].topPoint;
                        saveLine( lineNFP, thisPath, topPoint );
                        savePolygon(thisRotatePolyGonMoving, thisPath, thisRotatePolyGonMoving.topPoint );
                        savePolygon(thisRotatePolyGonFixed, thisPath, thisRotatePolyGonFixed.topPoint );
                        result = system( pythonScript );
                        cout << endl;
                    }
                    */
                        thisSet.addNFP( thisNFP );
                }
            }

            nfpAssembly.emplace_back( thisSet );
            thisSet.clear();

        }
        allNFP.emplace_back( nfpAssembly );
    }

    // caculate F after the third figure is rotated 90 degree and moved to the left with ( 3, 0 );



    cout << " ============================= begin ================================= " << endl;

    auto memoryPathDirectionCopy = memoryPathDirection;

/*    for (int i = 0; i < 12; ++i) {
        int k = i - 1;
        if ( k == -1 )
        {
            k = 11;
        }
        Point startPoint = allNFP[k][i].nfpSeqence[0].referencePoint + memoryPathDirection[i];
        double beginFitness = calculateFitness( i, memoryPathDirection, rotationAngle, startPoint, allNFP );
        cout << " the testing fitness is " << beginFitness << endl;

    }*/
    vector<int> permutationSeq( allNFP.size() );
    for (int i = 0; i < permutationSeq.size(); ++i) {
        permutationSeq[i] = i;
    }
    random_device rd1;
    mt19937 gen1( rd1() );
    shuffle( permutationSeq.begin(), permutationSeq.end(), gen1 );

    auto start = std::chrono::high_resolution_clock::now();

    vector<int> seq;
    for (int i = 0; i < 12; ++i) {
        seq.emplace_back( i );
    }

    shuffle( seq.begin(), seq.end(), gen1 );

    vector<Point> bestPointSeq( sourcePolygonSet.size() );

    vector<double> finalFitness( sourcePolygonSet.size() );

/*
    for (int k = 0; k < seq.size(); ++k) {

        int j = seq[k];
        int rowIndex = j - 1;
        if ( j == 0 )
        {
            rowIndex = 11;
        }
        IFP ifp7 = allNFP[rowIndex][j].nfpSeqence[0].ifp;

        ifp7[1] = ifp7[1] + Point( -4.50, 0 );
        double w1 = ::fabs(ifp7[1].x - ifp7[0].x);
        double h2 = ::fabs(ifp7[1].y - ifp7[0].y);
        w1 -= 4.5;
        CuckooSearch1 cs( w1, 40 );
        Point startPoint = allNFP[rowIndex][j].nfpSeqence[0].referencePoint + memoryPathDirection[j];

        double theLeastFitness = INT64_MAX;
        int currentStep = 0;
        Point bestPoint;
        while( currentStep < 200 )
        {
            currentStep++;
            double beginFitness = calculateFitness( j, memoryPathDirection, rotationAngle, startPoint, allNFP );
            if ( beginFitness == 0 )
            {
                cout << " j = " << j << endl;
                bestPoint = startPoint;
                theLeastFitness = beginFitness;
                break;
            }

            auto levyPoint = cs.getCuckooLevy(100, startPoint, ifp7);
            for (int i = 0; i < levyPoint.size(); ++i) {
                double theFitness = calculateFitness( j, memoryPathDirection, rotationAngle, levyPoint[i], allNFP );
                //        cout << " the index of j is " << j << " and the fitness is " << theFitness << endl;
                if ( theLeastFitness > theFitness )
                {
                    theLeastFitness = theFitness;
                    bestPoint = levyPoint[i];
                    if ( theLeastFitness == 0 )
                    {
                        break;
                    }
                }
            }
            startPoint = bestPoint;
            if ( theLeastFitness == 0 )
            {
                break;
            }

        }
        cout << " the fitness is " << theLeastFitness << endl;
        cout << bestPoint.x << " " << bestPoint.y << endl;
        finalFitness[j] = theLeastFitness;
        memoryPathDirection[j] = bestPoint - allNFP[rowIndex][j].nfpSeqence[0].referencePoint;
        bestPointSeq[j] = bestPoint;

    }

*/

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 12; ++j) {
            seq.emplace_back( j );
        }
    }

    shuffle( seq.begin(), seq.end(), gen1 );
    seq.insert( seq.begin(), 7 );
    seq.insert( seq.begin(), 10 );
    seq.insert( seq.begin(), 11 );
/*
    for (int k = 0; k < seq.size(); ++k) {
        int j = seq[k];
        int rowIndex = j - 1;
        if ( j == 0 )
        {
            rowIndex = 11;
        }
        vector<Point> bestPoint( angelSeq.size());
        vector<double> bestAngle( angelSeq.size());
        vector<double> bestFitness( angelSeq.size(), INT64_MAX);
        vector<Direction> bestDirection( angelSeq.size());
        int angurlIndex;
        for (int kk = 0; kk < angelSeq.size(); ++kk) {
            cout << " kk = " << kk << endl;
            if ( kk == 1 )
                cout << " j = " << j << endl;
            IFP ifp7 = allNFP[rowIndex][j].nfpSeqence[kk].ifp;
            Direction shrinkDirection = Point( -outerContainWidth*(1 - shrinkRate ), 0 );
            ifp7[1] = ifp7[1] + shrinkDirection;
            double w1 = ::fabs(ifp7[1].x - ifp7[0].x);
            double h1 = ::fabs(ifp7[1].y - ifp7[0].y);
            w1 = outerContainWidth * shrinkRate;
            CuckooSearch1 cs( w1, h1 );
            Point startPoint = allNFP[rowIndex][j].nfpSeqence[kk].referencePoint + memoryPathDirection[j];
            double theLeastFitness = INT64_MAX;

            int currentStep = 0;
            while( currentStep < 200 )
            {
                currentStep++;
                double beginFitness = calculateFitnessRotateable( j, memoryPathDirection, rotationAngle, startPoint, allNFP, angelSeq[kk] );
                if ( beginFitness == 0 )
                {
                    cout << " j = " << j << endl;
                    bestPoint[kk] = startPoint;
                    theLeastFitness = beginFitness;
                    bestFitness[kk] = theLeastFitness;
                    bestAngle[kk] = angelSeq[kk];
                    bestDirection[kk] = memoryPathDirection[j];
                    break;
                }

                auto levyPoint = cs.getCuckooLevy(100, startPoint, ifp7);
                for (int i = 0; i < levyPoint.size(); ++i) {
                    double theFitness = calculateFitnessRotateable( j, memoryPathDirection, rotationAngle, levyPoint[i], allNFP , angelSeq[kk] );
                    if ( theLeastFitness > theFitness )
                    {
//                        cout << " the index of j is " << j << " angel is " << angelSeq[kk] << " and the fitness is " << theFitness << endl;
                        theLeastFitness = theFitness;
                        bestPoint[kk] = levyPoint[i];
                        bestFitness[kk] = theLeastFitness;
                        bestAngle[kk] = angelSeq[kk];
                        bestDirection[kk] = levyPoint[i] - allNFP[rowIndex][j].nfpSeqence[kk].referencePoint;
                        if ( theLeastFitness == 0 )
                        {
                            break;
                        }
                    }
                }
                startPoint = bestPoint[kk];
                if ( theLeastFitness == 0 )
                {
                    break;
                }

            }

            if ( theLeastFitness == 0 )
            {
                cout << " in break is " << theLeastFitness << endl;
                break;
            }
//            cout << " the fitness is " << theLeastFitness << endl;
//            cout << bestPoint.x << " " << bestPoint.y << endl;

        }

        auto minorIndex = min_element( bestFitness.begin(), bestFitness.end() );
        int theBestIndex = minorIndex - bestFitness.begin();
//        cout << " the best fitness is " << bestFitness[theBestIndex] << endl;
//        cout << " the best point is " << bestPoint[theBestIndex].x << " " << bestPoint[theBestIndex].y << endl;
//        cout << " the best angle is " << bestAngle[theBestIndex] << endl;
//        cout << " the best direction is " << bestDirection[theBestIndex].x << " " << bestDirection[theBestIndex].y << endl;
        finalFitness[j] = bestFitness[theBestIndex];
        rotationAngle[j] = bestAngle[theBestIndex];
        memoryPathDirection[j] = bestDirection[theBestIndex];
        bestPointSeq[j] = bestPoint[theBestIndex];


//        memoryPathDirection[j] = bestPoint - allNFP[rowIndex][j].nfpSeqence[angurlIndex].referencePoint;

    }

*/


    cout << " ================================ new start ================================== " << endl;

    vector<vector<double>> penalty( sourcePolygonSet.size() );
    for (int i = 0; i < penalty.size(); ++i) {
        for (int j = 0; j < penalty.size(); ++j) {
            penalty[i].emplace_back( 1 );
        }
    }

    double maxFitness = 1;


    for (int k = 0; k < seq.size(); ++k) {
        int j = seq[k];
        int rowIndex = j - 1;
        if ( j == 0 )
        {
            rowIndex = 11;
        }
        vector<Point> bestPoint( angelSeq.size());
        vector<double> bestAngle( angelSeq.size());
        vector<double> bestFitness( angelSeq.size(), INT64_MAX);
        vector<Direction> bestDirection( angelSeq.size());
        vector<vector<double>> uij( angelSeq.size() );
        vector<double> thisMaxFitness( angelSeq.size() );
        int angurlIndex;
        for (int kk = 0; kk < angelSeq.size(); ++kk) {
            cout << " kk = " << kk << endl;
            if ( kk == 1 )
                cout << " j = " << j << endl;
            IFP ifp7 = allNFP[rowIndex][j].nfpSeqence[kk].ifp;
            Direction shrinkDirection = Point( -outerContainWidth*(1 - shrinkRate ), 0 );
            ifp7[1] = ifp7[1] + shrinkDirection;
            double w1 = ::fabs(ifp7[1].x - ifp7[0].x);
            double h1 = ::fabs(ifp7[1].y - ifp7[0].y);
            w1 = outerContainWidth * shrinkRate;
            CuckooSearch1 cs( w1, h1 );
            Point startPoint = allNFP[rowIndex][j].nfpSeqence[kk].referencePoint + memoryPathDirection[j];
            double theLeastFitness = INT64_MAX;

            vector<double> thisuij( allNFP.size() );
            double tmpMaxFitness = maxFitness;

            int currentStep = 0;

            while( currentStep < 200 )
            {
                currentStep++;
                vector<double> tmpuij( allNFP.size() );
                double beginFitness = calFitnessRotateAndPenalty(j, memoryPathDirection, rotationAngle, startPoint, allNFP, angelSeq[kk], penalty,
                                                                 tmpMaxFitness,tmpuij);
                if ( beginFitness == 0 )
                {
                    cout << " j = " << j << endl;
                    bestPoint[kk] = startPoint;
                    theLeastFitness = beginFitness;
                    bestFitness[kk] = theLeastFitness;
                    bestAngle[kk] = angelSeq[kk];
                    bestDirection[kk] = memoryPathDirection[j];
                    uij[kk] = tmpuij;
                    thisMaxFitness [kk] = tmpMaxFitness;
                    break;
                }
                tmpMaxFitness = maxFitness;
                auto levyPoint = cs.getCuckooLevy(100, startPoint, ifp7);
                for (int i = 0; i < levyPoint.size(); ++i) {
                    double theFitness = calFitnessRotateAndPenalty( j, memoryPathDirection, rotationAngle, levyPoint[i], allNFP , angelSeq[kk], penalty, tmpMaxFitness, thisuij);
                    if ( theLeastFitness > theFitness )
                    {
//                        cout << " the index of j is " << j << " angel is " << angelSeq[kk] << " and the fitness is " << theFitness << endl;
                        theLeastFitness = theFitness;
                        bestPoint[kk] = levyPoint[i];
                        bestFitness[kk] = theLeastFitness;
                        bestAngle[kk] = angelSeq[kk];
                        bestDirection[kk] = levyPoint[i] - allNFP[rowIndex][j].nfpSeqence[kk].referencePoint;
                        thisMaxFitness[kk] = tmpMaxFitness;
                        uij[kk] = thisuij;
                        if ( theLeastFitness == 0 )
                        {
                            break;
                        }
                    }
                }
                startPoint = bestPoint[kk];
                if ( theLeastFitness == 0 )
                {
                    break;
                }

            }

            if ( theLeastFitness == 0 )
            {
                cout << " in break is " << theLeastFitness << endl;
                break;
            }
//            cout << " the fitness is " << theLeastFitness << endl;
//            cout << bestPoint.x << " " << bestPoint.y << endl;

        }

        auto minorIndex = min_element( bestFitness.begin(), bestFitness.end() );
        int theBestIndex = minorIndex - bestFitness.begin();
        finalFitness[j] = bestFitness[theBestIndex];
        rotationAngle[j] = bestAngle[theBestIndex];
        memoryPathDirection[j] = bestDirection[theBestIndex];
        bestPointSeq[j] = bestPoint[theBestIndex];
        maxFitness = thisMaxFitness[theBestIndex];

        for (int i = 0; i < penalty.size(); ++i) {
            if ( i == theBestIndex )
                continue;
            penalty[i][theBestIndex] = uij[theBestIndex][i];

        }


    }

    cout << " ================================ new end ================================== " << endl;


    cout << " ================================ second start ================================== " << endl;


   /* double maxFitness = 1;
    vector<vector<double>> penalty1( sourcePolygonSet.size() );
    for (int i = 0; i < penalty1.size(); ++i) {
        for (int j = 0; j < penalty1.size(); ++j) {
            penalty1[i].emplace_back( 1 );
        }
    }
    double maxFitness1 = 1;
    for (int k = 0; k < seq.size(); ++k) {
        int j = seq[k];
        int rowIndex = j - 1;
        if ( j == 0 )
        {
            rowIndex = 11;
        }
        vector<Point> bestPoint( angelSeq.size());
        vector<double> bestAngle( angelSeq.size());
        vector<double> bestFitness( angelSeq.size(), INT64_MAX);
        vector<Direction> bestDirection( angelSeq.size());
        vector<vector<double>> uij( angelSeq.size() );
        vector<double> thisMaxFitness( angelSeq.size() );
        int angurlIndex;
        for (int kk = 0; kk < angelSeq.size(); ++kk) {
            cout << " kk = " << kk << endl;
            if ( kk == 1 )
                cout << " j = " << j << endl;
            IFP ifp7 = allNFP[rowIndex][j].nfpSeqence[kk].ifp;
            Direction shrinkDirection = Point( -outerContainWidth*(1 - shrinkRate ), 0 );
            ifp7[1] = ifp7[1] + shrinkDirection;
            double w1 = ::fabs(ifp7[1].x - ifp7[0].x);
            double h1 = ::fabs(ifp7[1].y - ifp7[0].y);
            w1 = outerContainWidth * shrinkRate;
            CuckooSearch1 cs( w1, h1 );
            Point startPoint = allNFP[rowIndex][j].nfpSeqence[kk].referencePoint + memoryPathDirection[j];
            double theLeastFitness = INT64_MAX;

            vector<double> thisuij( allNFP.size() );
            double tmpMaxFitness = maxFitness1;

            int currentStep = 0;

            while( currentStep < 10 )
            {
                currentStep++;
                vector<double> tmpuij( allNFP.size() );

                double beginFitness = calFitnessRotateAndPenalty(j, memoryPathDirection, rotationAngle, startPoint, allNFP, angelSeq[kk], penalty1,
                                                                 tmpMaxFitness,tmpuij);
                if ( beginFitness == 0 )
                {
                    cout << " j = " << j << endl;
                    bestPoint[kk] = startPoint;
                    theLeastFitness = beginFitness;
                    bestFitness[kk] = theLeastFitness;
                    bestAngle[kk] = angelSeq[kk];
                    bestDirection[kk] = memoryPathDirection[j];
                    uij[kk] = tmpuij;
                    thisMaxFitness [kk] = tmpMaxFitness;
                    break;
                }
                tmpMaxFitness = maxFitness;
                auto levyPoint = cs.getCuckooLevy(100, startPoint, ifp7);
                for (int i = 0; i < levyPoint.size(); ++i) {
                    double theFitness = calFitnessRotateAndPenalty( j, memoryPathDirection, rotationAngle, levyPoint[i], allNFP , angelSeq[kk], penalty1, tmpMaxFitness, thisuij);
                    if ( theLeastFitness > theFitness )
                    {
//                        cout << " the index of j is " << j << " angel is " << angelSeq[kk] << " and the fitness is " << theFitness << endl;
                        theLeastFitness = theFitness;
                        bestPoint[kk] = levyPoint[i];
                        bestFitness[kk] = theLeastFitness;
                        bestAngle[kk] = angelSeq[kk];
                        bestDirection[kk] = levyPoint[i] - allNFP[rowIndex][j].nfpSeqence[kk].referencePoint;
                        thisMaxFitness[kk] = tmpMaxFitness;
                        uij[kk] = thisuij;
                        if ( theLeastFitness == 0 )
                        {
                            break;
                        }
                    }
                }
                startPoint = bestPoint[kk];
                if ( theLeastFitness == 0 )
                {
                    break;
                }

            }

            if ( theLeastFitness == 0 )
            {
                cout << " in break is " << theLeastFitness << endl;
                break;
            }
        }

        auto minorIndex = min_element( bestFitness.begin(), bestFitness.end() );
        int theBestIndex = minorIndex - bestFitness.begin();
        finalFitness[j] = bestFitness[theBestIndex];
        rotationAngle[j] = bestAngle[theBestIndex];
        memoryPathDirection[j] = bestDirection[theBestIndex];
        bestPointSeq[j] = bestPoint[theBestIndex];
        maxFitness = thisMaxFitness[theBestIndex];

        for (int i = 0; i < penalty1.size(); ++i) {
            if ( i == theBestIndex )
                continue;
            penalty1[i][theBestIndex] = uij[theBestIndex][i];

        }


    }*/


    cout << " ================================ second end ================================== " << endl;


    cout << " ================================ third start ================================== " << endl;

/*

    for (int i = 0; i < memoryPathDirection.size(); ++i) {
        memoryPathDirection[i] = Point(0,0);
    }
    vector<vector<double>> penalty2( sourcePolygonSet.size() );
    for (int i = 0; i < penalty2.size(); ++i) {
        for (int j = 0; j < penalty2.size(); ++j) {
            penalty2[i].emplace_back( 1 );
        }
    }
    double maxFitness2 = 1;
    for (int k = 0; k < seq.size(); ++k) {
        cout << " k = " << k << endl;
        int j = seq[k];
        int rowIndex = j - 1;
        if ( j == 0 )
        {
            rowIndex = 11;
        }
        vector<Point> bestPoint( angelSeq.size());
        vector<double> bestAngle( angelSeq.size());
        vector<double> bestFitness( angelSeq.size(), INT64_MAX);
        vector<Direction> bestDirection( angelSeq.size());
        vector<vector<double>> uij( angelSeq.size() );
        vector<double> thisMaxFitness( angelSeq.size() );
        int angurlIndex;
        for (int kk = 0; kk < angelSeq.size(); ++kk) {

            IFP ifp7 = allNFP[rowIndex][j].nfpSeqence[kk].ifp;
            Direction shrinkDirection = Point( -outerContainWidth*(1 - shrinkRate ), 0 );
            ifp7[1] = ifp7[1] + shrinkDirection;
            double w1 = ::fabs(ifp7[1].x - ifp7[0].x);
            double h1 = ::fabs(ifp7[1].y - ifp7[0].y);
            w1 = outerContainWidth * shrinkRate;
            CuckooSearch1 cs( w1, h1 );
//            Point startPoint = allNFP[rowIndex][j].nfpSeqence[kk].referencePoint + memoryPathDirection[j];
            double theLeastFitness = INT64_MAX;

            vector<double> thisuij( allNFP.size() );
            double tmpMaxFitness = maxFitness2;

            int currentStep = 0;
            auto cuckooPoint = cs.generateCuckoo( 15, ifp7 );
            for (int i = 0; i < cuckooPoint.size(); ++i) {
                if ( cuckooPoint[i].x > ifp7[1].x )
                {
                    cout << " cuckooPoint is " << cuckooPoint[i].x << " " << cuckooPoint[i].y << endl;
                }
            }

            double theBestGenFitness = INT64_MAX;

            while( currentStep < 400 )
            {
                currentStep++;
//                cout << "the currentStep is " << currentStep << endl;
                vector<double> tmpuij( allNFP.size() );

                int theBestIndex;
                for (int i = 0; i < cuckooPoint.size(); ++i) {
                    double beginFitness = calFitnessRotateAndPenalty(j, memoryPathDirection, rotationAngle, cuckooPoint[i], allNFP, angelSeq[kk], penalty2,
                                                                     tmpMaxFitness, tmpuij );
                    if ( theBestGenFitness > beginFitness && theBestGenFitness != 0 )
                    {
                        theBestGenFitness = beginFitness;
                        bestPointSeq[kk] = cuckooPoint[i];
                        theBestIndex = i;
                        bestPoint[kk] = cuckooPoint[i];;
                        theLeastFitness = beginFitness;
                        bestFitness[kk] = theLeastFitness;
                        bestAngle[kk] = angelSeq[kk];
                        bestDirection[kk] = cuckooPoint[i] - allNFP[rowIndex][j].nfpSeqence[kk].referencePoint;
                        uij[kk] = tmpuij;
                        thisMaxFitness [kk] = tmpMaxFitness;
                    }
                    if( theBestGenFitness == 0 )
                    {
                        break;
                    }

                }

                cuckooPoint = cs.CuckooSearchLocal( ifp7, cuckooPoint, theBestIndex );
                for (int i = 0; i < cuckooPoint.size(); ++i) {
                    if ( cuckooPoint[i].x > ifp7[1].x )
                    {
                        cout << " ifp[7][1].x is " << ifp7[1].x << endl;
                        cout << " ====== 2 ====== " << endl;
                        cout << " cuckooPoint is " << cuckooPoint[i].x << " " << cuckooPoint[i].y << endl;
                    }
                }
                for (int i = 0; i < cuckooPoint.size(); ++i) {
                    double beginFitness = calFitnessRotateAndPenalty(j, memoryPathDirection, rotationAngle, cuckooPoint[i], allNFP, angelSeq[kk], penalty2,
                                                                     tmpMaxFitness, tmpuij );
                    if ( theBestGenFitness > beginFitness && theBestGenFitness != 0 )
                    {
                        theBestGenFitness = beginFitness;
                        bestPointSeq[kk] = cuckooPoint[i];
                        theBestIndex = i;
                        bestPoint[kk] = cuckooPoint[i];;
                        theLeastFitness = beginFitness;
                        bestFitness[kk] = theLeastFitness;
                        bestAngle[kk] = angelSeq[kk];
                        bestDirection[kk] = cuckooPoint[i]  - allNFP[rowIndex][j].nfpSeqence[kk].referencePoint;
                        uij[kk] = tmpuij;
                        thisMaxFitness [kk] = tmpMaxFitness;
                    }
                    if( theBestGenFitness == 0 )
                    {
                        break;
                    }

                }

                for (int i = 0; i < cuckooPoint.size(); ++i) {
                   auto thisLevyPoint = cs.getCuckooLevy( 1, cuckooPoint[i], ifp7 );
                   cuckooPoint[i] = thisLevyPoint[0];
                }
                for (int i = 0; i < cuckooPoint.size(); ++i) {
                    if ( cuckooPoint[i].x > ifp7[1].x )
                    {
                        cout << " ifp[7][1].x is " << ifp7[1].x << endl;
                        cout << " ====== 3 ====== " << endl;
                        cout << " cuckooPoint is " << cuckooPoint[i].x << " " << cuckooPoint[i].y << endl;
                    }
                }

                for (int i = 0; i < cuckooPoint.size(); ++i) {
                    double beginFitness = calFitnessRotateAndPenalty(j, memoryPathDirection, rotationAngle, cuckooPoint[i], allNFP, angelSeq[kk], penalty2,
                                                                     tmpMaxFitness, tmpuij );
                    if ( theBestGenFitness > beginFitness && theBestGenFitness != 0 )
                    {
                        theBestGenFitness = beginFitness;
                        bestPointSeq[kk] = cuckooPoint[i];
                        theBestIndex = i;
                        bestPoint[kk] = cuckooPoint[i];;
                        theLeastFitness = beginFitness;
                        bestFitness[kk] = theLeastFitness;
                        bestAngle[kk] = angelSeq[kk];
                        bestDirection[kk] = cuckooPoint[i]  - allNFP[rowIndex][j].nfpSeqence[kk].referencePoint;
//                        cout << bestDirection[kk].x << " " << bestDirection[kk].y << endl;
                        uij[kk] = tmpuij;
                        thisMaxFitness [kk] = tmpMaxFitness;
                    }
                    if( theBestGenFitness == 0 )
                    {
                        break;
                    }

                }

                if ( theLeastFitness == 0 )
                {
                    break;
                }

            }
            if ( theLeastFitness == 0 )
            {
                break;
            }
        }

        auto minorIndex = min_element( bestFitness.begin(), bestFitness.end() );
        int theBestIndex = minorIndex - bestFitness.begin();
        finalFitness[j] = bestFitness[theBestIndex];
        rotationAngle[j] = bestAngle[theBestIndex];
        memoryPathDirection[j] = bestDirection[theBestIndex];
        bestPointSeq[j] = bestPoint[theBestIndex];
        maxFitness2  = thisMaxFitness[theBestIndex];
//        cout << bestDirection[theBestIndex].x << " " << bestDirection[theBestIndex].y << endl;

        for (int i = 0; i < penalty2.size(); ++i) {
            if ( i == theBestIndex )
                continue;
            penalty2[i][theBestIndex] = uij[theBestIndex][i];

        }


    }
*/

    cout << " ================================ third end ================================== " << endl;



    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "程序运行时间: " << duration.count() << " 秒" << std::endl;




//    cout << " the best point is " << bestPoint.x << " " << bestPoint.y << endl;
//    cout << " the best fitness is " << theLeastFitness << endl;

    for (int i = 0; i < memoryPathDirection.size(); ++i) {
        cout << memoryPathDirection[i].x << " " << memoryPathDirection[i].y << ", ";
    }
    cout << endl;
    for (int i = 0; i < 12; ++i) {
       cout << bestPointSeq[i].x << " " << bestPointSeq[i].y << " ";
    }
    cout << endl;
    for (int i = 0; i < finalFitness.size(); ++i) {
        cout << finalFitness[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < rotationAngle.size(); ++i) {
        cout << rotationAngle[i] << " ";
    }
    cout << endl;

    thisString2 = "E:\\myNewReposity\\testLib\\calculateNFP\\coordinates03.txt";
    vector<Polygon> newPolygonSet1( sourcePolygonSet.size() );
    for (int i = 0; i < 12; ++i) {
        auto thisPolygon = sourcePolygonSet[i].rotatePolygonInside( rotationAngle[i] );
        cout << thisPolygon.topPoint.x << " " << thisPolygon.topPoint.y << endl;
        newPolygonSet1[i] = thisPolygon.movePolygonInside(  memoryPathDirection[i] );

    }

    savePolygonSet( newPolygonSet1, thisString2, Point(0, 0) );

/*
    for (int i = 0; i < 12; ++i) {
        auto thisPolygon = sourcePolygonSet[i].rotatePolygonInside( rotationAngle[i] );
        newPolygonSet1[i] = thisPolygon.movePolygonInside(  memoryPathDirection[i] );
        auto fitness = calculateFitnessRotateable( i, memoryPathDirection, rotationAngle, newPolygonSet1[i].topPoint, allNFP , rotationAngle[i] );
        cout << " the final fitness is " << fitness << endl;
        cout << " i = " << i << endl;
    }*/


    for (int j = 0; j < 12; ++j) {
//        auto startPoint = newPolygonSet1[j].topPoint;
        auto startPoint = bestPointSeq[j];
        double beginFitness = calculateFitnessRotateable( j, memoryPathDirection, rotationAngle, startPoint, allNFP , rotationAngle[j] );
        cout << " the begin fitness is " << beginFitness << endl;
        cout << " j = " << j << endl;

    }


    cout << " ================================ end ================================== " << endl;




/*
    memoryPathDirectionCopy = memoryPathDirection;
    for (int j = 0; j < 12; ++j) {

        int tt = j - 1;
        if ( j == 0 )
            tt = 11;
        auto allAngular = rotationAngle;
        auto allDirection = memoryPathDirectionCopy ;
        auto targetIndex = j;
        auto movingPosition = allNFP[tt][j].nfpSeqence[0].referencePoint + memoryPathDirectionCopy[j];

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
//                cout << " i is " << i << endl;
                auto & lineNFP = allNFP[i][targetIndex].nfpSeqence[relativeIndex].lineSeq;
                auto thisDepth = getDepthleast( relativePosition, lineNFP );
                totalFitness += thisDepth;
//                cout << endl << thisDepth << endl;
                string thisPath = "E:\\myNewReposity\\testLib\\calculateNFP\\PointSeq.txt";
                auto thisPointSeq = lineNFP;
                saveLine(lineNFP, thisPath, relativePosition );
                const char* pythonScript = "python E:\\myNewReposity\\testLib\\calculateNFP\\drawLine.py";
//                int result = system( pythonScript );

            }
        }
        cout << " j = " << j << endl;
        cout << " the total fitness is " << totalFitness << endl;
    }

*/


    memoryPathDirection = memoryPathDirectionCopy;

/*
    for (int i = 0; i < 12; ++i) {
        int k = i - 1;
        if ( k == -1 )
        {
            k = 11;
        }
        Point startPoint = allNFP[k][i].nfpSeqence[0].referencePoint + memoryPathDirection[i];
        double beginFitness = calculateFitness( i, memoryPathDirection, rotationAngle, startPoint, allNFP );
        cout << " the testing fitness is " << beginFitness << endl;

    }
*/


/*
    for (int i = 0; i < permutationSeq.size(); ++i) {
        int targetPolygonIndex = permutationSeq[i];
//        cout << " try new polygon : " << targetPolygonIndex << endl;
        for (int j = 0; j < angelSeq.size(); ++j) {
//            cout << " try some new angel : " << endl;
            for (int k = 0; k < orientation.size(); ++k) {
                double thisOrientationFitness = 0;
                for (int l = 0; l < allNFP.size(); ++l) {
                    if ( l == targetPolygonIndex )
                        continue;

                    int rowIndex = targetPolygonIndex - 1;
                    if ( targetPolygonIndex == 0 ) rowIndex = 11;
                    int nfpReferencePointIndex = ( rotationAngle[j] / 90 ) * 4 + ( angelSeq[j] / 90 + 1 ) - 1;
//                    allNFP.at(rowIndex).at(targetPolygonIndex).nfpSeqence.at( nfpReferencePointIndex ).referencePoint;
                    Point targetReferencePoint = allNFP[rowIndex][targetPolygonIndex].nfpSeqence[nfpReferencePointIndex].referencePoint;
                    Direction movingDirection = position1 - targetReferencePoint;
                    auto relativeDirection = movingDirection - memoryPathDirection[ l ];
                    auto tranlationPosition = targetReferencePoint + relativeDirection;
                    if (Point_In_Polygon_2D( tranlationPosition.x, tranlationPosition.y, allNFP[l][targetPolygonIndex].nfpSeqence[nfpReferencePointIndex].pointNfp ))
                    {
                        auto lineNFP = allNFP[l][targetPolygonIndex].nfpSeqence[nfpReferencePointIndex].lineSeq;
//                        auto thisDepth = getDepth( tranlationPosition, orientation[k], lineNFP);
                        auto thisDepth = getDepthleast( tranlationPosition, lineNFP);

//                        getDepth( tranlationPosition, orientation[k], lineNFP);
//                        getDepth( tranlationPosition, orientation[k], lineNFP);
//                        getDepth( tranlationPosition, orientation[k], lineNFP);
//                        cout << " the depth is  : " << getDepth( tranlationPosition, orientation[k], lineNFP) << endl;

                        thisOrientationFitness += thisDepth;
                    }

                }
//                cout << " the fitness is  : " << thisOrientationFitness << endl;
            }
        }
    }
*/



    // 计算总的Fitness

    double totalFitness = 0;
    double polygonFixedAngel = 0;
    double polygonMovingAngel = 0;
    int referencePointIndex = ( polygonFixedAngel / 90 ) * 4 + ( polygonMovingAngel / 90 + 1 ) - 1;




    for (int i = 0; i < allleftestX.size(); ++i) {
        int k = i + 1;
        if( i == allleftestX.size() - 1 )
        {
            k = 0 ;
        }
        auto targetPoint = allNFP[k][i].nfpSeqence[referencePointIndex].referencePoint;
        auto targetPointMovedRaw = targetPoint + memoryPathDirection[i];
//        for (int j = 0; j < allNFP.size(); ++j) {
        int j = 0;
            if ( i == j ) continue;
            auto targetPointMoved = targetPointMovedRaw - memoryPathDirection[j];
            if (Point_In_Polygon_2D( targetPointMoved.x, targetPointMoved.y, allNFP[j][i].nfpSeqence[referencePointIndex].pointNfp ))
            {

//                cout << endl << endl;
//                cout << referencePointIndex << endl;
//                cout << " i = " << i << " j = " << j << endl;
//                cout << memoryPathDirection[i].x << " " << memoryPathDirection[i].y << endl;
//                cout << memoryPathDirection[j].x << " " << memoryPathDirection[j].y << endl;
//                cout << targetPointMoved.x << " " << targetPointMoved.y << endl;

                auto lineNFP = allNFP[j][i].nfpSeqence[referencePointIndex].lineSeq;
                cout << " from left to right is : " << getDepth( targetPointMoved, Direction (1, 0), lineNFP) << endl;
                cout << " from right to left is : " << getDepth( targetPointMoved, Direction (-1, 0), lineNFP)<< endl;
//                cout << " from the bottom up is : " << getDepth( targetPointMoved, Direction (0, 1), lineNFP) << endl;
//                cout << " from top to bottom is : " << getDepth( targetPointMoved, Direction (0, -1), lineNFP)<< endl;

            }

//        }

    }




    vector<Point> allPointDirrection( allNFP.size() );

    int k1 = (0/90)*4 + (180/90+1) - 1;

    auto targetPoint = allNFP[ 3- 1 ][ 3 ].nfpSeqence[k1].referencePoint;
    auto movedDirection = Point( 2, 3 );

    auto targetPointMoved = targetPoint.movingDirection( movedDirection );

    double f3 = 0;
    for (int i = 0; i < allNFP.size(); ++i) {
        if ( i == 3 )
            continue;
        auto thisLineNFP = allNFP[i][3].nfpSeqence[k1].lineSeq;
        auto thisPointNFP = allNFP[i][3].nfpSeqence[k1].pointNfp;
        auto targetPointPosition = targetPointMoved - allPointDirrection[i];

        if ( Point_In_Polygon_2D( targetPointPosition.x, targetPointPosition.y, thisPointNFP) )
        {
            auto thisDepth = getDepth( targetPointMoved, targetPointPosition, thisLineNFP );
            if( thisDepth > 40 )
            {
                cout << targetPointPosition.x << " " << targetPointPosition.y << endl;
                string thisPath = "E:\\myNewReposity\\testLib\\calculateNFP\\PointSeq.txt";
                auto thisPointSeq = thisPointNFP;
                savePoint(thisPointNFP, thisPath, targetPointPosition );
                const char* pythonScript = "python E:\\myNewReposity\\testLib\\calculateNFP\\drawLine.py";
                int result = system( pythonScript );

                cout << " this depth is " << thisDepth << endl;
            }
            f3 += thisDepth;
            cout << " this depth is " << thisDepth << endl;


        }
    }

    cout << " the fitness of the third after changing the position " << f3 << endl;
    // todo
    // if the point pass the inspection


    // todo Fittness

    // Polygon number 3 moved to a with the direction( 1, 3 ), rotate with angel 90;

    int index = 0;
    vector<Direction> movingDirection( sourcePolygonSet.size() );
    Direction d1( 0, 0 );
    int count = 1;
    for (int i = 0; i < sourcePolygonSet.size(); ++i) {
        for (int j = 0; j < allNFP.size(); ++j) {
            for (int k = 0; k < allNFP[i].size(); ++k) {
                if ( j == k ) continue;
                index = 3;
                Point thisRefPoint = allNFP[j][k].nfpSeqence[index].referencePoint;
                Point targetPoint =    thisRefPoint.movingDirection(d1 );

                string thisPath = "E:\\myNewReposity\\testLib\\calculateNFP\\PointSeq.txt";
                auto thisPointSeq = allNFP[j][k].nfpSeqence[index].pointNfp;
                savePoint(thisPointSeq, thisPath, targetPoint );

                const char* pythonScript = "python E:\\myNewReposity\\testLib\\calculateNFP\\drawLine.py";
//                int result = system( pythonScript );


//                if (inConcave( allNFP[j][k].nfpSeqence[index].pointNfp, targetPoint ))
                if ( Point_In_Polygon_2D(targetPoint.x, targetPoint.y, allNFP[j][k].nfpSeqence[index].pointNfp ))
                {
//                    cout << i << " " << j << " " << k << " " << index << endl;
//                    cout << targetPoint.x << " " << targetPoint.y << endl;

//                    cout << getDepth(targetPoint, Direction(-1, 0), allNFP[j][k].nfpSeqence[index].lineSeq ) << endl;
//                    auto depth = getDepth(targetPoint, Direction(1, 0), allNFP[j][k].nfpSeqence[index].lineSeq ) ;
//                    string thisPath = "E:\\myNewReposity\\testLib\\calculateNFP\\PointSeq.txt";
//                    auto thisPointSeq = allNFP[j][k].nfpSeqence[index].pointNfp;
//                    savePoint(thisPointSeq, thisPath, targetPoint );
//                    const char* pythonScript = "python E:\\myNewReposity\\testLib\\calculateNFP\\drawLine.py";
//                    int result = system( pythonScript );
//                    cout << count++ << endl;

//                    if ( depth > 100 )
//                    {
//                        cout << " Is point in the polygon ? " << Point_In_Polygon_2D(targetPoint.x, targetPoint.y, allNFP[j][k].nfpSeqence[index].pointNfp ) << endl;
//                        inConcave(allNFP[j][k].nfpSeqence[index].pointNfp, targetPoint );
//                        getDepth(targetPoint, Direction(1, 0), allNFP[j][k].nfpSeqence[index].lineSeq );
//                        cout << " something amazing happen !! " << endl;
//                    }
                }
            }
        }
    }


    CuckooSearch1 cs1( 45, 60);
    Point startPoint1( 0, 0 );

    std::cout << std::endl;














    return 0;
}

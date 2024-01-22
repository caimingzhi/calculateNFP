//
// Created by Admin on 2023/8/31.
//
#include "geometry.h"
#include "inConcaveCai.h"

#ifndef CALCULATENFP_CACULATEDEPTH_H
#define CALCULATENFP_CACULATEDEPTH_H
double getDepth( Point pointTarget, Direction entryDirection , vector<LineSegment> & lineNFP );
double calculateFitness ( int targetIndex, vector<Direction> & allDirection, vector<double> allAngular, Direction movingPosition , vector<vector<NFPset>> &allNFP);
double
calculateFitnessRotateable(int targetIndex, vector<Direction> &allDirection, vector<double> allAngular, Direction movingPosition,
                           vector<vector<NFPset>> &allNFP, double rotationAngle) ;
double
calFitnessRotateAndPenalty(int targetIndex, vector<Direction> &allDirection, vector<double> allAngular, Direction movingPosition,
                           vector<vector<NFPset>> &allNFP, double rotationAngle, vector<vector<double>> &penalty, double & maxFitness, vector<double> & newUij );

#endif //CALCULATENFP_CACULATEDEPTH_H

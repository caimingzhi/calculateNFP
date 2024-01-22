cmake_minimum_required(VERSION 3.24)
project(calculateNFP)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculateNFP main.cpp segmentSolution.cpp segmentSolution.h
        caculateDepth.cpp
        geometry.h
        caculateDepth.h
        geometry.cpp
        SkyLine.h inConcaveCai.h cuckoo.h inConcaveCai.cpp cuckooBeta.cpp cuckooBeta.h)

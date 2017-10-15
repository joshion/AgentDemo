#ifndef CMSKM_H
#define CMSKM_H
#include <CKm.h>

/*****************************************************
* ====================================================
#   Copyright (C)2016 All rights reserved.
#
#   Author        : betterboy
#   Email         : betterboy3@live.com
#   File Name     : master-slavekm.h
#   Last Modified : 2016-01-19 14:15
#   Describe      :
#
#   Log           :
#
# =====================================================
******************************************************/

#include <vector>
#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <iomanip>

class RectangularVectors
{
    public:
        static std::vector<std::vector<int> > ReturnRectangularIntVector(int size1, int size2)
        {
            std::vector<std::vector<int> > newIntVector(size1);
            for (int i=0; i< size1; i++)
            {
                newIntVector[i] = std::vector<int>(size2, 0);
            }
            return newIntVector;
        }
        static std::vector<std::vector<float> > ReturnRectangularFloatVector(int size1, int size2)
        {
            std::vector<std::vector<float> > newFloatVector(size1);
            for (int i=0; i<size1; i++)
            {
                newFloatVector[i] = std::vector<float>(size2, 0.0);
            }
            return newFloatVector;
        }
};

class CMsKm : public CKm
{
    public:
        static std::vector<std::vector<int> > RatedAssign(const std::vector<std::vector<float> > &mQ, const std::vector<int> &vL);
        static bool RatedAssign(const std::vector<std::vector<float> > &Q, const std::vector<int> &l,
                                std::vector<std::vector<int>> &T);
        static void TestResult();

    private:
        static int DFS(int x, int nx, int ny, std::vector<int> &visx, std::vector<int> &visy, std::vector<float> &lx, std::vector<float> &ly, std::vector<std::vector<float> > &matrix, std::vector<int> &link, std::vector<float> &slack);
        static float KM(std::vector<std::vector<float> > &matrix, std::vector<int> &link);
        static bool lIsEmpty(std::vector<int> &l);

};


#endif // CMSKM_H

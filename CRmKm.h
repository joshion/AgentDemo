
#pragma once
#include "CKm.h"
#include <limits>
#include <algorithm>

class CRmKm : public CKm
{

public:
    static vector<vector<int>> computeAssignments(vector<vector<float>> &matrix, vector<int> &RC,
                                                  vector<int> &LL, int n, vector<int> &L, vector<int> &BA);

private:
    static bool allAreCovered(vector<int> &coveredCols);

    static void reduceMatrix(vector<vector<float>> &matrix);

    static void initStars(vector<vector<float>> &costMatrix, vector<int> &starsByRow,
                          vector<int> &starsByCol, vector<int> &RC, vector<int> &LL,
                          vector<vector<int>> &infinity, int n, vector<int> &L, vector<int> &BA);

    static void coverColumnsOfStarredZeroes(vector<int> &starsByCol, vector<int> &coveredCols);

    static vector<int> primeSomeUncoveredZero(vector<vector<float>> &matrix, vector<int> &primesByRow,
                                              vector<int> &coveredRows, vector<int> &coveredCols, vector<vector<int>> &infinity);

    static void incrementSetOfStarredZeroes(vector<int> &unpairedZeroPrime, vector<int> &starsByRow, vector<int> &starsByCol,
                                            vector<int> &primesByRow, vector<int> &RC, vector<int> &LL, vector<vector<int>> &infinity,
                                            vector<vector<float>> &matrix, int n, vector<int> &L, vector<int> &BA);

    static void makeMoreZeroes(vector<vector<float>> &matrix, vector<int> &coveredRows, vector<int> &coveredCols,
                               vector<vector<int>> &infinity);
public:
    static float RatedAssign(vector<int> &L, vector<int> &BA, vector<vector<float>> &Q,
                             vector<vector<int>> &T, int m, int n);
    //需要修改成const传参 返回T矩阵
//    static vector<vector<int>> RatedAssign(const Ckm *km);
};


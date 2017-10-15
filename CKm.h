#ifndef CKM_H
#define CKM_H

#pragma once
#include <vector>
#include <QString>
using namespace std;

class CKmMatrix
{
public:
    static vector<vector<int>> intMatrix(int row, int column)   // 返回一个row*column的int矩阵,初值为0
    {
        vector<vector<int>> newVector(row);
        for (int i = 0; i < row; ++i)
        {
            newVector[i] = vector<int>(column, 0);
        }
        return newVector;
    }

    static vector<vector<float>> floatMatrix(int row, int column)   // 返回一个row*column的float矩阵,初值为0.0
    {
        vector<vector<float>> newVector(row);
        for (int i = 0; i < row; ++i)
        {
            newVector[i] = vector<float>(column, 0.0f);
        }
        return newVector;
    }
};

class CKm
{
public:
    int m_m;    //agent个数
    int m_n;    //role种类个数
    vector<QString> m_vRoleName;    //role的名字
    vector<int> m_vL;   //
    vector<int> m_vLa;
    vector<vector<float>> m_mQ;
    vector<vector<int>> m_mT;

public:
    CKm(const int m, const int n);
    void update();
    bool isKmLegal() const;   //判断Km的参数是否合法,合法返回true,否则返回false
    ~CKm();
};

#endif // CKM_H

#ifndef CJWKM_H
#define CJWKM_H
#include "CKm.h"

class CJwKm : public CKm
{
public:
    static bool RatedAssign(const vector<vector<float>> &mQ, const vector<int> &vL,
                            vector<vector<int>> &mT);  //用mQ矩阵和vL向量计算mT,计算成功返回true,否则返回false

private:
    static vector<int> selectAgent(const vector<float> vRole,
                                  const vector<float> vSort, const int need); //对每个role选择agent,返回选择结果向量

    inline static void sortVector(vector<float> &vOld)  //对vOld向量进行降序排序
    {
        sort(vOld.rbegin(), vOld.rend());
    }
    inline static void sortVector(vector<int> &vOld)  //对vOld向量进行降序排序
    {
        sort(vOld.rbegin(), vOld.rend());
    }

    static bool transposeMatrix(vector<vector<float>> &mOld);    //对矩阵进行转置,成功则返回true,否则返回false
    static bool transposeMatrix(vector<vector<int>> &mOld);    //对矩阵进行转置,成功返回ture,否则返回false
};

#endif // CJWKM_H

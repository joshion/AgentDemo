#include "CJwKm.h"

bool CJwKm::RatedAssign(const vector<vector<float>> &mQ, const vector<int> &vL,
                        vector<vector<int>> &mT)  //用mQ矩阵和vL向量计算mT,计算成功返回true,否则返回false
{
    vector<vector<float>> Q = mQ;

    // 将矩阵T的值全部置零
    if (mT.size() > 0)
    {
        for (int i = 0; i < static_cast<int>(mT.size()); ++i)
        {
            for (int j = 0; j < static_cast<int>(mT[i].size()); ++j)
            {
                mT[i][j] = 0;
            }
        }
    }

    transposeMatrix(Q); //将Q矩阵转置
    vector<vector<float>> QSorted = Q;  //存储排序后的Q矩阵;
    for (auto &vTemp : QSorted) //对QSorted的每一行进行降序排序
    {
        sortVector(vTemp);
    }

    transposeMatrix(mT);
    for(int i = 0; i < static_cast<int>(Q.size()); ++i) //对每一个role选择agnet
    {
        mT[i] = selectAgent(Q[i], QSorted[i], vL[i]);
    }
    transposeMatrix(mT);
    return true;
}

vector<int> CJwKm::selectAgent(const vector<float> vRole,
                              const vector<float> vSorted, const int need) //对每个role选择agent,返回选择结果向量
{
    //vRole的每一项为对应agnet的测试准确度
    //vSorted为排序后的测试准确度
    //need为需要的agent个数,也就是要在vRole中选择vSorted的前need项最大值
    //vRole和vSorted的项数相等且大于等于need

    vector<int> vT = vector<int>(vRole.size(), 0);  //记录选择agent的向量,1为已选择,0为不选择,初值全部为0

    int selected = 0;   //几路已选择agent的个数
    for(int i = 0; i < static_cast<int>(vRole.size()); ++i)
    {
        if (vRole[i] >= vSorted[need - 1])  //如果agent的准确度大于等于临界值则选择,下标从0开始,故减一
        {
            vT[i] = 1;
            ++selected;
        }
        if(selected >= need)    //如果已选择够了agent,则不再选择
            break;
    }
    return vT;
}

bool CJwKm::transposeMatrix(vector<vector<float>> &mOld)    //对矩阵进行转置,成功则返回true,否则返回false
{
    //  如果矩阵不符合转置要求,返回false
    if (mOld.empty())
        return false;
    for (auto vTemp : mOld)
    {
        if (vTemp.empty())
            return false;
    }

    //  创建新矩阵, 行数为mOld的列数, 列数为mOld的行数
    vector<vector<float>> mNew = CKmMatrix::floatMatrix(mOld[0].size(), mOld.size());

    for (int i = 0; i < static_cast<int>(mOld.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(mOld[i].size()); ++j)
        {
            mNew[j][i] = mOld[i][j];
        }
    }
    mOld = mNew;
    return true;
}

bool CJwKm::transposeMatrix(vector<vector<int>> &mOld)    //对矩阵进行转置,成功返回ture,否则返回false
{
    //  如果矩阵不符合转置要求,返回false
    if (mOld.empty())
        return false;
    for (auto vTemp : mOld)
    {
        if (vTemp.empty())
            return false;
    }

    //  创建新矩阵, 行数为mOld的列数, 列数为mOld的行数
    vector<vector<int>> mNew = CKmMatrix::intMatrix(mOld[0].size(), mOld.size());

    for (int i = 0; i < static_cast<int>(mOld.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(mOld[i].size()); ++j)
        {
            mNew[j][i] = mOld[i][j];
        }
    }
    mOld = mNew;
    return true;
}

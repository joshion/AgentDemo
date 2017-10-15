#include "CKm.h"

CKm::CKm(const int m = 0, const int n = 0)
    : m_m(m), m_n(n)
{
//    m_m = m;
//    m_n = n;

    m_vLa = vector<int>(m_m);
    m_vL = vector<int>(m_n);
    m_vRoleName = vector<QString>(m_n);

    m_mQ = CKmMatrix::floatMatrix(m_m, m_n);
    m_mT = CKmMatrix::intMatrix(m_m, m_n);
}

CKm::~CKm()
{

}

void CKm::update()
{
    m_vLa = vector<int>(m_m);
    m_vL = vector<int>(m_n);
    m_vRoleName = vector<QString>(m_n);

    m_mQ = CKmMatrix::floatMatrix(m_m, m_n);
    m_mT = CKmMatrix::intMatrix(m_m, m_n);
}

bool CKm::isKmLegal() const
{
    //各矩阵,向量不能为空
    if (m_m <= 0 || m_n <= 0)
        return false;

    if (m_vLa.size() <= 0 || m_vL.size() <= 0 || m_vRoleName.size() <= 0)
        return false;

    if (m_mQ.size() <= 0)
    {
        for(int i = 0; i < static_cast<int>(m_mQ.size()); ++i)
        {
            if (m_mQ[i].size() <= 0)
                return false;
        }
    }

    for (int i = 0; i < static_cast<int>(m_vL.size()); ++i) //L中元素的值范围为[1, m]
    {
        if (m_vL[i] < 1 || m_vL[i] > m_m)
            return false;
    }

    for (int i = 0; i < static_cast<int>(m_vLa.size()); ++i) //La中元素的值范围为[1, n]
    {
        if (m_vLa[i] < 1 || m_vLa[i] > m_n)
            return false;
    }

    return true;
}

#include "CRmKm.h"

vector<vector<int>> CRmKm::computeAssignments(vector<vector<float>> &matrix, vector<int> &RC,
                                                     vector<int> &LL, int n, vector<int> &L, vector<int> &BA)
{

    reduceMatrix(matrix);

    vector<int> starsByRow(matrix.size(), -1);
    vector<int> starsByCol(matrix[0].size(), -1);
    vector<int> primesByRow(matrix.size(), -1);
    vector<vector<int>> infinity = CKmMatrix::intMatrix(matrix.size(), matrix[0].size());

    vector<int> coveredRows(matrix.size());
    vector<int> coveredCols(matrix[0].size());

    initStars(matrix, starsByRow, starsByCol, RC, LL, infinity, n, L, BA);
    coverColumnsOfStarredZeroes(starsByCol, coveredCols);

    while (!allAreCovered(coveredCols))
    {

        vector<int> primedZero = primeSomeUncoveredZero(matrix, primesByRow, coveredRows, coveredCols, infinity);

        while (primedZero.empty())
        {
            makeMoreZeroes(matrix, coveredRows, coveredCols, infinity);
            primedZero = primeSomeUncoveredZero(matrix, primesByRow, coveredRows, coveredCols, infinity);
        }


        int i = primedZero[0];
        int j = primedZero[1];
        if (LL[j] < n && L[LL[j]]>1 && BA[RC[i]] > 1)
        {
            int t = j;
            int s = i;
            while (t >= 0)
            {
                if (LL[t] == LL[j])
                {
                    t--;
                }
                else
                {
                    break;
                }
            }
            while (s >= 0)
            {
                if (RC[s] == RC[i])
                {
                    s--;
                }
                else
                {
                    break;
                }
            }
            for (int k = t + 1; LL[k] <= LL[j];)
            {
                if (LL[k] == LL[j] && k != j)
                {
                    for (int h = s + 1; RC[h] <= RC[i];)
                    {
                        if (RC[h] == RC[i] && h != i && infinity[h][k] == 0)
                        {
                            infinity[h][k] = -1;
                        }
                        h++;
                        if (h == matrix.size())
                        {
                            break;
                        }
                    }
                }
                k++;
                if (k == matrix.size())
                {
                    break;
                }
            }
        }

        int columnIndex = starsByRow[primedZero[0]];
        if (-1 == columnIndex)
        {

            incrementSetOfStarredZeroes(primedZero, starsByRow, starsByCol, primesByRow, RC, LL, infinity, matrix, n, L, BA);

            for (int f = 0; f < matrix.size(); f++)
            {
                if (primesByRow[f] != -1 && LL[primesByRow[f]] < n && L[LL[primesByRow[f]]]>1 && BA[RC[f]] > 1)
                {
                    int t = primesByRow[f];
                    int s = f;
                    while (t >= 0)
                    {
                        if (LL[t] == LL[primesByRow[f]])
                        {
                            t--;
                        }
                        else
                        {
                            break;
                        }
                    }
                    while (s >= 0)
                    {
                        if (RC[s] == RC[f])
                        {
                            s--;
                        }
                        else
                        {
                            break;
                        }
                    }
                    for (int k = t + 1; LL[k] <= LL[primesByRow[f]];)
                    {
                        if (LL[k] == LL[primesByRow[f]] && k != primesByRow[f])
                        {
                            for (int h = s + 1; RC[h] <= RC[f];)
                            {
                                if (RC[h] == RC[f] && h != f && infinity[h][k] == -1)
                                {
                                    infinity[h][k] = 0;
                                }
                                h++;
                                if (h == matrix.size())
                                {
                                    break;
                                }
                            }
                        }
                        k++;
                        if (k == matrix.size())
                        {
                            break;
                        }
                    }
                }
            }
            primesByRow.assign(primesByRow.size(), -1);
            coveredRows.assign(coveredRows.size(), 0);
            coveredCols.assign(coveredCols.size(), 0);
            coverColumnsOfStarredZeroes(starsByCol, coveredCols);
        }
        else
        {
            coveredRows[primedZero[0]] = 1;
            coveredCols[columnIndex] = 0;
        }
    }

    vector<vector<int>> retval(matrix.size());
    for (int i = 0; i < starsByCol.size(); i++)
    {
        retval[i] = vector<int>{ starsByCol[i],i };
    }
    return retval;
}

bool CRmKm::allAreCovered(vector<int> &coveredCols)
{
    for (auto covered : coveredCols)
    {
        if (0 == covered)
        {
            return false;
        }
    }
    return true;
}

void CRmKm::reduceMatrix(vector<vector<float>> &matrix)
{

    for (int i = 0; i < matrix.size(); i++)
    {

        float minValInRow = numeric_limits<float>::max();
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (minValInRow > matrix[i][j])
            {
                minValInRow = matrix[i][j];
            }
        }

        for (int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] -= minValInRow;
        }
    }

    for (int i = 0; i < matrix[0].size(); i++)
    {
        float minValInCol = numeric_limits<float>::max();
        for (int j = 0; j < matrix.size(); j++)
        {
            if (minValInCol > matrix[j][i])
            {
                minValInCol = matrix[j][i];
            }
        }

        for (int j = 0; j < matrix.size(); j++)
        {
            matrix[j][i] -= minValInCol;
        }
    }
}

void CRmKm::initStars(vector<vector<float>> &costMatrix, vector<int> &starsByRow, vector<int> &starsByCol,
                             vector<int> &RC, vector<int> &LL, vector<vector<int>> &infinity,
                             int n, vector<int> &L, vector<int> &BA)
{
    vector<int> rowHasStarredZero(costMatrix.size());
    vector<int> colHasStarredZero(costMatrix[0].size());
    for (int i = 0; i < costMatrix.size(); i++)
    {
        for (int j = 0; j < costMatrix[i].size(); j++)
        {
            if (0 == costMatrix[i][j] && 0 == rowHasStarredZero[i] && 0 == colHasStarredZero[j] && infinity[i][j] == 0)
            {
                starsByRow[i] = j;
                starsByCol[j] = i;
                rowHasStarredZero[i] = 1;
                colHasStarredZero[j] = 1;

                if (LL[j] < n && L[LL[j]]>1 && BA[RC[i]] > 1)
                {
                    int t = j;
                    int s = i;
                    while (t >= 0)
                    {
                        if (LL[t] == LL[j])
                        {
                            t--;
                        }
                        else
                        {
                            break;
                        }
                    }
                    while (s >= 0)
                    {
                        if (RC[s] == RC[i])
                        {
                            s--;
                        }
                        else
                        {
                            break;
                        }
                    }
                    for (int k = t + 1; LL[k] <= LL[j];)
                    {
                        if (LL[k] == LL[j] && k != j)
                        {
                            for (int h = s + 1; RC[h] <= RC[i];)
                            {
                                if (RC[h] == RC[i] && h != i)
                                {
                                    infinity[h][k] = 1;
                                }
                                h++;
                                if (h == costMatrix.size())
                                {
                                    break;
                                }
                            }
                        }
                        k++;
                        if (k == costMatrix.size())
                        {
                            break;
                        }
                    }
                }

                break;
            }
        }
    }
}

void CRmKm::coverColumnsOfStarredZeroes(vector<int> &starsByCol, vector<int> &coveredCols)
{
    for (int i = 0; i < starsByCol.size(); i++)
    {
        coveredCols[i] = -1 == starsByCol[i] ? 0 : 1;
    }
}

vector<int> CRmKm::primeSomeUncoveredZero(vector<vector<float>> &matrix, vector<int> &primesByRow,
                                          vector<int> &coveredRows, vector<int> &coveredCols, vector<vector<int>> &infinity)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        if (1 == coveredRows[i])
        {
            continue;
        }
        for (int j = 0; j < matrix[i].size(); j++)
        {

            if (0 == matrix[i][j] && 0 == coveredCols[j] && infinity[i][j] == 0)
            {



                primesByRow[i] = j;

                return vector<int>{i, j};
            }
        }
    }
    return vector<int>();
}

void CRmKm::incrementSetOfStarredZeroes(vector<int> &unpairedZeroPrime, vector<int> &starsByRow, vector<int> &starsByCol,
                                               vector<int> &primesByRow, vector<int> &RC, vector<int> &LL,
                                               vector<vector<int>> &infinity, vector<vector<float>> &matrix,
                                               int n, vector<int> &L, vector<int> &BA)
{
    int i, j = unpairedZeroPrime[1];
    vector<vector<int>> zeroSequence = vector<vector<int>>();
    zeroSequence.push_back(unpairedZeroPrime);
    bool paired = false;
    do
    {
        i = starsByCol[j];
        paired = -1 != i;
        if (!paired)
        {
            break;
        }
        else
        {
            zeroSequence.push_back(vector<int>{i, j});
        }

        j = primesByRow[i];
        paired = -1 != j;
        if (paired)
        {
            zeroSequence.push_back(vector<int>{i, j});
        }

    } while (paired);



    for (auto zero : zeroSequence)
    {
        if (starsByRow[zero[0]] == zero[1])
        {
            if (LL[zero[1]] < n && L[LL[zero[1]]]>1 && BA[RC[zero[0]]] > 1)
            {
                int t = zero[1];
                int s = zero[0];
                while (t >= 0)
                {
                    if (LL[t] == LL[zero[1]])
                    {
                        t--;
                    }
                    else
                    {
                        break;
                    }
                }
                while (s >= 0)
                {
                    if (RC[s] == RC[zero[0]])
                    {
                        s--;
                    }
                    else
                    {
                        break;
                    }
                }
                for (int k = t + 1; LL[k] <= LL[zero[1]];)
                {
                    if (LL[k] == LL[zero[1]] && k != zero[1])
                    {
                        for (int h = s + 1; RC[h] <= RC[zero[0]];)
                        {
                            if (RC[h] == RC[zero[0]] && h != zero[0])
                            {
                                infinity[h][k] = 0;
                            }
                            h++;
                            if (h == matrix.size())
                            {
                                break;
                            }
                        }
                    }
                    k++;
                    if (k == matrix.size())
                    {
                        break;
                    }
                }
            }
        }

        if (primesByRow[zero[0]] == zero[1])
        {
            starsByRow[zero[0]] = zero[1];
            starsByCol[zero[1]] = zero[0];

            primesByRow[zero[0]] = -1;
        }

    }

    for (auto zero : zeroSequence)
    {
        if (starsByRow[zero[0]] == zero[1])
        {
            if (LL[zero[1]] < n && L[LL[zero[1]]]>1 && BA[RC[zero[0]]] > 1)
            {
                int t = zero[1];
                int s = zero[0];
                while (t >= 0)
                {
                    if (LL[t] == LL[zero[1]])
                    {
                        t--;
                    }
                    else
                    {
                        break;
                    }
                }
                while (s >= 0)
                {
                    if (RC[s] == RC[zero[0]])
                    {
                        s--;
                    }
                    else
                    {
                        break;
                    }
                }
                for (int k = t + 1; LL[k] <= LL[zero[1]];)
                {
                    if (LL[k] == LL[zero[1]] && k != zero[1])
                    {
                        for (int h = s + 1; RC[h] <= RC[zero[0]];)
                        {
                            if (RC[h] == RC[zero[0]] && h != zero[0])
                            {
                                infinity[h][k] = 1;
                            }
                            h++;
                            if (h == matrix.size())
                            {
                                break;
                            }
                        }
                    }
                    k++;
                    if (k == matrix.size())
                    {
                        break;
                    }
                }
            }
        }
    }

}

void CRmKm::makeMoreZeroes(vector<vector<float>> &matrix, vector<int> &coveredRows,
                                  vector<int> &coveredCols, vector<vector<int>> &infinity)
{
    float minUncoveredValue = numeric_limits<float>::max();
    for (int i = 0; i < matrix.size(); i++)
    {
        if (0 == coveredRows[i])
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {

                if (0 == coveredCols[j] && matrix[i][j] < minUncoveredValue && infinity[i][j] == 0)
                {
                    minUncoveredValue = matrix[i][j];
                }
            }
        }
    }

    for (int i = 0; i < coveredRows.size(); i++)
    {
        if (1 == coveredRows[i])
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                matrix[i][j] += minUncoveredValue;
            }
        }
    }

    for (int i = 0; i < coveredCols.size(); i++)
    {
        if (0 == coveredCols[i])
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                matrix[j][i] -= minUncoveredValue;
            }
        }
    }
}

float CRmKm::RatedAssign(vector<int> &L, vector<int> &BA,
                                vector<vector<float>> &Q, vector<vector<int>> &T,
                                int m, int n)
{
    // 将矩阵T的值全部置零
    if (T.size()>= 0)
    {
        for (int i = 0; i < static_cast<int>(T.size()); ++i)
        {
            for (int j = 0; j < static_cast<int>(T[i].size()); ++j)
            {
                T[i][j] = 0;
            }
        }
    }

    float v = 0.0f;
    int cnt = 0, BAcnt = 0;
    for (int i = 0; i < m; i++)
    {
        if (i < n)
        {
            cnt += L[i];
        }
        BAcnt += BA[i];
    }
    vector<int> LL(BAcnt);
    vector<int> RC(BAcnt);
    vector<vector<float>> Q1 = CKmMatrix::floatMatrix(BAcnt, n);

    if (cnt > BAcnt)
    {
        return 0.0f;
    }

    vector<int> arrL(L.begin(), L.end());
    vector<int> arrBA(BA.begin(), BA.end());
    int len = arrBA.size();
    int s = 0, zero = 0;

    for (int i = arrL.size() - 1; i >= 0; i--)
    {
        if (arrL[i] <= len)
        {
            for (int j = arrBA.size() - 1; s < arrL[i]; j--)
            {
                arrBA[j]--;
                s++;
                if (arrBA[j] == 0)
                {
                    zero++;
                }
            }
            s = 0;
            len = arrBA.size() - zero;
            sort(arrBA.begin(), arrBA.end(), less<int>());

        }
        else
        {
            return 0.0f;
        }
    }

    int index = 0;
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < L[j]; k++)
        {
            LL[index++] = j;
        }
    }
    int t = n;
    for (int k = index; k < BAcnt; k++)
    {
        LL[k] = t;
        t++;
    }

    index = 0;
    for (int j = 0; j < m; j++)
    {
        for (int k = 0; k < BA[j]; k++)
        {
            RC[index++] = j;
        }
    }

    for (int j = 0; j < n; j++)
    {
        index = 0;
        for (int i = 0; i < m; i++)
        {
            for (int k = 0; k < BA[i]; k++)
            {
                Q1[index++][j] = Q[i][j];
            }
        }
    }

    vector<vector<float>> M = CKmMatrix::floatMatrix(BAcnt, BAcnt);
    for (int i = 0; i < BAcnt; i++)
    {
        index = 0;
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < L[j]; k++)
            {
                M[i][index++] = 1 - Q1[i][j];
            }
        }
    }

    vector<vector<int>> N = computeAssignments(M, RC, LL, n, L, BA);

    for (int i = 0; i < N.size(); i++)
    {
        if (LL[N[i][1]] < n)
        {
            T[RC[N[i][0]]][LL[N[i][1]]] = 1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            v += Q[i][j] * T[i][j];
        }
    }
    return v;
}

//vector<vector<int>> CRmKm::RatedAssign(const Ckm* km)
//{
//    RatedAssign(km->m_vL, km->m_vBA, km->m_mQ, km->m_mT, km->m_m, km->m_n);
//    return km->m_mT;
//}

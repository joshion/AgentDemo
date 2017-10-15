#include "CMsKm.h"
const float inf = 0x3f3f3f;
const float EPSILON = 0.0000001;

int CMsKm::DFS(int x, int nx, int ny,
              std::vector<int> &visx, std::vector<int> &visy, std::vector<float> &lx,
              std::vector<float> &ly, std::vector<std::vector<float> > &matrix, std::vector<int> &link, std::vector<float> &slack)
{

    visx[x] = 1;

    for(int y=0; y<ny; y++)
    {
        if (visy[y])
            continue;
        float t = lx[x] + ly[y] - matrix[x][y];
        if (fabs(t - 0.0) < EPSILON)
        {
            visy[y] = 1;
            if (link[y] == -1 || DFS(link[y], nx, ny, visx, visy, lx, ly, matrix, link, slack))
            {
                link[y] = x;
                return 1;
            }
        }else if(slack[y] > t)
            slack[y] = t;
    }
    return 0;
}

float CMsKm::KM(std::vector<std::vector<float> > &matrix, std::vector<int> &link)
{
    int nx, ny;
    nx = ny = matrix.size();
    link.assign(ny, -1);
    std::vector<float> ly(ny, 0);
    std::vector<float> lx(nx, 0);
    std::vector<float> slack(ny);
    std::vector<int> visx(nx);
    std::vector<int> visy(ny);

    for (int i=0; i<nx; i++)
        for (int j=0; j<ny; j++)
            if (matrix[i][j] > lx[i])
                lx[i] = matrix[i][j];

    for (int x=0; x<nx; x++)
    {
        slack.assign(ny, inf);
        while(1)
        {
            visx.assign(nx, 0);
            visy.assign(ny, 0);
            if (DFS(x, nx, ny, visx, visy, lx, ly,matrix, link, slack))
            {
                break;
            }
            float d = inf;
            for (int i=0; i<ny; i++)
            {
                if (!visy[i] && d>slack[i])
                    d = slack[i];
            }
            for (int i=0; i<nx; i++)
            {
                if (visx[i])
                    lx[i] -= d;
            }
            for (int i=0; i<ny; i++)
            {
                if(visy[i])
                    ly[i] += d;
                else
                    slack[i] -= d;
            }
        }
    }
    float res = 0.0;
    for (int i=0; i<ny; i++)
    {
        if (link[i] > -1)
            res += matrix[link[i]][i];
    }
    return res;
}

bool CMsKm::lIsEmpty(std::vector<int> &l)
{
    for (std::vector<int>::iterator it = l.begin(); it != l.end(); it++)
    {
        if (*it > 0)
            return false;
    }
    return true;
}

bool CMsKm::RatedAssign(const std::vector<std::vector<float>> &Q, const std::vector<int> &l,
                        std::vector<std::vector<int>> &T)
{
    T = RatedAssign(Q, l);
    return true;
}

std::vector<std::vector<int> > CMsKm::RatedAssign(const std::vector<std::vector<float>> &mQ,
                                                  const std::vector<int> &vL)
{
    std::vector<std::vector<float>> Q = mQ;
    std::vector<int> l = vL;
    int agent,role;
    agent = Q.size();
    role = Q[0].size();
    int nx,ny;
    nx = ny = agent;
    std::vector<std::vector<float> > matrix = RectangularVectors::ReturnRectangularFloatVector(agent, agent);
    std::vector<std::vector<int> > T = RectangularVectors::ReturnRectangularIntVector(agent, role);
    std::vector<int> link(ny);
    while(!lIsEmpty(l))
    {
        std::vector<int> lToDispatch(role, 0);
        for (int i=0; i<role; i++)
        {
            if (l[i] > 0)
                lToDispatch[i] = l[i] - 1;
            else
                lToDispatch[i] = 0;
        }

        for (int i=0; i<role; i++)
        {
            lToDispatch[i] = l[i] - lToDispatch[i];
            l[i] = l[i] - lToDispatch[i];
        }

        if (agent >= role)
        {
            for (int i=0; i<agent; i++)
            {
                for (int j=0; j<agent; j++)
                {
                    if (lToDispatch[j]>0 && j<role)
                        matrix[i][j] = Q[i][j];
                    else
                        matrix[i][j] = EPSILON;
                }
            }
            KM(matrix, link);
            for (int i=0; i<ny; i++)
            {
                if (link[i] > -1)
                    Q[link[i]][i] = 0;
                if (i < role && lToDispatch[i])
                {
                    T[link[i]][i] = 1;
                }
            }
        }
        else
        {
            int roleCnt = role/agent;
            int roleRemain = role%agent;
            std::vector<int> tmpL1(agent, 0);
            std::vector<int> tmpL2(roleRemain, 0);
            int interval = 0;
            for (int i=0; i<roleCnt; i++)
            {
                for (int j=0; j<agent; j++)
                {
                    tmpL1[j] = lToDispatch[j + interval];
                }
                for (int i=0; i<agent; i++)
                {
                    for (int j=0; j<agent; j++)
                    {
                        if(tmpL1[j] > 0)
                            matrix[i][j] = Q[i][j+interval];
                        else
                            matrix[i][j] = EPSILON;
                    }
                }

                KM(matrix, link);
                for (int i=0; i<ny; i++)
                {
                    if (link[i] > -1)
                        Q[link[i]][i+interval] = 0;
                    if (tmpL1[i])
                    {
                        T[link[i]][i+interval] = 1;
                    }
                }
                interval += agent;
            }
            if (roleRemain > 0)
            {
                for (int i=interval; i<role; i++)
                    tmpL2[i-interval] = lToDispatch[i];
                for (int i=0; i<agent; i++)
                {
                    for (int j=0; j<agent; j++)
                    {
                        if (tmpL2[j]>0 && j<roleRemain)
                            matrix[i][j] = Q[i][j];
                        else
                            matrix[i][j] = EPSILON;
                    }
                }
                KM(matrix, link);
                for (int i=0; i<ny; i++)
                {
                    if(i < roleRemain && tmpL2[i])
                    {
                        T[link[i]][i] = 1;
                    }
                }
            }
        }
    }
    return T;
}

void CMsKm::TestResult()
{
    //Test: agent = 6, role = 3
    //Test: agent = 3, role = 6
    int agent = 3, role = 6;
    std::vector<int> l(role);
    for (int i=0; i<role; i++) {
        l[i] = rand()%2 + 1;
    }

    std::vector<std::vector<float> > Q = RectangularVectors::ReturnRectangularFloatVector(agent, role);

    //Q:Randomly initializtion
    int temp = 0;
    for (int i=0; i<agent; i++) {
        for (int j=0; j<role; j++){
            if (temp = rand() % role <role){
                Q[i][j] = (static_cast<float>(temp = rand() % 100) + 1) / 100;
            }
        }
    }

    std::cout<<"Q=:"<<std::endl;
    for (int i=0; i<agent; i++){
        for (int j=0; j<role; j++){
            std::cout<<std::setprecision(3)<<Q[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    std::vector<std::vector<int> > T = RatedAssign(Q, l);
    for (int i=0; i<agent; i++) {
        for (int j=0; j<role; j++){
            std::cout<<T[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

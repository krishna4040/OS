#include <iostream>

int main(int argc, char const *argv[])
{
    int n = 5;
    int m = 3;

    int alloc[5][3] = {
        {0,1,0},
        {2,0,0},
        {3,0,2},
        {2,1,1},
        {0,0,2}
    };

    int max[5][3] = {
        {7,5,3},
        {3,2,2},
        {9,0,2},
        {2,2,2},
        {4,3,3}
    };

    int avail[3] = {3,3,2};

    int need[3][5];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    int isProcessCompleted[] = {};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!isProcessCompleted[j])
            {
                bool flag = 0;
                for (int k = 0; k < m; k++)
                {
                    if (need[i][j] > avail[k])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (!flag)
                {
                    isProcessCompleted[j] = 1;
                    for (int k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }
                }
                
            }
            
        }
        
    }
    

    return 0;
}

#include <iostream>
#include <list>
using namespace std;

int main() 
{
    int n, k;
    int stores[100];
    int distance[100];

    cout << "n = "; cin >> n;
    cout << "k = "; cin >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> stores[i];

        if (i > 0)
        {
            distance[i - 1] = stores[i] - stores[i - 1];
        }
    }

    // splitting groups

    const int GROUP_BREAK = -1;
    int max_val, max_index;
    
    for (int i = 0; i < k - 1; i++)
    {
        max_val = INT_MIN;

        for (int j = 0; j < n - 1; j++)
        {
            if (distance[j] > max_val)
            {
                max_val = distance[j];
                max_index = j;
            }
        }

        distance[max_index] = GROUP_BREAK;
    }

    // group center and print

    int group_size = 0;

    for (int i = 0; i < n; i++)
    {
        group_size++;

        if (distance[i] == GROUP_BREAK || i == n - 1)
        {
            cout << "Grup size = " << group_size << endl;
            int groupCenterIndex = i - (group_size / 2);
            group_size = 0;

            cout << "SEF: d[" << groupCenterIndex << "] = " << stores[groupCenterIndex] << endl;
        }
    }

    // other prints

    cout << "s = ( ";
    for (int i = 0; i < n; i++) 
    {
        cout << stores[i];
        if(i != n - 1) cout << " , ";
    }
    cout << " )" << endl;

    cout << "d = ( ";
    for (int i = 0; i < n - 1; i++)
    {
        cout << distance[i];
        if (i != n - 2) cout << " , ";
    }
    cout << " )";

}

s = ( 4 , 6 , 7 , 10 , 11 , 12 , 14 , 15 , 17 , 18 , 19 )
d = ( 2 , 1 , 3 , 1 , 1 , 2 , 1 , 2 , 1 , 1 )
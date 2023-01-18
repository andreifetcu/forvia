#include <iostream>
#include <list>
using namespace std;

int main()
{
    int n, k;
    int stores[100];
    int splits[100];

    cout << "n = "; cin >> n;
    cout << "k = "; cin >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> stores[i];
    }

    const int GROUP_BREAK = -1;

    int previous_max_group_cost = INT_MAX;

    for (int split = 0; split < k - 1; split++)
    {
        int break_index = 0;

        for (int split_index = 0; split_index < n - 1; split_index++)
        {
            if (splits[split_index] == GROUP_BREAK) continue;

            //calculam toate group length cu splitul actual si cele de dinainte
            int total_groups_cost = 0;

            int curent_group_start_index = 0;
            int curent_group_size = 0;

            cout << "GRUP: ";
            for (int i = 0; i < n; i++)
            {
                curent_group_size++;

                if (i == split_index || splits[i] == GROUP_BREAK || i == n - 1)
                {
                    int groupCenterIndex = i - (curent_group_size / 2);

                    int curent_group_cost = 0;
                    for (int j = curent_group_start_index; j < curent_group_start_index + curent_group_size; j++)
                    {
                        curent_group_cost += abs(stores[groupCenterIndex] - stores[j]);
                    }

                    cout << "(" << curent_group_cost << ": " << curent_group_start_index  << " " << curent_group_start_index + curent_group_size - 1 << " ) ";

                    total_groups_cost += curent_group_cost;

                    curent_group_start_index = i + 1;
                    curent_group_size = 0;
                }
            }
            cout << endl << "TOTAL GROUPS COST: " << total_groups_cost;


            // daca e mai bun ca ce aveam inainte

            if (total_groups_cost < previous_max_group_cost)
            {
                previous_max_group_cost = total_groups_cost;
                break_index = split_index;

                cout << "<---";
            }
            cout << endl;

        }
        cout << endl;

        splits[break_index] = GROUP_BREAK;

        cout << "groups = ( ";
        for (int i = 0; i < n; i++)
        {
            cout << stores[i];
            if (i != n - 1) cout << " , ";
            if (splits[i] == GROUP_BREAK) cout << " | ";
        }
        cout << " )" << endl;
    }

    cout << "Final Groups = ( ";
    for (int i = 0; i < n; i++)
    {
        cout << stores[i];
        if (i != n - 1) cout << " , ";
        if (splits[i] == GROUP_BREAK) cout << " | ";
    }
    cout << " )" << endl;

}
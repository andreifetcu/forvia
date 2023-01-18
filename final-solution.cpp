#include <iostream>
#include <fstream>
using namespace std;

// n and k are the number of stores and warehouses
int n, k;
// store_pos is our main array of store positions
int store_pos[40];

// warehouse is used to store positions for backtracking
int warehouse[40];
// best_warehouse is used for storing our best result
int best_warehouse[40];

int best_total_cost = INT_MAX;

bool valid_item(int x)
{
    // we iterate trough the generated items and check that
    // the element at position x was not used before
    for (int i = 0; i < x; i++)
    {
        if (warehouse[x] == warehouse[i])
        {
            return false;
        }
    }
    return true;
}

void backtrack(int x)
{
    // we use backtracking to generate all possible arrangements of k items from 0 to n
    for (int i = x; i < n; ++i)
    {
        warehouse[x] = i;

        // we check if the item we used is valid
        if (valid_item(x))
        {
            // if x is equal to k it means we generated all k warehouse positions
            if (x == k)
            {
                // we now want to calculate the cost of the generated arrangement
                
                // central_index stores the index of the nearest warehouse
                int central_index = 0;
                int total_cost = 0;

                // we loop trough all the stores
                for (int i = 0; i < n; i++)
                {
                    // we check if the current nearest warehouse is not the last one
                    if (central_index < k - 1)
                    {
                        // if it's not, we check if we are closer to the next one
                        if (abs(store_pos[warehouse[central_index]] - store_pos[i]) > abs(store_pos[warehouse[central_index + 1]] - store_pos[i]))
                        {
                            // if so we make this our current warehouse
                            central_index++;
                        }
                    }

                    // we add to the total cost of this arrangement the distance to the nearest store with a warehouse 
                    total_cost += abs(store_pos[warehouse[central_index]] - store_pos[i]);
                }

                // if the total cost is smaller than our previous best, we store it and copy the warehouse positions
                if (total_cost < best_total_cost)
                {
                    best_total_cost = total_cost;

                    // copy the warehouse positions
                    for (int j = 0; j < k; j++)
                    {
                        best_warehouse[j] = warehouse[j];
                    }
                }
            }

            else backtrack(x + 1);
        }
    }
}

void read_data()
{
    // we try to open the file
    ifstream fileStream;
    fileStream.open("cofetaria.in");
    // we print an error and close the app if the file is not found
    if (!fileStream)
    {
        cout << "No file present.";
        exit(1);
    }
    // we read n and k
    fileStream >> n;
    fileStream >> k;

    // we read all the n stores
    for (int i = 0; i < n; i++)
    {
        fileStream >> store_pos[i];
    }

    fileStream.close();
}

void print_data()
{
    // we try to open the output file, and we clear it in case it was written to before
    ofstream fileStream;
    fileStream.open("cofetaria.out");
    fileStream.clear();
    
    // we first print our total cost
    fileStream << best_total_cost << endl;
    
    // we then print the warehouse positions
    for (int i = 0; i < k; i++)
    {
        fileStream << best_warehouse[i] + 1 << endl;
    }

    fileStream.close();
}   

int main() 
{
    // read the data from the file
    read_data();
    
    // call the backtracking function
    backtrack(0);
    
    // output the results
    print_data();

    system("pause");
    return 0;
}
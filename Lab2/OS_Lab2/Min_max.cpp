#include <Windows.h>
#include <iostream>
#include "ArrayStruct.h"

using namespace std;

extern double min_amount_global, max_amount_global, average_amount;
extern int min_idx, max_idx;


DWORD WINAPI min_max(LPVOID as)
{
    cout << "Thread min_max starts it's work\n";

    ArrayStruct* data = (ArrayStruct*)as;
    double max = (*data).arr[0];
    double min = (*data).arr[0];

    for (int i = 1; i < (*data).size; i++)
    {
        if (max < (*data).arr[i]) 
        {
            max = (*data).arr[i];
            max_idx = i;
        }

        if (min > (*data).arr[i]) 
        {
            min = (*data).arr[i];
            min_idx = i;
        }

        Sleep(7);
    }

    min_amount_global = min;
    max_amount_global = max;

    cout << "***Min_max thread:***\n";
    cout << "Maximum: " << max << "\nMinimum: " << min << "\n";

    cout << "Thread min_max ends it's work\n\n";

    return 0;
}

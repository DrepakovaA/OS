#include <Windows.h>
#include <iostream>
#include "ArrayStruct.h"

using namespace std;

extern double min_amount_global, max_amount_global, average_amount;
extern int min_idx, max_idx;


DWORD WINAPI average(LPVOID as)
{
    cout << "Thread average starts it's work\n\n";

    double count = 0;
    double sum = 0;
    ArrayStruct* data = (ArrayStruct*)as;

    for (int i = 0; i < (*data).size; i++) 
    {
        sum += (*data).arr[i];
        Sleep(12);
    }

    average_amount = sum / (*data).size;

    cout << "***Average thread***\n";
    cout<<"Average amount: " << average_amount << "\n";

    cout << "Thread average ends it's work\n\n";

    return 0;
}
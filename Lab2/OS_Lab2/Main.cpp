#include <Windows.h>
#include <iostream>
#include "ArrayStruct.h"

using namespace std;

double min_amount_global, max_amount_global, average_amount;
int min_idx, max_idx;

DWORD WINAPI min_max(LPVOID);
DWORD WINAPI average(LPVOID);

int main()
{
    ArrayStruct* as = new ArrayStruct;

    cout << "Enter array size:\n";
    cin >> (*as).size;
    cout << "\n";

    (*as).arr = new double[(*as).size];

    cout << "Enter elements:\n";

    for (int i = 0; i < (*as).size; i++) 
    {
        cout << "Element " << i + 1 << ": ";
        cin >> (*as).arr[i];
        cout << "\n";
    }

    HANDLE hThread_min_max = CreateThread(
        NULL,
        0,
        min_max,
        (LPVOID)as,
        0,
        NULL);

    HANDLE hThread_average = CreateThread(
        NULL,
        0,
        average,
        (LPVOID)as,
        0,
        NULL);

    WaitForSingleObject(hThread_min_max, INFINITE);
    WaitForSingleObject(hThread_average, INFINITE);

    (*as).arr[min_idx] = average_amount;
    (*as).arr[max_idx] = average_amount;

    cout << "Result: \n";

    for (int i = 0; i < (*as).size; i++) 
    {
        cout << (*as).arr[i] << "\n";
    }

    CloseHandle(hThread_average);
    CloseHandle(hThread_min_max);
    delete[](*as).arr;

    return 0;
}

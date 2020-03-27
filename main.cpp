#include <iostream>

#include "MinMaxHeap.h"

using namespace std;

int main()
{
    /*
    vector<int> arr({10, 100, 50, 2, 1, 10, 100000, 17, 18, 19, 29, 20, 1, -1});
    MinMaxHeap<int> minMaxHeap(arr);
    minMaxHeap.Insert(-1000);
    minMaxHeap.Insert(-2);
    minMaxHeap.Insert(-10000);
    minMaxHeap.Insert(2000000);
    minMaxHeap.Insert(7);

    while (minMaxHeap.GetSize())
    {
        cout << minMaxHeap.PopMax() << endl;
        cout << minMaxHeap.PopMin() << endl;

        cout << endl;
    }*/

    MinMaxHeap<int> minMaxHeap;
    minMaxHeap.Insert(100);
    minMaxHeap.Insert(200);
    minMaxHeap.Insert(400);
    minMaxHeap.Insert(800);

    while(minMaxHeap.GetSize())
    {
        cout << minMaxHeap.PopMax() << endl;
    }

    return 0;
}

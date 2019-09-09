#include <windows.h>
#include <iostream>

using namespace std;

const int SIZE_H = 10, SIZE_W = 8;

int main(){
    
     int arr[SIZE_H][SIZE_W] = {};

    arr[1][1] = 10;


    cout << arr[1][1] << endl;

    int** ptr_arr = (int**)arr;

    cout << ptr_arr[1][1] << endl;

    return 0;
}
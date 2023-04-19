#include <iostream>
#include <vector>
#include "Sort.h"
using namespace std;

int main(){
    cout << endl;
    vector<int> nums{3,44,38,5,47,15,36,26,27,2,46,4,19,50,48};
    Sort* sort = new Sort();

    sort->bubbleSort(nums);

    sort->insertionSort(nums);

    sort->shellSort(nums);

    sort->selectionSort(nums);

    sort->heapSort(nums);

    vector<int> res = sort->mergeSort(nums);
    cout << "MergeSort Result:";
    for(int i=0;i<res.size();i++){
            cout << res[i] << ' ';
        }
    cout << endl;

    sort->countingSort(nums);
    
    sort->bucketSort(nums);
    
    sort->radixSort(nums);

    //快排我使用了引用传递，所以排完序后会使nums会变得有序，所以放在最后演示
    //其他排序算法我使用值传递，每次调用完不会改变nums，所以可以重复使用nums
    sort->quickSort(nums,0,nums.size()-1);
    cout << "QuickSort Result:";
    for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
    cout << endl;
}
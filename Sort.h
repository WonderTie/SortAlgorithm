#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Sort
{
    //划分函数，用于将数组划分为左右两部分，并返回基准的位置
    static int partition(vector<int>& nums, int left, int right){
        int pivot = left; //设置初始基准为第一个元素
        int index = pivot + 1; //index指向大于基准元素的第一个元素
        int tmp;
        for(int i = index ; i <=right; i++){ //遍历数组中每一个元素
            if(nums[i] < nums[pivot]){ //如果当前元素小于基准元素
                tmp = nums[i]; //交换当前元素与index指向的元素
                nums[i] = nums[index];
                nums[index] = tmp;
                index++;
            }
        }
        //将基准元素放到index-1位置
        //index-1左边是所有小于基准的元素，右边是所有大于基准的元素
        tmp = nums[index-1];
        nums[index-1] = nums[pivot];
        nums[pivot] = tmp;
        return index;
    }
    
    //归并排序合并两个有序区间
    static vector<int> merge(vector<int>& left, vector<int>& right){
        vector<int> result;
        int leftIndex = 0;
        int rightIndex = 0;
        while(leftIndex<left.size()&&rightIndex<right.size()){
            if(left[leftIndex] < right[rightIndex]){
                result.push_back(left[leftIndex++]);
            }
            else{
                result.push_back(right[rightIndex++]);
            }
        }
        while (leftIndex<left.size())
        {
            result.push_back(left[leftIndex++]);
        }
        while (rightIndex<right.size())
        {
            result.push_back(right[rightIndex++]);
        }
        return result;
    }

public:  
    /*---------------------------交换排序---------------------------*/
    //冒泡排序
    void bubbleSort(vector<int> nums){
        //外层循环控制比较轮数，共进行 nums.size() - 1 轮比较
        for(int i = 0;i<nums.size();i++){
            //内层循环控制每轮比较的次数
            //每轮比较完之后，会将最大元素冒泡到无序区最右边，所以比较次数每轮递减
            for(int j = 0;j<nums.size()-i-1;j++){
                if(nums[j] > nums[j+1]){
                    int tmp = nums[j+1];
                    nums[j+1] = nums[j];
                    nums[j] = tmp;
                }
            }
        }
        cout << "BubbleSort Result:" ;
        for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
        cout << endl;
    }
    
    //快速排序
    void quickSort(vector<int>& nums,int left,int right){
        if(left<right){ //当left小于right时，说明还有元素要排序
            //划分数组并得到基准元素的位置
            int partitionIndex = partition(nums, left, right);
            quickSort(nums,left, partitionIndex-1); //递归的排序左边部分
            quickSort(nums,partitionIndex, right);  //递归的排序右半部分
        }
    }

    /*---------------------------插入排序---------------------------*/
    //简单插入排序
    void insertionSort(vector<int> nums){
        int len = nums.size();
        int preIndex, cur;
        //从第2个数开始插入排序
        for(int i=1;i<len;i++){
            preIndex= i-1;
            cur = nums[i];
            //比较当前数和前面已经排序好的数
            while(preIndex>=0 && nums[preIndex]>cur){
                nums[preIndex+1] = nums[preIndex]; //将已排序数后移
                preIndex--;
            }
            nums[preIndex+1] = cur; //将当前数插入正确位置
        }
        cout << "InsertionSort Result:" ;
        for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
        cout << endl;
    }
    
    //希尔排序(改进的插入排序)
    void shellSort(vector<int> nums){
        int len = nums.size();
        int gap = len/2;  //初始间隔为待排序数组的一半
        int preIndex, cur;
        for(; gap>0; gap=gap/2 ){ //不断缩小间隔
            for(int i=0;i<len;i+=gap){ //以间隔为步长进行插入排序
                preIndex = i-gap; //与当前元素比较的前一个元素的位置
                cur = nums[i]; //记录当前元素
                while(preIndex>=0 && cur < nums[preIndex]){ //在已排序区间内查找插入位置
                    nums[preIndex+gap] = nums[preIndex]; //将比当前元素大的位置向后移
                    preIndex-=gap; 
                }
                nums[preIndex+gap] = cur; //插入当前元素
            }
        }
        //输出排序结果
        cout << "ShellSort Result:" ;
        for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
        cout << endl;
    }

    /*---------------------------选择排序---------------------------*/
    //简单选择排序
    void selectionSort(vector<int> nums){
        int len = nums.size();
        int minIndex;   //保存无序区中最小数的索引
        int tmp;
        for(int i=0;i<len-1;i++){
            minIndex = i;
            //i之前为有序区，i之后为无序区
            for(int j=i+1;j<len;j++){
                if(nums[j] < nums[minIndex]){ //寻找最小的数
                    minIndex = j; //将最小数的索引保存
                }
            }
            //将无序区中的最小元素放在有序区结尾
            tmp = nums[i];
            nums[i] = nums[minIndex];
            nums[minIndex] = tmp;
        }
        cout << "SelectionSort Result:" ;
        for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
        cout << endl;
    }

    //堆排序
    void heapSort(vector<int> nums){
        int len = nums.size();
        //建立大顶堆
        for(int i=len/2-1;i>=0;i--){
            int parent = i; //当前节点
            int child = 2*i+1; //左孩子
            while (child < len)
            {
                //右孩子存在且右孩子值大于左孩子的值
                if(child+1 < len && nums[child+1] > nums[child]){
                    child++;
                }
                //当前节点的值大于等于左右孩子节点的值
                if(nums[parent] >= nums[child]){
                    break;
                }
                //将当前节点与左右孩子中较大的节点交换
                swap(nums[parent],nums[child]);
                //当前节点下移
                parent = child;
                //下移后的左孩子节点
                child = 2*parent + 1;
            }  
        }

        //排序
        for(int i=len-1;i>0;i--){
            //将堆顶元素与当前未排序的最后一个元素交换
            swap(nums[0],nums[i]);
            //前i-1个元素重新构造最大堆
            int parent = 0;
            int child = 2*parent+1;
            while(child < i){
                if (child + 1 < i && nums[child + 1] > nums[child]) {
                    child++;
                }
                if (nums[parent] >= nums[child]) {
                    break;
                }
                swap(nums[parent], nums[child]);
                parent = child;
                child = 2 * parent + 1;
            }
        }
        //输出结果
        cout << "heapSort Result:" ;
        for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
        cout << endl;
    }

    /*---------------------------归并排序---------------------------*/
    vector<int> mergeSort(vector<int>& nums){
        int len = nums.size();
        if(len<2) return nums; //数组长度为1，不用排序
        int middle = len/2;
        vector<int> left(nums.begin(),nums.begin()+middle);
        vector<int> right(nums.begin()+middle, nums.end());
        vector<int> res1 = mergeSort(left); //给左区间排序
        vector<int> res2 = mergeSort(right); //给右区间排序
        return merge(res1,res2); //合并
    }

    /*--------------------------非比较排序--------------------------*/
    //计数排序
    void countingSort(vector<int> nums){
        //获取待排序元素中的最小值
        int minValue = *min_element(nums.begin(),nums.end());
        //获取待排序元素中的最大值
        int maxValue = *max_element(nums.begin(),nums.end());
        //构建一个可以容纳最小值到最大值范围内所有整数的桶
        vector<int> bucket (maxValue-minValue+1,0);
        //将待排序元素存储到桶的对应下标处：下标i处的元素值为i+minValue
        for(int i=0;i<nums.size();i++){
            bucket[nums[i]-minValue]++;
        }
        int startIndex = 0;
        //按照下标从低到高依次取出桶中的元素放入结果数组中
        for(int j=0;j<bucket.size();j++){
            while(bucket[j]>0){
                nums[startIndex++] = j+minValue;
                bucket[j]--;
            }
        }
        cout << "CountingSort Result:" ;
        for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
        cout << endl;
    }

    //桶排序
    void bucketSort(vector<int> nums){
        int minValue = *min_element(nums.begin(),nums.end());
        int maxValue = *max_element(nums.begin(),nums.end());
        int bucketsize = 5; //每个桶的容量
        int bucketCount =((maxValue-minValue)/bucketsize)+1; //计算桶的数量
        vector<vector<int>> buckets(bucketCount);
        //通过映射函数将每个元素分配到对应的桶中
        for(int i=0;i<nums.size();i++){
            int bucketIndex = (nums[i]-minValue)/bucketsize;
            buckets[bucketIndex].push_back(nums[i]);
        }
        //分别对每个桶内元素排序
        for(int i=0;i<bucketCount;i++){
            sort(buckets[i].begin(),buckets[i].end());
        }
        //将各个桶中的数据合并
        int k=0;
        for(int i=0;i<bucketCount;i++){
            for(int j=0;j<buckets[i].size();j++){
                nums[k++] = buckets[i][j];
            }
        }
        //输出结果
        cout << "BucketSort Result:" ;
        for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
        cout << endl;
    }

    //基数排序
    void radixSort(vector<int> nums) {
        //获取待排元素中的最大值
        int maxNum = *max_element(nums.begin(),nums.end());
        int digit = 0;
        while (maxNum != 0) {
            maxNum /= 10;
            digit++; // 计算最大数有多少位
        }

        int mod = 10, div = 1;
        vector<vector<int>> bucket(10);

        for (int i = 0; i < digit; i++, mod *= 10, div *= 10) {
            for (int j = 0; j < nums.size(); j++) {
                int index = nums[j] % mod / div; // 计算每个数当前位的值
                bucket[index].push_back(nums[j]); // 将数放入对应的桶中
            }
            int k = 0;
            for (int j = 0; j < bucket.size(); j++) {
                for (int m = 0; m < bucket[j].size(); m++) {
                    nums[k++] = bucket[j][m]; // 将桶中的数按顺序放回原数组
                }
                bucket[j].clear(); // 清空桶
            }
        }
        //输出结果
        cout << "RadixSort Result:" ;
        for(int i=0;i<nums.size();i++){
            cout << nums[i] << ' ';
        }
        cout << endl;
    }
};

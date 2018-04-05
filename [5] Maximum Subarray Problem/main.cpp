//Maximum Subarray Problem
#include <iostream>
#include <string>
#include <climits>
#include <ctime>
using namespace std;

int resultArr[2];
clock_t timer;

int readTime(clock_t t){
    cout << "It took " << t << " clicks (" << t / (long double) (CLOCKS_PER_SEC / 1000) << "ms) to calculate. " << endl << endl;
    return 0;
}

int bruteForce(int A[]){
    int profitBuyDay, profitSellDay, profit;
    for (int i = 0; i < 17; i++){
        for (int j = i; j < 17; j++){
            //cout << "Buy on day " << i << " for $" << A[i];
            //cout << " and sell on day " << j << " for $" << A[j] << ". Profit: $" << A[j]-A[i] << "." << endl;
            if (A[j]-A[i] > profit){
                profit = A[j]-A[i];
                profitBuyDay = i;
                profitSellDay = j;
            }
        }
    }
    cout << endl << "Buy on day " << profitBuyDay << " and sell on day " << profitSellDay << " to make a maximum profit of $" << profit << "." << endl << endl;
    return 0;
}

int findMaxCrossing(int A[], int low, int mid, int high){
    int maxLeft, maxRight;
    int leftSum = INT_MIN;
    int sum = 0;
    for (int i = mid; i>= low; i--){
    sum += A[i];
        if (sum > leftSum){
        leftSum = sum;
        maxLeft = i;
        }
    }
    int rightSum = INT_MIN;
    sum = 0;
    for (int j = mid + 1; j <= high; j++){
    sum += A[j];
        if (sum > rightSum){
        rightSum = sum;
        maxRight = j+1;
        }
    }
    resultArr[0] = maxLeft;
    resultArr[1] = maxRight;
    return (leftSum + rightSum);
}

int findMax(int A[], int low, int high){
    if (high == low){
    return A[low];
    }
    else{
    int mid = low + ((high - low) / 2);
    int leftSum = findMax(A, low, mid);
    int rightSum = findMax(A, mid + 1, high);
    int crossSum = findMaxCrossing(A, low, mid, high);
        if (leftSum >= rightSum && leftSum >= crossSum){
        return leftSum;
        }
        else if (rightSum >= leftSum && rightSum >= crossSum){
        return rightSum;
        }
        else{ 
        return crossSum;
        }
    }
}

int main(){
    int price[]={100,113,110,85,105,102,86,63,1,101,94,106,101,79,94,90,97};
    int diff[16];
    cout << "First Differences: |";
    for (int i=0; i<16; i++)
    {
        diff[i]=price[i+1]-price[i];
        cout << diff[i] << "|";
    }
    cout << endl;
    cout << endl << "----------Divide and Conquer----------" << endl;
    timer = clock();
    int profit = findMax(diff, 1, 15);
    timer = clock() - timer;
    cout << "Buy on day " << resultArr[0] << " and sell on day " << resultArr[1] << " to make a maximum profit of $" << profit << "." << endl << endl;
    readTime(timer);
    timer = 0;
    cout << "-------------Brute Force--------------" << endl;
    timer = clock();
    bruteForce(price);
    timer = clock() - timer;
    readTime(timer);
    return 0;
}



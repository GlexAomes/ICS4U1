//Rod Cutting Problem
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <ctime>

using namespace std;

class rods
{
	int prices[11];
	int r[11];
	int s[11];

	public:
	rods(){
		prices[0]=0;
		prices[1]=1;
		prices[2]=5;
		prices[3]=8;
		prices[4]=9;
		prices[5]=10;
		prices[6]=17;
		prices[7]=17;
		prices[8]=20;
		prices[9]=24;
		prices[10]=30;
		r[0]=0;
		r[1]=0;
		r[2]=0;
		r[3]=0;
		r[4]=0;
		r[5]=0;
		r[6]=0;
		r[7]=0;
		r[8]=0;
		r[9]=0;
		r[10]=0;
		s[0]=0;
		s[1]=0;
		s[2]=0;
		s[3]=0;
		s[4]=0;
		s[5]=0;
		s[6]=0;
		s[7]=0;
		s[8]=0;
		s[9]=0;
		s[10]=0;
	}

//here you have the methods that your class can do
// cut recursively top down
	int cutRodRecursiveTopDown(int n);
	int bottomUpCutRod(int n);
	int extendedBottomUpCutRod(int n);
	int printCutRodSolution(int n);
};

int rods::bottomUpCutRod(int n){
    int r[n];
    r[0] = 0;
    for (int j = 1; j <=n; j++){
        int q = INT_MIN;
        for (int i = 1; i <=j; i++){
            q = max(q, prices[i] + r[j-i]);
            r[j] = q;
        }
    }
    return r[n];
}

int rods::extendedBottomUpCutRod(int n){
    for(int j = 1; j <= n; j++){
        int q = INT_MIN;
        for(int i = 1; i <= j; i++){
            if (q < prices[i] + r[j-i]){
                q = prices[i] + r[j-i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return 0;
}

int rods::printCutRodSolution(int n){
    cout << "Profit: $" << r[n] << endl;
    cout << "Cuts: " << endl;
    while(n > 0){
    cout << s[n] << endl;
    n -= s[n];
    }
    return 0;
}

int rods::cutRodRecursiveTopDown(int n){
	if (n==0){return 0;}
	int q = INT_MIN;
	for (int i=1; i<=n; i++){
		q = max(q,prices[i]+cutRodRecursiveTopDown(n-i));
	}
	return q;
}

int main()
{
	int howManyInches = 7;
	rods myRods;
	clock_t time, diffTime;
	
	cout << "----------Recursive Top Down----------" << endl; //Following is for recursive topdown
	time = clock();
	cout << "Profit: $" << myRods.cutRodRecursiveTopDown(howManyInches) << endl;
    diffTime = clock() - time;
    long double timeInMilliseconds = diffTime / (long double) (CLOCKS_PER_SEC / 1000);
	cout << "Using cutRodRecursiveTopDown to calculate best price for length " << howManyInches << "\" took " << timeInMilliseconds << "ms to calculate." << endl << endl;
	time = 0; diffTime = 0;
	
	cout << "--------------Bottom Up--------------" << endl; //Following is for bottom up
	time = clock();
	cout << "Profit: $" << myRods.bottomUpCutRod(howManyInches) << endl;
    diffTime = clock() - time;
    timeInMilliseconds = diffTime / (long double) (CLOCKS_PER_SEC / 1000);
	cout << "Using bottomUpCut to calculate best price for length " << howManyInches << "\" took " << timeInMilliseconds << "ms to calculate." << endl << endl;
	time = 0; diffTime = 0;
	
	cout << "----------Extended Bottom Up----------" << endl; //Following is for extended bottom up
	time = clock();
	myRods.extendedBottomUpCutRod(howManyInches);
	myRods.printCutRodSolution(howManyInches);
    diffTime = clock() - time;
    timeInMilliseconds = diffTime / (long double) (CLOCKS_PER_SEC / 1000);
	cout << "Using extendedBottomUpCut to calculate best price for length " << howManyInches << "\" took " << timeInMilliseconds << "ms to calculate." << endl << endl;
	time = 0; diffTime = 0;
	
	return 0;
}








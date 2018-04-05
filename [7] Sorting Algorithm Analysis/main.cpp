#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#define maxSpace 32767 //how much space to put in the array
#define rngRange 9999 //all generated random numbers must be smaller than this number
#define maxNums1 10 //test 1
#define maxNums2 32 //test 2
#define maxNums3 100 //test 3
#define maxNums4 316 //test 4
#define maxNums5 1000 //test 5
#define maxNums6 3162 //test 6
#define maxNums7 10000 //test 7
#define maxNums8 31623 //test 8
#define maxNums9 100000 //test 9
//#define maxNums10 316228 //test 10 overflow

using namespace std;

//Create a class sorter
//class is like struct that can hold things
//but it can also do things
class sorter
{

	public:
// here you have the data that your class stores, a bunch of space not all needed
	int rng[maxSpace];
	int sorted[maxSpace];
	int unsortedforCounting[maxSpace];
// here is the number of entries stored (needed since not all the storage space is used)
	int numEntries;

//here you have the methods that your class can do

// generate random numbers
	int generateRandomNumbers(;/ n howManyNumbers);
// copy randomNumbersArray into sorted
	int copyRandomNumbers();
// print random numbers
	int printRandomNumbers();
// print sorted numbers
	int printSortedNumbers();

// Want to compare at least Merge/Bubble/Insertion/Selection/Quick/Counting sorts
// https://en.wikipedia.org/wiki/Merge_sort
	int mergeSort(int p, int r);
// https://en.wikipedia.org/wiki/Bubble_sort
	int bubbleSort(int n);
// https://en.wikipedia.org/wiki/Insertion_sort
	int insertionSort(int n);
// https://en.wikipedia.org/wiki/Selection_sort
	int selectionSort(int n);
// https://en.wikipedia.org/wiki/Quicksort
	int quickSort(int low, int high);
// https://en.wikipedia.org/wiki/Counting_sort
	int countingSort(int n);

// helper functions go here
	int merge(int p, int q, int r);
	int partition(int low, int high);
};



// generate random numbers
int sorter::generateRandomNumbers(int howManyNumbers){
	numEntries=howManyNumbers;
	for (int i=0; i<numEntries; i++)
		rng[i]=rand()%rngRange; //don't want random numbers to be too big, hard to read
	return 0;
}

// copy randomNumbersArray into sorted
int sorter::copyRandomNumbers(){
	for (int i=0; i<numEntries; i++){
		sorted[i]=rng[i];
		unsortedforCounting[i] = rng[i];
	}
	return 0;
}

// print random numbers
int sorter::printRandomNumbers(){
	cout << "Random numbers" << endl;
	for (int i=0; i<numEntries; i++)
		cout << rng[i] <<endl;
	return 0;
}

// print sorted numbers
int sorter::printSortedNumbers(){
	cout << "Sorted numbers" << endl;
	for (int i=0; i<numEntries; i++)
		cout << sorted[i] <<endl;
	return 0;
}

// helper function for mergeSort
int sorter::merge(int p, int q, int r){
    int n1=q-p+1; //test array of 16, n1 is 8 (the first time it gets called)
    int n2=r-q; //test array of 16, n2 is 8 (the first time it gets called)
    int arrayLeft[maxSpace];
    int arrayRight[maxSpace];
    for (int i=0; i<n1; i++){
        arrayLeft[i]=sorted[p+i];
    }
    for (int j=0; j<n2; j++){
        arrayRight[j]=sorted[q+j+1];
    }
    arrayLeft[n1]=maxSpace; // if 0 to 7 gets filled with real stuff, then 8 is the filler infinity
    arrayRight[n2]=maxSpace;
    //my x y z are i j k in the pseudocode
    int x=INT_MIN;
    int y=INT_MIN;
    for (int z=p; z<=r; z++){
        if(arrayLeft[x]<=arrayRight[y]){
            sorted[z]=arrayLeft[x];
            x++;
        } else {
            sorted[z]=arrayRight[y];
            y++;
        }
    }
    return 0;
}

int sorter::mergeSort (int p, int r){
    if (p<r){
        int q = p + (r - p) /2;
        mergeSort(p,q);
        mergeSort(q+1,r);
        merge(p,q,r);
    }
    return 0;
}

int sorter::bubbleSort(int n){
    bool swapped = false;
    int j = 0;
    int buffer;
    while (!swapped){
        swapped = true;
        j++;
        for (int i = 0; i < n-j; i++){
            if (sorted[i] > sorted[i+1]){
                buffer = sorted[i];
                sorted[i] = sorted[i+1];
                sorted[i+1] = buffer;
                swapped = false;
            }
        }
    }
    return 0;
}

int sorter::insertionSort(int n){
    int j, buffer;
    for (int i = 0; i <n; i++){
        j = i;
        while(j > 0 && sorted[j] < sorted[j-1]){
            buffer = sorted[j];
            sorted[j] = sorted[j-1];
            sorted[j-1] = buffer;
            j--;
        }
    }
    return 0;
}

int sorter::selectionSort(int n){
    int min, buffer;
    for (int i = 0; i<n; i++){
        min = i;
        for (int j = i+1; j<n; j++){
            if (sorted[j] < sorted[min]){
                min = j;
            }
        }
        if (min != i){
                buffer = sorted[i];
                sorted[i] = sorted[min];
                sorted[min] = buffer;
            }
    }
    return 0;
}

//quickSort helper function
int sorter::partition(int low, int high){
    int buffer;
    int pivot = sorted[low + (high - low) / 2];
    while (low <= high){
        while (sorted[low] < pivot){
            low++;
        }
        while (sorted[high] > pivot){
            high--;
        }
        if (low <= high){
            buffer = sorted[low];
            sorted[low] = sorted[high];
            sorted[high] = buffer;
            low++;
            high--;
        }
    }
    return low;
}

int sorter::quickSort(int low, int high){
    if (low < high){
        int p = partition(low, high);
        if (low < p - 1){
            quickSort(low, p - 1);
        }
        if (p < high){
        quickSort(p, high);
        }
    }
    return 0;
}

int sorter::countingSort(int n){
    int buffer[rngRange];
    for(int i = 0; i < rngRange; i++){
        buffer[i] = 0;
    }
    for(int i = 0; i < n; i++){
        buffer[unsortedforCounting[i]]++;
    }
    for(int i = 1; i < rngRange; i++){
        buffer[i]+=buffer[i-1];
    }
    for(int i = n-1; i>= 0; i--){
        sorted[buffer[unsortedforCounting[i]]-1] = unsortedforCounting[i];
        buffer[unsortedforCounting[i]]--;
    }
    return 0;
}

int main()
{
	sorter mySorter;
	mySorter.generateRandomNumbers(maxNums8);
	mySorter.printRandomNumbers();
	mySorter.copyRandomNumbers(); // this way I have don't touch the random numbers 
	clock_t t;
	t = clock();
	//mySorter.mergeSort(0,maxNums8-1);
	//mySorter.bubbleSort(maxNums8);
	//mySorter.insertionSort(maxNums8);
	//mySorter.selectionSort(maxNums8);
	//mySorter.quickSort(0, maxNums8-1);
	mySorter.countingSort(maxNums8);
	t = clock() - t;
	mySorter.printSortedNumbers();
	cout << "To sort " << maxNums8 <<  " numbers it took me " << t << " clicks (" << ((float)t)/(CLOCKS_PER_SEC) << " seconds)." << endl;
	cout << "Test complete, press Enter to continue." << endl;
	cin.get();
	return 0;

	//DATA: https://goo.gl/3yB7ZT
}



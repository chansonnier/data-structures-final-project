#include "dll.hpp"
#include <iostream>
#include <ios>
#include <fstream>
#include <chrono>

using namespace std;

// helper function to generate/randomize arr of #s 0 thru x (x being 100, 199, 299, etc)
void randomizeNums(int arr[], int rangeEnd){
  for (int i = 0; i < 100; i++){
    arr[i] = rand() % rangeEnd; // rangeEnd starts at 100, grows by 100, so it's then 200, then 300, etc
    for (int i2 = 0; i2 < 100; i2++){
      while ((arr[i] == arr[i2]) && (i != i2)){ // to have no duplicates / ensure unique indices
        arr[i] = rand() % rangeEnd;
        i2 = 0;
      }
    }
  }
}

int main(){
  std::srand(std::time(0));
  DLL dLinkedList;
  int testData[10000];   // to take the data (ID numbers) from the dataSet csv files
  int randomNums[100]; // for indexing into the above arr (testData) when searching it
  float insert[100];     // for storing the timing results at each 100-unit interval
  float search[100];     // ^




  ifstream myfile;
  myfile.open("dataSetB.csv");
  string line;
  int idx = 0;
  while (getline(myfile, line, ',')){       // split on comma
    testData[idx] = stoi(line);             // do string-to-integer on each item in the csv
    idx++;
  }

  int interval = 100;           // this will be incremented by 100 each loop thru the data
  int floatIdx = 0;             // and this will be ++ incremented

  // main loop
  while (floatIdx < 100){       // 100 iterations of this loop for 100 * 100 = 10,000 total records

    // generate a new set of random nums
    randomizeNums(randomNums, interval); // interval grows by 100 each loop thru


    // insert 100 records, divide total time taken by 100, then put this result in insert[floatIdx]
    auto start = chrono::steady_clock::now(); // timing of insert operations starts here
    for (int i = (-100 + interval); i < interval; i++) { 
      dLinkedList.insert(testData[i]);
    }
    auto end = chrono::steady_clock::now();   // timing of insert operations ends here

    // record the time taken 
    insert[floatIdx] = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) / 100;

    // now search for 100 records, divide total time taken by 100, and record the result in search[floatIdx]
    start = chrono::steady_clock::now();      // timing of search operations starts here
    for (int i = 0; i < 100; i++) {
      dLinkedList.search(testData[randomNums[i]]); // search for a randomly indexed ID number in the testData
    }
    end = chrono::steady_clock::now();        // timing of search operations ends here

    // record the time taken
    search[floatIdx] = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) / 100;


    // if ((floatIdx % 10 == 0) || (floatIdx > 90)){  // let's see 10 results throughout the whole go-thru
    //   cout << "---------------------------------------------------------------------------------------------" << endl;
    //   cout << floatIdx << "th timing result: " << insert[floatIdx] << " nanoseconds per insert and " << search[floatIdx] << " nanoseconds per search" << endl;
    //   cout << "---------------------------------------------------------------------------------------------" << endl;
    // }

    interval += 100;
    floatIdx++;
  }

  ofstream outfile1;
  ofstream outfile2;
  outfile1.open("insert_performance_doubly_ll_dataSetB.csv");
  outfile2.open("search_performance_doubly_ll_dataSetB.csv");
  for (int i = 0; i < 100; ++i) {
    outfile1 << i << "," << insert[i] << endl;
    outfile2 << i << "," << search[i] << endl;
  }

  myfile.close();
  outfile1.close();
  outfile2.close();
  return 0;
}

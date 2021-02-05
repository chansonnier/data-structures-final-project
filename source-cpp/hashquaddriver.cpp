#include "hashquad.hpp"
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
  HashTable table;
  int testData[10000];   // to take the data (ID numbers) from the dataSet csv files
  int randomNums[100]; // for indexing into the above arr (testData) when searching it
  float insert[100];     // for storing the timing results at each 100-unit interval
  float search[100];     // ^
  int numCollisionsPer100Searches[100];
  int numCollisionsPer100Inserts[100];




  ifstream myfile;
  myfile.open("dataSetA.csv");
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
    // if (floatIdx % 10 == 0){             // just for testing that the interval each set of random indices fall into is ok
    //   for (int i = 0; i < 100; i++){
    //     cout << i << "th random index: " << randomNums[i] << endl;
    //   }
    // }


    // insert 100 records, divide total time taken by 100, then put this result in insert[floatIdx]
    auto start = chrono::steady_clock::now(); // timing of insert operations starts here
    for (int i = (-100 + interval); i < interval; i++) { 
      table.insertItem(testData[i]);
    }
    auto end = chrono::steady_clock::now();   // timing of insert operations ends here

    // record the time taken and num of INSERT collisions
    insert[floatIdx] = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) / 100;
    numCollisionsPer100Inserts[floatIdx] = table.getNumOfInsertCollisions();

    // now search for 100 records, divide total time taken by 100, and record the result in search[floatIdx]
    start = chrono::steady_clock::now();      // timing of search operations starts here
    for (int i = 0; i < 100; i++) {
      table.searchItem(testData[randomNums[i]]); // search for a randomly indexed ID number in the testData
    }
    end = chrono::steady_clock::now();        // timing of search operations ends here

    // record the time taken and num of SEARCH collisions
    search[floatIdx] = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) / 100;
    numCollisionsPer100Searches[floatIdx] = table.getNumOfSearchCollisions();


    // if ((floatIdx % 10 == 0) || (floatIdx > 90)){  // let's see 10 results throughout the whole go-thru
    //   cout << "---------------------------------------------------------------------------------------------" << endl;
    //   cout << floatIdx << "th timing result: " << insert[floatIdx] << " nanoseconds per insert and " << search[floatIdx] << " nanoseconds per search" << endl;
    //   cout << floatIdx << "th num of collisions per 100 inserts and 100 searches: " << numCollisionsPer100Inserts[floatIdx] << " insert collisions and " << numCollisionsPer100Searches[floatIdx] << " search collisions" << endl;
    //   cout << "---------------------------------------------------------------------------------------------" << endl;
    // }

    table.resetNumOfInsertCollisions();
    table.resetNumOfSearchCollisions(); // otherwise we will be inserting the cumulative collisions for the whole table at each of the 100 floatIdxs
    interval += 100;
    floatIdx++;
  }

  int cumulativeCollisionsSearch = 0;
  int cumulativeCollisionsInsert = 0;
  for (int i = 0; i < 100; i++){
    cumulativeCollisionsInsert += numCollisionsPer100Inserts[i];
    cumulativeCollisionsSearch += numCollisionsPer100Searches[i];
  }
  // cout << "Total collisions: " << cumulativeCollisionsInsert << " insert collisions and " << cumulativeCollisionsSearch << " search collisions" << endl;
  table.setNumOfInsertCollisions(cumulativeCollisionsInsert);
  table.setNumOfSearchCollisions(cumulativeCollisionsSearch);
  // cout << "Total collisions: " << table.getNumOfInsertCollisions() << " insert collisions and " << table.getNumOfSearchCollisions() << " search collisions" << endl;

  ofstream outfile1;
  ofstream outfile2;
  ofstream outfile3;
  ofstream outfile4;
  outfile1.open("insert_performance_hashquad_dataSetA.csv");
  outfile2.open("search_performance_hashquad_dataSetA.csv");
  outfile3.open("insert_collisions_performance_hashquad_dataSetA.csv");
  outfile4.open("search_collisions_performance_hashquad_dataSetA.csv");
  for (int i = 0; i < 100; ++i) {
    outfile1 << i << "," << insert[i] << endl;
    outfile2 << i << "," << search[i] << endl;
    outfile3 << i << "," << numCollisionsPer100Inserts[i] << endl;
    outfile4 << i << "," << numCollisionsPer100Searches[i] << endl;
  }

  myfile.close();
  outfile1.close();
  outfile2.close();
  outfile3.close();
  outfile4.close();
  return 0;
}

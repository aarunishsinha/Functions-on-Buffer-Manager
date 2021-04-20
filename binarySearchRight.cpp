
#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <fstream>
#include <bits/stdc++.h>

void searchRight(int firstPageNum, int lastPageNum, int &rightPage, int &rightOffset, int num, FileHandler &fh){
  //searching left index
  while(lastPageNum >= firstPageNum){
    // cout<<"run";
    bool found = false;
    int mid = (lastPageNum + firstPageNum)/2;
    // cout<<"mid "<<mid<<endl;
    PageHandler midPage = fh.PageAt(mid);
    char* data = midPage.GetData ();

    // bool allValuesNum = true;   // true if all values on the page = num, in this case look both left and right
    // bool startingValueNum = false;  //start value = num. Binary search again to the left
    // bool endingValueNum = false;  //ending value = num. Binary search to the right
    int first = 0;         // for reading
    int last = 0;

    //linear search for that num in the page
    // for(int i = 0;i<PAGE_CONTENT_SIZE;i=i+4){
    memcpy (&first, &data[0], sizeof(int));  //read the integer
    memcpy (&last, &data[PAGE_CONTENT_SIZE-4], sizeof(int));
    // cout<<"last: "<<last<<endl;
    // break;

    //BOOKKEEPING
    if(last == num){      //continue with the search for the left index. Update the variables just in case this was tthe first occurence
      // cout<<"first at "<<mid<<endl;
      rightPage = mid;
      rightOffset = PAGE_CONTENT_SIZE-4;
      firstPageNum = mid + 1;
      // startingValueNum = true;
      // break;
    }

    else if(last > num || last == INT_MIN){
      if(first <= num){
        int temp = 0;
        for(int i =PAGE_CONTENT_SIZE; i>=0;i=i-4){
          memcpy (&temp, &data[i], sizeof(int));
          if(temp == num){
            rightPage = mid;
            rightOffset = i;
            found = true;
            break;
          }
        }
        if(!found){
          found = true;
          rightPage = -1;
          rightOffset = -1;
        }
      }

      else { // first > num. Search towards left
        // cout<<"first<num last < num at "<<mid<<endl;
        // if(rightPage > -1){ //already found at index 0 on next page
        //   found = true;
        //   break;
        // }
        lastPageNum = mid - 1;
        // break;
      }
    }

    else{   // last < num search towards right
      // cout<<"first>num at "<<mid<<endl;
      firstPageNum = mid + 1;
    }

    fh.UnpinPage(mid);
    // cout<<"Unpin"<<endl;
    if(found) break;
  }
}

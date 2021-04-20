
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

    int first = 0;         // for reading
    int last = 0;

    memcpy (&first, &data[0], sizeof(int));  //read the integer
    memcpy (&last, &data[PAGE_CONTENT_SIZE-4], sizeof(int));

    //BOOKKEEPING
    if(last == num){      //continue with the search for the left index. Update the variables just in case this was tthe first occurence
      // cout<<"first at "<<mid<<endl;
      rightPage = mid;
      rightOffset = PAGE_CONTENT_SIZE-4;
      firstPageNum = mid + 1;
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
        lastPageNum = mid - 1;
      }
    }

    else{   // last < num search towards right
      firstPageNum = mid + 1;
    }
    // cout<<"Unpin"<<endl;
    fh.UnpinPage(mid);
    if(found) break;
  }
}

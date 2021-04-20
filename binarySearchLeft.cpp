
#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <fstream>
#include <bits/stdc++.h>


void searchLeft(int firstPageNum, int lastPageNum, int &leftPage, int &leftOffset, int num, FileHandler &fh){
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
    if(first == num){      //continue with the search for the left index. Update the variables just in case this was tthe first occurence
      // cout<<"first at "<<mid<<endl;
      leftPage = mid;
      leftOffset = 0;
      lastPageNum = mid -1;
      // startingValueNum = true;
      // break;
    }

    else if(first < num){
      if(last >= num || last == INT_MIN){
        // cout<<"first<num last >=num at "<<mid<<endl;
        // cout<<last<<endl;
        // cout<<num<<endl;
        // num on this page. Linear Search here
        int temp = 0;
        for(int i = 0;i<PAGE_CONTENT_SIZE;i=i+4){
          memcpy (&temp, &data[i], sizeof(int));
          if(temp == num){
            leftPage = mid;
            leftOffset = i;
            found = true;
            break;
          }
        }
        if(!found){
          found = true;
          leftPage = -1;
          leftOffset = -1;
        }
      }

      else { // last < num. Search towards right
        // cout<<"first<num last < num at "<<mid<<endl;
        // if(leftPage > -1){ //already found at index 0 on next page
        //   found = true;
        //   break;
        // }
        firstPageNum = mid +1;
        // break;
      }
    }

    else{   // first > num search towards left
      // cout<<"first>num at "<<mid<<endl;
      lastPageNum = mid - 1;
    }

    fh.UnpinPage(mid);
    // cout<<"Unpin"<<endl;
    if(found) break;
  }
}

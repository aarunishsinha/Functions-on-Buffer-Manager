//Sample file for students to get their code running

#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <fstream>
#include <bits/stdc++.h>

/*
PLAN:
Binary search the left page, left offset
if number does not exist then go to the next number
binary search the rightpage, rightOffset
start copying rightPage,rightOffset+1 to leftPage,leftOffset
Fill the remaining page with INTMINs
Delete the extra pages
*/


using namespace std;

void searchLeft(int firstPageNum, int lastPageNum, int &leftPage, int &leftOffset, int num, FileHandler &fh);
void searchRight(int firstPageNum, int lastPageNum, int &rightPage, int &rightOffset, int num, FileHandler &fh);


void checkNewPage(int &index, int &outPageNum, PageHandler &outPageHandler, FileHandler &out, char* &outPutData, bool dirty){
  if(index > PAGE_CONTENT_SIZE-4){    //new page
    index = 0;
    out.UnpinPage(outPageNum);
    if(dirty)
      out.MarkDirty(outPageNum);
    out.FlushPage(outPageNum);
    outPageHandler = out.NewPage();
    outPutData = outPageHandler.GetData ();
    outPageNum++;
  }
}


int main(int argc, char *argv[]) {
  const char* inputFile = argv[1];
  const char* queryFile = argv[2];    //CONFIRM IF WE HAVE TO APPEND TXT
  // const char* outputFile = argv[3];
  // open query file
  fstream  query;
  query.open(queryFile);
  string SEARCH;    // for reading the constant string SEARCH
  int num;    // reading the number to be searched for

  FileManager fm;
  FileHandler fh = fm.OpenFile (inputFile);
  // memcpy (&num, &data[0], sizeof(int));   read in this way

  int index = 0;
  int outPageNum = 0;


  //getting first and last pagenums
  PageHandler first = fh.FirstPage();
  int firstPageNum = first.GetPageNum();
  fh.UnpinPage(firstPageNum);
  PageHandler last = fh.LastPage();
  int lastPageNum = last.GetPageNum();
  fh.UnpinPage(lastPageNum);
  int originalLastPageNum = lastPageNum;



  while (query >> SEARCH){
    query >> num;
    cout<<"num: "<<num<<endl;

    //ONE BINARY SEARCH STARTS HERE
    int leftPage = -1;
    int leftOffset = -1;
    int rightPage = -1;
    int rightOffset = -1;

    searchLeft(firstPageNum,lastPageNum, leftPage, leftOffset, num, fh);
    if(leftPage != -1){   //only search for the right if the number is found at all else just proceed
      searchRight(firstPageNum, lastPageNum,rightPage,rightOffset,num,fh);

      // running variables to copy
      int leftPageIndex = leftPage;
      int leftOffsetIndex = leftOffset;
      int rightPageIndex = rightPage + (rightOffset+4)/(PAGE_CONTENT_SIZE);
      int rightOffsetIndex = (rightOffset+4)%PAGE_CONTENT_SIZE;

      PageHandler left = fh.PageAt(leftPageIndex);
      char* leftData = left.GetData();
      PageHandler right;
      char* rightData;
      if(rightPageIndex == leftPageIndex){
        right = left;
        rightData = leftData;
      }
      else{
        right = fh.PageAt(rightPageIndex);
        rightData = right.GetData();
      }

      while(!(rightPageIndex == lastPageNum && rightOffsetIndex == PAGE_CONTENT_SIZE)){ //go till the End of the file

        //copy
        if(rightOffsetIndex >= PAGE_CONTENT_SIZE){
          //unpinning prev page
          if(leftPageIndex != rightPageIndex){
            fh.UnpinPage(rightPageIndex);
            // fh.FlushPage(rightPageIndex);
          }

          // fetch new page irrespective
          right = fh.NextPage(rightPageIndex);
          rightData = right.GetData();
          rightPageIndex++;
          rightOffsetIndex = 0;

        }
        if(leftOffsetIndex >= PAGE_CONTENT_SIZE){   //then right is definitely on next page or so
          // Evicting
          // cout<<"Flushing Page: "<<left.GetPageNum()<<endl;
          fh.MarkDirty(leftPageIndex);
          fh.UnpinPage(leftPageIndex);
          // fh.FlushPage(leftPageIndex);
          //updating
          leftPageIndex+=1;
          leftOffsetIndex = 0;
          //if new page number is the right page number, then dont fetch
          if(leftPageIndex==rightPageIndex){
            left = right;
            leftData = rightData;
          }
          else{
            left = fh.NextPage(leftPageIndex-1);
            leftData = left.GetData();
          }
        }

        cout<<"Left: "<<leftPageIndex<<" "<<leftOffsetIndex<<endl;
        cout<<"Right: "<<rightPageIndex<<" "<<rightOffsetIndex<<endl;

        int temp;

        memcpy (&temp, &rightData[rightOffsetIndex], sizeof(int));
        // cout<<"Temp: "<<temp<<endl;
        memcpy (&leftData[leftOffsetIndex], &temp, sizeof(int));
        // int temp2;
        // memcpy (&temp2, &leftData[leftOffsetIndex], sizeof(int));
        // cout<<"temp: "<<temp<<"temp2: "<<temp2<<endl;
        leftOffsetIndex+=4;
        rightOffsetIndex+=4;


      }

      lastPageNum = leftPageIndex;      // next binary search will take lesser time
      for(int i =leftOffsetIndex; i<PAGE_CONTENT_SIZE;i+=4){    // writing all intmins on that page for the next binary search
        int intmin = INT_MIN;
        memcpy (&leftData[i], &intmin, sizeof(int));
      }
      fh.MarkDirty(leftPageIndex);
      fh.UnpinPage(leftPageIndex);
      if(leftPageIndex!=rightPageIndex)
        fh.UnpinPage(rightPageIndex);
      fh.FlushPages();

    }
  }
  fm.CloseFile(fh);
  // fh.FlushPages();


  // deleting remaining pages
    // for(;leftOffsetIndex<PAGE_CONTENT_SIZE-4;leftOffsetIndex+=4){
    //   int intmin = INT_MIN;
    //   memcpy (&leftData[leftOffsetIndex], &intmin, sizeof(int));
    // }

}







// try{
//   while(true){
//     ph = fh.NextPage (pageNum);
//     data = ph.GetData ();
//     pageNum = ph.GetPageNum();
//     numPagesRead++;
//   }
// }
// catch(NoBufferSpaceException ex){
//   cout<<ex.what()<<" "<<numPagesRead<<endl;
// }

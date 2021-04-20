//Sample file for students to get their code running

#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;

void searchLeft(int firstPageNum, int lastPageNum, int &leftPage, int &leftOffset, int num, FileHandler &fh);
void searchRight(int firstPageNum, int lastPageNum, int &rightPage, int &rightOffset, int num, FileHandler &fh);


void checkNewPage(int &index, int &outPageNum, PageHandler &outPageHandler, FileHandler &out, char* &outPutData){
  if(index > PAGE_CONTENT_SIZE-4){    //new page
    index = 0;
    out.UnpinPage(outPageNum);
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
  const char* outputFile = argv[3];
  // open query file
  fstream  query;
  query.open(queryFile);
  string SEARCH;    // for reading the constant string SEARCH
  int num;    // reading the number to be searched for

  FileManager fm;
  FileHandler fh = fm.OpenFile (inputFile);
  // memcpy (&num, &data[0], sizeof(int));   read in this way


//TODO: UNCOMMENT
  FileHandler out = fm.CreateFile(outputFile); // creating the output file
  PageHandler outPageHandler = out.NewPage ();
	char *outPutData = outPageHandler.GetData ();
  // int num = 5;
	// memcpy (&data[0], &num, sizeof(int));     write like this
  int index = 0;
  int outPageNum = 0;

  while (query >> SEARCH){
    query >> num;
    // cout<<"num: "<<num<<endl;

    //ONE BINARY SEARCH STARTS HERE

    //getting first and last pagenums
    PageHandler first = fh.FirstPage();
    int firstPageNum = first.GetPageNum();
    fh.UnpinPage(firstPageNum);
    PageHandler last = fh.LastPage();
    int lastPageNum = last.GetPageNum();
    fh.UnpinPage(lastPageNum);

    int leftPage = -1;
    int leftOffset = -1;
    int rightPage = -1;
    int rightOffset = -1;

    //outputting




    searchLeft(firstPageNum,lastPageNum, leftPage, leftOffset, num, fh);
    // cout<<leftPage<<" "<<leftOffset<<endl;
    if(leftPage != -1){   //only search for the right if the number is found at all
      searchRight(firstPageNum, lastPageNum,rightPage,rightOffset,num,fh);
      // cout<<leftPage<<" "<<leftOffset<<" - "<<rightPage<<" "<<rightOffset<<endl;
    // cout<<rightPage<<" "<<rightOffset<<endl;
      if(leftPage == rightPage){    //then go from leftOffset to rightOffset
        for(int i= leftOffset;i<=rightOffset;i=i+4){   //wrtitting all occurences on left page
          //fetching new page if needed
          // cout<<leftPage<<" "<<i<<endl;

          checkNewPage(index, outPageNum, outPageHandler, out, outPutData);
          memcpy (&outPutData[index], &leftPage, sizeof(int));
          memcpy (&outPutData[index+4], &i, sizeof(int));
          index += 8;
        }
      }
      else{
        for(int i= leftOffset;i<PAGE_CONTENT_SIZE;i=i+4){   //wrtitting all occurences on left page
          //fetching new page if needed
          checkNewPage(index, outPageNum, outPageHandler, out, outPutData);
          memcpy (&outPutData[index], &leftPage, sizeof(int));
          memcpy (&outPutData[index+4], &i, sizeof(int));
          index += 8;
        }

        for(int j = leftPage+1;j<rightPage;j++){   //everything between left and right pages
          for(int i = 0; i<PAGE_CONTENT_SIZE;i+=4){
            checkNewPage(index, outPageNum, outPageHandler, out, outPutData);
            memcpy (&outPutData[index], &j, sizeof(int));
            memcpy (&outPutData[index+4], &i, sizeof(int));
            index += 8;
          }
        }

        for(int i= 0;i<=rightOffset;i=i+4){   //wrtitting all occurences on right page
          //fetching new page if needed
          checkNewPage(index, outPageNum, outPageHandler, out, outPutData);
          memcpy (&outPutData[index], &rightPage, sizeof(int));
          memcpy (&outPutData[index+4], &i, sizeof(int));
          index += 8;
        }
      }
    }

    //writting -1-1
    checkNewPage(index, outPageNum, outPageHandler, out, outPutData);
    int minusOne = -1;
    memcpy (&outPutData[index], &minusOne, sizeof(int));
    memcpy (&outPutData[index+4], &minusOne, sizeof(int));
    index += 8;
    //fill the rest with INTIMIN

    }
    for(;index<PAGE_CONTENT_SIZE-4;index+=4){
      int intmin = INT_MIN;
      memcpy (&outPutData[index], &intmin, sizeof(int));
      memcpy (&outPutData[index+4], &intmin, sizeof(int));
  }

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

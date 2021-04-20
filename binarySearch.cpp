//Sample file for students to get their code running

#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <fstream>

using namespace std;

void searchLeft(int firstPageNum, int lastPageNum, int &leftPage, int &leftOffset, int num, FileHandler &fh);
void searchRight(int firstPageNum, int lastPageNum, int &rightPage, int &rightOffset, int num, FileHandler &fh);

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
  // FileHandler out = fm.CreateFile(outputFile); // creating the output file
  // PageHandler outPageHandler = out.NewPage ();
	// char *outPutData = outPageHandler.GetData ();
  // int num = 5;
	// memcpy (&data[0], &num, sizeof(int));     write like this


  while (query >> SEARCH){
    query >> num;
    cout<<"num: "<<num<<endl;

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


    searchLeft(firstPageNum,lastPageNum, leftPage, leftOffset, num, fh);
    cout<<leftPage<<" "<<leftOffset<<endl;
    searchRight(firstPageNum, lastPageNum,rightPage,rightOffset,num,fh);
    cout<<rightPage<<" "<<rightOffset<<endl;
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

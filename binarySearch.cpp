//Sample file for students to get their code running

#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <fstream>

using namespace std;


int main(int argc, char *argv[]) {
  const char* inputFile = argv[1];
  const char* queryFile = argv[2];    //CONFIRM IF WE HAVE TO APPEND TXT
  const char* outputFile = argv[3];
  // open query file
  fstream  query;
  query.open(queryFile);
  string SEARCH;    // for reading the constant string SEARCH
  int num;    // reading the number to be searched for

  while (query >> SEARCH){
    query >> num;
    cout<<num<<endl;
  }

	FileManager fm;

  FileHandler fh = fm.OpenFile (inputFile);
  cout << "File opened" << endl;
  int numPagesRead = 1;
  PageHandler ph = fh.FirstPage ();
  char* data = ph.GetData ();
  int pageNum = ph.GetPageNum();
  try{
    while(true){
      ph = fh.NextPage (pageNum);
      data = ph.GetData ();
      pageNum = ph.GetPageNum();
      numPagesRead++;
    }
  }
  catch(NoBufferSpaceException ex){
    cout<<ex.what()<<" "<<numPagesRead<<endl;
  }
  //
  // // Get the very first page and its data
  // PageHandler ph = fh.FirstPage ();
  // char* data = ph.GetData ();
  //
	// // Create the Output file
	// FileHandler out = fm.CreateFile(outputFile);
  //
	// // Create a new page
	// PageHandler ph = fh.NewPage ();
	// char *data = ph.GetData ();
  //
	// // Store an integer at the very first location
	// int num = 5;
	// memcpy (&data[0], &num, sizeof(int));
  //
	// // Store an integer at the second location
	// num = 1000;
	// memcpy (&data[4], &num, sizeof(int));
  //
	// // Flush the page
	// fh.FlushPages ();
	// cout << "Data written and flushed" << endl;
  //
	// // Close the file
	// fm.CloseFile(fh);
  //
	// // Reopen the same file, but for reading this time
	// FileHandler fh = fm.OpenFile ("temp.txt");
	// cout << "File opened" << endl;
  //
	// // Get the very first page and its data
	// PageHandler ph = fh.FirstPage ();
	// char* data = ph.GetData ();
  //
	// // Output the first integer
	// memcpy (&num, &data[0], sizeof(int));
	// cout << "First number: " << num << endl;
  //
	// // Output the second integer
	// memcpy (&num, &data[4], sizeof(int));
	// cout << "Second number: " << num << endl;;
  //
	// // Close the file and destory it
	// fm.CloseFile (fh);
	// fm.DestroyFile ("temp.txt");
}

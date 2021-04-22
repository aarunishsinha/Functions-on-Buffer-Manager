#include <iostream>
#include "file_manager.h"
#include "errors.h"
#include "constants.h"
#include <cstring>
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
  FileManager fm;
  FileHandler fh_read = fm.OpenFile (inputFile);
  FileHandler fh_write = fm.OpenFile (outputFile);
  // FileHandler fh_write = fm.CreateFile("temp.txt");
  PageHandler last = fh_read.LastPage();

  int lastPageNumber = last.GetPageNum();
  bool f = fh_read.UnpinPage(lastPageNumber);
  f = fh_read.FlushPage(lastPageNumber);

  PageHandler ph_out = fh_write.NewPage();
  char* write_data = ph_out.GetData();
  int out_curr = ph_out.GetPageNum();
  int out_iter = 0;

  int close = 0;
  // fm.PrintBuffer();
  while (query >> SEARCH){
    query >> num;
    // cout<<num<<endl;

    PageHandler ph = fh_read.FirstPage ();

    char* data = ph.GetData ();
    int num_read = 0;
    int offset = -1;

    int curr = ph.GetPageNum();
    f = fh_read.UnpinPage(curr);
    f = fh_read.FlushPage(curr);
    // fm.PrintBuffer();
    try{
      while(curr<=lastPageNumber){
        offset = 0;
        // Read a page from the input
        ph = fh_read.PageAt(curr);
        data = ph.GetData();
        // Starting linear search in that page
        for(int i = 0; i<PAGE_CONTENT_SIZE;i+=4){
          memcpy(&num_read,&data[i],sizeof(int));
          // cout<<num_read<<endl;
          if(num_read==num){      // FOUND THE INTEGER IN QUERY
            // cout<<"Found One!"<<endl;
            // Check if page is filled
            if(out_iter>=PAGE_CONTENT_SIZE){
              // cout<<"Page Written:"<<out_curr<<endl;
              out_iter=0;
              ph_out = fh_write.NewPage();
              fh_write.UnpinPage(out_curr);
              fh_write.MarkDirty(out_curr);
              fh_write.FlushPage(out_curr);
              // ph_out = fh_write.NewPage();
              out_curr = ph_out.GetPageNum();
              // cout<<"Page Created:"<<out_curr<<endl;
              write_data = ph_out.GetData();
            }
            // Write the page number in output
            memcpy(&write_data[out_iter], &curr, sizeof(int));
            out_iter+=4;
            // cout<<"Wrote:"<<curr<<endl;
            // Check if page is filled
            if(out_iter>=PAGE_CONTENT_SIZE){
              // cout<<"Page Written:"<<out_curr<<endl;
              out_iter=0;
              ph_out = fh_write.NewPage();
              fh_write.UnpinPage(out_curr);
              fh_write.MarkDirty(out_curr);
              fh_write.FlushPage(out_curr);
              out_curr = ph_out.GetPageNum();
              // cout<<"Page Created:"<<out_curr<<endl;
              write_data = ph_out.GetData();
            }
            // Write offset in output
            memcpy(&write_data[out_iter], &offset, sizeof(int));
            out_iter+=4;
            // cout<<"Wrote:"<<offset<<endl;
          }
          if(num_read==INT_MIN){
            break;
          }
          offset++;
        }
        fh_read.UnpinPage(curr);
        fh_read.FlushPage(curr);
        // cout<<"Current Page Number:"<<curr<<endl;
        curr++;
        // fm.PrintBuffer();
      }
    }
    catch(NoBufferSpaceException ex){
      cout<<ex.what()<<" "<<endl;
    }
    // Output (-1,-1)
    // Check if page is filled
    if(out_iter>=PAGE_CONTENT_SIZE){
      // cout<<"Page Written:"<<out_curr<<endl;
      out_iter=0;
      ph_out = fh_write.NewPage();
      fh_write.UnpinPage(out_curr);
      fh_write.MarkDirty(out_curr);
      fh_write.FlushPage(out_curr);
      // ph_out = fh_write.NewPage();
      out_curr = ph_out.GetPageNum();
      // cout<<"Page Created:"<<out_curr<<endl;
      write_data = ph_out.GetData();
    }
    offset = -1;
    memcpy(&write_data[out_iter], &offset, sizeof(int));
    out_iter+=4;
    // cout<<"Wrote:"<<offset<<endl;
    // Check if page is filled
    if(out_iter>=PAGE_CONTENT_SIZE){
      // cout<<"Page Written:"<<out_curr<<endl;
      out_iter=0;
      ph_out = fh_write.NewPage();
      fh_write.UnpinPage(out_curr);
      fh_write.MarkDirty(out_curr);
      fh_write.FlushPage(out_curr);
      // ph_out = fh_write.NewPage();
      out_curr = ph_out.GetPageNum();
      // cout<<"Page Created:"<<out_curr<<endl;
      write_data = ph_out.GetData();
    }
    // Write offset in output
    memcpy(&write_data[out_iter], &offset, sizeof(int));
    out_iter+=4;
    // cout<<"Wrote:"<<offset<<endl;
    // break;
  }
  // Store INT_MIN in the remaining positions
  while(out_iter<PAGE_CONTENT_SIZE){
    int intmin=INT_MIN;
    memcpy(&write_data[out_iter],&intmin,sizeof(int));
    out_iter+= (sizeof(int));
  }

  // // Printing Output
  // int curr = 0;
  // int firstPage = 0;
  // int lastPage = 0;
  // PageHandler p = fh_write.FirstPage();
  // firstPage = p.GetPageNum();
  // fh_write.UnpinPage(firstPage);
  // fh_write.FlushPage(firstPage);
  // p = fh_write.LastPage();
  // lastPage = p.GetPageNum();
  // fh_write.UnpinPage(lastPage);
  // fh_write.FlushPage(lastPage);
  // curr = firstPage;
  // char* data;
  // int num1;
  // while(curr<=lastPage){
  //   p = fh_write.PageAt(curr);
  //   data = p.GetData();
  //   for(int i=0;i<PAGE_CONTENT_SIZE;i+=4){
  //     memcpy(&num1, &data[i], sizeof(int));
  //     cout<<curr<<","<<i/4<<":"<<num1<<endl;
  //   }
  //   curr++;
  // }

  fm.CloseFile(fh_read);
  fm.CloseFile(fh_write);
  // fm.DestroyFile ("temp.txt");
}

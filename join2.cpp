#include <iostream>
#include "file_manager.h"
#include "errors.h"
#include "constants.h"
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
#include <climits>

using namespace std;

void searchLeft(int firstPageNum, int lastPageNum, int &leftPage, int &leftOffset, int num, FileHandler &fh);
void searchRight(int firstPageNum, int lastPageNum, int &rightPage, int &rightOffset, int num, FileHandler &fh);

int main(int argc, char *argv[]) {
  const char* inputFile_1 = argv[1];
  const char* inputFile_2 = argv[2];
  const char* outputFile = argv[3];

  FileManager fm;
  FileHandler fh_inp1 = fm.OpenFile (inputFile_1);
  FileHandler fh_inp2 = fm.OpenFile (inputFile_2);
  FileHandler fh_out = fm.OpenFile (outputFile);
  // FileHandler fh_out = fm.CreateFile("temp.txt");

  PageHandler ph = fh_inp1.FirstPage();
  int inp1_first = ph.GetPageNum();
  fh_inp1.UnpinPage(inp1_first);
  fh_inp1.FlushPage(inp1_first);
  ph = fh_inp1.LastPage();
  int inp1_last = ph.GetPageNum();
  fh_inp1.UnpinPage(inp1_last);
  fh_inp1.FlushPage(inp1_last);

  ph = fh_inp2.FirstPage();
  int inp2_first = ph.GetPageNum();
  fh_inp2.UnpinPage(inp2_first);
  fh_inp2.FlushPage(inp2_first);
  ph = fh_inp2.LastPage();
  int inp2_last = ph.GetPageNum();
  fh_inp2.UnpinPage(inp2_last);
  fh_inp2.FlushPage(inp2_last);

  int curr1 = inp1_first;
  int curr2 = inp2_first;

  PageHandler ph1,ph2,ph_out;

  char* inp1_data;
  char* inp2_data;
  char* out_data;

  ph_out = fh_out.NewPage();
  out_data = ph_out.GetData();
  int out_curr = ph_out.GetPageNum();
  int temp = out_curr;
  int out_iter = 0;

  while(curr1<=inp1_last){
    ph1 = fh_inp1.PageAt(curr1);
    inp1_data = ph1.GetData();
    for(int i=0;i<PAGE_CONTENT_SIZE;i+=(sizeof(int))){
      int num1 = -1;
      memcpy(&num1,&inp1_data[i],sizeof(int));

      int leftPage = -1;
      int leftOffset = -2;
      int rightPage = -1;
      int rightOffset = -2;
      searchLeft(inp2_first,inp2_last, leftPage, leftOffset, num1, fh_inp2);
      if(leftPage != -1){
        searchRight(inp2_first,inp2_last,rightPage,rightOffset,num1, fh_inp2);
      }
      else{
        continue;
      }
      // int offset = leftOffset;
      if(leftPage==rightPage){
        for(int j=leftOffset;j<=rightOffset;j+=4){
          if(out_iter>=PAGE_CONTENT_SIZE){
            out_iter=0;
            fh_out.UnpinPage(out_curr);
            fh_out.MarkDirty(out_curr);
            fh_out.FlushPage(out_curr);
            ph_out = fh_out.NewPage();
            out_curr = ph_out.GetPageNum();
            out_data = ph_out.GetData();
          }
          memcpy(&out_data[out_iter],&num1,sizeof(int));
          out_iter+=4;
        }
      }
      else{
        for(int j=leftOffset;j<PAGE_CONTENT_SIZE;j+=4){
          if(out_iter>=PAGE_CONTENT_SIZE){
            out_iter=0;
            fh_out.UnpinPage(out_curr);
            fh_out.MarkDirty(out_curr);
            fh_out.FlushPage(out_curr);
            ph_out = fh_out.NewPage();
            out_curr = ph_out.GetPageNum();
            out_data = ph_out.GetData();
          }
          memcpy(&out_data[out_iter],&num1,sizeof(int));
          out_iter+=4;
        }
        for(int j=leftPage+1;j<rightPage;j++){
          for(int k=0;k<PAGE_CONTENT_SIZE;k+=4){
            if(out_iter>=PAGE_CONTENT_SIZE){
              out_iter=0;
              fh_out.UnpinPage(out_curr);
              fh_out.MarkDirty(out_curr);
              fh_out.FlushPage(out_curr);
              ph_out = fh_out.NewPage();
              out_curr = ph_out.GetPageNum();
              out_data = ph_out.GetData();
            }
            memcpy(&out_data[out_iter],&num1,sizeof(int));
            out_iter+=4;
          }
        }
        for(int j=0;j<=rightOffset;j+=4){
          if(out_iter>=PAGE_CONTENT_SIZE){
            out_iter=0;
            fh_out.UnpinPage(out_curr);
            fh_out.MarkDirty(out_curr);
            fh_out.FlushPage(out_curr);
            ph_out = fh_out.NewPage();
            out_curr = ph_out.GetPageNum();
            out_data = ph_out.GetData();
          }
          memcpy(&out_data[out_iter],&num1,sizeof(int));
          out_iter+=4;
        }
      }
    }
    fh_inp1.UnpinPage(curr1);
    fh_inp1.FlushPage(curr1);
    curr1++;
  }
  // Store INT_MIN in the remaining positions
  while(out_iter<PAGE_CONTENT_SIZE){
    int intmin=INT_MIN;
    memcpy(&out_data[out_iter],&intmin,sizeof(int));
    out_iter+= (sizeof(int));
  }
  if(out_curr==temp){
    fh_out.DisposePage(out_curr);
  }

  // // Printing Output
  // cout<<"Printing"<<endl;
  // int curr = 0;
  // int firstPage = 0;
  // int lastPage = 0;
  // PageHandler p = fh_out.FirstPage();
  // firstPage = p.GetPageNum();
  // fh_out.UnpinPage(firstPage);
  // fh_out.FlushPage(firstPage);
  // p = fh_out.LastPage();
  // lastPage = p.GetPageNum();
  // fh_out.UnpinPage(lastPage);
  // fh_out.FlushPage(lastPage);
  // cout<<lastPage<<endl;
  // curr = firstPage;
  // char* data;
  // int num1;
  // while(curr<=lastPage){
  //   p = fh_out.PageAt(curr);
  //   data = p.GetData();
  //   for(int i=0;i<PAGE_CONTENT_SIZE;i+=4){
  //     memcpy(&num1, &data[i], sizeof(int));
  //     cout<<curr<<","<<i/4<<":"<<num1<<endl;
  //   }
  //   fh_out.UnpinPage(curr);
  //   curr++;
  // }

  fm.CloseFile(fh_inp1);
  fm.CloseFile(fh_inp2);
  fm.CloseFile(fh_out);
  // fm.DestroyFile ("temp.txt");
}

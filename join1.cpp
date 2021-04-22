#include <iostream>
#include "file_manager.h"
#include "errors.h"
#include "constants.h"
#include <cstring>
#include <fstream>

using namespace std;


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
  int out_iter = 0;

  while(curr1<=inp1_last){
    ph1 = fh_inp1.PageAt(curr1);
    inp1_data = ph1.GetData();
    while(curr2<=inp2_last){
      ph2 = fh_inp2.PageAt(curr2);
      inp2_data = ph2.GetData();
      for(int i=0;i<PAGE_CONTENT_SIZE;i+=(sizeof(int))){
        int num1 = -1;
        memcpy(&num1,&inp1_data[i],sizeof(int));
        for(int j=0;j<PAGE_CONTENT_SIZE;j+=(sizeof(int))){
          int num2 = -1;
          memcpy(&num2,&inp2_data[j],sizeof(int));
          if(num1==num2){
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
            // cout<<out_curr<<","<<out_iter/4<<":"<<num1<<endl;
            out_iter+=4;
          }
        }
      }
      fh_inp2.UnpinPage(curr2);
      curr2++;
    }
    curr2 = inp2_first;
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
  // // Printing Output
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
  fh_inp2.FlushPages();
  fm.CloseFile(fh_inp1);
  fm.CloseFile(fh_inp2);
  fm.CloseFile(fh_out);
  // fm.DestroyFile ("temp.txt");
}

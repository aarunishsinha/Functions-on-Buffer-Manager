//Sample file for students to get their code running

#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>

using namespace std;


int main() {
	FileManager fm;

	FileHandler fh = fm.OpenFile ("TestCases/TC_search/output_search_my");
	cout << "File opened" << endl;

	// Get the very first page and its data
	PageHandler ph = fh.FirstPage ();
  int pagenum = ph.GetPageNum();
	char* data = ph.GetData ();

  try{
    while(true){
      cout<<pagenum<<endl;
      for(int i = 0;i<PAGE_CONTENT_SIZE;i=i+4){
        int num = 0;
        memcpy (&num, &data[i], sizeof(int));
        cout<<num<<" ";
      }
      cout<<endl;
      ph = fh.NextPage (pagenum);
      data = ph.GetData ();
      pagenum = ph.GetPageNum();
      fh.UnpinPage(pagenum);

    }
  }
  catch(NoBufferSpaceException ex){
    // cout<<ex.what()<<" "<<numPagesRead<<endl;
  }
  // }
	fm.CloseFile (fh);
	// fm.DestroyFile ("temp.txt");
}

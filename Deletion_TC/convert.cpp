
#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <bits/stdc++.h>

using namespace std;
const int INT_PER_PAGE = PAGE_CONTENT_SIZE/sizeof(int);

void readBinary(FileHandler fh,string fileName)
{
    ofstream fn(fileName);
	int lastPageNumber = -1;
	
    PageHandler ph = fh.LastPage();
    if(ph.GetPageNum()==-1){
        cout<<"empty file"<<endl;
        return;
    }
    lastPageNumber = ph.GetPageNum();
    fh.UnpinPage(lastPageNumber);
	int p = -1;
    while(p < lastPageNumber)
    {
        // cout<<"p "<<p<<endl;
        PageHandler ph = fh.NextPage(p);
        p = ph.GetPageNum();
        int *data = (int *)ph.GetData();
        for (int i=0; i<INT_PER_PAGE; i++)
        {
            // cout<<"Page: "<<p<<"\tOffset: "<<i<<"\tNumber: "<<data[i]<<endl;
            if(data[i]== INT_MIN){
                fh.UnpinPage(p);
                return;
            }
            fn<<data[i]<<endl;
            
        }
        fh.UnpinPage(p);
    }

}



int main(int argc, char** argv ) {
	FileManager fm;   
    char* inputFile = argv[1];
    char* outputFile = argv[2];
	FileHandler fh1 = fm.OpenFile(inputFile);
    readBinary(fh1, outputFile);
	fm.CloseFile(fh1);    
}
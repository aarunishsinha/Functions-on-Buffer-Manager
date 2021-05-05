#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int INT_PER_PAGE = 0;

map<int, int> getcount(FileHandler &fh)
{
	map<int, int> count;
	int lastPageNumber = -1;
	try{
		lastPageNumber = fh.LastPage().GetPageNum();
	}catch(InvalidPageException e){}
	// cout<<"lastPageNumber = "<<lastPageNumber<<endl;
	int p = -1;
	while(p < lastPageNumber)
	{
		PageHandler ph = fh.NextPage(p);
		p = ph.GetPageNum();
		int *data = (int *)ph.GetData();
		for (int i=0; i<INT_PER_PAGE; i++){
			count[data[i]]++;
		}
		fh.UnpinPage(p);
	}
	return count;
}

int main(int argc, char** argv){
	string tc(argv[1]);

	FileManager fm;

	INT_PER_PAGE = PAGE_CONTENT_SIZE / sizeof(int);

	string filename = "user_TC" + tc + "_output_bin";

	FileHandler fh = fm.OpenFile(filename.c_str());

	map<int, int> count = getcount(fh);

	fm.CloseFile(fh);

	ofstream fout;
	fout.open("user_TC" + tc + "_output");

	map<int, int>::iterator it;
	for(it = count.begin();it!=count.end();it++){
		if(it->first != INT_MIN){
			fout<<it->first<<"\t"<<it->second<<endl;
		}
	}

	fout.close();
}
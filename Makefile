sampleobjects = buffer_manager.o file_manager.o sample_run.o
linearsearchobjects = buffer_manager.o file_manager.o linearsearch.o
binarysearchobjects = buffer_manager.o file_manager.o binarySearch.o binarySearchLeft.o binarySearchRight.o

sample_run : $(sampleobjects)
	     g++ -std=c++11 -o sample_run $(sampleobjects)

linearsearch : $(linearsearchobjects)
			 g++ -std=c++11 -o linearsearch $(linearsearchobjects)

binarysearch : $(binarysearchobjects)
		 	 # rm TestCases/TC_search/output_search_my
			 g++ -std=c++11 -o binarysearch $(binarysearchobjects)

sample_run.o : sample_run.cpp
	g++ -std=c++11 -c sample_run.cpp

linearsearch.o : linearsearch.cpp
	g++ -std=c++11 -c linearsearch.cpp

binarySearch.o : binarySearch.cpp
	g++ -std=c++11 -c binarySearch.cpp

binarysearchLeft.o : binarySearchLeft.cpp
	g++ -std=c++11 -c binarySearchLeft.cpp

binarysearchRight.o : binarySearchRight.cpp
	g++ -std=c++11 -c binarySearchRight.cpp

buffer_manager.o : buffer_manager.cpp
	g++ -std=c++11 -c buffer_manager.cpp

file_manager.o : file_manager.cpp
	g++ -std=c++11 -c file_manager.cpp

clean :
	rm -f *.o
	rm -f sample_run
	rm -f linearsearch binarysearch

runbinary:
	./binarysearch "TestCases/TC_search/sorted_input" "TestCases/TC_search/query_search.txt" "./TestCases/TC_search/output_search_my"

showbinaryoutput: reading
	./outContent
reading: reading.cpp file_manager.cpp  buffer_manager.cpp
	g++ -std=c++11 reading.cpp file_manager.cpp  buffer_manager.cpp -o outContent

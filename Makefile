sampleobjects = buffer_manager.o file_manager.o sample_run.o
linearsearchobjects = buffer_manager.o file_manager.o linearsearch.o
binarysearchobjects = buffer_manager.o file_manager.o binarySearch.o binarySearchLeft.o binarySearchRight.o
deletionObjects = deletion.o buffer_manager.o file_manager.o binarySearchLeft.o binarySearchRight.o
join1objects = buffer_manager.o file_manager.o join1.o
join2objects = buffer_manager.o file_manager.o join2.o binarySearchLeft.o binarySearchRight.o

sample_run : $(sampleobjects)
	     g++ -std=c++11 -o sample_run $(sampleobjects)

linearsearch : $(linearsearchobjects)
			 g++ -std=c++11 -o linearsearch $(linearsearchobjects)

binarysearch : $(binarysearchobjects)
		 	 # rm TestCases/TC_search/output_search_my
			 g++ -g -std=c++11 -o binarysearch $(binarysearchobjects)

deletion : $(deletionObjects)
			 g++ -g -std=c++11 -o deletion $(deletionObjects)

join1 : $(join1objects)
			 g++ -g -std=c++11 -o join1 $(join1objects)

join2 : $(join2objects)
			 g++ -g -std=c++11 -o join2 $(join2objects)

deletion.o : deletion.cpp
			 g++ -g -std=c++11 -c deletion.cpp

sample_run.o : sample_run.cpp
	g++ -std=c++11 -c sample_run.cpp

linearsearch.o : linearsearch.cpp
	g++ -std=c++11 -c linearsearch.cpp

binarySearch.o : binarySearch.cpp
	g++ -g -std=c++11 -c binarySearch.cpp

binarySearchLeft.o : binarySearchLeft.cpp
	g++ -g -std=c++11 -c binarySearchLeft.cpp

binarySearchRight.o : binarySearchRight.cpp
	g++ -g -std=c++11 -c binarySearchRight.cpp

join1.o : join1.cpp
	g++ -g -std=c++11 -c join1.cpp

join2.o : join2.cpp
	g++ -g -std=c++11 -c join2.cpp

buffer_manager.o : buffer_manager.cpp
	g++ -std=c++11 -c buffer_manager.cpp

file_manager.o : file_manager.cpp
	g++ -std=c++11 -c file_manager.cpp

clean :
	rm -f *.o
	rm -f sample_run
	rm -f linearsearch binarysearch deletion join1

rundeletion :
	./deletion "TestCases/TC_delete/sorted_input" "TestCases/TC_delete/query_delete.txt"

runbinary:
	./binarysearch "TestCases/TC_search/sorted_input" "TestCases/TC_search/query_search.txt" "./TestCases/TC_search/output_search_my"

showbinaryoutput: reading
	./outContent
reading: reading.cpp file_manager.cpp  buffer_manager.cpp
	g++ -std=c++11 reading.cpp file_manager.cpp  buffer_manager.cpp -o outContent

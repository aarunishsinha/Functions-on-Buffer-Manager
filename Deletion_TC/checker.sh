
# Test case 1
make clean
make deletion
timeout 1m ./deletion Deletion/tc1/input Deletion/tc1/query.txt >log1
./convert Deletion/tc1/input output1.txt
cmp --silent output1.txt Deletion/tc1/output.txt && echo 'TC1: SUCCESS' || echo 'TC1: FAILED'

# Test case 2
make clean
make deletion
timeout 1m ./deletion Deletion/tc2/input Deletion/tc2/query.txt >log2
./convert Deletion/tc2/input output2.txt
cmp --silent output2.txt Deletion/tc2/output.txt && echo 'TC2: SUCCESS' || echo 'TC2: FAILED'

# Test case 3
make clean
make deletion
timeout 2m ./deletion Deletion/tc3/input Deletion/tc3/query.txt >log3
./convert Deletion/tc3/input output3.txt
cmp --silent output3.txt Deletion/tc3/output.txt && echo 'TC3: SUCCESS' || echo 'TC3: FAILED'

# Test case 4
make clean
make deletion
timeout 2m ./deletion Deletion/tc4/input Deletion/tc4/query.txt >log4
./convert Deletion/tc4/input output4.txt
cmp --silent output4.txt Deletion/tc4/output.txt && echo 'TC4: SUCCESS' || echo 'TC4: FAILED'

# Test case 5
make clean
make deletion
timeout 2m ./deletion Deletion/tc5/input Deletion/tc5/query.txt >log5
./convert Deletion/tc5/input output5.txt
cmp --silent output5.txt Deletion/tc5/output.txt && echo 'TC5: SUCCESS' || echo 'TC5: FAILED'



echo "Running Testcase 1"
make clean
make join2
./join2 TC1_input1 TC1_input2 user_TC1_output_bin
./bin_to_txt 1
diff TC1_output user_TC1_output > TC1_diff.txt

echo "Running Testcase 2"
make clean
make join2
./join2 TC2_input1 TC2_input2 user_TC2_output_bin
./bin_to_txt 2
diff TC2_output user_TC2_output > TC2_diff.txt

echo "Running Testcase 3"
make clean
make join2
./join2 TC3_input1 TC3_input2 user_TC3_output_bin
./bin_to_txt 3
diff TC3_output user_TC3_output > TC3_diff.txt

echo "Running Testcase 4"
make clean
make join2
./join2 TC4_input1 TC4_input2 user_TC4_output_bin
./bin_to_txt 4
diff TC4_output user_TC4_output > TC4_diff.txt

echo "Running Testcase 5"
make clean
make join2
./join2 TC5_input1 TC5_input2 user_TC5_output_bin
./bin_to_txt 5
diff TC5_output user_TC5_output > TC5_diff.txt

echo "Running Testcase 6"
make clean
make join2
./join2 TC6_input1 TC6_input2 user_TC6_output_bin
./bin_to_txt 6
diff TC6_output user_TC6_output > TC6_diff.txt

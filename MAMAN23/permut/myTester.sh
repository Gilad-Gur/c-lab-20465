#!/bin/bash
make
echo "###################################################################" > text.out
echo "Testing data1.in file for word \"amo\"" >> text.out 
echo "Testing data1.in file for word \"amo\""
./permut >> text.out data1.in amo 2> errors.out
echo "###################################################################" >> text.out
echo "Testing data2.in file for word \"chair\"" >> text.out 
echo "Testing data2.in file for word \"chair\""
./permut >> text.out data2.in chair 2>> errors.out
echo "###################################################################" >> text.out
echo "Testing data3.in file for word \"room\"" >> text.out
echo "Testing data3.in file for word \"room\"" 
./permut >> text.out data3.in room 2>> errors.out
echo "###################################################################" >> text.out
echo "Testing data4.in file for word \"dog\"" >> text.out
echo "Testing data4.in file for word \"dog\""  
./permut >> text.out data4.in dog  2>> errors.out
echo "###################################################################" >> text.out
echo "Testing data5.in file for word \"dog\"" >> text.out
echo "Testing data5.in file for word \"dog\""  
./permut >> text.out data5.in dog 2>> errors.out
echo "###################################################################" >> text.out
echo "Testing data6.in file for word \"garlic\"" >> text.out
echo "Testing data6.in file for word \"garlic\""  
./permut >> text.out data6.in garlic 2>> errors.out
echo "###################################################################" >> text.out
echo "Testing data7.in file for word \"garlic\"" >> text.out
echo "Testing data7.in file for word \"garlic\""  
./permut >> text.out data7.in garlic 2>> errors.out
echo "###################################################################" >> text.out
echo "I am done, bye now"

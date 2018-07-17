#!/bin/bash

for i in `seq 1 3`; do
	./myset < test$i.txt > output$i.txt
done

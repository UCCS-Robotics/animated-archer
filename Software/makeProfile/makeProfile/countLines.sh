#!/bin/bash

echo Number of lines excluding QCP:

grep -v '^.*/' $(ls -1 *h *.c *.cpp | grep -v 'qcustomplot.*') | grep -v '^.*\*' | wc -l

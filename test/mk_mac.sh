#!/bin/sh
clang -std=gnu11 test.c -o test && \
clang -std=gnu11 wctest.c -o wctest  


#! /bin/bash

gcc -x c -o main \
  adt/adt.c adt/flt/adtflt.c adt/int/adtint.c adt/str/adtstr.c \
  stack/stack.c \
  queue/queue.c \
  utility.c main.c

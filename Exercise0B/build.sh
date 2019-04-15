
#! /bin/bash

gcc -x c -o main \
  adt/adt.c adt/int/adtint.c adt/flt/adtflt.c adt/str/adtstr.c adt/str/adtrec.c \
  stack/stack.c \
  queue/queue.c \
  utility.c main.c

#! /bin/bash

gcc -x c -o main \
  adt/adt.c adt/int/adtint.c adt/flt/adtflt.c adt/str/adtstr.c adt/rec/adtrec.c adt/ptr/adtptr.c\
  stack/stack.c stack/vec/stackvec.c stack/lst/stacklst.c \
  queue/queue.c queue/vec/queuevec.c queue/lst/queuelst.c \
  bst/bst.c bst/rec/bstrec.c bst/itr/bstitr.c \
  graph/graph.c graph/rec/graphrec.c graph/itr/graphitr.c \
  graph/rep/mat/graphmat.c graph/rep/lst/graphlst.c graph/rep/bst/graphbst.c graph/rep/mat/graphmatitradjacent.c graph/rep/bst/graphbstitradjacent.c graph/rep/lst/graphlstitradjacent.c \
  itr/itr.c \
  bst/bstitrpreord.c bst/bstitrinord.c bst/bstitrpostord.c bst/bstitrbreadth.c \
  graph/graphitrvertex.c \
  graph/graphitrpreord.c graph/graphitrpostord.c graph/graphitrbreadth.c \
  utility.c main.c testGraph.c testBST.c

cmake_minimum_required(VERSION 3.13)
project(Exercise1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(adt)
include_directories(adt/flt)
include_directories(adt/int)
include_directories(adt/rec)
include_directories(adt/str)
include_directories(queue)
include_directories(queue/lst)
include_directories(queue/vec)
include_directories(stack)
include_directories(stack/lst)
include_directories(stack/vec)

add_executable(Exercise1
        adt/flt/adtflt.c
        adt/flt/adtflt.h
        adt/int/adtint.c
        adt/int/adtint.h
        adt/rec/adtrec.c
        adt/rec/adtrec.h
        adt/str/adtstr.c
        adt/str/adtstr.h
        adt/adt.c
        adt/adt.h
        queue/lst/queuelst.c
        queue/lst/queuelst.h
        queue/vec/queuevec.c
        queue/vec/queuevec.h
        queue/queue.c
        queue/queue.h
        stack/lst/stacklst.c
        stack/lst/stacklst.h
        stack/vec/stackvec.c
        stack/vec/stackvec.h
        stack/stack.c
        stack/stack.h
        main.c
        utility.c
        utility.h test.c test.h)

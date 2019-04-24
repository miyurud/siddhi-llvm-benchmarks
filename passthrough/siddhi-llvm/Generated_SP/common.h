#ifndef GENERATED_SP_COMMON_H
#define GENERATED_SP_COMMON_H

#include <iostream>
#include <sys/time.h>

using namespace std;

inline long getCurrentTime() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec*(uint64_t)1000000+tp.tv_usec;
}

#endif
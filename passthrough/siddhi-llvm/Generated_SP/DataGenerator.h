#ifndef GENERATED_SP_DATAGENERATOR_H
#define GENERATED_SP_DATAGENERATOR_H

#include "Execution.h"

class DataGenerator {
private: Execution *execution;
    int flag = 0;
    int RECORD_WINDOW = 10000;
    long eventCountTotal = 0;
    long eventCount = 0;
    long value;
    long timeSpent = 0;
    long totalTimeSpent = 0;
    struct hdr_histogram *histogram1;
    struct hdr_histogram *histogram2;

public:
    DataGenerator( Execution *execution);
    void run(long veryFirstTime, int totalTime);
};

#endif
#include "DataGenerator.h"
#include "common.h"
#include <sys/time.h>
#include <hdr_histogram/hdr_histogram.h>

DataGenerator::DataGenerator(Execution  * execution) {
    this->execution = execution;
}

void DataGenerator::run(long veryFirstTime , int totalTime) {

    long startTime = veryFirstTime;
    hdr_init(1,INT64_C(3600000000),3,&histogram1);
    hdr_init(1,INT64_C(3600000000),3,&histogram2);

    while (flag == 0 ) {
        long timestamp = getCurrentTime();
        eventCount++;
        eventCountTotal++;
        long currentTime = getCurrentTime();
        timeSpent += (currentTime - timestamp);
        hdr_record_value(histogram1,timeSpent);
        hdr_record_value(histogram2,timeSpent);

        if (eventCount % RECORD_WINDOW == 0) {
            totalTimeSpent += timeSpent;
            value = currentTime - startTime;

            if (value == 0) {
                value++;
            }

            this->execution->setInputSource((eventCountTotal/RECORD_WINDOW),((eventCount * 1000000) / value),((eventCountTotal * 1000000) / (currentTime - veryFirstTime)),
                                            ((currentTime - veryFirstTime)/1000000.0),((timeSpent*1.0)/eventCount),((totalTimeSpent*1.0)/eventCountTotal),eventCountTotal,hdr_value_at_percentile(histogram1, 90),
                                            hdr_value_at_percentile(histogram1, 95),hdr_value_at_percentile(histogram1, 99),hdr_value_at_percentile(histogram2, 90),hdr_value_at_percentile(histogram2, 95),
                                            hdr_value_at_percentile(histogram2, 99));

            if ((currentTime - veryFirstTime) > (long)(totalTime * 60000000)) {
                flag = 1;
            }

            eventCount = 0;
            timeSpent = 0;
            hdr_reset(histogram2);
            startTime = getCurrentTime();
        }
    }
}
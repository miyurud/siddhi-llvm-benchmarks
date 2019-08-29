/**
Copyright 2019 Siddhi-LLVM Team
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "BenchmarkTest.h"
#include "common.h"
#include "iostream"
#include "PerformanceMonitor.h"

int BenchmarkTest::exitFlag = 0;
int BenchmarkTest::RECORD_WINDOW = 1000000;
long BenchmarkTest::startTime = getCurrentTime();
long BenchmarkTest::eventCountTotal = 0;
long BenchmarkTest::eventCount = 0;
long BenchmarkTest::value = 0;
long BenchmarkTest::timeSpent = 0;
long BenchmarkTest::totalTimeSpent = 0;
long BenchmarkTest::previousTimeForEvent = 0;
long BenchmarkTest::totalExperimentDuration = 0;
BenchmarkTest* BenchmarkTest::instance;

BenchmarkTest::BenchmarkTest(int min) {
    myfile.open("llvm-results.csv", ios::out | ios::trunc);
    myfile << "Id, Throughput in this window (events/second), Entire throughput for the run (events/second), Total "
              "elapsed time(s), Average latency per event (ms), Entire Average latency per event (ms), Total number of "
              "events received (non-atomic)\n";
    BenchmarkTest::instance = this;
    BenchmarkTest::totalExperimentDuration = min;
}

void BenchmarkTest::run(long iijTimestamp, long currentTime) {
    eventCount++;
    eventCountTotal++;
    timeSpent += (currentTime - iijTimestamp);
    if (eventCount % RECORD_WINDOW == 0) {
        totalTimeSpent += timeSpent;
        value = max((currentTime - startTime),(long)1);
        instance->myfile
                  << to_string(eventCountTotal / RECORD_WINDOW) + "," + to_string((eventCount * 1000000000) / value) +
                  "," + to_string((eventCountTotal * 1000) / (currentTime - PerformanceMonitor::getVeryFirstTime())) +
                  "," + to_string((currentTime - PerformanceMonitor::getVeryFirstTime()) / 1000.0) + "," +
                  to_string(timeSpent * 1.0 / eventCount) + "," + to_string((totalTimeSpent * 1.0) / eventCountTotal) +
                  "," + to_string(eventCountTotal) + "\n";
        if ((exitFlag == 0) && ((currentTime - PerformanceMonitor::getVeryFirstTime()) > (long) (totalExperimentDuration * 60000))) {
            exitFlag = 1;
        }
        startTime = getCurrentTime();
        eventCount = 0;
        timeSpent = 0;
    }
    previousTimeForEvent = getCurrentTime();
}

int BenchmarkTest::getFlag() {
    return exitFlag;
}

void BenchmarkTest::closeFile() {
    instance->myfile.close();
}
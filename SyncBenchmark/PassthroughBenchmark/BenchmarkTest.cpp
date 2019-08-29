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
#include "iostream"
#include "PerformanceMonitor.h"

int BenchmarkTest::exitFlag = 0;
int BenchmarkTest::RECORD_WINDOW = 1000000;
chrono::system_clock::time_point BenchmarkTest::startTime;
long BenchmarkTest::windowTime = 0;
long BenchmarkTest::eventCountTotal = 0;
long BenchmarkTest::eventCount = 0;
long BenchmarkTest::totalTimeSpent = 0;
chrono::system_clock::time_point BenchmarkTest::previousTimeForEvent = chrono::system_clock::now();
long BenchmarkTest::totalExperimentDuration = 0;
BenchmarkTest* BenchmarkTest::instance;

BenchmarkTest::BenchmarkTest(int min) {
    myfile.open("llvm-results.csv", ios::out | ios::trunc);
    myfile << "Id, Throughput in this window (events/second), Entire throughput for the run (events/second), Total "
              "elapsed time(s), Average latency per event (ms), Entire Average latency per event (ms), Total number of "
              "events received (non-atomic)\n";
    BenchmarkTest::instance = this;
    BenchmarkTest::totalExperimentDuration = min;
    startTime = PerformanceMonitor::getVeryFirstTime();
}

void BenchmarkTest::run(chrono::system_clock::time_point iijTimestamp, chrono::system_clock::time_point currentTime) {
    eventCount++;
    eventCountTotal++;
    long temp = (std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - iijTimestamp)).count();
    totalTimeSpent +=  temp;
    windowTime += temp;
    if (eventCount % RECORD_WINDOW == 0) {
        instance->myfile
                << to_string(eventCountTotal / RECORD_WINDOW) + "," + to_string((eventCount * 1000000000) /
                (std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - startTime)).count()) + "," +
                to_string((eventCountTotal * 1000000000) / (std::chrono::duration_cast<std::chrono::nanoseconds>
                (currentTime - PerformanceMonitor::getVeryFirstTime())).count()) + "," + to_string((std::chrono::
                duration_cast<std::chrono::nanoseconds>(currentTime - PerformanceMonitor::getVeryFirstTime())).count()
                / 1000000000.0) + "," + to_string((windowTime / (eventCount * 1000000.0))) + "," + to_string
                ((totalTimeSpent / (eventCountTotal * 1000000.0))) + "," + to_string(eventCountTotal) + "\n";
        if ((exitFlag == 0) && ((std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - PerformanceMonitor::
        getVeryFirstTime())).count() > (long) (totalExperimentDuration * 60000000000))) {
            exitFlag = 1;
        }
        eventCount = 0;
        windowTime = 0;
        startTime = chrono::system_clock::now();
    }
    previousTimeForEvent = chrono::system_clock::now();
}

int BenchmarkTest::getFlag() {
    return exitFlag;
}
void BenchmarkTest::closeFile() {
    instance->myfile.close();
}
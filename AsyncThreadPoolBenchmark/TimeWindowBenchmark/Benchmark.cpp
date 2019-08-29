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

#include <iostream>
#include <chrono>

#include "Benchmark.h"
#include "common.h"

chrono::_V2::high_resolution_clock::time_point Benchmark::veryFirstTime;
chrono::_V2::high_resolution_clock::time_point Benchmark::emitEndTime;
chrono::_V2::high_resolution_clock::time_point Benchmark::emitPreviousTime;
mutex Benchmark::m_mutex;
long Benchmark::latency = 0;
long Benchmark::totalLatency = 0;
long Benchmark::eventCount = 0;
long Benchmark::eventCountTotal = 0;
long Benchmark::totalTime = 0;
long Benchmark::preTotalTime = 0;
int Benchmark::exitFlag = 0;
int Benchmark::RECORD_WINDOW = 1000000;
ofstream Benchmark::myfile;

void Benchmark::prepareFile() {
    myfile.open("../llvm-results.csv", ios::out | ios::trunc);
    myfile << "Id, Throughput in this window (events/second), Entire throughput for the run (events/second), Total "
              "elapsed time(s), Average latency per event (ms), Entire Average latency per event (ms), Total number of "
              "events received (non-atomic)\n";
}

void Benchmark::run(long nanoGap) {
    m_mutex.lock();
    latency = ((latency * eventCount) + nanoGap) / (eventCount + 1);
    totalLatency = ((totalLatency * eventCountTotal) + nanoGap) / (eventCountTotal + 1);
    eventCount++;
    eventCountTotal++;

    if (eventCountTotal % RECORD_WINDOW == 0) {
        long temTotalTime;
        totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(getCurrentTime() - Benchmark::veryFirstTime).
                count();
        if (preTotalTime == 0) {
            temTotalTime = totalTime;
        } else {
            temTotalTime = totalTime - preTotalTime;
        }
        preTotalTime = totalTime;
        myfile << to_string(eventCountTotal / RECORD_WINDOW) + "," +
                to_string((eventCount * 1000000000) / temTotalTime) + "," +
                to_string((eventCountTotal * 1000000000) / totalTime) + "," +
                to_string(totalTime / 1000000000.0) + "," +
                to_string(latency / 1000000.0) + "," +
                to_string(totalLatency / 1000000.0) + "," +
                to_string(eventCountTotal) + "\n";
        if ((exitFlag == 0) && ((totalTime / 1000000000.0) > 1800)) {
            exitFlag = 1;
            myfile.close();
            cout << "Done the experiment. Exiting the benchmark." << endl;
            exit(0);
        }
        eventCount = 0;
        latency = 0;
    }
    m_mutex.unlock();
}

long Benchmark::getAvgNanoGap() {
    return latency;
}
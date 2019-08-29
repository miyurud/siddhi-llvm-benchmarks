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

#ifndef STREAM_PROCESSOR_BENCHMARKTEST_H
#define STREAM_PROCESSOR_BENCHMARKTEST_H

#include <fstream>
#include <chrono>

using namespace std;
class BenchmarkTest {
private:
    static int exitFlag;
    static int RECORD_WINDOW;
    static chrono::system_clock::time_point startTime;
    static long windowTime;
    static long eventCountTotal;
    static long eventCount;
    static long totalTimeSpent;
    ofstream myfile;
    static BenchmarkTest* instance;
    static long totalExperimentDuration;

public:
    static void run(chrono::system_clock::time_point iijTimestamp, chrono::system_clock::time_point currentTime);

    static int getFlag();

    static void closeFile();

    BenchmarkTest(int min);

    static chrono::system_clock::time_point previousTimeForEvent;
};

#endif
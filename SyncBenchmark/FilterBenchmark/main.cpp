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
#include "PerformanceMonitor.h"
#include "BenchmarkTest.h"
#include "TestTime.h"
#include "ListenerImpl.h"

int main() {
    TestTime testTime;
    ListenerImpl listener;
    testTime.setListener(listener);
    PerformanceMonitor::setStart();
    BenchmarkTest initiate(30);
    while (BenchmarkTest::getFlag() == 0) {
        testTime.sendData(chrono::system_clock::now());
    }
    BenchmarkTest::closeFile();
    cout << "Done the experiment. Exiting the benchmark." << endl;
    return 0;
}
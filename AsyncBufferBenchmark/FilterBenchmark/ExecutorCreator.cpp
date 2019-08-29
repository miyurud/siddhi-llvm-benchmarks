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

#include "ExecutorCreator.h"

long ExecutorCreator::iijTimestamp = getCurrentTime();
BufferContainer* ExecutorCreator::bufferContainer = nullptr;

ExecutorCreator::ExecutorCreator() {
    numberOfOutputAttributes = DetailContainer::getNumberOfOutputAttributes();
}

void ExecutorCreator::run(int consumerIndex) {
    while (BenchmarkTest::getFlag() == 0) {
        bufferContainer->executeProcess(consumerIndex);
    }
}

void ExecutorCreator::tempFunc() {
    PerformanceMonitor::setStart();
    BenchmarkTest initiate(1);
    int i = 0;
    while (BenchmarkTest::getFlag() == 0) {
        iijTimestamp = getCurrentTime();
        if (i % 10 > 2) {
            bufferContainer->pushWeight1Buffer(i);
        }
        i++;
    }
    BenchmarkTest::closeFile();
    cout << "Done the experiment. Exiting the benchmark." << endl;
}

void ExecutorCreator::createThreads(ExecutorCreator* executorCreator) {
    bufferContainer = new BufferContainer();
    thread t[numberOfOutputAttributes];
    for (int i = 0; i < numberOfOutputAttributes; ++i) {
        t[i] = std::thread(&ExecutorCreator::run, executorCreator, i);
    }
    thread th = thread(&ExecutorCreator::tempFunc, executorCreator);
    thread outputThread = thread(&ExecutorCreator::outputThreadFunc,executorCreator);
    for (int i = 0; i < numberOfOutputAttributes; ++i) {
        t[i].join();
    }
    th.join();
    outputThread.join();
    delete bufferContainer;
}

void ExecutorCreator::outputThreadFunc() {
    OutputEmitter outputEmitter;
    while (BenchmarkTest::getFlag() == 0) {
        outputEmitter.emitData(bufferContainer);
    }
}

BufferContainer* ExecutorCreator::getBufferContainer() {
    return bufferContainer;
}

long ExecutorCreator::getTimeStamp() {
    return iijTimestamp;
}
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

#ifndef STREAM_PROCESSOR_BUFFERLOCKER_H
#define STREAM_PROCESSOR_BUFFERLOCKER_H

#include <iostream>
#include "thread"
#include <mutex>
#include <condition_variable>
#include "DetailContainer.h"
#include "ProcessedThreadHandler.h"

using namespace std;
class BufferLocker {
private:
    static condition_variable m_condVar[constants::inputAttributeCount];
    static vector<int> processedConsumerList[constants::inputAttributeCount];
public:
    static mutex cout_mutex;
    static mutex mutexForPopPushLock[constants::inputAttributeCount];
    static bool canPopData(int inputIndex, int consumerIndex,unique_lock<mutex>* locker);
    static bool isNew(vector<int> vec, int val);
    static mutex* getCoutLock();
};

#endif
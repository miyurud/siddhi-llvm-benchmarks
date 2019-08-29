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

#include "BufferLocker.h"

condition_variable BufferLocker::m_condVar[constants::inputAttributeCount];
mutex BufferLocker::mutexForPopPushLock[constants::inputAttributeCount];
vector<int> BufferLocker::processedConsumerList[constants::inputAttributeCount];
mutex BufferLocker::cout_mutex;

bool BufferLocker::canPopData(int inputIndex, int consumerIndex,unique_lock<mutex>* locker) {
    while (!ProcessedThreadHandler::getValueForInputAndConsumer(consumerIndex,inputIndex)) {
        m_condVar[inputIndex].wait(*locker);
    }
    ProcessedThreadHandler::setValueForInputAndConsumer(false,consumerIndex,inputIndex);
    if (ProcessedThreadHandler::allSet(inputIndex)) {
        ProcessedThreadHandler::setAllDefault(inputIndex);
        m_condVar[inputIndex].notify_one();
        return true;
    }
    else {
        return false;
    }
    while (!isNew(processedConsumerList[inputIndex], consumerIndex)) {
        m_condVar[inputIndex].wait(*locker);
    }
    processedConsumerList[inputIndex].push_back(consumerIndex);
    if(processedConsumerList[inputIndex].size() == DetailContainer::getDependentConsumerCountForInput(inputIndex)){
        processedConsumerList[inputIndex].clear();
        m_condVar[inputIndex].notify_one();
        return true;
    }
    else{
        return false;
    }
}

bool BufferLocker::isNew(vector<int> vec, int val){
    for (int i = 0; i < vec.size(); ++i) {
        if(vec[i] == val){
            return false;
        }
    }
    return true;
}

mutex* BufferLocker::getCoutLock() {
    return &cout_mutex;
}
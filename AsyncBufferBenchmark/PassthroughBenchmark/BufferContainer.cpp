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

#include "BufferContainer.h"

BufferContainer::BufferContainer() {}

mutex BufferContainer::mutexForPopPushLock[constants::inputAttributeCount];

void BufferContainer::pushWeight1Buffer(int value) {
    weight1Buffer.push(value);
}

int BufferContainer::getFromWeight1Buffer(int consumerIndex) {
    unique_lock<mutex> lock(mutexForPopPushLock[0]);
    if (BufferLocker::canPopData(0, consumerIndex, &lock)) {
        return weight1Buffer.pop();
    }
    else{
        return weight1Buffer.front();
    }
}

void BufferContainer::processLogic0() {
    int weight1 = getFromWeight1Buffer(0);
    Executor::executeWeight1(weight1 );
}

void BufferContainer::executeProcess(int option) {
    switch(option) {
        case 0 : processLogic0();
        break;
    }
}

int BufferContainer::getFromWeight1OutputBuffer() {
    return weight1OutputBuffer.pop();
}

void BufferContainer::pushWeight1OutputBuffer(int value) {
    weight1OutputBuffer.push(value);
}
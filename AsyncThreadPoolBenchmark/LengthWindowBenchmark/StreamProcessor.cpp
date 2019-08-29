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

#include "StreamProcessor.h"
#include "TimeWindow.h"
#include "LengthWindow.h"

Buffer<Data> *StreamProcessor::buffer = NULL;
Processor *StreamProcessor::processor = NULL;
Window *StreamProcessor::window = NULL;

void StreamProcessor::initialize(int T_NUM) {
    StreamProcessor::buffer = new Buffer<Data>();
    StreamProcessor::processor = new Processor();
    StreamProcessor::window = new LengthWindow;
    window->setCondVariable(10);
    this->threadPool->initializeThreads(T_NUM);
}
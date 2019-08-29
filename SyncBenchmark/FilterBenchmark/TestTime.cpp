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

#include "TestTime.h"

Listener TestTime::listener;
void TestTime::sendData(chrono::system_clock::time_point time) {
    int value = std::chrono::time_point_cast<std::chrono::nanoseconds>(time).time_since_epoch().count() % 10;
    if (value > 2) {
        listener.recievedata(time);
    }
}

void TestTime::setListener(Listener listener1) {
    listener = listener1;
}
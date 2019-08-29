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

#include "ProcessedThreadHandler.h"

ProcessedThreadHandler::ProcessedThreadHandler() {}

bool ProcessedThreadHandler::boolArrayWeight1[1] = {true};

bool ProcessedThreadHandler::allSet(int  inputIndex) {
    switch (inputIndex) {
    case 0 :
        return !boolArrayWeight1[0];
    }
}

void ProcessedThreadHandler::setAllDefault(int  inputIndex) {
    switch (inputIndex) {
        case 0 :
            boolArrayWeight1[0] = true;
            break;
    }
}

void ProcessedThreadHandler::setValueForInputAndConsumer(bool value,int consumerIndex,int  inputIndex) {
    switch (inputIndex) {
        case 0 :
        switch (consumerIndex) {
            case 0 :
                boolArrayWeight1[0] = value;
                break;
        }
    }
}

bool ProcessedThreadHandler::getValueForInputAndConsumer(int consumerIndex,int  inputIndex) {
    switch (inputIndex) {
        case 0 :
            switch (consumerIndex) {
                case 0 :
                    return boolArrayWeight1[0];
            }
    }
}
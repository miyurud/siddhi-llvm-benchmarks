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

#ifndef STREAM_PROCESSOR_INPUTOUTPUTMAPPER_H
#define STREAM_PROCESSOR_INPUTOUTPUTMAPPER_H

#include <string>
#include "vector"

using namespace std;
class InputOutputMapper {
private:
    vector<string> dependOnList;
    string output;
public:
    void addToDependOn(string input);
    vector<string> getDependList();
    void setOutput(string outputM);
    string getOutput();
};

void InputOutputMapper::addToDependOn(string input) {
    dependOnList.push_back(input);
}

vector<string> InputOutputMapper::getDependList(){
    return dependOnList;
}

void InputOutputMapper::setOutput(string outputM){
    output = outputM;
}

string InputOutputMapper::getOutput(){
    return output;
}

#endif
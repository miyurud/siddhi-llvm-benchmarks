#include "Execution.h"

Execution::Execution() {}

void Execution::setInputSource(long col1, long col2, long col3, double col4, double col5, double col6, long col7, long col8, long col9, long col10, long col11, long col12, long col13) {
    inputSource.setData(col1, col2, col3, col4, col5, col6, col7, col8, col9, col10, col11, col12, col13);
    execute();
}
void Execution::execute(){
    outputSource.setData(inputSource.getData().getCol1(),inputSource.getData().getCol2(),inputSource.getData().getCol3(),inputSource.getData().getCol4(),
                         inputSource.getData().getCol5(),inputSource.getData().getCol6(),inputSource.getData().getCol7(),inputSource.getData().getCol8(),inputSource.getData().getCol9(),
                         inputSource.getData().getCol10(),inputSource.getData().getCol11(),inputSource.getData().getCol12(),inputSource.getData().getCol13());
}
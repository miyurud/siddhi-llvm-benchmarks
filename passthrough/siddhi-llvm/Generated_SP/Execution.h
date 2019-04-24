#ifndef GENERATED_SP_EXECUTION_H
#define GENERATED_SP_EXECUTION_H

#include "common.h"
#include "CargoStream.h"
#include "OutputStream.h"

class Execution {
public :
    Execution();
    void setInputSource(long col1, long col2, long col3, double col4, double col5, double col6, long col7, long col8, long col9, long col10, long col11, long col12, long col13);
    void execute();
    CargoStream inputSource;
    OutputStream outputSource;
};

#endif
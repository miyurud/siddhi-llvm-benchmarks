#include "CargoStream.h"

CargoStream::CargoStream() {}

void CargoStream::setData(long col1, long col2, long col3, double col4, double col5, double col6, long col7, long col8, long col9, long col10, long col11, long col12, long col13) {
    data.setCol1(col1);
    data.setCol2(col2);
    data.setCol3(col3);
    data.setCol4(col4);
    data.setCol5(col5);
    data.setCol6(col6);
    data.setCol7(col7);
    data.setCol8(col8);
    data.setCol9(col9);
    data.setCol10(col10);
    data.setCol11(col11);
    data.setCol12(col12);
    data.setCol13(col13);
}

Data CargoStream::getData() {
    return data;
}
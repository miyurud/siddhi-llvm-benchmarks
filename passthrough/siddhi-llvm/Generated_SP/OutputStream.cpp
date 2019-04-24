#include "OutputStream.h"
#include "Data.h"
#include "iostream"
#include "fstream"

OutputStream::OutputStream() {}

Data OutputStream::getData() {
    return data;
}

void OutputStream::setData(long col1, long col2, long col3, double col4, double col5, double col6, long col7, long col8, long col9, long col10, long col11, long col12, long col13) {

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

    ofstream myfile;
    myfile.open ("output.csv", ios::out | ios::app);
    myfile << (std::to_string(col1)+","+std::to_string(col2)+","+std::to_string(col3)+","+std::to_string(col4)+","+std::to_string(col5)
               +","+std::to_string(col6)+","+std::to_string(col7))+","+std::to_string(col8)+","+std::to_string(col9)+","+std::to_string(col10)
              +","+std::to_string(col11)+","+std::to_string(col12)+","+std::to_string(col13)+"\n";
    myfile.close();

}
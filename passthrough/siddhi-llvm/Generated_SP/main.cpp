#include <sys/time.h>
#include "DataGenerator.h"
#include "BenchMarkTesting.h"
#include "iostream"
#include "fstream"

int main() {

    int time = 1;
    ofstream myfile;
    myfile.open ("output.csv", ios::out | ios::app);
    myfile << "Id, Throughput in this window (events/second), Entire throughput for the run (events/second), "
              "Total elapsed time(s), Average latency per event (µs), Entire Average latency per event (µs), "
              "Total number of events received (non-atomic), AVG latency from start (90), AVG latency from start(95), "
              "AVG latency from start (99), AVG latency in this window(90), AVG latency in this window(95), AVG latency in this window(99)\n";
    myfile.close();
    BenchMarkTesting benchMarkTesting;
    benchMarkTesting.runBenchMark(time);

}
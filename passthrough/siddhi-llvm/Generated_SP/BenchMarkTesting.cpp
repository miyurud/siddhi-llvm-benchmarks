#include "BenchMarkTesting.h"
#include "common.h"
#include <sys/time.h>

BenchMarkTesting::BenchMarkTesting() {
    this->veryFirstTime = getCurrentTime();
}

void BenchMarkTesting::runBenchMark(int totalExperimentTime) {
    DataGenerator  dataGenerator(&execution);
    dataGenerator.run(veryFirstTime , totalExperimentTime);
}
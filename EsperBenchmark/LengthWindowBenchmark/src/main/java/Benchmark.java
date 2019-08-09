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

import com.espertech.esper.common.client.EPCompiled;
import com.espertech.esper.common.client.EventBean;
import com.espertech.esper.common.client.configuration.Configuration;
import com.espertech.esper.compiler.client.CompilerArguments;
import com.espertech.esper.compiler.client.EPCompileException;
import com.espertech.esper.compiler.client.EPCompiler;
import com.espertech.esper.compiler.client.EPCompilerProvider;
import com.espertech.esper.runtime.client.EPDeployException;
import com.espertech.esper.runtime.client.EPDeployment;
import com.espertech.esper.runtime.client.EPRuntime;
import com.espertech.esper.runtime.client.EPRuntimeProvider;
import com.espertech.esper.runtime.client.EPStatement;
import com.espertech.esper.runtime.client.UpdateListener;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.nio.charset.StandardCharsets;
import java.util.Random;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;

public class Benchmark {

    private static final Logger log = Logger.getLogger(Benchmark.class);
    private static String logDir = "./LengthWindowBenchmark/results";
    private static final int RECORD_WINDOW = 1000000; //This is the number of events to record.
    private static long eventCountTotal = 0;
    private static long eventCount = 0;
    private static long timeSpent = 0;
    private static long totalTimeSpent = 0;
    private static long totalExperimentDuration = 0;
    private static long startTime = System.currentTimeMillis();
    private static boolean flag;
    private static long veryFirstTime = System.currentTimeMillis();
    private static Writer fstream = null;
    private static long outputFileTimeStamp;
    private static boolean exitFlag = false;

    public static void main(String[] args) {

        Random rand = new Random();

        BasicConfigurator.configure();

        totalExperimentDuration = Long.parseLong(args[0]) * 60000;

        EPCompiler compiler = EPCompilerProvider.getCompiler();

        Configuration configuration = new Configuration();
        configuration.getCommon().addEventType(DataGenerator.class);

        CompilerArguments compilerArguments = new CompilerArguments(configuration);

        EPCompiled epCompiled;

        try {
            epCompiled = compiler.compile("@name('my-statement') select data, currentTime from " +
                    "DataGenerator.win:length(10)", compilerArguments);
        } catch (EPCompileException e) {
            throw new RuntimeException(e);
        }

        try {
            File directory = new File(logDir);

            if (!directory.exists()) {
                if (!directory.mkdir()) {
                    log.error("Error while creating the output directory.");
                }
            }

            outputFileTimeStamp = System.currentTimeMillis();
            fstream = new OutputStreamWriter(new FileOutputStream(new File(logDir +
                    "/esper-lengthwindow-results-" + (outputFileTimeStamp) + ".csv").getAbsoluteFile()),
                    StandardCharsets.UTF_8);

        } catch (IOException e) {
            log.error("Error while creating statistics output file, " + e.getMessage(), e);
        }

        EPRuntime runtime = EPRuntimeProvider.getDefaultRuntime(configuration);

        EPDeployment deployment;
        try {
            deployment = runtime.getDeploymentService().deploy(epCompiled);
        } catch (EPDeployException e) {
            throw new RuntimeException(e);
        }

        EPStatement epStatement = runtime.getDeploymentService().getStatement(deployment.getDeploymentId(),
                "my-statement");

        epStatement.addListener(new UpdateListener() {
            @Override
            public void update(EventBean[] eventBeans, EventBean[] eventBeans1, EPStatement epStatement, EPRuntime epRuntime) {
                long currentTime = System.currentTimeMillis();

                long iijTimestamp = (long) eventBeans[0].get("currentTime");

                try {
                    eventCount++;
                    eventCountTotal++;
                    timeSpent += (currentTime - iijTimestamp);

                    if (eventCount % RECORD_WINDOW == 0) {
                        totalTimeSpent += timeSpent;
                        long value = currentTime - startTime;

                        if (value == 0) {
                            value++;
                        }

                        if (!flag) {
                            flag = true;
                            fstream.write("Id, Throughput in this window (events/second), Entire throughput " +
                                    "for the run (events/second), Total elapsed time(s), Average latency per " +
                                    "event (ms), Entire Average latency per event (ms), Total number of events " +
                                    "received (non-atomic)"
                            );
                            fstream.write("\r\n");
                        }

                        fstream.write((eventCountTotal / RECORD_WINDOW) + "," + ((eventCount * 1000) / value) +
                                "," + ((eventCountTotal * 1000) / (currentTime - veryFirstTime)) + ","
                                + ((currentTime - veryFirstTime) / 1000f) + "," + (timeSpent * 1.0 / eventCount) +
                                "," + ((totalTimeSpent * 1.0) / eventCountTotal) + "," + eventCountTotal
                        );
                        fstream.write("\r\n");
                        fstream.flush();
                        startTime = System.currentTimeMillis();
                        eventCount = 0;
                        timeSpent = 0;

                        if (!exitFlag && ((currentTime - veryFirstTime) > totalExperimentDuration)) {
                            log.info("Exit flag set.");
                            exitFlag = true;
                        }
                    }
                } catch (Exception e) {
                    log.error("Error while consuming event, " + e.getMessage(), e);
                }

            }
        });

        while (!exitFlag) {
            runtime.getEventService().sendEventBean(new DataGenerator(rand.nextFloat(), System.currentTimeMillis()),
                    "DataGenerator");
        }

        log.info("Done the experiment. Exiting the benchmark.");

    }
}

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

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.nio.charset.StandardCharsets;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;
import org.wso2.siddhi.core.SiddhiAppRuntime;
import org.wso2.siddhi.core.SiddhiManager;
import org.wso2.siddhi.core.event.Event;
import org.wso2.siddhi.core.stream.input.InputHandler;
import org.wso2.siddhi.core.stream.output.StreamCallback;

public class Benchmark {

    private static final Logger log = Logger.getLogger(Benchmark.class);
    private static String logDir = "./PassthroughBenchmark/results";
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

        BasicConfigurator.configure();

        totalExperimentDuration = Long.parseLong(args[0]) * 60000;

        try {
            File directory = new File(logDir);

            if (!directory.exists()) {
                if (!directory.mkdir()) {
                    log.error("Error while creating the output directory.");
                }
            }

            outputFileTimeStamp = System.currentTimeMillis();
            fstream = new OutputStreamWriter(new FileOutputStream(new File(logDir +
                    "/siddhi-passthrough-results-" + (outputFileTimeStamp) + ".csv").getAbsoluteFile()),
                    StandardCharsets.UTF_8);
        } catch (IOException e) {
            log.error("Error while creating statistics output file, " + e.getMessage(), e);
        }

        SiddhiManager siddhiManager = new SiddhiManager();

        String siddhiApp = "define stream inputStream ( iij_timestamp long, value float); " +
                "define stream outputStream ( iij_timestamp long, value float); " +
                "@info(name = 'query1') from inputStream " +
                "select iij_timestamp, value insert into outputStream;";

        final SiddhiAppRuntime siddhiAppRuntime = siddhiManager.createSiddhiAppRuntime(siddhiApp);

        InputHandler inputHandler = siddhiAppRuntime.getInputHandler("inputStream");
        final DataGenerator dataLoader = new DataGenerator(inputHandler);
        dataLoader.start();

        siddhiAppRuntime.addCallback("outputStream", new StreamCallback() {

            @Override
            public void receive(Event[] events) {
                for (Event evt : events) {
                    long currentTime = System.currentTimeMillis();
                    long iijTimestamp = Long.parseLong(evt.getData()[0].toString());

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
                                    "," + ((eventCountTotal * 1000) / (currentTime - veryFirstTime)) + "," +
                                    ((currentTime - veryFirstTime) / 1000f) + "," + (timeSpent * 1.0 / eventCount) +
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
                                dataLoader.shutdown();
                                siddhiAppRuntime.shutdown();
                            }
                        }
                    } catch (Exception e) {
                        log.error("Error while consuming event, " + e.getMessage(), e);
                    }
                }
            }
        });

        while (!exitFlag) {
            try {
                Thread.sleep(10 * 1000);
            } catch (InterruptedException e) {
                log.error("Thread interrupted. " + e.getMessage(), e);
            }
        }

        log.info("Done the experiment. Exiting the benchmark.");

    }
}

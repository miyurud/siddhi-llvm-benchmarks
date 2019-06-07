import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

import org.HdrHistogram.Histogram;
import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;
import org.wso2.siddhi.core.SiddhiAppRuntime;
import org.wso2.siddhi.core.SiddhiManager;
import org.wso2.siddhi.core.event.Event;
import org.wso2.siddhi.core.stream.input.InputHandler;
import org.wso2.siddhi.core.stream.output.StreamCallback;

public class Main {

    private static final Logger log = Logger.getLogger(Main.class);
    private static String logDir = "./PassthroughBenchmark/results";
    private static String filteredLogDir = "./PassthroughBenchmark/filtered-results";
    private static final int RECORD_WINDOW = 10000; //This is the number of events to record.
    private static long eventCountTotal = 0;
    private static long eventCount = 0;
    private static long timeSpent = 0;
    private static long totalTimeSpent = 0;
    private static long warmupPeriod = 0;
    private static long totalExperimentDuration = 0;
    private static long startTime = System.currentTimeMillis();
    private static boolean flag;
    private static long veryFirstTime = System.currentTimeMillis();
    private static Writer fstream = null;
    private static long outputFileTimeStamp;
    private static boolean exitFlag = false;
    private static final Histogram histogram1 = new Histogram(2);
    private static final Histogram histogram2 = new Histogram(2);
    private static long time1 = System.currentTimeMillis();
    private static long time2 = System.currentTimeMillis();
    private static long totalTime = 0;

    public static void main(String[] args) {

        BasicConfigurator.configure();

        totalExperimentDuration = Long.parseLong(args[0]) * 60000;
        warmupPeriod = Long.parseLong(args[1]) * 60000;

        try {
            File directory = new File(logDir);

            if (!directory.exists()) {
                if (!directory.mkdir()) {
                    log.error("Error while creating the output directory.");
                }
            }

            outputFileTimeStamp = System.currentTimeMillis();
            fstream = new OutputStreamWriter(new FileOutputStream(new File(logDir + "/siddhi-results-" +
                    (outputFileTimeStamp) + ".csv").getAbsoluteFile()), StandardCharsets.UTF_8);
        } catch (IOException e) {
            log.error("Error while creating statistics output file, " + e.getMessage(), e);
        }

        SiddhiManager siddhiManager = new SiddhiManager();

        String siddhiApp = "define stream inputStream ( iij_timestamp long, value float);"
                + "define stream outputStream ( iij_timestamp long, value float);"
                + "@info(name = 'query1') from inputStream "
                + "select iij_timestamp, value insert into outputStream;";

        final SiddhiAppRuntime siddhiAppRuntime = siddhiManager.createSiddhiAppRuntime(siddhiApp);

        InputHandler inputHandler = siddhiAppRuntime.getInputHandler("inputStream");
        final DataGenerator dataLoader = new DataGenerator(inputHandler);
        dataLoader.start();

        siddhiAppRuntime.addCallback("outputStream", new StreamCallback() {

            @Override
            public void receive(Event[] events) {
                for (Event evt : events) {
                    time1 = System.currentTimeMillis();
                    long currentTime = System.currentTimeMillis();
                    histogram1.recordValue(timeSpent);
                    histogram2.recordValue(timeSpent);

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
                                fstream.write("Id, Throughput in this window (events/second), Entire throughput for the run (events/second), Total elapsed time(s), Average " +
                                        "latency per event (ms), Entire Average latency per event (ms), Total number of events received (non-atomic), AVG latency from start (90), " +
                                        "AVG latency from start(95), AVG latency from start (99), AVG latency in this window(90)," + "AVG latency in this window(95), AVG latency in this window(99)");
                                fstream.write("\r\n");
                            }

                            fstream.write((eventCountTotal / RECORD_WINDOW) + "," + ((eventCount * 1000) / value) + "," + ((eventCountTotal * 1000) / (currentTime - veryFirstTime)) + ","
                                    + ((currentTime - veryFirstTime) / 1000f) + "," + (timeSpent * 1.0 / eventCount) + "," + ((totalTimeSpent * 1.0) / eventCountTotal) + "," + eventCountTotal + ","
                                    + histogram1.getValueAtPercentile(90) + "," + histogram1.getValueAtPercentile(95) + "," + histogram1.getValueAtPercentile(99) + ","
                                    + histogram2.getValueAtPercentile(90) + "," + histogram2.getValueAtPercentile(95) + "," + histogram2.getValueAtPercentile(99));
                            fstream.write("\r\n");
                            fstream.flush();
                            histogram2.reset();
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
                    time2 = System.currentTimeMillis();
                    totalTime += (time2 - time1);
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

        log.info("Done the experiment. Exitting the benchmark.");
        System.out.println(getTime());

        preprocessPerformanceData();

    }

    private static void preprocessPerformanceData() {

        try {
            File directory = new File(filteredLogDir);

            if (!directory.exists()) {
                if (!directory.mkdir()) {
                    log.error("Error while creating the output directory.");
                }
            }

            fstream = new OutputStreamWriter(new FileOutputStream(new File(filteredLogDir + "/siddhi-results-" +
                    (outputFileTimeStamp) + ".csv").getAbsoluteFile()), StandardCharsets.UTF_8);
        } catch (IOException e) {
            log.error("Error while creating statistics output file, " + e.getMessage(), e);
        }

        BufferedReader br = null;

        //File reading
        try {
            String line;
            String csvSplitBy = ",";
            int iteration = 0;
            br = new BufferedReader(
                    new InputStreamReader(new FileInputStream(logDir + "/siddhi-results-" +
                            (outputFileTimeStamp) + ".csv"), Charset.forName("UTF-8")));

            while ((line = br.readLine()) != null) {
                if (iteration == 0) {
                    iteration++;
                    continue;
                }
                //use coma separator./
                String[] filteredData = line.split(csvSplitBy);
                float time = Float.parseFloat(filteredData[3]);
                if (time > warmupPeriod / 1000.0) {
                    fstream.write(
                            filteredData[0] + "," + filteredData[1] + "," + filteredData[2] + "," + filteredData[3]
                                    + "," + filteredData[4] + "," + filteredData[5] + "," + filteredData[6]
                                    + "," + filteredData[7] + "," + filteredData[8] + "," + filteredData[9]
                                    + "," + filteredData[10] + "," + filteredData[11] + "," + filteredData[12]);
                    fstream.write("\r\n");
                    fstream.flush();
                }
            }
        } catch (IOException ex) {
            log.error(ex);
        } finally {
            if (br != null) {
                try {
                    br.close();
                    fstream.close();

                } catch (IOException e) {
                    log.error(e);
                }
            }
        }
    }

    private static long getTime() {
        return totalTime;
    }
}
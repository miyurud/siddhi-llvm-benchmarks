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
import java.util.Random;

import org.HdrHistogram.Histogram;
import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;

public class Main {

    private static final Logger log = Logger.getLogger(Main.class);
    private static String logDir = "./FilterBenchmark/results";
    private static String filteredLogDir = "./FilterBenchmark/filtered-results";
    private static final int RECORD_WINDOW = 10000;
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

    public static void main(String[] args) {

        Random rand = new Random();

        BasicConfigurator.configure();

        totalExperimentDuration = Long.parseLong(args[0]) * 60000;
        warmupPeriod = Long.parseLong(args[1]) * 60000;

        EPCompiler compiler = EPCompilerProvider.getCompiler();

        Configuration configuration = new Configuration();
        configuration.getCommon().addEventType(DataGenerator.class);

        CompilerArguments compilerArguments = new CompilerArguments(configuration);

        EPCompiled epCompiled;

        try {
            epCompiled = compiler.compile("@name('my-statement') select data, currentTime from DataGenerator (data < 2)", compilerArguments);
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
            fstream = new OutputStreamWriter(new FileOutputStream(new File(logDir + "/esper-results-" +
                    (outputFileTimeStamp) + ".csv").getAbsoluteFile()), StandardCharsets.UTF_8);

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

        EPStatement epStatement = runtime.getDeploymentService().getStatement(deployment.getDeploymentId(), "my-statement");

        epStatement.addListener(new UpdateListener() {
            @Override
            public void update(EventBean[] eventBeans, EventBean[] eventBeans1, EPStatement epStatement, EPRuntime epRuntime) {
                long currentTime = System.currentTimeMillis();
                histogram1.recordValue(timeSpent);
                histogram2.recordValue(timeSpent);

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
                        }
                    }
                } catch (Exception e) {
                    log.error("Error while consuming event, " + e.getMessage(), e);
                }

            }
        });

        while (!exitFlag) {
            runtime.getEventService().sendEventBean(new DataGenerator(rand.nextFloat(), System.currentTimeMillis()), "DataGenerator");
        }

        log.info("Done the experiment. Exitting the benchmark.");

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

            fstream = new OutputStreamWriter(new FileOutputStream(new File(filteredLogDir + "/esper-results-" +
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
                    new InputStreamReader(new FileInputStream(logDir + "/esper-results-" +
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
}
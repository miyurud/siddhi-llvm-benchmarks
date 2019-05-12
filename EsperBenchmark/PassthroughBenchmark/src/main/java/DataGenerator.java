public class DataGenerator {
    long data;
    long currentTime;

    public DataGenerator(long data, long currentTime) {
        this.data = data;
        this.currentTime = currentTime;
    }

    public long getData() {
        return data;
    }

    public void setData(long data) {
        this.data = data;
    }

    public long getCurrentTime() {
        return currentTime;
    }

    public void setCurrentTime(long currentTime) {
        this.currentTime = currentTime;
    }
}
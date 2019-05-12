public class DataGenerator {
    float data;
    long currentTime;

    public DataGenerator(float data, long currentTime) {
        this.data = data;
        this.currentTime = currentTime;
    }

    public float getData() {
        return data;
    }

    public void setData(float data) {
        this.data = data;
    }

    public long getCurrentTime() {
        return currentTime;
    }

    public void setCurrentTime(long currentTime) {
        this.currentTime = currentTime;
    }
}
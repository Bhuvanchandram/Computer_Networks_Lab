public class LeakyBucket {
    private static final int BUCKET_SIZE = 10;
    private static final int PACKET_RATE = 5;

    private int bucketSize;
    private int packetRate;
    private int currentSize;
    private long lastUpdateTime;

    public LeakyBucket() {
        this(BUCKET_SIZE, PACKET_RATE);
    }

    public LeakyBucket(int bucketSize, int packetRate) {
        this.bucketSize = bucketSize;
        this.packetRate = packetRate;
        this.currentSize = 0;
        this.lastUpdateTime = System.currentTimeMillis();
    }

    public boolean canSendPacket() {
        // Calculate elapsed time since last update
        long elapsedTime = System.currentTimeMillis() - lastUpdateTime;

        // Update the current size of the bucket
        currentSize = Math.max(0, currentSize - elapsedTime * packetRate);

        // Update the last update time
        lastUpdateTime = System.currentTimeMillis();

        // Check if there is room in the bucket for the packet
        return currentSize + 1 <= bucketSize;
    }

    public void sendPacket() {
        // Increment the current size of the bucket
        currentSize++;
    }
}


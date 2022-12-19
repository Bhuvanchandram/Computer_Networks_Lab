public class TokenBucket {
    private static final int BUCKET_SIZE = 10;
    private static final int TOKEN_RATE = 5;

    private int bucketSize;
    private int tokenRate;
    private int currentSize;
    private long lastUpdateTime;

    public TokenBucket() {
        this(BUCKET_SIZE, TOKEN_RATE);
    }

    public TokenBucket(int bucketSize, int tokenRate) {
        this.bucketSize = bucketSize;
        this.tokenRate = tokenRate;
        this.currentSize = 0;
        this.lastUpdateTime = System.currentTimeMillis();
    }

    public boolean canSendPacket() {
        // Calculate elapsed time since last update
        long elapsedTime = System.currentTimeMillis() - lastUpdateTime;

        // Update the current size of the bucket
        currentSize = Math.min(bucketSize, currentSize + (int)(elapsedTime * tokenRate));

        // Update the last update time
        lastUpdateTime = System.currentTimeMillis();

        // Check if there are enough tokens in the bucket for the packet
        return currentSize >= 1;
    }

    public void sendPacket() {
        // Decrement the current size of the bucket
        currentSize--;
    }
}

package civicsentinel;

/**
 * Binary Indexed Tree (Fenwick Tree) for Ward Commodity & PDS Tracking.
 * 
 * Provides O(log W) point updates and O(log W) range queries across W municipal wards.
 * Essential for high-concurrency food grain monitoring, ration stockout detection,
 * and emergency buffer reallocation during food crises (ISPP Food Security dimension).
 */
public class WardCommodityBIT {
    private final int totalWards;
    private final long[] bitTree;

    public WardCommodityBIT(int numWards) {
        this.totalWards = numWards;
        this.bitTree = new long[numWards + 1];
    }

    /**
     * Adds or removes grain stock from a specific ward.
     * Complexity: O(log W)
     */
    public void addStock(int ward, long deltaKg) {
        if (ward < 1 || ward > totalWards) return;
        for (; ward <= totalWards; ward += ward & -ward) {
            bitTree[ward] += deltaKg;
        }
    }

    /**
     * Computes cumulative grain stock from Ward 1 through Ward k.
     * Complexity: O(log W)
     */
    public long prefixStock(int ward) {
        if (ward > totalWards) ward = totalWards;
        long sum = 0;
        for (; ward > 0; ward -= ward & -ward) {
            sum += bitTree[ward];
        }
        return sum;
    }

    /**
     * Computes total grain reserves in a contiguous ward sector [left_ward, right_ward].
     * Complexity: O(log W)
     */
    public long rangeStock(int leftWard, int rightWard) {
        if (leftWard < 1) leftWard = 1;
        if (rightWard > totalWards) rightWard = totalWards;
        if (leftWard > rightWard) return 0;
        return prefixStock(rightWard) - prefixStock(leftWard - 1);
    }

    /**
     * Returns current stock in an isolated single ward.
     * Complexity: O(log W)
     */
    public long getWardStock(int ward) {
        return rangeStock(ward, ward);
    }

    public int getWardCount() {
        return totalWards;
    }
}

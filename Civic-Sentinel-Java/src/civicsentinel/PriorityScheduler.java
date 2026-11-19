package civicsentinel;

import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * ============================================================================
 * DSA CONCEPT: BINARY MAX-HEAP (PriorityQueue)
 * Outside code never touches the raw PriorityQueue directly (OOP Encapsulation).
 * Uses a custom comparator to order records in descending priority score.
 * ============================================================================
 */
public class PriorityScheduler {

    public static class RecordPriorityComparator implements Comparator<BaseRecord> {
        @Override
        public int compare(BaseRecord a, BaseRecord b) {
            // Descending order for Max-Heap
            return Double.compare(b.calculatePriorityScore(), a.calculatePriorityScore());
        }
    }

    // Binary Max-Heap storing polymorphic records: O(N) space
    private final PriorityQueue<BaseRecord> maxHeap;

    public PriorityScheduler() {
        this.maxHeap = new PriorityQueue<>(new RecordPriorityComparator());
    }

    // Insert new grievance into Heap: O(log N)
    public void schedule(BaseRecord record) {
        if (record != null) {
            maxHeap.offer(record);
        }
    }

    // Inspect the top crisis without removing it: O(1)
    public BaseRecord peekHighestPriority() {
        return maxHeap.peek();
    }

    // Extract the most urgent crisis for the municipal team to resolve: O(log N)
    public BaseRecord popHighestPriority() {
        return maxHeap.poll();
    }

    public boolean isEmpty() {
        return maxHeap.isEmpty();
    }

    public int size() {
        return maxHeap.size();
    }
}

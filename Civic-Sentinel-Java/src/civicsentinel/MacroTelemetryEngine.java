package civicsentinel;

import java.util.Map;
import java.util.TreeMap;

/**
 * Macroeconomic Telemetry Engine using Balanced Search Trees (Red-Black BST via java.util.TreeMap).
 * 
 * Provides O(log M) insertion and chronological range queries across monthly evaluation cycles.
 * Used by the rating equation:
 * Rating = 0.35 * GrievanceScore + 0.35 * PovertyReductionDelta + 0.30 * EconomicActivityGrowth
 */
public class MacroTelemetryEngine {
    private final TreeMap<Long, MonthlyMacroTelemetry> telemetryBst; // Red-Black BST

    public MacroTelemetryEngine() {
        this.telemetryBst = new TreeMap<>();
    }

    public void recordSnapshot(MonthlyMacroTelemetry snapshot) {
        if (snapshot != null) {
            telemetryBst.put(snapshot.month_id, snapshot);
        }
    }

    public MonthlyMacroTelemetry getSnapshot(long monthId) {
        return telemetryBst.get(monthId);
    }

    /**
     * Computes poverty reduction delta between two evaluation months.
     * Complexity: O(log M)
     */
    public double computePovertyReductionDelta(long startMonth, long endMonth) {
        MonthlyMacroTelemetry start = telemetryBst.get(startMonth);
        MonthlyMacroTelemetry end = telemetryBst.get(endMonth);

        if (start == null || end == null) {
            return 0.0;
        }

        double startBpl = start.bpl_households;
        double endBpl = end.bpl_households;

        if (startBpl == 0.0) return 0.0;

        // Percentage reduction in BPL households: positive value indicates poverty reduction
        return ((startBpl - endBpl) / startBpl) * 100.0;
    }

    /**
     * Displays chronological audit trail for all recorded cycles.
     */
    public void displayAuditTrail() {
        System.out.println("\n===========================================================");
        System.out.println("   CHRONOLOGICAL MACROECONOMIC AUDIT TRAIL (RED-BLACK BST) ");
        System.out.println("===========================================================");
        for (Map.Entry<Long, MonthlyMacroTelemetry> entry : telemetryBst.entrySet()) {
            System.out.println(">>> CYCLE: " + entry.getKey());
            entry.getValue().display();
            System.out.println("-----------------------------------------------------------");
        }
    }
}

package civicsentinel;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;

/**
 * ============================================================================
 * DSA CONCEPT: BALANCED SEARCH TREE (RED-BLACK TREE via java.util.TreeMap)
 * Stores monthly telemetry sorted chronologically in O(log M) time.
 * Enables O(log M + K) range queries via subMap().
 * ============================================================================
 */
public class TelemetryEngine {
    // Red-Black Tree mapping chronological DateKey ("YYYY-MM") -> MonthlyTelemetry
    private final TreeMap<String, MonthlyTelemetry> historicalTelemetry;

    public TelemetryEngine() {
        this.historicalTelemetry = new TreeMap<>();
    }

    // Insert monthly log: O(log M)
    public void logMonth(MonthlyTelemetry telemetry) {
        if (telemetry != null && telemetry.monthKey != null) {
            historicalTelemetry.put(telemetry.monthKey, telemetry);
        }
    }

    // Dynamic Range Query using BST subMap: O(log M + K)
    public List<MonthlyTelemetry> getRangeTelemetry(String startMonth, String endMonth) {
        List<MonthlyTelemetry> result = new ArrayList<>();
        if (startMonth == null || endMonth == null) return result;

        Map<String, MonthlyTelemetry> subMap = historicalTelemetry.subMap(startMonth, true, endMonth, true);
        result.addAll(subMap.values());
        return result;
    }

    /**
     * ========================================================================
     * ALGORITHMIC POLITICIAN EVALUATION FORMULA (0 - 100 SCORECARD)
     * Rating = (0.35 * GrievanceScore) + (0.35 * PovertyDelta) + (0.30 * Satisfaction)
     * ========================================================================
     */
    public double calculatePoliticianScore(String startMonth, String endMonth) {
        List<MonthlyTelemetry> logs = getRangeTelemetry(startMonth, endMonth);
        if (logs.isEmpty()) return 0.0;

        double totalResolutionRatio = 0.0;
        double totalPovertyDelta = 0.0;
        double totalSatisfaction = 0.0;

        for (MonthlyTelemetry log : logs) {
            double ratio = (log.grievancesReported > 0)
                    ? (((double) log.grievancesResolved) / log.grievancesReported) * 100.0
                    : 100.0;
            totalResolutionRatio += Math.min(100.0, ratio);
            totalPovertyDelta += log.povertyReductionDelta * 20.0; // Scaled to 100
            totalSatisfaction += log.citizenSatisfactionScore;
        }

        int n = logs.size();
        double avgResolution = totalResolutionRatio / n;
        double avgPoverty = Math.min(100.0, Math.max(0.0, totalPovertyDelta / n));
        double avgSatisfaction = totalSatisfaction / n;

        // Synopsis Formula: 35% Resolution + 35% Poverty Alleviation + 30% Public Satisfaction
        return (0.35 * avgResolution) + (0.35 * avgPoverty) + (0.30 * avgSatisfaction);
    }

    public void displayPoliticianAudit(String politicianName, String wardId,
                                       String startMonth, String endMonth) {
        List<MonthlyTelemetry> logs = getRangeTelemetry(startMonth, endMonth);

        System.out.println("\n========================================================");
        System.out.println("  POLITICIAN ACCOUNTABILITY AUDIT SCORECARD (0-100)    ");
        System.out.println("========================================================");
        System.out.println(" Representative : " + politicianName);
        System.out.println(" Jurisdiction   : " + wardId);
        System.out.println(" Audit Window   : " + startMonth + " to " + endMonth
                + " (" + logs.size() + " Months Audited)");
        System.out.println("--------------------------------------------------------");

        for (MonthlyTelemetry log : logs) {
            System.out.printf(Locale.US,
                    " [%s] Reported: %2d | Resolved: %2d | Poverty Delta: +%.1f%% | Public Satisfaction: %.1f/100%n",
                    log.monthKey, log.grievancesReported, log.grievancesResolved,
                    log.povertyReductionDelta, log.citizenSatisfactionScore);
        }

        double score = calculatePoliticianScore(startMonth, endMonth);
        System.out.println("--------------------------------------------------------");
        System.out.printf(Locale.US, " FINAL COMPOSITE DEMOCRATIC RATING: %.2f / 100.00%n", score);

        // Democratic Grading Scale
        if (score >= 85.0)      System.out.println(" PERFORMANCE GRADE: [A+] Exemplary Public Leadership");
        else if (score >= 70.0) System.out.println(" PERFORMANCE GRADE: [B] Satisfactory Progress");
        else if (score >= 50.0) System.out.println(" PERFORMANCE GRADE: [C] Moderate Public Deficit");
        else                    System.out.println(" PERFORMANCE GRADE: [F] CRITICAL FAILURE - High Electoral Vulnerability");
        System.out.println("========================================================");
    }
}

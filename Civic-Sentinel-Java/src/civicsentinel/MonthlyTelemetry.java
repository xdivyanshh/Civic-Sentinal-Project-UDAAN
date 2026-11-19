package civicsentinel;

/**
 * Single monthly telemetry snapshot.
 */
public class MonthlyTelemetry {
    public String monthKey; // Format: "YYYY-MM" (e.g. "2026-08")
    public int grievancesReported;
    public int grievancesResolved;
    public double povertyReductionDelta;    // In % (e.g. +3.2%)
    public double economicGrowthDelta;       // In % (e.g. +2.1%)
    public double citizenSatisfactionScore;  // 0 to 100

    public MonthlyTelemetry(String monthKey, int grievancesReported, int grievancesResolved,
                            double povertyReductionDelta, double economicGrowthDelta,
                            double citizenSatisfactionScore) {
        this.monthKey = monthKey;
        this.grievancesReported = grievancesReported;
        this.grievancesResolved = grievancesResolved;
        this.povertyReductionDelta = povertyReductionDelta;
        this.economicGrowthDelta = economicGrowthDelta;
        this.citizenSatisfactionScore = citizenSatisfactionScore;
    }
}

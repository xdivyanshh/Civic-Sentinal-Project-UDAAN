package civicsentinel;

import java.util.Locale;

/**
 * Monthly Macroeconomic Snapshot.
 * Captures ward and municipal level socio-economic telemetry for administrative audit.
 */
public class MonthlyMacroTelemetry {
    public long month_id;              // e.g., 202610, 202611
    public int total_population;
    public int bpl_households;
    public double average_monthly_income;
    public double unemployment_rate;
    public int jobs_placed_count;
    public double emergency_stimulus_disbursed;
    public double pds_grain_distributed_kg;

    public MonthlyMacroTelemetry(long month_id, int total_population, int bpl_households,
                                 double average_monthly_income, double unemployment_rate,
                                 int jobs_placed_count, double emergency_stimulus_disbursed,
                                 double pds_grain_distributed_kg) {
        this.month_id = month_id;
        this.total_population = total_population;
        this.bpl_households = bpl_households;
        this.average_monthly_income = average_monthly_income;
        this.unemployment_rate = unemployment_rate;
        this.jobs_placed_count = jobs_placed_count;
        this.emergency_stimulus_disbursed = emergency_stimulus_disbursed;
        this.pds_grain_distributed_kg = pds_grain_distributed_kg;
    }

    public void display() {
        System.out.println("  Snapshot Month            : " + month_id);
        System.out.println("  Total Population Monitored : " + total_population);
        System.out.println("  BPL Household Count       : " + bpl_households);
        System.out.printf(Locale.US, "  Average Monthly Income    : Rs.%.2f%n", average_monthly_income);
        System.out.printf(Locale.US, "  Unemployment Rate         : %.1f%%%n", unemployment_rate);
        System.out.println("  Jobs Placed (Public Works): " + jobs_placed_count);
        System.out.printf(Locale.US, "  Stimulus Relief Disbursed : Rs.%.2f%n", emergency_stimulus_disbursed);
        System.out.printf(Locale.US, "  PDS Grain Distributed     : %.1f kg%n", pds_grain_distributed_kg);
    }
}

package civicsentinel;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

/**
 * Citizen Profile and Multidimensional Poverty Index (MPI) Model.
 * 
 * Incorporates multidimensional poverty indicators based on research from the
 * Indian School of Public Policy (ISPP) and Collins Ayoo (IntechOpen):
 * - Monetary Dimension: Monthly Income, Debt Burden
 * - Human Capital Dimension: Health Vulnerability, Vocational Skills
 * - Demographic Dimension: Dependent Ratio, Living Standard Status (BPL)
 */
public class CitizenProfile {
    public long citizen_id;               // Unique Voter / Aadhaar Hash
    public int ward_id;                   // Geospatial Municipal Ward ID (1 to W)
    public double monthly_income;         // Direct monthly earnings (INR)
    public int dependents;                // Non-earning family members (children, elderly)
    public double debt_obligation;        // Total outstanding formal/informal liabilities
    public int health_vulnerability;      // Scale 1 (Good) to 5 (Severe chronic health burden)
    public List<String> skills;           // Categorized vocational skills
    public int employment_status;         // 0: Unemployed, 1: Daily Wage / Seasonal, 2: Stable
    public boolean is_bpl;                // Below Poverty Line flag

    public CitizenProfile(long citizen_id, int ward_id, double monthly_income,
                          int dependents, double debt_obligation, int health_vulnerability,
                          List<String> skills, int employment_status, boolean is_bpl) {
        this.citizen_id = citizen_id;
        this.ward_id = ward_id;
        this.monthly_income = monthly_income;
        this.dependents = dependents;
        this.debt_obligation = debt_obligation;
        this.health_vulnerability = health_vulnerability;
        this.skills = skills != null ? new ArrayList<>(skills) : new ArrayList<>();
        this.employment_status = employment_status;
        this.is_bpl = is_bpl;
    }

    /**
     * Computes the Multidimensional Poverty Index (MPI) for the citizen.
     * Higher score indicates higher socio-economic vulnerability.
     */
    public double compute_mpi() {
        // 1. Income Inverse Factor: Lower income exponentially increases vulnerability
        double income_factor = (monthly_income <= 0) ? 100.0 : (10000.0 / (monthly_income + 50.0));

        // 2. Dependency Burden Factor
        double dependent_factor = dependents * 3.5;

        // 3. Debt Stress Ratio Factor (Debt to Income leverage)
        double debt_factor = (debt_obligation / (monthly_income + 100.0)) * 12.0;

        // 4. Chronic Health Burden Factor
        double health_factor = health_vulnerability * 4.0;

        // 5. Employment Insecurity Weight
        double employment_factor = (employment_status == 0) ? 25.0 : ((employment_status == 1) ? 10.0 : 0.0);

        return income_factor + dependent_factor + debt_factor + health_factor + employment_factor;
    }

    public void display() {
        String statusStr = (employment_status == 0 ? "Unemployed" : (employment_status == 1 ? "Daily-Wage" : "Stable"));
        System.out.printf(Locale.US,
                "Citizen #%d | Ward %d | Income: Rs.%.2f | Debt: Rs.%.2f | Dependents: %d | Status: %s | MPI: %.2f | BPL: %s%n",
                citizen_id, ward_id, monthly_income, debt_obligation, dependents, statusStr, compute_mpi(), (is_bpl ? "YES" : "NO"));
    }
}

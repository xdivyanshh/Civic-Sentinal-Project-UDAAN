package civicsentinel;

/**
 * Citizen Economic Grievance Node.
 * Represents an issue submitted by verified citizens with dynamic priority ranking.
 */
public class EconomicGrievance {
    public int issue_id;
    public EconomicSector sector;
    public int ward_id;
    public String description;
    public int verified_upvotes;
    public double aggregated_mpi;         // Sum of MPI of all endorsing citizens
    public long timestamp;                // Epoch tick when issue was lodged

    public EconomicGrievance(int issue_id, EconomicSector sector, int ward_id,
                             String description, int verified_upvotes,
                             double aggregated_mpi, long timestamp) {
        this.issue_id = issue_id;
        this.sector = sector;
        this.ward_id = ward_id;
        this.description = description;
        this.verified_upvotes = verified_upvotes;
        this.aggregated_mpi = aggregated_mpi;
        this.timestamp = timestamp;
    }

    /**
     * Computes priority score combining vulnerability, consensus, and starvation aging.
     * 
     * Formula:
     *   Priority = (0.45 * aggregated_mpi) + (0.35 * verified_upvotes) + (0.20 * (current_tick - timestamp))
     * 
     * - aggregated_mpi prevents affluent wards from dominating queue roots.
     * - verified_upvotes preserves community consensus.
     * - (current_tick - timestamp) guarantees starvation prevention (aging factor).
     */
    public double priority_score(long current_tick) {
        double urgency = (aggregated_mpi * 0.45) + (verified_upvotes * 0.35);
        double aging_escalation = (current_tick >= timestamp) ? (current_tick - timestamp) * 0.20 : 0.0;
        return urgency + aging_escalation;
    }
}

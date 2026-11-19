package civicsentinel;

import java.util.Locale;

/**
 * ============================================================================
 * OOP PILLAR 3: INHERITANCE
 * SuggestionRecord specializes BaseRecord for civic policy proposals.
 * ============================================================================
 */
public class SuggestionRecord extends BaseRecord {
    private String targetDepartment;
    private int feasibilityVotes;
    private int projectedBeneficiaries;

    public SuggestionRecord(int id, CivicCategory category, String title,
                            String description, String wardId, String citizenId,
                            String targetDepartment, int projectedBeneficiaries) {
        super(id, RecordType.SUGGESTION, category, title, description, wardId, citizenId);
        this.targetDepartment = targetDepartment;
        this.feasibilityVotes = 0;
        this.projectedBeneficiaries = projectedBeneficiaries;
    }

    // Getters
    public String getTargetDepartment() { return targetDepartment; }
    public int getFeasibilityVotes() { return feasibilityVotes; }
    public int getProjectedBeneficiaries() { return projectedBeneficiaries; }

    public void addFeasibilityVote() {
        this.feasibilityVotes++;
    }

    // ========================================================================
    // OOP PILLAR 4: POLYMORPHISM
    // Policy suggestions are weighted based on citizen feasibility votes
    // and projected public impact.
    // ========================================================================
    @Override
    public double calculatePriorityScore() {
        double voteWeight = ((double) feasibilityVotes) * 0.60;
        double impactWeight = Math.min(10.0, ((double) projectedBeneficiaries) / 500.0) * 0.40;
        return voteWeight + impactWeight + 1.0;
    }

    @Override
    public void displaySummary() {
        System.out.println("----------------------------------------------------");
        System.out.println("[CIVIC SUGGESTION #" + id + "] " + title);
        System.out.println(" Ward: " + wardId + " | Category: " + category.getDisplayName());
        System.out.println(" Department: " + targetDepartment
                + " | Est. Beneficiaries: " + projectedBeneficiaries);
        System.out.printf(Locale.US, " Feasibility Endorsements: %d | Priority Score: %.1f%n",
                feasibilityVotes, calculatePriorityScore());
        System.out.println(" Proposal: " + description);
        System.out.println("----------------------------------------------------");
    }
}

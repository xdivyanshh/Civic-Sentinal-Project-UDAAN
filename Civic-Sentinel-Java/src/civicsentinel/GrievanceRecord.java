package civicsentinel;

import java.util.Locale;

/**
 * ============================================================================
 * OOP PILLAR 3: INHERITANCE
 * GrievanceRecord inherits common attributes & behavior from BaseRecord.
 * ============================================================================
 */
public class GrievanceRecord extends BaseRecord {
    // ========================================================================
    // OOP PILLAR 2: ENCAPSULATION
    // Specific attributes unique to citizen complaints are kept private.
    // ========================================================================
    private SeverityLevel severity;
    private int upvotes;
    private LifecycleState state;
    private double allocatedBudget;
    private String assignedOfficer;
    private String resolutionNotes;

    public GrievanceRecord(int id, CivicCategory category, String title,
                           String description, String wardId, String citizenId,
                           SeverityLevel severity) {
        super(id, RecordType.COMPLAINT, category, title, description, wardId, citizenId);
        this.severity = severity;
        this.upvotes = 0;
        this.state = LifecycleState.OPEN;
        this.allocatedBudget = 0.0;
        this.assignedOfficer = "";
        this.resolutionNotes = "";
    }

    // Getters
    public SeverityLevel getSeverity() { return severity; }
    public int getUpvotes() { return upvotes; }
    public LifecycleState getState() { return state; }
    public double getAllocatedBudget() { return allocatedBudget; }
    public String getAssignedOfficer() { return assignedOfficer; }
    public String getResolutionNotes() { return resolutionNotes; }

    // Controlled State Mutations (Encapsulation)
    public void addUpvote() {
        this.upvotes++;
    }

    public void assignBudget(String officer, double amount) {
        if (amount > 0.0) {
            this.assignedOfficer = officer;
            this.allocatedBudget = amount;
            this.state = LifecycleState.IN_PROGRESS;
        }
    }

    public void resolve(String notes) {
        this.resolutionNotes = notes;
        this.state = LifecycleState.RESOLVED;
    }

    public void markVerified() {
        this.state = LifecycleState.VERIFIED;
    }

    // ========================================================================
    // OOP PILLAR 4: POLYMORPHISM
    // Concrete implementation of pure abstract methods from BaseRecord.
    // ========================================================================
    @Override
    public double calculatePriorityScore() {
        // Multi-Factor Weighting:
        // Each upvote adds 0.5 points.
        // Severity scale: LOW (1 * 3.5) to CRITICAL (4 * 3.5 = 14 points).
        double severityWeight = severity.getValue() * 3.5;
        double upvoteWeight = ((double) upvotes) * 0.50;
        return severityWeight + upvoteWeight + 1.5;
    }

    @Override
    public void displaySummary() {
        System.out.println("----------------------------------------------------");
        System.out.println("[TICKET #" + id + "] " + title);
        System.out.println(" Ward: " + wardId + " | Category: " + category.getDisplayName());
        System.out.println(" Severity: " + severity.getDisplayName());
        System.out.printf(Locale.US, " State: %s | Upvotes: %d | Priority Score: %.1f%n",
                state.getDisplayName(), upvotes, calculatePriorityScore());
        System.out.println(" Description: " + description);
        if (!assignedOfficer.isEmpty()) {
            System.out.printf(Locale.US, " Assigned Officer: %s | Budget: $%.2f%n",
                    assignedOfficer, allocatedBudget);
        }
        if (!resolutionNotes.isEmpty()) {
            System.out.println(" Resolution Proof: " + resolutionNotes);
        }
        System.out.println("----------------------------------------------------");
    }
}

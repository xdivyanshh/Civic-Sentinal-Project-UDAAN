package civicsentinel;

/**
 * ============================================================================
 * OOP PILLAR 3: INHERITANCE
 * ComplimentRecord recognizes completed municipal works and rewards efficiency.
 * ============================================================================
 */
public class ComplimentRecord extends BaseRecord {
    private int targetGrievanceId;
    private int satisfactionStars; // 1 to 5 stars
    private String officerRecognized;

    public ComplimentRecord(int id, CivicCategory category, String title,
                            String remarks, String wardId, String citizenId,
                            int targetGrievanceId, int satisfactionStars, String officerRecognized) {
        super(id, RecordType.COMPLIMENT, category, title, remarks, wardId, citizenId);
        this.targetGrievanceId = targetGrievanceId;
        this.satisfactionStars = Math.max(1, Math.min(5, satisfactionStars));
        this.officerRecognized = officerRecognized;
    }

    public int getTargetGrievanceId() { return targetGrievanceId; }
    public int getSatisfactionStars() { return satisfactionStars; }
    public String getOfficerRecognized() { return officerRecognized; }

    // Compliments are commendation logs, not crisis tasks, so priority is 0.0
    @Override
    public double calculatePriorityScore() {
        return 0.0;
    }

    @Override
    public void displaySummary() {
        System.out.println("----------------------------------------------------");
        System.out.println("[CITIZEN COMMENDATION #" + id + "] " + title);
        System.out.println(" Ward: " + wardId + " | Category: " + category.getDisplayName());
        System.out.println(" Linked Ticket Ref: #" + targetGrievanceId + " | Officer: " + officerRecognized);
        System.out.print(" Satisfaction: ");
        for (int i = 0; i < satisfactionStars; ++i) {
            System.out.print("*");
        }
        System.out.println(" (" + satisfactionStars + "/5)");
        System.out.println(" Citizen Remarks: " + description);
        System.out.println("----------------------------------------------------");
    }
}

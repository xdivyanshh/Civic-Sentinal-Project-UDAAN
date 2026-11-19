package civicsentinel;

/**
 * The three intake streams from the field.
 */
public enum RecordType {
    COMPLAINT("COMPLAINT"),      // Citizen public grievance
    COMPLIMENT("COMPLIMENT"),    // Commendation for completed public works
    SUGGESTION("SUGGESTION");    // Grassroots development or policy proposal

    private final String displayName;

    RecordType(String displayName) {
        this.displayName = displayName;
    }

    public String getDisplayName() {
        return displayName;
    }

    @Override
    public String toString() {
        return displayName;
    }
}

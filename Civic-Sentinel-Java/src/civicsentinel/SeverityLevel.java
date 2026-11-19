package civicsentinel;

/**
 * Urgency level used by the Priority Queue comparator.
 */
public enum SeverityLevel {
    LOW(1, "LOW (Level 1)"),
    MEDIUM(2, "MEDIUM (Level 2)"),
    HIGH(3, "HIGH (Level 3)"),
    CRITICAL(4, "CRITICAL (Level 4)");

    private final int value;
    private final String displayName;

    SeverityLevel(int value, String displayName) {
        this.value = value;
        this.displayName = displayName;
    }

    public int getValue() {
        return value;
    }

    public String getDisplayName() {
        return displayName;
    }

    @Override
    public String toString() {
        return displayName;
    }

    public static SeverityLevel fromValue(int val) {
        for (SeverityLevel s : SeverityLevel.values()) {
            if (s.value == val) return s;
        }
        return LOW;
    }
}

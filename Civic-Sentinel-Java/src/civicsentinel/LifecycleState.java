package civicsentinel;

/**
 * Finite State Machine (FSM) Lifecycle States.
 */
public enum LifecycleState {
    OPEN("OPEN"),                 // In community prioritization queue
    IN_PROGRESS("IN_PROGRESS"),   // Claimed by administration with budget
    RESOLVED("RESOLVED"),         // Marked fixed by municipal team
    VERIFIED("VERIFIED");         // Confirmed complete by citizen compliments

    private final String displayName;

    LifecycleState(String displayName) {
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

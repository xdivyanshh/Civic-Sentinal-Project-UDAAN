package civicsentinel;

import java.util.Locale;

/**
 * ============================================================================
 * DSA CONCEPT: DIRECTED GRAPH / STATE TRANSITION VALIDATOR
 * Enforces that civic tickets can only follow deterministic lifecycle edges.
 * ============================================================================
 */
public class LifecycleFSM {

    // 1. Claim an issue: OPEN -> IN_PROGRESS
    public static boolean claimIssue(GrievanceRecord record, String officerName, double budget) {
        if (record == null) return false;

        if (record.getState() != LifecycleState.OPEN) {
            System.out.println(" [X] FSM TRANSITION REJECTED: Ticket #" + record.getId()
                    + " is in state '" + record.getState().getDisplayName()
                    + "' and cannot be claimed!");
            return false;
        }

        if (budget <= 0.0) {
            System.out.printf(Locale.US,
                    " [X] FSM TRANSITION REJECTED: Cannot claim Ticket #%d with zero or negative budget ($%.2f)!%n",
                    record.getId(), budget);
            return false;
        }

        record.assignBudget(officerName, budget);
        System.out.printf(Locale.US,
                " [OK] FSM TRANSITION: Ticket #%d moved OPEN -> IN_PROGRESS by Officer '%s' (Budget: $%.2f)%n",
                record.getId(), officerName, budget);
        return true;
    }

    // 2. Complete municipal work: IN_PROGRESS -> RESOLVED
    public static boolean resolveIssue(GrievanceRecord record, String resolutionProofNotes) {
        if (record == null) return false;

        if (record.getState() != LifecycleState.IN_PROGRESS) {
            System.out.println(" [X] ILLEGAL STAGE SKIPPING: Ticket #" + record.getId()
                    + " cannot jump to RESOLVED from '" + record.getState().getDisplayName()
                    + "'! It must first be IN_PROGRESS with assigned budget.");
            return false;
        }

        if (resolutionProofNotes == null || resolutionProofNotes.trim().isEmpty()) {
            System.out.println(" [X] FSM TRANSITION REJECTED: Completion proof notes cannot be blank!");
            return false;
        }

        record.resolve(resolutionProofNotes);
        System.out.println(" [OK] FSM TRANSITION: Ticket #" + record.getId()
                + " moved IN_PROGRESS -> RESOLVED. Proof: '" + resolutionProofNotes + "'");
        return true;
    }

    // 3. Citizen Verification (Final Milestone): RESOLVED -> VERIFIED
    public static boolean verifyIssue(GrievanceRecord record) {
        if (record == null) return false;

        if (record.getState() != LifecycleState.RESOLVED) {
            System.out.println(" [X] FSM TRANSITION REJECTED: Ticket #" + record.getId()
                    + " cannot be VERIFIED until it is marked RESOLVED by field workers!");
            return false;
        }

        record.markVerified();
        System.out.println(" [*] DEMOCRATIC VERIFICATION: Ticket #" + record.getId()
                + " moved RESOLVED -> VERIFIED! Citizens confirmed completion.");
        return true;
    }
}

package civicsentinel;

import java.util.HashSet;
import java.util.Set;

/**
 * ============================================================================
 * DSA CONCEPT: HASH TABLE (HashSet)
 * Enforces single-vote integrity in O(1) average time.
 * ============================================================================
 */
public class AntiSybilVault {
    // Hash set storing unique composite keys: "CITIZEN_ID::RECORD_ID"
    // Space Complexity: O(V) where V = total unique votes cast
    private final Set<String> voteLedger;

    public AntiSybilVault() {
        this.voteLedger = new HashSet<>();
    }

    // Helper to generate the composite key
    private String generateVoteKey(String citizenId, int recordId) {
        return citizenId + "::" + recordId;
    }

    // O(1) Attempt to cast a vote
    public boolean castVote(String citizenId, GrievanceRecord record) {
        if (record == null) return false;

        String key = generateVoteKey(citizenId, record.getId());

        // 1. Hash Table Lookup in O(1): Has this citizen already voted for this ticket?
        if (voteLedger.contains(key)) {
            System.out.println(" [!] FRAUD BLOCKED: Citizen '" + citizenId
                    + "' has ALREADY voted for Ticket #" + record.getId() + "!");
            return false; // Sybil duplicate vote rejected
        }

        // 2. Hash Table Insert in O(1): Register the vote in the ledger
        voteLedger.add(key);

        // 3. Increment the record's encapsulated upvote count
        record.addUpvote();
        System.out.println(" [+] VOTE ACCEPTED: Citizen '" + citizenId
                + "' upvoted Ticket #" + record.getId()
                + " (Total Upvotes: " + record.getUpvotes() + ")");

        return true;
    }

    public int getTotalVotesCast() {
        return voteLedger.size();
    }
}

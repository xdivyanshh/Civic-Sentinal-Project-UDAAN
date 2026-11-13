#ifndef ANTI_SYBIL_VAULT_HPP
#define ANTI_SYBIL_VAULT_HPP

#include <iostream>
#include <string>
#include <unordered_set>
#include "GrievanceRecord.hpp"

using namespace std;

namespace CivicSentinel {

// ============================================================================
// DSA CONCEPT: HASH TABLE (std::unordered_set)
// Enforces single-vote integrity in O(1) average time.
// ============================================================================
class AntiSybilVault {
private:
    // Hash set storing unique composite keys: "CITIZEN_ID::RECORD_ID"
    // Space Complexity: O(V) where V = total unique votes cast
    unordered_set<string> voteLedger;

    // Helper to generate the composite key
    string generateVoteKey(const string& citizenId, int recordId) const {
        return citizenId + "::" + to_string(recordId);
    }

public:
    // O(1) Attempt to cast a vote
    bool castVote(const string& citizenId, shared_ptr<GrievanceRecord> record) {
        if (!record) return false;

        string key = generateVoteKey(citizenId, record->getId());

        // 1. Hash Table Lookup in O(1): Has this citizen already voted for this ticket?
        if (voteLedger.find(key) != voteLedger.end()) {
            cout << " [!] FRAUD BLOCKED: Citizen '" << citizenId 
                 << "' has ALREADY voted for Ticket #" << record->getId() << "!" << endl;
            return false; // Sybil duplicate vote rejected
        }

        // 2. Hash Table Insert in O(1): Register the vote in the ledger
        voteLedger.insert(key);

        // 3. Increment the record's encapsulated upvote count
        record->addUpvote();
        cout << " [+] VOTE ACCEPTED: Citizen '" << citizenId 
             << "' upvoted Ticket #" << record->getId() 
             << " (Total Upvotes: " << record->getUpvotes() << ")" << endl;

        return true;
    }

    size_t getTotalVotesCast() const { return voteLedger.size(); }
};

} // namespace CivicSentinel

#endif // ANTI_SYBIL_VAULT_HPP
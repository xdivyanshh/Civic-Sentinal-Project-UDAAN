#ifndef LIFECYCLE_FSM_HPP
#define LIFECYCLE_FSM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GrievanceRecord.hpp"

using namespace std;

namespace CivicSentinel {

// ============================================================================
// DSA CONCEPT: DIRECTED GRAPH / STATE TRANSITION VALIDATOR
// Enforces that civic tickets can only follow deterministic lifecycle edges.
// ============================================================================
class LifecycleFSM {
public:
    // 1. Claim an issue: OPEN -> IN_PROGRESS
    static bool claimIssue(shared_ptr<GrievanceRecord> record, const string& officerName, double budget) {
        if (!record) return false;

        if (record->getState() != LifecycleState::OPEN) {
            cout << " [X] FSM TRANSITION REJECTED: Ticket #" << record->getId() 
                 << " is in state '" << stateToString(record->getState()) 
                 << "' and cannot be claimed!" << endl;
            return false;
        }

        if (budget <= 0.0) {
            cout << " [X] FSM TRANSITION REJECTED: Cannot claim Ticket #" << record->getId() 
                 << " with zero or negative budget ($" << budget << ")!" << endl;
            return false;
        }

        record->assignBudget(officerName, budget);
        cout << " [OK] FSM TRANSITION: Ticket #" << record->getId() 
             << " moved OPEN -> IN_PROGRESS by Officer '" << officerName 
             << "' (Budget: $" << fixed << setprecision(2) << budget << ")" << endl;
        return true;
    }

    // 2. Complete municipal work: IN_PROGRESS -> RESOLVED
    static bool resolveIssue(shared_ptr<GrievanceRecord> record, const string& resolutionProofNotes) {
        if (!record) return false;

        if (record->getState() != LifecycleState::IN_PROGRESS) {
            cout << " [X] ILLEGAL STAGE SKIPPING: Ticket #" << record->getId() 
                 << " cannot jump to RESOLVED from '" << stateToString(record->getState()) 
                 << "'! It must first be IN_PROGRESS with assigned budget." << endl;
            return false;
        }

        if (resolutionProofNotes.empty()) {
            cout << " [X] FSM TRANSITION REJECTED: Completion proof notes cannot be blank!" << endl;
            return false;
        }

        record->resolve(resolutionProofNotes);
        cout << " [OK] FSM TRANSITION: Ticket #" << record->getId() 
             << " moved IN_PROGRESS -> RESOLVED. Proof: '" << resolutionProofNotes << "'" << endl;
        return true;
    }

    // 3. Citizen Verification (Final Milestone): RESOLVED -> VERIFIED
    static bool verifyIssue(shared_ptr<GrievanceRecord> record) {
        if (!record) return false;

        if (record->getState() != LifecycleState::RESOLVED) {
            cout << " [X] FSM TRANSITION REJECTED: Ticket #" << record->getId() 
                 << " cannot be VERIFIED until it is marked RESOLVED by field workers!" << endl;
            return false;
        }

        record->markVerified();
        cout << " [*] DEMOCRATIC VERIFICATION: Ticket #" << record->getId() 
             << " moved RESOLVED -> VERIFIED! Citizens confirmed completion." << endl;
        return true;
    }
};

} // namespace CivicSentinel

#endif // LIFECYCLE_FSM_HPP

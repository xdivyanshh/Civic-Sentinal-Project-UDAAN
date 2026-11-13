#ifndef GRIEVANCE_RECORD_HPP
#define GRIEVANCE_RECORD_HPP

#include <iostream>
#include <iomanip>
#include "BaseRecord.hpp"

using namespace std;

namespace CivicSentinel {

// ============================================================================
// OOP PILLAR 3: INHERITANCE
// GrievanceRecord inherits common attributes & behavior from BaseRecord.
// ============================================================================
class GrievanceRecord : public BaseRecord {
private:
    // ========================================================================
    // OOP PILLAR 2: ENCAPSULATION
    // Specific attributes unique to citizen complaints are kept private.
    // ========================================================================
    SeverityLevel severity;
    int upvotes;
    LifecycleState state;
    double allocatedBudget;
    string assignedOfficer;
    string resolutionNotes;

public:
    // Constructor delegating base fields to BaseRecord
    GrievanceRecord(int id, CivicCategory category, string title, 
                    string description, string wardId, string citizenId, 
                    SeverityLevel severity)
        : BaseRecord(id, RecordType::COMPLAINT, category, title, description, wardId, citizenId),
          severity(severity), upvotes(0), state(LifecycleState::OPEN), allocatedBudget(0.0), assignedOfficer("") {}

    // Getters
    SeverityLevel getSeverity() const { return severity; }
    int getUpvotes() const { return upvotes; }
    LifecycleState getState() const { return state; }
    double getAllocatedBudget() const { return allocatedBudget; }
    string getAssignedOfficer() const { return assignedOfficer; }
    string getResolutionNotes() const { return resolutionNotes; }

    // Controlled State Mutations (Encapsulation)
    void addUpvote() {
        upvotes++;
    }

    void assignBudget(const string& officer, double amount) {
        if (amount > 0.0) {
            assignedOfficer = officer;
            allocatedBudget = amount;
            state = LifecycleState::IN_PROGRESS;
        }
    }

    void resolve(const string& notes) {
        resolutionNotes = notes;
        state = LifecycleState::RESOLVED;
    }

    void markVerified() {
        state = LifecycleState::VERIFIED;
    }

    // ========================================================================
    // OOP PILLAR 4: POLYMORPHISM
    // Concrete implementation of pure virtual methods from BaseRecord.
    // ========================================================================
    double calculatePriorityScore() const override {
        // Multi-Factor Weighting:
        // Each upvote adds 0.5 points.
        // Severity scale: LOW (1 * 3.5) to CRITICAL (4 * 3.5 = 14 points).
        double severityWeight = static_cast<int>(severity) * 3.5;
        double upvoteWeight = static_cast<double>(upvotes) * 0.50;
        return severityWeight + upvoteWeight + 1.5;
    }

    void displaySummary() const override {
        cout << "----------------------------------------------------" << endl;
        cout << "[TICKET #" << id << "] " << title << endl;
        cout << " Ward: " << wardId << " | Category: " << categoryToString(category) << endl;
        cout << " Severity: " << severityToString(severity) << endl;
        cout << " State: " << stateToString(state) 
             << " | Upvotes: " << upvotes 
             << " | Priority Score: " << fixed << setprecision(1) << calculatePriorityScore() << endl;
        cout << " Description: " << description << endl;
        if (!assignedOfficer.empty()) {
            cout << " Assigned Officer: " << assignedOfficer 
                 << " | Budget: $" << fixed << setprecision(2) << allocatedBudget << endl;
        }
        if (!resolutionNotes.empty()) {
            cout << " Resolution Proof: " << resolutionNotes << endl;
        }
        cout << "----------------------------------------------------" << endl;
    }
};

} // namespace CivicSentinel

#endif // GRIEVANCE_RECORD_HPP

#ifndef SUGGESTION_RECORD_HPP
#define SUGGESTION_RECORD_HPP

#include <iostream>
#include <iomanip>
#include "BaseRecord.hpp"

using namespace std;

namespace CivicSentinel {

// ============================================================================
// OOP PILLAR 3: INHERITANCE
// SuggestionRecord specializes BaseRecord for civic policy proposals.
// ============================================================================
class SuggestionRecord : public BaseRecord {
private:
    string targetDepartment;
    int feasibilityVotes;
    int projectedBeneficiaries;

public:
    SuggestionRecord(int id, CivicCategory category, string title, 
                     string description, string wardId, string citizenId, 
                     string targetDepartment, int projectedBeneficiaries)
        : BaseRecord(id, RecordType::SUGGESTION, category, title, description, wardId, citizenId),
          targetDepartment(targetDepartment), feasibilityVotes(0), 
          projectedBeneficiaries(projectedBeneficiaries) {}

    // Getters
    string getTargetDepartment() const { return targetDepartment; }
    int getFeasibilityVotes() const { return feasibilityVotes; }
    int getProjectedBeneficiaries() const { return projectedBeneficiaries; }

    void addFeasibilityVote() {
        feasibilityVotes++;
    }

    // ========================================================================
    // OOP PILLAR 4: POLYMORPHISM
    // Policy suggestions are weighted based on citizen feasibility votes
    // and projected public impact.
    // ========================================================================
    double calculatePriorityScore() const override {
        double voteWeight = static_cast<double>(feasibilityVotes) * 0.60;
        double impactWeight = min(10.0, static_cast<double>(projectedBeneficiaries) / 500.0) * 0.40;
        return voteWeight + impactWeight + 1.0;
    }

    void displaySummary() const override {
        cout << "----------------------------------------------------" << endl;
        cout << "[CIVIC SUGGESTION #" << id << "] " << title << endl;
        cout << " Ward: " << wardId << " | Category: " << categoryToString(category) << endl;
        cout << " Department: " << targetDepartment 
             << " | Est. Beneficiaries: " << projectedBeneficiaries << endl;
        cout << " Feasibility Endorsements: " << feasibilityVotes 
             << " | Priority Score: " << fixed << setprecision(1) << calculatePriorityScore() << endl;
        cout << " Proposal: " << description << endl;
        cout << "----------------------------------------------------" << endl;
    }
};

} // namespace CivicSentinel

#endif // SUGGESTION_RECORD_HPP

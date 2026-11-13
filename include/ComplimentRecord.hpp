#ifndef COMPLIMENT_RECORD_HPP
#define COMPLIMENT_RECORD_HPP

#include <iostream>
#include <iomanip>
#include "BaseRecord.hpp"

using namespace std;

namespace CivicSentinel {

// ============================================================================
// OOP PILLAR 3: INHERITANCE
// ComplimentRecord recognizes completed municipal works and rewards efficiency.
// ============================================================================
class ComplimentRecord : public BaseRecord {
private:
    int targetGrievanceId;
    int satisfactionStars; // 1 to 5 stars
    string officerRecognized;

public:
    ComplimentRecord(int id, CivicCategory category, string title, 
                     string remarks, string wardId, string citizenId, 
                     int targetGrievanceId, int satisfactionStars, string officerRecognized)
        : BaseRecord(id, RecordType::COMPLIMENT, category, title, remarks, wardId, citizenId),
          targetGrievanceId(targetGrievanceId), 
          satisfactionStars(max(1, min(5, satisfactionStars))), 
          officerRecognized(officerRecognized) {}

    int getTargetGrievanceId() const { return targetGrievanceId; }
    int getSatisfactionStars() const { return satisfactionStars; }
    string getOfficerRecognized() const { return officerRecognized; }

    // Compliments are commendation logs, not crisis tasks, so priority is 0.0
    double calculatePriorityScore() const override {
        return 0.0;
    }

    void displaySummary() const override {
        cout << "----------------------------------------------------" << endl;
        cout << "[CITIZEN COMMENDATION #" << id << "] " << title << endl;
        cout << " Ward: " << wardId << " | Category: " << categoryToString(category) << endl;
        cout << " Linked Ticket Ref: #" << targetGrievanceId << " | Officer: " << officerRecognized << endl;
        cout << " Satisfaction: ";
        for (int i = 0; i < satisfactionStars; ++i) cout << "*";
        cout << " (" << satisfactionStars << "/5)" << endl;
        cout << " Citizen Remarks: " << description << endl;
        cout << "----------------------------------------------------" << endl;
    }
};

} // namespace CivicSentinel

#endif // COMPLIMENT_RECORD_HPP

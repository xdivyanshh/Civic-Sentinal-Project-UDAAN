#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <string>

using namespace std;

namespace CivicSentinel {

// 1. The three intake streams from the field
enum class RecordType {
    COMPLAINT,      // Citizen public grievance
    COMPLIMENT,     // Commendation for completed public works
    SUGGESTION      // Grassroots development or policy proposal
};

// 2. Municipal problem sectors
enum class CivicCategory {
    SANITATION,
    ROADS_INFRASTRUCTURE,
    WATER_SUPPLY,
    HEALTHCARE,
    ELECTRICITY,
    PUBLIC_TRANSPORT,
    COMMERCE_MARKETS,
    GENERAL_POLICY
};

// 3. Urgency level (Used by your Priority Queue comparator)
enum class SeverityLevel {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    CRITICAL = 4
};

// 4. Finite State Machine (FSM) Lifecycle States
enum class LifecycleState {
    OPEN,           // In community prioritization queue
    IN_PROGRESS,    // Claimed by administration with budget
    RESOLVED,       // Marked fixed by municipal team
    VERIFIED        // Confirmed complete by citizen compliments
};

// Helper function to print states in CLI
inline string stateToString(LifecycleState state) {
    switch (state) {
        case LifecycleState::OPEN:        return "OPEN";
        case LifecycleState::IN_PROGRESS: return "IN_PROGRESS";
        case LifecycleState::RESOLVED:    return "RESOLVED";
        case LifecycleState::VERIFIED:    return "VERIFIED";
        default:                          return "UNKNOWN";
    }
}

} // namespace CivicSentinel

#endif // ENUMS_HPP
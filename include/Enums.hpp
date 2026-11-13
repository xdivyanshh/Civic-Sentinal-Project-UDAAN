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

// Helper string conversions for clean terminal display
inline string recordTypeToString(RecordType type) {
    switch (type) {
        case RecordType::COMPLAINT:  return "COMPLAINT";
        case RecordType::COMPLIMENT: return "COMPLIMENT";
        case RecordType::SUGGESTION: return "SUGGESTION";
        default:                     return "UNKNOWN";
    }
}

inline string categoryToString(CivicCategory category) {
    switch (category) {
        case CivicCategory::SANITATION:            return "Sanitation & Waste Management";
        case CivicCategory::ROADS_INFRASTRUCTURE:  return "Roads & Civil Infrastructure";
        case CivicCategory::WATER_SUPPLY:          return "Drinking Water Supply & Drainage";
        case CivicCategory::HEALTHCARE:            return "Public Healthcare & Clinics";
        case CivicCategory::ELECTRICITY:           return "Power Grid & Street Lighting";
        case CivicCategory::PUBLIC_TRANSPORT:      return "Public Bus & Transit Network";
        case CivicCategory::COMMERCE_MARKETS:      return "Local Commercial Markets & Trade";
        case CivicCategory::GENERAL_POLICY:        return "General Civic Development Policy";
        default:                                   return "Uncategorized";
    }
}

inline string severityToString(SeverityLevel level) {
    switch (level) {
        case SeverityLevel::LOW:      return "LOW (Level 1)";
        case SeverityLevel::MEDIUM:   return "MEDIUM (Level 2)";
        case SeverityLevel::HIGH:     return "HIGH (Level 3)";
        case SeverityLevel::CRITICAL: return "CRITICAL (Level 4)";
        default:                      return "UNDEFINED";
    }
}

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

#ifndef BASE_RECORD_HPP
#define BASE_RECORD_HPP

#include <iostream>
#include <string>
#include <ctime>
#include "Enums.hpp"

using namespace std;

namespace CivicSentinel {

// ============================================================================
// OOP PILLAR 1: ABSTRACTION
// BaseRecord is an Abstract Base Class. It cannot be directly instantiated.
// It establishes a common interface for Complaints, Compliments, and Suggestions.
// ============================================================================
class BaseRecord {
protected:
    // ========================================================================
    // OOP PILLAR 2: ENCAPSULATION
    // Internal state variables are protected from uncontrolled external modification.
    // ========================================================================
    int id;
    RecordType type;
    CivicCategory category;
    string title;
    string description;
    string wardId;
    string citizenId;
    time_t timestamp;

public:
    // Parameterized Constructor
    BaseRecord(int id, RecordType type, CivicCategory category, 
               string title, string description, string wardId, string citizenId)
        : id(id), type(type), category(category), 
          title(title), description(description), 
          wardId(wardId), citizenId(citizenId), timestamp(time(nullptr)) {}

    // Virtual Destructor (Crucial for proper polymorphic object deletion)
    virtual ~BaseRecord() = default;

    // Encapsulated Getters
    int getId() const { return id; }
    RecordType getType() const { return type; }
    CivicCategory getCategory() const { return category; }
    string getTitle() const { return title; }
    string getDescription() const { return description; }
    string getWardId() const { return wardId; }
    string getCitizenId() const { return citizenId; }
    time_t getTimestamp() const { return timestamp; }

    // ========================================================================
    // PURE VIRTUAL FUNCTIONS (The Abstract Contract)
    // Every child class (Grievance, Suggestion, etc.) MUST implement these!
    // ========================================================================
    virtual double calculatePriorityScore() const = 0;
    virtual void displaySummary() const = 0;
};

} // namespace CivicSentinel

#endif // BASE_RECORD_HPP
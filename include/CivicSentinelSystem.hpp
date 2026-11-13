#ifndef CIVIC_SENTINEL_SYSTEM_HPP
#define CIVIC_SENTINEL_SYSTEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Enums.hpp"
#include "BaseRecord.hpp"
#include "GrievanceRecord.hpp"
#include "SuggestionRecord.hpp"
#include "ComplimentRecord.hpp"
#include "PriorityScheduler.hpp"
#include "AntiSybilVault.hpp"
#include "LifecycleFSM.hpp"
#include "TelemetryEngine.hpp"
#include "TagTrie.hpp"
#include "DuplicateDetector.hpp"

using namespace std;

namespace CivicSentinel {

// ============================================================================
// SYSTEM FACADE & UNIFIED CORE CONTROLLER
// Coordinates Citizen Field Portal and Core Engine seamlessly.
// ============================================================================
class CivicSentinelSystem {
private:
    int nextId;

    // Fast O(1) Primary Record Vault
    unordered_map<int, shared_ptr<BaseRecord>> masterRecordRegistry;

    // Core DSA Subsystems
    PriorityScheduler priorityScheduler;   // Max-Heap: O(log N)
    AntiSybilVault antiSybilVault;         // Hash Set: O(1)
    TelemetryEngine telemetryEngine;       // Red-Black Tree: O(log M)
    TagTrie tagTrie;                       // Prefix Trie: O(L)
    DuplicateDetector duplicateDetector;   // Inverted Index: O(1)

public:
    CivicSentinelSystem() : nextId(101) {
        seedInitialKnowledgeBase();
    }

    // Pre-populate realistic civic vocabulary and sample telemetry
    void seedInitialKnowledgeBase() {
        // 1. Seed Trie with common civic tags
        vector<string> tags = {
            "pothole", "pipeline", "water-leak", "water-contamination",
            "street-light", "transformer-flicker", "hospital-icu",
            "sanitation-dump", "garbage-overflow", "drainage-clog",
            "public-bus-frequency", "market-encroachment"
        };
        for (const string& tag : tags) {
            tagTrie.insert(tag);
        }

        // 2. Seed Red-Black Tree with historical monthly telemetry for Noida Ward-12
        telemetryEngine.logMonth({"2026-07", 45, 38, 2.1, 1.4, 82.0});
        telemetryEngine.logMonth({"2026-08", 60, 56, 2.8, 1.9, 87.5});
        telemetryEngine.logMonth({"2026-09", 35, 33, 3.2, 2.2, 91.0});
        telemetryEngine.logMonth({"2026-10", 70, 48, 1.4, 0.9, 66.0});

        // 3. Seed initial field complaints
        lodgeComplaint(
            CivicCategory::ROADS_INFRASTRUCTURE, 
            "Dangerous Pothole on Ring Road Flyover", 
            "Severe 2-foot crater near Sector 62 turn causing car accidents", 
            "Ward-12", "CITIZEN_ANANYA", SeverityLevel::HIGH
        );

        lodgeComplaint(
            CivicCategory::WATER_SUPPLY, 
            "Contaminated Brown Water in Sector 62 Taps", 
            "Sewage line mixed with main drinking water supply", 
            "Ward-12", "CITIZEN_RAHUL", SeverityLevel::CRITICAL
        );

        lodgeSuggestion(
            CivicCategory::ELECTRICITY, 
            "Install Solar-Powered LED Lights on Dark Stretches", 
            "Improve night safety for women near metro and coaching centres", 
            "Ward-12", "CITIZEN_PRIYA", "Power & Renewable Energy Dept", 12000
        );
    }

    // --- CITIZEN FIELD PORTAL INTERFACES ---

    // 1. Field Intake: Lodge Complaint (with Trie & Duplicate Check)
    int lodgeComplaint(CivicCategory category, const string& title, 
                       const string& desc, const string& wardId, 
                       const string& citizenId, SeverityLevel severity) {
        
        // Step A: Check for duplicates in the same ward using Inverted Index
        vector<int> duplicates = duplicateDetector.findPotentialDuplicates(wardId, title);
        if (!duplicates.empty()) {
            cout << " [!] NEAR-DUPLICATE DETECTED: Similar issues already exist in " << wardId 
                 << " (Ticket Ref: #" << duplicates[0] << ")! Consider upvoting instead." << endl;
        }

        int id = nextId++;
        auto complaint = make_shared<GrievanceRecord>(id, category, title, desc, wardId, citizenId, severity);
        
        masterRecordRegistry[id] = complaint;
        priorityScheduler.schedule(complaint);
        duplicateDetector.indexGrievance(id, wardId, title);

        cout << " [✓] FIELD INTAKE SUCCESS: Ticket #" << id << " created and queued in Max-Heap." << endl;
        return id;
    }

    // 2. Field Intake: Propose Policy Suggestion
    int lodgeSuggestion(CivicCategory category, const string& title, 
                        const string& desc, const string& wardId, 
                        const string& citizenId, const string& dept, int beneficiaries) {
        int id = nextId++;
        auto suggestion = make_shared<SuggestionRecord>(id, category, title, desc, wardId, citizenId, dept, beneficiaries);
        masterRecordRegistry[id] = suggestion;
        priorityScheduler.schedule(suggestion);

        cout << " [✓] POLICY INTAKE SUCCESS: Civic Suggestion #" << id << " logged for administration." << endl;
        return id;
    }

    // 3. Field Intake: Submit Compliment / Citizen Commendation
    int lodgeCompliment(CivicCategory category, const string& title, 
                        const string& remarks, const string& wardId, 
                        const string& citizenId, int targetTicketId, int stars, const string& officer) {
        int id = nextId++;
        auto compliment = make_shared<ComplimentRecord>(id, category, title, remarks, wardId, citizenId, targetTicketId, stars, officer);
        masterRecordRegistry[id] = compliment;

        // If target ticket is in RESOLVED state, citizen compliment automatically VERIFIES it!
        auto it = masterRecordRegistry.find(targetTicketId);
        if (it != masterRecordRegistry.end()) {
            auto grievance = dynamic_pointer_cast<GrievanceRecord>(it->second);
            if (grievance && grievance->getState() == LifecycleState::RESOLVED) {
                LifecycleFSM::verifyIssue(grievance);
            }
        }

        cout << " [✓] COMMENDATION RECORDED: Compliment #" << id << " filed for Officer '" << officer << "'!" << endl;
        return id;
    }

    // 4. Grassroots Voting with Anti-Sybil Vault
    bool voteOnGrievance(const string& citizenId, int ticketId) {
        auto it = masterRecordRegistry.find(ticketId);
        if (it == masterRecordRegistry.end()) {
            cout << " [X] ERROR: Ticket #" << ticketId << " does not exist!" << endl;
            return false;
        }

        auto grievance = dynamic_pointer_cast<GrievanceRecord>(it->second);
        if (!grievance) {
            cout << " [X] ERROR: Record #" << ticketId << " is not an upvotable grievance!" << endl;
            return false;
        }

        bool success = antiSybilVault.castVote(citizenId, grievance);
        if (success) {
            // Re-schedule into Heap so the updated score bubbles up
            priorityScheduler.schedule(grievance);
        }
        return success;
    }

    // 5. Prefix Trie Autocomplete
    vector<string> searchAutocompleteTags(const string& prefix) const {
        return tagTrie.autocomplete(prefix);
    }

    // --- CORE & POLITICIAN HUB INTERFACES ---

    // View Highest Priority Crisis from Max-Heap: O(1)
    void viewTopEmergency() const {
        auto top = priorityScheduler.peekHighestPriority();
        if (!top) {
            cout << "No active complaints in the priority queue." << endl;
            return;
        }
        cout << "\n>>> CURRENT #1 HIGHEST PRIORITY PUBLIC CRISIS:" << endl;
        top->displaySummary();
    }

    // Municipal Official Claims Ticket: OPEN -> IN_PROGRESS
    bool claimTicket(int ticketId, const string& officerName, double budget) {
        auto it = masterRecordRegistry.find(ticketId);
        if (it == masterRecordRegistry.end()) {
            cout << "Ticket #" << ticketId << " not found!" << endl;
            return false;
        }

        auto grievance = dynamic_pointer_cast<GrievanceRecord>(it->second);
        if (!grievance) {
            cout << "Record #" << ticketId << " is not a municipal grievance!" << endl;
            return false;
        }

        return LifecycleFSM::claimIssue(grievance, officerName, budget);
    }

    // Municipal Official Resolves Ticket: IN_PROGRESS -> RESOLVED
    bool resolveTicket(int ticketId, const string& proofNotes) {
        auto it = masterRecordRegistry.find(ticketId);
        if (it == masterRecordRegistry.end()) {
            cout << "Ticket #" << ticketId << " not found!" << endl;
            return false;
        }

        auto grievance = dynamic_pointer_cast<GrievanceRecord>(it->second);
        if (!grievance) {
            cout << "Record #" << ticketId << " is not a municipal grievance!" << endl;
            return false;
        }

        return LifecycleFSM::resolveIssue(grievance, proofNotes);
    }

    // Display all active records
    void displayAllRecords() const {
        cout << "\n================ MASTER CITIZEN REGISTRY (" << masterRecordRegistry.size() << " Records) ================" << endl;
        for (const auto& pair : masterRecordRegistry) {
            pair.second->displaySummary();
        }
    }

    // Politician 0-100 Accountability Audit
    void auditPolitician(const string& politicianName, const string& wardId, 
                         const string& startMonth, const string& endMonth) const {
        telemetryEngine.displayPoliticianAudit(politicianName, wardId, startMonth, endMonth);
    }
};

} // namespace CivicSentinel

#endif // CIVIC_SENTINEL_SYSTEM_HPP

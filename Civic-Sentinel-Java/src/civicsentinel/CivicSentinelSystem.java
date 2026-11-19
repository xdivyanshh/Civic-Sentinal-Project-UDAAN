package civicsentinel;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * ============================================================================
 * SYSTEM FACADE & UNIFIED CORE CONTROLLER
 * Coordinates Citizen Field Portal and Core Engine seamlessly.
 * ============================================================================
 */
public class CivicSentinelSystem {
    private int nextId;

    // Fast O(1) Primary Record Vault
    private final Map<Integer, BaseRecord> masterRecordRegistry;

    // Core DSA Subsystems
    private final PriorityScheduler priorityScheduler;   // Max-Heap: O(log N)
    private final AntiSybilVault antiSybilVault;         // Hash Set: O(1)
    private final TelemetryEngine telemetryEngine;       // Red-Black Tree: O(log M)
    private final TagTrie tagTrie;                       // Prefix Trie: O(L)
    private final DuplicateDetector duplicateDetector;   // Inverted Index: O(1)

    public CivicSentinelSystem() {
        this.nextId = 101;
        this.masterRecordRegistry = new HashMap<>();
        this.priorityScheduler = new PriorityScheduler();
        this.antiSybilVault = new AntiSybilVault();
        this.telemetryEngine = new TelemetryEngine();
        this.tagTrie = new TagTrie();
        this.duplicateDetector = new DuplicateDetector();

        seedInitialKnowledgeBase();
    }

    // Pre-populate realistic civic vocabulary and sample telemetry
    public void seedInitialKnowledgeBase() {
        // 1. Seed Trie with common civic tags
        String[] tags = {
            "pothole", "pipeline", "water-leak", "water-contamination",
            "street-light", "transformer-flicker", "hospital-icu",
            "sanitation-dump", "garbage-overflow", "drainage-clog",
            "public-bus-frequency", "market-encroachment"
        };
        for (String tag : tags) {
            tagTrie.insert(tag);
        }

        // 2. Seed Red-Black Tree with historical monthly telemetry for Noida Ward-12
        telemetryEngine.logMonth(new MonthlyTelemetry("2026-07", 45, 38, 2.1, 1.4, 82.0));
        telemetryEngine.logMonth(new MonthlyTelemetry("2026-08", 60, 56, 2.8, 1.9, 87.5));
        telemetryEngine.logMonth(new MonthlyTelemetry("2026-09", 35, 33, 3.2, 2.2, 91.0));
        telemetryEngine.logMonth(new MonthlyTelemetry("2026-10", 70, 48, 1.4, 0.9, 66.0));

        // 3. Seed initial field complaints
        lodgeComplaint(
            CivicCategory.ROADS_INFRASTRUCTURE,
            "Dangerous Pothole on Ring Road Flyover",
            "Severe 2-foot crater near Sector 62 turn causing car accidents",
            "Ward-12", "CITIZEN_ANANYA", SeverityLevel.HIGH
        );

        lodgeComplaint(
            CivicCategory.WATER_SUPPLY,
            "Contaminated Brown Water in Sector 62 Taps",
            "Sewage line mixed with main drinking water supply",
            "Ward-12", "CITIZEN_RAHUL", SeverityLevel.CRITICAL
        );

        lodgeSuggestion(
            CivicCategory.ELECTRICITY,
            "Install Solar-Powered LED Lights on Dark Stretches",
            "Improve night safety for women near metro and coaching centres",
            "Ward-12", "CITIZEN_PRIYA", "Power & Renewable Energy Dept", 12000
        );
    }

    // --- CITIZEN FIELD PORTAL INTERFACES ---

    // 1. Field Intake: Lodge Complaint (with Trie & Duplicate Check)
    public int lodgeComplaint(CivicCategory category, String title,
                              String desc, String wardId,
                              String citizenId, SeverityLevel severity) {

        // Step A: Check for duplicates in the same ward using Inverted Index
        List<Integer> duplicates = duplicateDetector.findPotentialDuplicates(wardId, title);
        if (!duplicates.isEmpty()) {
            System.out.println(" [!] NEAR-DUPLICATE DETECTED: Similar issues already exist in " + wardId
                    + " (Ticket Ref: #" + duplicates.get(0) + ")! Consider upvoting instead.");
        }

        int id = nextId++;
        GrievanceRecord complaint = new GrievanceRecord(id, category, title, desc, wardId, citizenId, severity);

        masterRecordRegistry.put(id, complaint);
        priorityScheduler.schedule(complaint);
        duplicateDetector.indexGrievance(id, wardId, title);

        System.out.println(" [OK] FIELD INTAKE SUCCESS: Ticket #" + id + " created and queued in Max-Heap.");
        return id;
    }

    // 2. Field Intake: Propose Policy Suggestion
    public int lodgeSuggestion(CivicCategory category, String title,
                               String desc, String wardId,
                               String citizenId, String dept, int beneficiaries) {
        int id = nextId++;
        SuggestionRecord suggestion = new SuggestionRecord(id, category, title, desc, wardId, citizenId, dept, beneficiaries);
        masterRecordRegistry.put(id, suggestion);
        priorityScheduler.schedule(suggestion);

        System.out.println(" [OK] POLICY INTAKE SUCCESS: Civic Suggestion #" + id + " logged for administration.");
        return id;
    }

    // 3. Field Intake: Submit Compliment / Citizen Commendation
    public int lodgeCompliment(CivicCategory category, String title,
                               String remarks, String wardId,
                               String citizenId, int targetTicketId, int stars, String officer) {
        int id = nextId++;
        ComplimentRecord compliment = new ComplimentRecord(id, category, title, remarks, wardId, citizenId, targetTicketId, stars, officer);
        masterRecordRegistry.put(id, compliment);

        // If target ticket is in RESOLVED state, citizen compliment automatically VERIFIES it!
        BaseRecord target = masterRecordRegistry.get(targetTicketId);
        if (target instanceof GrievanceRecord) {
            GrievanceRecord grievance = (GrievanceRecord) target;
            if (grievance.getState() == LifecycleState.RESOLVED) {
                LifecycleFSM.verifyIssue(grievance);
            }
        }

        System.out.println(" [OK] COMMENDATION RECORDED: Compliment #" + id + " filed for Officer '" + officer + "'!");
        return id;
    }

    // 4. Grassroots Voting with Anti-Sybil Vault
    public boolean voteOnGrievance(String citizenId, int ticketId) {
        BaseRecord record = masterRecordRegistry.get(ticketId);
        if (record == null) {
            System.out.println(" [X] ERROR: Ticket #" + ticketId + " does not exist!");
            return false;
        }

        if (!(record instanceof GrievanceRecord)) {
            System.out.println(" [X] ERROR: Record #" + ticketId + " is not an upvotable grievance!");
            return false;
        }

        GrievanceRecord grievance = (GrievanceRecord) record;
        boolean success = antiSybilVault.castVote(citizenId, grievance);
        if (success) {
            // Re-schedule into Heap so the updated score bubbles up
            priorityScheduler.schedule(grievance);
        }
        return success;
    }

    // 5. Prefix Trie Autocomplete
    public List<String> searchAutocompleteTags(String prefix) {
        return tagTrie.autocomplete(prefix);
    }

    // --- CORE & POLITICIAN HUB INTERFACES ---

    // View Highest Priority Crisis from Max-Heap: O(1)
    public void viewTopEmergency() {
        BaseRecord top = priorityScheduler.peekHighestPriority();
        if (top == null) {
            System.out.println("No active complaints in the priority queue.");
            return;
        }
        System.out.println("\n>>> CURRENT #1 HIGHEST PRIORITY PUBLIC CRISIS:");
        top.displaySummary();
    }

    // Municipal Official Claims Ticket: OPEN -> IN_PROGRESS
    public boolean claimTicket(int ticketId, String officerName, double budget) {
        BaseRecord record = masterRecordRegistry.get(ticketId);
        if (record == null) {
            System.out.println("Ticket #" + ticketId + " not found!");
            return false;
        }

        if (!(record instanceof GrievanceRecord)) {
            System.out.println("Record #" + ticketId + " is not a municipal grievance!");
            return false;
        }

        return LifecycleFSM.claimIssue((GrievanceRecord) record, officerName, budget);
    }

    // Municipal Official Resolves Ticket: IN_PROGRESS -> RESOLVED
    public boolean resolveTicket(int ticketId, String proofNotes) {
        BaseRecord record = masterRecordRegistry.get(ticketId);
        if (record == null) {
            System.out.println("Ticket #" + ticketId + " not found!");
            return false;
        }

        if (!(record instanceof GrievanceRecord)) {
            System.out.println("Record #" + ticketId + " is not a municipal grievance!");
            return false;
        }

        return LifecycleFSM.resolveIssue((GrievanceRecord) record, proofNotes);
    }

    // Display all active records
    public void displayAllRecords() {
        System.out.println("\n================ MASTER CITIZEN REGISTRY (" + masterRecordRegistry.size() + " Records) ================");
        for (BaseRecord record : masterRecordRegistry.values()) {
            record.displaySummary();
        }
    }

    // Politician 0-100 Accountability Audit
    public void auditPolitician(String politicianName, String wardId,
                                String startMonth, String endMonth) {
        telemetryEngine.displayPoliticianAudit(politicianName, wardId, startMonth, endMonth);
    }
}

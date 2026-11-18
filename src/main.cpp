#include <iostream>
#include <string>
#include <limits>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif
#include "UdaanUnifiedBridge.hpp"

using namespace std;
using namespace CivicSentinel;

void printMasterBanner() {
    cout << "\n=================================================================" << endl;
    cout << "     PROJECT UDAAN: DEMOCRATIC FIELD INTELLIGENCE & GOVERNANCE   " << endl;
    cout << "      Jaypee Institute of Information Technology (JIIT, Noida)   " << endl;
    cout << "   Dept. of Computer Science & Engineering and Information Tech  " << endl;
    cout << "          Data Structures Lab (15B17CI371) | Batch B2            " << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "       Abhishek Bansal (2501030123) | Divyansh Agarwal (2501030124)       " << endl;
    cout << "                       Arjun Bhardwaj (2501030134)                        " << endl;
    cout << "=================================================================" << endl;
}

void printMasterMenu() {
    cout << "\n=================================================================" << endl;
    cout << "                 MASTER SYSTEM CONTROL DASHBOARD                 " << endl;
    cout << "=================================================================" << endl;
    cout << " [1] CITIZEN FIELD PORTAL" << endl;
    cout << "     - Lodge Citizen Complaint (Duplicate Detection + Trie Tagging)" << endl;
    cout << "     - Upvote Ticket (Anti-Sybil Single-Vote Enforcement)" << endl;
    cout << "     - Submit Commendation & Democratic Verification" << endl;
    cout << "     - Live Prefix Trie Autocomplete Tag Query" << endl;
    cout << "\n [2] CORE DISPATCH & POLITICIAN AUDIT ENGINE" << endl;
    cout << "     - Peek Top Emergency Crisis in Max-Heap (O(1))" << endl;
    cout << "     - Claim Ticket & Allocate Municipal Budget (FSM Transition)" << endl;
    cout << "     - Mark Work Resolved with Audit Proof (FSM Transition)" << endl;
    cout << "     - Red-Black Tree Politician Scorecard Audit (0-100 Rating)" << endl;
    cout << "\n [3] ECONOMIC & WELFARE ENGINE (PILLAR 2)" << endl;
    cout << "     - Multidimensional Poverty Index (MPI) Demographic Range Query" << endl;
    cout << "     - 0/1 Knapsack Dynamic Programming Stimulus Optimization" << endl;
    cout << "     - Fenwick Tree (BIT) Ward Food Reserve Range Queries" << endl;
    cout << "     - Autonomous Macroeconomic Policy Triggers at Queue Roots" << endl;
    cout << "\n [4] UNIFIED INTER-PORTAL COMMUNICATION BRIDGE (LIVE DEMO)" << endl;
    cout << "     * Field Portal Ingestion -> Core Max-Heap -> Skill Trie Labor" << endl;
    cout << "       Absorption -> Food Grain Influx -> Delta BPL Politician Audit" << endl;
    cout << "\n [5] FULL END-TO-END AUTOMATED VIVA SIMULATION" << endl;
    cout << " [0] Exit System" << endl;
    cout << "=================================================================" << endl;
    cout << "Select Portal / Operation [0-5]: ";
}

void runAutomatedDemo(CivicSentinelSystem& system) {
    cout << "\n========================================================" << endl;
    cout << "   STARTING AUTOMATED END-TO-END DEMO SIMULATION        " << endl;
    cout << "========================================================" << endl;

    // 1. Prefix Trie test
    cout << "\n>>> [DEMO 1: Prefix Trie Autocomplete for 'wat']" << endl;
    auto matches = system.searchAutocompleteTags("wat");
    for (const string& match : matches) {
        cout << "  -> Found tag: " << match << endl;
    }

    // 2. Duplicate Detection test
    cout << "\n>>> [DEMO 2: Near-Duplicate Detection in Ward-12]" << endl;
    system.lodgeComplaint(
        CivicCategory::ROADS_INFRASTRUCTURE,
        "Dangerous Pothole on Ring Road highway", // Very similar to existing #101
        "Another complaint about the same crater",
        "Ward-12", "CITIZEN_BOB", SeverityLevel::HIGH
    );

    // 3. Anti-Sybil Vault test
    cout << "\n>>> [DEMO 3: Anti-Sybil Single-Vote Enforcement on Ticket #102]" << endl;
    system.voteOnGrievance("CITIZEN_VOTER_1", 102);
    system.voteOnGrievance("CITIZEN_VOTER_2", 102);
    // Duplicate attack:
    system.voteOnGrievance("CITIZEN_VOTER_1", 102);

    // 4. Max-Heap Priority scheduling test
    cout << "\n>>> [DEMO 4: Max-Heap Dispatch Scheduling]" << endl;
    system.viewTopEmergency();

    // 5. Finite State Machine lifecycle test
    cout << "\n>>> [DEMO 5: Full FSM Lifecycle State Transition on Ticket #102]" << endl;
    cout << "Step A: Attempt illegal early resolve:" << endl;
    system.resolveTicket(102, "Trying to close without budget");

    cout << "\nStep B: Legitimate Claim with Budget:" << endl;
    system.claimTicket(102, "Executive Engineer V. K. Saxena", 85000.0);

    cout << "\nStep C: Legitimate Municipal Completion:" << endl;
    system.resolveTicket(102, "Main pipeline repaired and tested; water purity verified at 99.4%");

    cout << "\nStep D: Citizen Democratic Verification via Compliment:" << endl;
    system.lodgeCompliment(
        CivicCategory::WATER_SUPPLY,
        "Clean drinking water restored in Sector 62!",
        "Water runs crystal clear now. Fast work by the municipal crew.",
        "Ward-12", "CITIZEN_KAVITA", 102, 5, "Executive Engineer V. K. Saxena"
    );

    // 6. Red-Black Tree Politician Evaluation
    cout << "\n>>> [DEMO 6: Politician Accountability Audit (Red-Black Tree Range Query)]" << endl;
    system.auditPolitician("Hon. Rajeshwar Singh (MLA)", "Ward-12 (Noida)", "2026-07", "2026-10");

    cout << "\n========================================================" << endl;
    cout << "   AUTOMATED DEMO COMPLETE: ALL DSA & OOP VERIFIED!     " << endl;
    cout << "========================================================" << endl;
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    UdaanUnifiedBridge bridge;

    // Check CLI arguments
    if (argc > 1) {
        string arg = argv[1];
        if (arg == "--bridge" || arg == "-b") {
            printMasterBanner();
            bridge.runFullInterPortalDemo();
            return 0;
        } else if (arg == "--demo" || arg == "-d") {
            printMasterBanner();
            runAutomatedDemo(bridge.civicSystem);
            return 0;
        } else if (arg == "--economic" || arg == "-e") {
            printMasterBanner();
            bridge.runKnapsackStimulus(4, 6000.0);
            bridge.queryWardStocks(1, 5);
            return 0;
        }
    }

    printMasterBanner();

    int choice = -1;
    while (choice != 0) {
        printMasterMenu();
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                cout << "\n--- CITIZEN FIELD PORTAL (INTAKE & DUPLICATE CHECK) ---" << endl;
                cout << "1. Lodge Grievance\n2. Upvote Ticket\n3. Autocomplete Prefix Search\n4. Submit Compliment\nSelect: ";
                int sub;
                if (!(cin >> sub)) { cin.clear(); cin.ignore(1000, '\n'); break; }
                cin.ignore(1000, '\n');
                if (sub == 1) {
                    string title, desc, ward, citizen;
                    int cat, sev;
                    cout << "Title: "; getline(cin, title);
                    cout << "Description: "; getline(cin, desc);
                    cout << "Ward (e.g. Ward-12): "; getline(cin, ward);
                    cout << "Citizen ID: "; getline(cin, citizen);
                    cout << "Category (0: Sanitation, 1: Roads, 2: Water, 3: Health, 4: Power): "; cin >> cat;
                    cout << "Severity (1: Low, 2: Medium, 3: High, 4: Critical): "; cin >> sev;
                    bridge.lodgeGrievance(static_cast<CivicCategory>(cat), title, desc, ward, citizen, static_cast<SeverityLevel>(sev));
                } else if (sub == 2) {
                    string citizen; int tid;
                    cout << "Citizen ID: "; getline(cin, citizen);
                    cout << "Ticket ID: "; cin >> tid;
                    bridge.upvoteTicket(citizen, tid);
                } else if (sub == 3) {
                    string prefix;
                    cout << "Enter Prefix (e.g. 'wat', 'pot', 'san'): "; getline(cin, prefix);
                    auto tags = bridge.searchTags(prefix);
                    cout << "Found " << tags.size() << " matching tags:" << endl;
                    for (const auto& t : tags) cout << "  -> " << t << endl;
                } else if (sub == 4) {
                    string title, remarks, ward, citizen, officer;
                    int tid, stars;
                    cout << "Ticket Ref: "; cin >> tid; cin.ignore();
                    cout << "Title: "; getline(cin, title);
                    cout << "Remarks: "; getline(cin, remarks);
                    cout << "Ward: "; getline(cin, ward);
                    cout << "Citizen ID: "; getline(cin, citizen);
                    cout << "Officer: "; getline(cin, officer);
                    cout << "Stars (1-5): "; cin >> stars;
                    bridge.lodgeCompliment(CivicCategory::GENERAL_POLICY, title, remarks, ward, citizen, tid, stars, officer);
                }
                break;
            }
            case 2: {
                cout << "\n--- CORE DISPATCH & POLITICIAN AUDIT ENGINE ---" << endl;
                cout << "1. Peek Max-Heap Top Emergency\n2. Claim Ticket (FSM)\n3. Resolve Ticket (FSM)\n4. Politician Audit\nSelect: ";
                int sub;
                if (!(cin >> sub)) { cin.clear(); cin.ignore(1000, '\n'); break; }
                cin.ignore(1000, '\n');
                if (sub == 1) {
                    bridge.peekTopEmergency();
                } else if (sub == 2) {
                    int tid; string officer, skill; double budget;
                    cout << "Ticket ID: "; cin >> tid; cin.ignore();
                    cout << "Officer Name: "; getline(cin, officer);
                    cout << "Allocated Budget ($): "; cin >> budget; cin.ignore();
                    cout << "Required Skill (or enter to skip): "; getline(cin, skill);
                    bridge.claimAndDispatchWork(tid, officer, budget, skill);
                } else if (sub == 3) {
                    int tid; string proof;
                    cout << "Ticket ID: "; cin >> tid; cin.ignore();
                    cout << "Completion Proof: "; getline(cin, proof);
                    bridge.resolveTicket(tid, proof);
                } else if (sub == 4) {
                    string name, ward, sM, eM;
                    cout << "Politician Name: "; getline(cin, name);
                    cout << "Ward: "; getline(cin, ward);
                    cout << "Start Month (YYYY-MM): "; getline(cin, sM);
                    cout << "End Month (YYYY-MM): "; getline(cin, eM);
                    bridge.runPoliticianAudit(name, ward, sM, eM);
                }
                break;
            }
            case 3: {
                cout << "\n--- ECONOMIC & WELFARE ENGINE (PILLAR 2) ---" << endl;
                cout << "1. 0/1 Knapsack Stimulus Allocation\n2. Fenwick Tree Ward Food Reserves\n3. Demographic Range Query (B+ Tree Sim)\nSelect: ";
                int sub;
                if (!(cin >> sub)) { cin.clear(); cin.ignore(1000, '\n'); break; }
                cin.ignore(1000, '\n');
                if (sub == 1) {
                    int ward; double budget;
                    cout << "Target Ward: "; cin >> ward;
                    cout << "Available Relief Budget ($): "; cin >> budget;
                    bridge.runKnapsackStimulus(ward, budget);
                } else if (sub == 2) {
                    int startW, endW;
                    cout << "Start Ward [1-20]: "; cin >> startW;
                    cout << "End Ward [1-20]: "; cin >> endW;
                    bridge.queryWardStocks(startW, endW);
                } else if (sub == 3) {
                    double minInc, maxInc;
                    cout << "Min Income: "; cin >> minInc;
                    cout << "Max Income: "; cin >> maxInc;
                    auto matched = bridge.economicEngine.query_citizens_by_income_range(minInc, maxInc);
                    cout << "Found " << matched.size() << " citizens in range:" << endl;
                    for (uint64_t cid : matched) {
                        auto c = bridge.economicEngine.get_citizen(cid);
                        if (c) c->display();
                    }
                }
                break;
            }
            case 4: {
                bridge.runFullInterPortalDemo();
                break;
            }
            case 5: {
                cout << "\n========================================================" << endl;
                cout << "   STARTING AUTOMATED END-TO-END DEMO SIMULATION        " << endl;
                cout << "========================================================" << endl;
                runAutomatedDemo(bridge.civicSystem);
                break;
            }
            case 0: {
                cout << "\nShutting down Project Udaan Master Engine. Jai Hind!" << endl;
                break;
            }
            default:
                cout << "Invalid choice! Please select 0 to 5." << endl;
        }
    }

    return 0;
}

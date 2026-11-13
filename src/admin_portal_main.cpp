#include <iostream>
#include <string>
#include <limits>
#include "CivicSentinelSystem.hpp"

using namespace std;
using namespace CivicSentinel;

void printBanner() {
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

void printMenu() {
    cout << "\n--- GROUND-LEVEL FIELD PORTAL (INTAKE & DUPLICATE CHECK) ---" << endl;
    cout << " 1. Lodge a Citizen Complaint (with Duplicate & Trie check)" << endl;
    cout << " 2. Upvote an Existing Issue (Anti-Sybil Vault protected)" << endl;
    cout << " 3. Submit Citizen Compliment (Commendation & FSM Verification)" << endl;
    cout << " 4. Propose a Civic Policy Suggestion" << endl;
    cout << " 5. Autocomplete Search for Civic Tags (Prefix Trie)" << endl;
    cout << "\n--- CORE ENGINE & POLITICIAN INTELLIGENCE ---" << endl;
    cout << " 6. Peek Highest-Priority Crisis in Max-Heap (O(1))" << endl;
    cout << " 7. Municipal Official: Claim Issue & Assign Budget (FSM)" << endl;
    cout << " 8. Municipal Official: Mark Work Resolved with Proof (FSM)" << endl;
    cout << " 9. Run Politician 0-100 Accountability Audit (Red-Black Tree)" << endl;
    cout << " 10. View Master Citizen Registry" << endl;
    cout << "\n--- AUTOMATED VIVA VERIFICATION ---" << endl;
    cout << " 11. Run Full End-to-End Automated Simulation (One-Click Demo)" << endl;
    cout << " 0. Exit System" << endl;
    cout << "=================================================================" << endl;
    cout << "Select an Option [0-11]: ";
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

int main() {
    CivicSentinelSystem system;
    printBanner();

    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

        switch (choice) {
            case 1: {
                cout << "\n--- LODGE CITIZEN COMPLAINT ---" << endl;
                string title, desc, ward, citizen;
                int catChoice, sevChoice;

                cout << "Enter Complaint Title: ";
                getline(cin, title);
                cout << "Enter Description: ";
                getline(cin, desc);
                cout << "Enter Ward (e.g. Ward-12): ";
                getline(cin, ward);
                cout << "Enter Your Citizen ID (e.g. CITIZEN_007): ";
                getline(cin, citizen);

                cout << "Select Category: (0: Sanitation, 1: Roads, 2: Water, 3: Health, 4: Power): ";
                cin >> catChoice;
                cout << "Select Severity: (1: Low, 2: Medium, 3: High, 4: Critical): ";
                cin >> sevChoice;

                system.lodgeComplaint(
                    static_cast<CivicCategory>(catChoice),
                    title, desc, ward, citizen,
                    static_cast<SeverityLevel>(sevChoice)
                );
                break;
            }
            case 2: {
                cout << "\n--- UPVOTE A CITIZEN TICKET ---" << endl;
                string citizenId;
                int ticketId;
                cout << "Enter Your Citizen ID: ";
                getline(cin, citizenId);
                cout << "Enter Ticket ID to Upvote: ";
                cin >> ticketId;

                system.voteOnGrievance(citizenId, ticketId);
                break;
            }
            case 3: {
                cout << "\n--- SUBMIT CITIZEN COMMENDATION (COMPLIMENT) ---" << endl;
                string title, remarks, ward, citizen, officer;
                int ticketId, stars;

                cout << "Enter Target Ticket ID Ref: ";
                cin >> ticketId;
                cin.ignore();
                cout << "Enter Commendation Title: ";
                getline(cin, title);
                cout << "Enter Remarks: ";
                getline(cin, remarks);
                cout << "Enter Ward: ";
                getline(cin, ward);
                cout << "Enter Your Citizen ID: ";
                getline(cin, citizen);
                cout << "Officer Name to Recognize: ";
                getline(cin, officer);
                cout << "Satisfaction Rating (1 to 5 Stars): ";
                cin >> stars;

                system.lodgeCompliment(
                    CivicCategory::GENERAL_POLICY,
                    title, remarks, ward, citizen,
                    ticketId, stars, officer
                );
                break;
            }
            case 4: {
                cout << "\n--- PROPOSE CIVIC POLICY SUGGESTION ---" << endl;
                string title, desc, ward, citizen, dept;
                int beneficiaries;

                cout << "Enter Suggestion Title: ";
                getline(cin, title);
                cout << "Enter Detailed Proposal: ";
                getline(cin, desc);
                cout << "Enter Ward: ";
                getline(cin, ward);
                cout << "Enter Your Citizen ID: ";
                getline(cin, citizen);
                cout << "Target Municipal Department: ";
                getline(cin, dept);
                cout << "Projected Public Beneficiaries (Number of Citizens): ";
                cin >> beneficiaries;

                system.lodgeSuggestion(
                    CivicCategory::GENERAL_POLICY,
                    title, desc, ward, citizen, dept, beneficiaries
                );
                break;
            }
            case 5: {
                cout << "\n--- AUTOCOMPLETE TAG SEARCH (PREFIX TRIE) ---" << endl;
                string prefix;
                cout << "Enter prefix to search (e.g. 'wat', 'pot', 'san', 'hosp'): ";
                getline(cin, prefix);

                auto matches = system.searchAutocompleteTags(prefix);
                cout << "Matching Civic Tags found (" << matches.size() << "):" << endl;
                for (const auto& tag : matches) {
                    cout << "  -> " << tag << endl;
                }
                break;
            }
            case 6: {
                system.viewTopEmergency();
                break;
            }
            case 7: {
                cout << "\n--- CLAIM TICKET & ALLOCATE BUDGET (FSM) ---" << endl;
                int ticketId;
                string officer;
                double budget;

                cout << "Enter Ticket ID to Claim: ";
                cin >> ticketId;
                cin.ignore();
                cout << "Enter Officer Name: ";
                getline(cin, officer);
                cout << "Enter Allocated Budget ($): ";
                cin >> budget;

                system.claimTicket(ticketId, officer, budget);
                break;
            }
            case 8: {
                cout << "\n--- MARK ISSUE RESOLVED (FSM) ---" << endl;
                int ticketId;
                string proof;

                cout << "Enter Ticket ID: ";
                cin >> ticketId;
                cin.ignore();
                cout << "Enter Completion Proof Notes: ";
                getline(cin, proof);

                system.resolveTicket(ticketId, proof);
                break;
            }
            case 9: {
                cout << "\n--- POLITICIAN ACCOUNTABILITY AUDIT (RED-BLACK TREE) ---" << endl;
                string name, ward, startM, endM;
                cout << "Enter Politician Name: ";
                getline(cin, name);
                cout << "Enter Ward / Constituency: ";
                getline(cin, ward);
                cout << "Start Month (YYYY-MM, e.g. '2026-07'): ";
                getline(cin, startM);
                cout << "End Month (YYYY-MM, e.g. '2026-10'): ";
                getline(cin, endM);

                system.auditPolitician(name, ward, startM, endM);
                break;
            }
            case 10: {
                system.displayAllRecords();
                break;
            }
            case 11: {
                runAutomatedDemo(system);
                break;
            }
            case 0: {
                cout << "\nShutting down Civic-Sentinel. Jai Hind!" << endl;
                break;
            }
            default:
                cout << "Invalid choice! Please select 0 to 11." << endl;
        }
    }

    return 0;
}

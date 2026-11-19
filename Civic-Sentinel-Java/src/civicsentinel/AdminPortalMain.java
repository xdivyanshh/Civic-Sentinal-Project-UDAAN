package civicsentinel;

import java.util.List;
import java.util.Scanner;

/**
 * Field Portal & Admin Intelligence CLI Driver for CIVIC-SENTINEL.
 * 
 * Course: Data Structures Lab (15B17CI371) — 2nd Year, 3rd Semester
 * Institution: Jaypee Institute of Information Technology (JIIT), Noida
 * Authors:
 *  - Abhishek Bansal (2501030123)
 *  - Divyansh Agarwal (2501030124)
 *  - Arjun Bhardwaj (2501030134)
 */
public class AdminPortalMain {

    public static void printBanner() {
        System.out.println("\n=================================================================");
        System.out.println("     PROJECT UDAAN: DEMOCRATIC FIELD INTELLIGENCE & GOVERNANCE   ");
        System.out.println("      Jaypee Institute of Information Technology (JIIT, Noida)   ");
        System.out.println("   Dept. of Computer Science & Engineering and Information Tech  ");
        System.out.println("          Data Structures Lab (15B17CI371) | Batch B2            ");
        System.out.println("-----------------------------------------------------------------");
        System.out.println("       Abhishek Bansal (2501030123) | Divyansh Agarwal (2501030124)       ");
        System.out.println("                       Arjun Bhardwaj (2501030134)                        ");
        System.out.println("=================================================================");
    }

    public static void printMenu() {
        System.out.println("\n--- GROUND-LEVEL FIELD PORTAL (INTAKE & DUPLICATE CHECK) ---");
        System.out.println(" 1. Lodge a Citizen Complaint (with Duplicate & Trie check)");
        System.out.println(" 2. Upvote an Existing Issue (Anti-Sybil Vault protected)");
        System.out.println(" 3. Submit Citizen Compliment (Commendation & FSM Verification)");
        System.out.println(" 4. Propose a Civic Policy Suggestion");
        System.out.println(" 5. Autocomplete Search for Civic Tags (Prefix Trie)");
        System.out.println("\n--- CORE ENGINE & POLITICIAN INTELLIGENCE ---");
        System.out.println(" 6. Peek Highest-Priority Crisis in Max-Heap (O(1))");
        System.out.println(" 7. Municipal Official: Claim Issue & Assign Budget (FSM)");
        System.out.println(" 8. Municipal Official: Mark Work Resolved with Proof (FSM)");
        System.out.println(" 9. Run Politician 0-100 Accountability Audit (Red-Black Tree)");
        System.out.println(" 10. View Master Citizen Registry");
        System.out.println("\n--- AUTOMATED VIVA VERIFICATION ---");
        System.out.println(" 11. Run Full End-to-End Automated Simulation (One-Click Demo)");
        System.out.println(" 0. Exit System");
        System.out.println("=================================================================");
        System.out.print("Select an Option [0-11]: ");
    }

    public static void runAutomatedDemo(CivicSentinelSystem system) {
        System.out.println("\n========================================================");
        System.out.println("   STARTING AUTOMATED END-TO-END DEMO SIMULATION        ");
        System.out.println("========================================================");

        // 1. Prefix Trie test
        System.out.println("\n>>> [DEMO 1: Prefix Trie Autocomplete for 'wat']");
        List<String> matches = system.searchAutocompleteTags("wat");
        for (String match : matches) {
            System.out.println("  -> Found tag: " + match);
        }

        // 2. Duplicate Detection test
        System.out.println("\n>>> [DEMO 2: Near-Duplicate Detection in Ward-12]");
        system.lodgeComplaint(
            CivicCategory.ROADS_INFRASTRUCTURE,
            "Dangerous Pothole on Ring Road highway", // Very similar to existing #101
            "Another complaint about the same crater",
            "Ward-12", "CITIZEN_BOB", SeverityLevel.HIGH
        );

        // 3. Anti-Sybil Vault test
        System.out.println("\n>>> [DEMO 3: Anti-Sybil Single-Vote Enforcement on Ticket #102]");
        system.voteOnGrievance("CITIZEN_VOTER_1", 102);
        system.voteOnGrievance("CITIZEN_VOTER_2", 102);
        // Duplicate attack:
        system.voteOnGrievance("CITIZEN_VOTER_1", 102);

        // 4. Max-Heap Priority scheduling test
        System.out.println("\n>>> [DEMO 4: Max-Heap Dispatch Scheduling]");
        system.viewTopEmergency();

        // 5. Finite State Machine lifecycle test
        System.out.println("\n>>> [DEMO 5: Full FSM Lifecycle State Transition on Ticket #102]");
        System.out.println("Step A: Attempt illegal early resolve:");
        system.resolveTicket(102, "Trying to close without budget");

        System.out.println("\nStep B: Legitimate Claim with Budget:");
        system.claimTicket(102, "Executive Engineer V. K. Saxena", 85000.0);

        System.out.println("\nStep C: Legitimate Municipal Completion:");
        system.resolveTicket(102, "Main pipeline repaired and tested; water purity verified at 99.4%");

        System.out.println("\nStep D: Citizen Democratic Verification via Compliment:");
        system.lodgeCompliment(
            CivicCategory.WATER_SUPPLY,
            "Clean drinking water restored in Sector 62!",
            "Water runs crystal clear now. Fast work by the municipal crew.",
            "Ward-12", "CITIZEN_KAVITA", 102, 5, "Executive Engineer V. K. Saxena"
        );

        // 6. Red-Black Tree Politician Evaluation
        System.out.println("\n>>> [DEMO 6: Politician Accountability Audit (Red-Black Tree Range Query)]");
        system.auditPolitician("Hon. Rajeshwar Singh (MLA)", "Ward-12 (Noida)", "2026-07", "2026-10");

        System.out.println("\n========================================================");
        System.out.println("   AUTOMATED DEMO COMPLETE: ALL DSA & OOP VERIFIED!     ");
        System.out.println("========================================================");
    }

    public static void main(String[] args) {
        CivicSentinelSystem system = new CivicSentinelSystem();
        printBanner();

        Scanner scanner = new Scanner(System.in);
        int choice = -1;

        while (choice != 0) {
            printMenu();
            if (!scanner.hasNextInt()) {
                if (!scanner.hasNext()) break;
                scanner.next();
                System.out.println("Invalid input! Please enter a number.");
                continue;
            }
            choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1: {
                    System.out.print("Enter Complaint Title: "); String title = scanner.nextLine();
                    System.out.print("Enter Detailed Description: "); String desc = scanner.nextLine();
                    System.out.print("Enter Ward ID (e.g., Ward-12): "); String ward = scanner.nextLine();
                    System.out.print("Enter Citizen ID: "); String citizen = scanner.nextLine();
                    System.out.print("Enter Category (0: Sanitation, 1: Roads, 2: Water, 3: Health, 4: Power, 5: Bus, 6: Market, 7: General): ");
                    int cat = scanner.nextInt();
                    System.out.print("Enter Severity (1: Low, 2: Medium, 3: High, 4: Critical): ");
                    int sev = scanner.nextInt();
                    scanner.nextLine();
                    system.lodgeComplaint(CivicCategory.fromOrdinal(cat), title, desc, ward, citizen, SeverityLevel.fromValue(sev));
                    break;
                }
                case 2: {
                    System.out.print("Enter Your Citizen ID (Voter Verification): "); String citizen = scanner.nextLine();
                    System.out.print("Enter Ticket ID to Upvote: "); int tid = scanner.nextInt();
                    scanner.nextLine();
                    system.voteOnGrievance(citizen, tid);
                    break;
                }
                case 3: {
                    System.out.print("Enter Verified Ticket ID Ref: "); int tid = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter Commendation Title: "); String title = scanner.nextLine();
                    System.out.print("Enter Citizen Remarks: "); String remarks = scanner.nextLine();
                    System.out.print("Enter Ward ID: "); String ward = scanner.nextLine();
                    System.out.print("Enter Citizen ID: "); String citizen = scanner.nextLine();
                    System.out.print("Enter Officer Name to Recognize: "); String officer = scanner.nextLine();
                    System.out.print("Enter Satisfaction Rating (1 to 5 Stars): "); int stars = scanner.nextInt();
                    scanner.nextLine();
                    system.lodgeCompliment(CivicCategory.GENERAL_POLICY, title, remarks, ward, citizen, tid, stars, officer);
                    break;
                }
                case 4: {
                    System.out.print("Enter Policy Suggestion Title: "); String title = scanner.nextLine();
                    System.out.print("Enter Proposal Details: "); String desc = scanner.nextLine();
                    System.out.print("Enter Ward ID: "); String ward = scanner.nextLine();
                    System.out.print("Enter Citizen ID: "); String citizen = scanner.nextLine();
                    System.out.print("Enter Target Department: "); String dept = scanner.nextLine();
                    System.out.print("Estimated Public Beneficiaries: "); int beneficiaries = scanner.nextInt();
                    scanner.nextLine();
                    system.lodgeSuggestion(CivicCategory.GENERAL_POLICY, title, desc, ward, citizen, dept, beneficiaries);
                    break;
                }
                case 5: {
                    System.out.print("Enter Keyword Prefix to Search (e.g., 'wat', 'pip', 'san'): ");
                    String prefix = scanner.nextLine();
                    List<String> results = system.searchAutocompleteTags(prefix);
                    System.out.println(" Prefix Trie found " + results.size() + " matches:");
                    for (String tag : results) {
                        System.out.println("  -> " + tag);
                    }
                    break;
                }
                case 6: {
                    system.viewTopEmergency();
                    break;
                }
                case 7: {
                    System.out.print("Enter Ticket ID to Claim: "); int tid = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter Official's Name: "); String officer = scanner.nextLine();
                    System.out.print("Enter Approved Budget ($): "); double budget = scanner.nextDouble();
                    scanner.nextLine();
                    system.claimTicket(tid, officer, budget);
                    break;
                }
                case 8: {
                    System.out.print("Enter Ticket ID to Mark Resolved: "); int tid = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter Field Resolution Proof / Notes: "); String proof = scanner.nextLine();
                    system.resolveTicket(tid, proof);
                    break;
                }
                case 9: {
                    System.out.print("Enter Politician / MLA Name: "); String name = scanner.nextLine();
                    System.out.print("Enter Jurisdiction / Ward: "); String ward = scanner.nextLine();
                    System.out.print("Enter Start Audit Month (YYYY-MM): "); String sM = scanner.nextLine();
                    System.out.print("Enter End Audit Month (YYYY-MM): "); String eM = scanner.nextLine();
                    system.auditPolitician(name, ward, sM, eM);
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
                    System.out.println("\nExiting Civic-Sentinel Field Console. Jai Hind!");
                    break;
                }
                default:
                    System.out.println("Invalid selection! Please enter an option from 0 to 11.");
            }
        }
    }
}

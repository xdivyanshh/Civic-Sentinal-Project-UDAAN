package civicsentinel;

import java.util.List;
import java.util.Scanner;

/**
 * Master Unified Simulation Driver for CIVIC-SENTINEL (Project Udaan).
 * 
 * Course: Data Structures Lab (15B17CI371) — 2nd Year, 3rd Semester
 * Institution: Jaypee Institute of Information Technology (JIIT), Noida
 * Authors:
 *  - Abhishek Bansal (2501030123)
 *  - Divyansh Agarwal (2501030124)
 *  - Arjun Bhardwaj (2501030134)
 */
public class Main {

    public static void printMasterBanner() {
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

    public static void printMasterMenu() {
        System.out.println("\n=================================================================");
        System.out.println("                 MASTER SYSTEM CONTROL DASHBOARD                 ");
        System.out.println("=================================================================");
        System.out.println(" [1] CITIZEN FIELD PORTAL");
        System.out.println("     - Lodge Citizen Complaint (Duplicate Detection + Trie Tagging)");
        System.out.println("     - Upvote Ticket (Anti-Sybil Single-Vote Enforcement)");
        System.out.println("     - Submit Commendation & Democratic Verification");
        System.out.println("     - Live Prefix Trie Autocomplete Tag Query");
        System.out.println("\n [2] CORE DISPATCH & POLITICIAN AUDIT ENGINE");
        System.out.println("     - Peek Top Emergency Crisis in Max-Heap (O(1))");
        System.out.println("     - Claim Ticket & Allocate Municipal Budget (FSM Transition)");
        System.out.println("     - Mark Work Resolved with Audit Proof (FSM Transition)");
        System.out.println("     - Red-Black Tree Politician Scorecard Audit (0-100 Rating)");
        System.out.println("\n [3] ECONOMIC & WELFARE ENGINE (PILLAR 2)");
        System.out.println("     - Multidimensional Poverty Index (MPI) Demographic Range Query");
        System.out.println("     - 0/1 Knapsack Dynamic Programming Stimulus Optimization");
        System.out.println("     - Fenwick Tree (BIT) Ward Food Reserve Range Queries");
        System.out.println("     - Autonomous Macroeconomic Policy Triggers at Queue Roots");
        System.out.println("\n [4] UNIFIED INTER-PORTAL COMMUNICATION BRIDGE (LIVE DEMO)");
        System.out.println("     * Field Portal Ingestion -> Core Max-Heap -> Skill Trie Labor");
        System.out.println("       Absorption -> Food Grain Influx -> Delta BPL Politician Audit");
        System.out.println("\n [5] FULL END-TO-END AUTOMATED VIVA SIMULATION");
        System.out.println(" [0] Exit System");
        System.out.println("=================================================================");
        System.out.print("Select Portal / Operation [0-5]: ");
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
        UdaanUnifiedBridge bridge = new UdaanUnifiedBridge();

        // Check CLI arguments
        if (args.length > 0) {
            String arg = args[0];
            if (arg.equals("--bridge") || arg.equals("-b")) {
                printMasterBanner();
                bridge.runFullInterPortalDemo();
                return;
            } else if (arg.equals("--demo") || arg.equals("-d")) {
                printMasterBanner();
                runAutomatedDemo(bridge.civicSystem);
                return;
            } else if (arg.equals("--economic") || arg.equals("-e")) {
                printMasterBanner();
                bridge.runKnapsackStimulus(4, 6000.0);
                bridge.queryWardStocks(1, 5);
                return;
            }
        }

        printMasterBanner();

        Scanner scanner = new Scanner(System.in);
        int choice = -1;

        while (choice != 0) {
            printMasterMenu();
            if (!scanner.hasNextInt()) {
                if (!scanner.hasNext()) break;
                scanner.next();
                System.out.println("Invalid input! Please enter a number.");
                continue;
            }
            choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1: {
                    System.out.println("\n--- CITIZEN FIELD PORTAL (INTAKE & DUPLICATE CHECK) ---");
                    System.out.print("1. Lodge Grievance\n2. Upvote Ticket\n3. Autocomplete Prefix Search\n4. Submit Compliment\nSelect: ");
                    if (!scanner.hasNextInt()) { scanner.nextLine(); break; }
                    int sub = scanner.nextInt();
                    scanner.nextLine();

                    if (sub == 1) {
                        System.out.print("Title: "); String title = scanner.nextLine();
                        System.out.print("Description: "); String desc = scanner.nextLine();
                        System.out.print("Ward (e.g. Ward-12): "); String ward = scanner.nextLine();
                        System.out.print("Citizen ID: "); String citizen = scanner.nextLine();
                        System.out.print("Category (0: Sanitation, 1: Roads, 2: Water, 3: Health, 4: Power): ");
                        int cat = scanner.nextInt();
                        System.out.print("Severity (1: Low, 2: Medium, 3: High, 4: Critical): ");
                        int sev = scanner.nextInt();
                        scanner.nextLine();
                        bridge.lodgeGrievance(CivicCategory.fromOrdinal(cat), title, desc, ward, citizen, SeverityLevel.fromValue(sev));
                    } else if (sub == 2) {
                        System.out.print("Citizen ID: "); String citizen = scanner.nextLine();
                        System.out.print("Ticket ID: "); int tid = scanner.nextInt();
                        scanner.nextLine();
                        bridge.upvoteTicket(citizen, tid);
                    } else if (sub == 3) {
                        System.out.print("Enter Prefix (e.g. 'wat', 'pot', 'san'): ");
                        String prefix = scanner.nextLine();
                        List<String> tags = bridge.searchTags(prefix);
                        System.out.println("Found " + tags.size() + " matching tags:");
                        for (String t : tags) System.out.println("  -> " + t);
                    } else if (sub == 4) {
                        System.out.print("Ticket Ref: "); int tid = scanner.nextInt();
                        scanner.nextLine();
                        System.out.print("Title: "); String title = scanner.nextLine();
                        System.out.print("Remarks: "); String remarks = scanner.nextLine();
                        System.out.print("Ward: "); String ward = scanner.nextLine();
                        System.out.print("Citizen ID: "); String citizen = scanner.nextLine();
                        System.out.print("Officer: "); String officer = scanner.nextLine();
                        System.out.print("Stars (1-5): "); int stars = scanner.nextInt();
                        scanner.nextLine();
                        bridge.lodgeCompliment(CivicCategory.GENERAL_POLICY, title, remarks, ward, citizen, tid, stars, officer);
                    }
                    break;
                }
                case 2: {
                    System.out.println("\n--- CORE DISPATCH & POLITICIAN AUDIT ENGINE ---");
                    System.out.print("1. Peek Max-Heap Top Emergency\n2. Claim Ticket (FSM)\n3. Resolve Ticket (FSM)\n4. Politician Audit\nSelect: ");
                    if (!scanner.hasNextInt()) { scanner.nextLine(); break; }
                    int sub = scanner.nextInt();
                    scanner.nextLine();

                    if (sub == 1) {
                        bridge.peekTopEmergency();
                    } else if (sub == 2) {
                        System.out.print("Ticket ID: "); int tid = scanner.nextInt();
                        scanner.nextLine();
                        System.out.print("Officer Name: "); String officer = scanner.nextLine();
                        System.out.print("Allocated Budget ($): "); double budget = scanner.nextDouble();
                        scanner.nextLine();
                        System.out.print("Required Skill (or enter to skip): "); String skill = scanner.nextLine();
                        bridge.claimAndDispatchWork(tid, officer, budget, skill);
                    } else if (sub == 3) {
                        System.out.print("Ticket ID: "); int tid = scanner.nextInt();
                        scanner.nextLine();
                        System.out.print("Completion Proof: "); String proof = scanner.nextLine();
                        bridge.resolveTicket(tid, proof);
                    } else if (sub == 4) {
                        System.out.print("Politician Name: "); String name = scanner.nextLine();
                        System.out.print("Ward: "); String ward = scanner.nextLine();
                        System.out.print("Start Month (YYYY-MM): "); String sM = scanner.nextLine();
                        System.out.print("End Month (YYYY-MM): "); String eM = scanner.nextLine();
                        bridge.runPoliticianAudit(name, ward, sM, eM);
                    }
                    break;
                }
                case 3: {
                    System.out.println("\n--- ECONOMIC & WELFARE ENGINE (PILLAR 2) ---");
                    System.out.print("1. 0/1 Knapsack Stimulus Allocation\n2. Fenwick Tree Ward Food Reserves\n3. Demographic Range Query (B+ Tree Sim)\nSelect: ");
                    if (!scanner.hasNextInt()) { scanner.nextLine(); break; }
                    int sub = scanner.nextInt();
                    scanner.nextLine();

                    if (sub == 1) {
                        System.out.print("Target Ward: "); int ward = scanner.nextInt();
                        System.out.print("Available Relief Budget ($): "); double budget = scanner.nextDouble();
                        scanner.nextLine();
                        bridge.runKnapsackStimulus(ward, budget);
                    } else if (sub == 2) {
                        System.out.print("Start Ward [1-20]: "); int startW = scanner.nextInt();
                        System.out.print("End Ward [1-20]: "); int endW = scanner.nextInt();
                        scanner.nextLine();
                        bridge.queryWardStocks(startW, endW);
                    } else if (sub == 3) {
                        System.out.print("Min Income: "); double minInc = scanner.nextDouble();
                        System.out.print("Max Income: "); double maxInc = scanner.nextDouble();
                        scanner.nextLine();
                        List<Long> matched = bridge.economicEngine.queryCitizensByIncomeRange(minInc, maxInc);
                        System.out.println("Found " + matched.size() + " citizens in range:");
                        for (long cid : matched) {
                            CitizenProfile c = bridge.economicEngine.getCitizen(cid);
                            if (c != null) c.display();
                        }
                    }
                    break;
                }
                case 4: {
                    bridge.runFullInterPortalDemo();
                    break;
                }
                case 5: {
                    System.out.println("\n========================================================");
                    System.out.println("   STARTING AUTOMATED END-TO-END DEMO SIMULATION        ");
                    System.out.println("========================================================");
                    runAutomatedDemo(bridge.civicSystem);
                    break;
                }
                case 0: {
                    System.out.println("\nShutting down Project Udaan Master Engine. Jai Hind!");
                    break;
                }
                default:
                    System.out.println("Invalid choice! Please select 0 to 5.");
            }
        }
    }
}

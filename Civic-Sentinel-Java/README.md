# CIVIC-SENTINEL: Java Edition (Project Udaan)

> **Course**: Java Programming / Data Structures Lab (15B17CI371) — 2nd Year, 3rd Semester  
> **Institution**: Jaypee Institute of Information Technology (JIIT), Noida  
> **Department**: Computer Science & Engineering and Information Technology  
> **Course Faculty**: Dr. Lalita Mishra  
> **Authors**:
> - Abhishek Bansal (Enrolment No.: 2501030123)
> - Divyansh Agarwal (Enrolment No.: 2501030124)
> - Arjun Bhardwaj (Enrolment No.: 2501030134)

---

## 1. Project Overview

**CIVIC-SENTINEL (Java Edition)** is an enterprise-grade automated democratic accountability, citizen grievance prioritization, and regional socio-economic welfare evaluation engine written entirely in **pure Java** (Standard JDK 8+).

This project unifies three core systems:
1. **Citizen Field Portal**: Live prefix trie tag autocomplete, $O(1)$ inverted index near-duplicate complaint detection, and $O(1)$ Anti-Sybil vote deduplication.
2. **Core Dispatch & Politician Evaluation Engine**: Dynamic priority queue (Binary Max-Heap) grievance scheduling, deterministic Finite State Machine (FSM) lifecycle transitions, and Red-Black Balanced BST (`java.util.TreeMap`) politician accountability audits.
3. **Economic & Welfare Engine (Pillar 2)**: Multidimensional Poverty Index (MPI) profiling, Binary Indexed Tree (Fenwick Tree) food grain reserve accounting, Skill Taxonomy Trie labor absorption, and 0/1 Knapsack Dynamic Programming for direct benefit transfers (DBT).

---

## 2. Directory Structure

```
Civic-Sentinel-Java/
├── build.bat                      # One-click Windows build and package script (javac & jar)
├── run.bat                        # Interactive Master System Control Dashboard
├── run_demo.bat                   # Automated End-to-End Viva Verification
├── run_bridge.bat                 # Unified Inter-Portal Live Demo
├── run_economic.bat               # 0/1 Knapsack & Fenwick Tree Demonstration
├── run_admin.bat                  # Field Portal & Admin Intelligence CLI
├── start_portal.bat               # Interactive Web Dashboard launcher
├── README.md                      # Primary project documentation for Java Lab
├── PROJECT_NOTES_AND_PROGRESS.md  # Learning log & Java concepts viva guide
├── bin/                           # Compiled .class bytecode (generated upon build)
├── docs/                          # Detailed architecture and theoretical proofs
│   ├── ARCHITECTURE.md            # System architecture and data flow diagrams
│   ├── DATA_STRUCTURES_COMPLEXITY.md # Theoretical bounds and Big-O matrix
│   └── ECONOMIC_THEORY_ISPP_INTECHOPEN.md # Policy models (ISPP & Collins Ayoo)
├── web/                           # Front-end HTML5 portal and visualizations
│   ├── index.html                 # Interactive system portal UI
│   ├── dfa.html                   # Interactive Finite State Machine diagram
│   └── tags_and_keywords.html     # Semantic dictionary & Trie visualization
└── src/
    └── civicsentinel/             # Primary Java package
        ├── RecordType.java        # Enum: COMPLAINT, COMPLIMENT, SUGGESTION
        ├── CivicCategory.java     # Enum: Municipal problem sectors
        ├── SeverityLevel.java     # Enum: LOW, MEDIUM, HIGH, CRITICAL
        ├── LifecycleState.java    # Enum: OPEN, IN_PROGRESS, RESOLVED, VERIFIED
        ├── EconomicSector.java    # Enum: Macroeconomic crisis sectors
        ├── BaseRecord.java        # OOP Abstraction: Abstract base class
        ├── GrievanceRecord.java   # OOP Inheritance & Polymorphism: Citizen grievance
        ├── SuggestionRecord.java  # OOP Inheritance: Policy proposal
        ├── ComplimentRecord.java  # OOP Inheritance: Municipal commendation
        ├── CitizenProfile.java    # Socio-economic MPI profiling
        ├── EconomicGrievance.java # Dynamic aging factor & heap priority node
        ├── TagTrie.java           # Prefix Tree (Trie) for civic tags
        ├── SkillTaxonomyTrie.java # Prefix Tree (Trie) for labor absorption
        ├── WardCommodityBIT.java  # Binary Indexed Tree (Fenwick) for PDS tracking
        ├── DuplicateDetector.java # Inverted Keyword Index (HashMap)
        ├── AntiSybilVault.java    # Single-vote integrity hash table (HashSet)
        ├── PriorityScheduler.java # Binary Max-Heap (PriorityQueue + Comparator)
        ├── LifecycleFSM.java      # Deterministic graph-state transition validator
        ├── MonthlyTelemetry.java  # Monthly audit metric record
        ├── TelemetryEngine.java   # Red-Black BST (TreeMap) politician scoring
        ├── MonthlyMacroTelemetry.java # Regional macroeconomic snapshot
        ├── MacroTelemetryEngine.java # Red-Black BST (TreeMap) chronological audits
        ├── KnapsackStimulusSolver.java # 0/1 Knapsack DP solver for targeted DBT
        ├── CivicSentinelSystem.java # Core system controller facade
        ├── MasterEconomicEngine.java # Pillar 2 economic engine coordinator
        ├── UdaanUnifiedBridge.java # Bi-directional inter-portal bridge
        ├── Main.java              # Master interactive CLI simulation driver
        └── AdminPortalMain.java   # 11-Option Admin Portal CLI console
```

---

## 3. Four Pillars of OOP in Java

| OOP Pillar | Java Implementation | Purpose |
| :--- | :--- | :--- |
| **Abstraction** | `abstract class BaseRecord` | Defines interface contract (`calculatePriorityScore()`, `displaySummary()`) without exposing concrete calculation details. |
| **Encapsulation** | `private` / `protected` fields with public getters & mutators | Protects ticket state, budgets, and vote tallies from illegal direct manipulation. |
| **Inheritance** | `GrievanceRecord`, `SuggestionRecord`, `ComplimentRecord extends BaseRecord` | Reuses core metadata (`id`, `category`, `wardId`, `citizenId`, `timestamp`) across specialized record models. |
| **Polymorphism** | Dynamic method dispatch (`calculatePriorityScore()`, `displaySummary()`) | Allows `PriorityScheduler` to seamlessly hold any `BaseRecord` subtype in a unified `PriorityQueue<BaseRecord>`. |

---

## 4. Data Structures & Java Collections Mapping

| Data Structure | Java Implementation | Complexity | Application |
| :--- | :--- | :--- | :--- |
| **Binary Max-Heap** | `java.util.PriorityQueue` + custom `Comparator` | Push/Pop: $O(\log N)$, Peek: $O(1)$ | Starvation-free priority dispatch scheduler. |
| **Balanced Search Tree** | `java.util.TreeMap` (Red-Black BST) | Insert/Search: $O(\log M)$, Range: $O(\log M + K)$ | Monthly telemetry chronological audits via `subMap()`. |
| **Hash Tables / Sets** | `java.util.HashMap` & `java.util.HashSet` | Average: $O(1)$ | Anti-Sybil vote deduplication & Master registry. |
| **Prefix Tree (Trie)** | Custom `TagTrie` & `SkillTaxonomyTrie` | Insert/Search: $O(L)$ | Instant tag autocomplete and vocational skill labor matching. |
| **Binary Indexed Tree** | Custom `WardCommodityBIT` (Fenwick) | Point Update: $O(\log W)$, Range Query: $O(\log W)$ | Real-time grain reserves and food buffer accounting across 20 wards. |
| **Inverted Index** | `Map<String, List<Integer>>` | Lookup: $O(1)$ | Near-duplicate complaint detection in same ward. |
| **Dynamic Programming** | 2D Tabulation in `KnapsackStimulusSolver` | Time/Space: $O(N \cdot W)$ | Optimal direct benefit transfer disbursement under constrained budget. |

---

## 5. Compilation & Execution

### Option A: Windows One-Click (Recommended)
Double-click `build.bat` or run in Command Prompt / PowerShell:
```cmd
build.bat
```
This compiles all 28 classes into `bin/` and runs the unified inter-portal demonstration.

### Option B: Interactive Dashboard
```cmd
run.bat
```
Launches the Master System Control Dashboard with full interactive menu.

### Option C: Manual Compilation with Standard `javac`
```cmd
# 1. Compile all Java source files
javac -d bin src/civicsentinel/*.java

# 2. Run Master CLI
java -cp bin civicsentinel.Main

# 3. Or Run with CLI Arguments
java -cp bin civicsentinel.Main --bridge    # Run Unified Live Bridge Demo
java -cp bin civicsentinel.Main --demo      # Run Automated Viva Verification
java -cp bin civicsentinel.Main --economic  # Run 0/1 Knapsack & BIT Demo

# 4. Or Run Admin Field Portal
java -cp bin civicsentinel.AdminPortalMain
```

### Option D: IDE Setup (Eclipse / IntelliJ IDEA / VS Code)
1. Open the `Civic-Sentinel-Java` folder in your IDE.
2. Mark `src` as the Source Root.
3. Run `civicsentinel.Main` as the main application class. No external libraries are needed.

---

## 6. Key Simulation Workflow

1. **Prefix Trie Autocomplete**: As citizens type a grievance tag (e.g. `"wat"`), the Trie returns `["water-leak", "water-contamination"]` in $O(L)$ time.
2. **Inverted Index Duplicate Check**: Similar issues in the same ward are caught before ticket generation, prompting upvotes instead.
3. **Anti-Sybil Single-Vote Hash Table**: Prevents bot-farming and vote-stuffing by storing `CITIZEN_ID::RECORD_ID` hash tokens.
4. **Max-Heap Scheduling**: Multi-factor priority weighting bubbles up the critical issues to the root.
5. **Deterministic FSM Lifecycle**: Ensures tickets can only transition:
   $$\text{OPEN} \xrightarrow{\text{claim with budget}} \text{IN\_PROGRESS} \xrightarrow{\text{resolve with proof}} \text{RESOLVED} \xrightarrow{\text{citizen compliment}} \text{VERIFIED}$$
6. **Red-Black BST Telemetry**: Evaluates politicians over chosen time ranges using:
   $$\text{Rating} = 0.35 \times \text{Resolution} + 0.35 \times \text{PovertyAlleviation} + 0.30 \times \text{PublicSatisfaction}$$
7. **0/1 Knapsack Stimulus & Fenwick Tree**: Allocates emergency cash transfers to maximize social utility and manages grain reserves.

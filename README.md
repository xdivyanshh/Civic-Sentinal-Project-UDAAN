# CIVIC-SENTINEL: Economic & Welfare Engine (Project Udaan)

> **Course**: Data Structures Lab (15B17CI371) — 2nd Year, 3rd Semester  
> **Institution**: Jaypee Institute of Information Technology (JIIT), Noida  
> **Department**: Computer Science & Engineering and Information Technology  
> **Course Faculty**: Dr. Lalita Mishra  
> **Authors**:
> - Abhishek Bansal (Enrolment No.: 2501030123)
> - Divyansh Agarwal (Enrolment No.: 2501030124)
> - Arjun Bhardwaj (Enrolment No.: 2501030134)

---

## 1. Project Overview

**CIVIC-SENTINEL** is an automated democratic accountability, citizen grievance prioritization, and regional socio-economic growth evaluation engine.

This repository implements the complete **Economic & Welfare Engine (Pillar 2)** of the project. It handles citizen socio-economic profiling, multidimensional poverty calculation, anti-Sybil economic grievance prioritization, labor absorption through skill matching, emergency food security buffer tracking, and targeted direct benefit transfers (DBT).

---

## 2. Directory Structure

```
dsa lab - project udaan/
├── CMakeLists.txt                 # CMake configuration (C++17)
├── Makefile                       # Unix / MinGW Makefile
├── build.bat                      # Windows one-click build and run script
├── README.md                      # Primary project documentation
├── include/                       # Modular C++ header definitions
│   ├── Citizen.hpp                # CitizenProfile model & MPI calculation
│   ├── EconomicGrievance.hpp      # Sectoral grievances & Starvation-Free Max-Heap
│   ├── SkillTaxonomyTrie.hpp      # Prefix Tree (Trie) for vocational skills
│   ├── WardCommodityBIT.hpp       # Binary Indexed Tree (Fenwick) for PDS tracking
│   ├── KnapsackStimulus.hpp       # 0/1 Knapsack DP solver for targeted DBT
│   ├── MacroTelemetry.hpp         # Red-Black BST (std::map) for monthly audits
│   └── EconomicEngine.hpp         # Master coordinator connecting all components
├── src/
│   └── main.cpp                   # Comprehensive interactive simulation driver
└── docs/                          # Detailed engineering documentation
    ├── ARCHITECTURE.md            # System architecture and data flow diagrams
    ├── DATA_STRUCTURES_COMPLEXITY.md # Theoretical bounds and Big-O matrix
    └── ECONOMIC_THEORY_ISPP_INTECHOPEN.md # Policy models (ISPP & Collins Ayoo)
```

---

## 3. Data Structures Employed

| Data Structure | Implementation | Purpose |
| :--- | :--- | :--- |
| **B+ Tree Indexing** | Simulated In-Memory / SQLite3 B-Tree | Demographic range queries across income and ward brackets ($O(\log_B N + K)$). |
| **Binary Max-Heap** | `std::priority_queue` | Prioritizing economic grievances by vulnerability, votes, and starvation aging ($O(\log K)$). |
| **Balanced Search Tree** | `std::multimap` / `std::map` (Red-Black BST) | Real-time ordering by MPI ($O(\log N)$) and chronological monthly audit telemetry ($O(\log M)$). |
| **Prefix Tree (Trie)** | Custom `TrieNode` | Instant $O(L)$ keyword and prefix matching of candidate skills for public works drives. |
| **Binary Indexed Tree** | Fenwick Tree (`WardCommodityBIT`) | Real-time ward grain stock updates and range queries ($O(\log W)$). |
| **Dynamic Programming** | 0/1 Knapsack Table | Maximizing social utility for targeted cash transfers under budget ceiling $B$ ($O(N \cdot B)$). |
| **Hash Tables / Sets** | `std::unordered_map` / `std::unordered_set` | $O(1)$ citizen profile retrieval and anti-Sybil single-vote deduplication. |

---

## 4. Compilation & Execution

### Option A: Windows One-Click (Recommended)
Double-click `build.bat` or run in Command Prompt / PowerShell:
```cmd
build.bat
```

### Option B: Direct Compilation with MinGW / GCC (C++17)
```cmd
"C:\Program Files (x86)\CodeBlocks\MinGW\bin\g++.exe" -std=c++17 -Wall -Wextra -O2 -Iinclude src/main.cpp -o economic_engine.exe
economic_engine.exe
```

### Option C: Using CMake
```bash
mkdir build && cd build
cmake ..
cmake --build .
./economic_engine
```

### Option D: Using Make (Linux / macOS / MSYS2)
```bash
make
make run
```

---

## 5. Key Simulation Workflow Demonstrated in `main.cpp`

1. **Citizen Ingestion**: Registers citizens with multidimensional indicators (income, dependents, usurious debt, chronic health burdens, and vocational skill sets).
2. **Demographic Range Scan**: Queries citizens in the bracket $[0, 6000\text{ INR}]$ using simulated B+ Tree leaf traversal.
3. **Anti-Sybil Deduplication**: Validates incoming grievance votes using bitwise composite tokens `(citizen_id ^ (issue_id << 32))`, rejecting malicious duplicates.
4. **Starvation-Free Prioritization**: Demonstrates how aging factor $(current\_tick - timestamp) \cdot 0.20$ guarantees older issues bubble up to the heap root.
5. **Autonomous Policy Triggers**:
   * Critical food insecurity in Ward 3 triggers an emergency 15,000 kg grain buffer allocation via the Fenwick Tree.
   * Severe unemployment in Ward 4 triggers a public works construction drive, using the Skill Trie to match and hire destitute qualified masons.
   * Debt usury crisis in Ward 2 triggers zero-interest micro-credit and targeted DBT grants.
6. **0/1 Knapsack DBT Stimulus**: Maximizes social utility under a finite municipal cash relief budget.
7. **Macroeconomic Audit Feedback**: Calculates the concrete $\text{PovertyReductionDelta}$ ($66.67\%$) and passes it into Chapter 3's administrative accountability scoring equation.

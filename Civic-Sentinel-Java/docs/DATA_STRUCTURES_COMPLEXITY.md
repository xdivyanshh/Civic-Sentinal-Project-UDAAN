# Data Structures & Asymptotic Complexity Analysis

This document details the data structures, algorithms, and asymptotic theoretical bounds implemented across the **CIVIC-SENTINEL Economic Engine**.

---

## 1. Master Complexity Matrix

| Functional Module | Data Structure / Implementation | Algorithmic Operation | Time Complexity (Best/Avg) | Time Complexity (Worst) | Space Complexity |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Citizen Demographic Registry** | `std::unordered_map<uint64_t, CitizenProfile>` (Hash Table) | Citizen profile lookup, registration, and field mutation | $O(1)$ | $O(N)$ (hash collision) | $O(N)$ profiles |
| **Demographic Range Scanner** | **B+ Tree Indexing** (Disk/RAM Leaf Chain) | Income bracket and demographic cohort queries | $O(\log_B N + K)$ | $O(\log_B N + K)$ | $O(N)$ tree nodes |
| **Poverty Escalation Ranker** | `std::multimap<double, uint64_t>` (Red-Black BST) | Real-time ordering of population by MPI | $O(\log N)$ insert/delete, $O(1)$ max peek | $O(\log N)$ | $O(N)$ tree nodes |
| **Sectoral Grievance Queues** | `std::priority_queue` (Binary Max-Heap) | Dynamic priority scheduling by urgency and aging | $O(\log K)$ push/pop, $O(1)$ root inspect | $O(\log K)$ | $O(K)$ active issues |
| **Anti-Sybil Deduplication** | `std::unordered_set<uint64_t>` (Hash Set) | Enforcing single-vote integrity per issue | $O(1)$ | $O(V)$ | $O(V)$ unique votes |
| **Vocational Skill Taxonomy** | **Trie (Prefix Tree)** | Keyword and prefix matching of candidate skills | $O(L)$ where $L$ = strlen | $O(L)$ | $O(\Sigma \cdot L \cdot S)$ nodes |
| **Labor Selection Allocator** | Candidate `std::priority_queue` (Max-Heap) | Extracting top qualified and destitute workers | $O(C \log C)$ heapify/extraction | $O(C \log C)$ | $O(C)$ candidates |
| **PDS Commodity Telemetry** | **Binary Indexed Tree (Fenwick Tree)** | Ward grain stock addition and regional range sums | $O(\log W)$ point update & prefix sum | $O(\log W)$ | $O(W)$ array |
| **Targeted Relief Stimulus** | **0/1 Knapsack Dynamic Programming** | Maximizing social utility under budget ceiling $B$ | $O(N \cdot B)$ | $O(N \cdot B)$ | $O(N \cdot B)$ or $O(B)$ |
| **Monthly Audit Telemetry** | `std::map<uint32_t, MonthlyMacroTelemetry>` (Red-Black BST) | Chronological range lookups and poverty deltas | $O(\log M)$ query & insert | $O(\log M)$ | $O(M)$ monthly logs |

*Notation: $N$ = total citizens, $B$ = B+ tree branching factor / Knapsack budget, $K$ = active grievances, $V$ = recorded votes, $L$ = skill string length, $C$ = candidate pool size, $W$ = municipal wards, $M$ = monthly audit cycles.*

---

## 2. In-Depth Algorithmic Rationale

### A. Binary Max-Heap with Dynamic Aging Factor
* **The Challenge**: Standard queues allow urgent issues to be starved if new emergencies arrive continuously.
* **The Solution**: The comparator evaluates `priority_score(current_tick)`. The aging factor $(current\_tick - timestamp) \cdot 0.20$ guarantees that an issue's score strictly increases over time, mathematically bounding the maximum latency before any unresolved issue reaches the root.

### B. B+ Tree for Demographic Range Inquiries
* **The Challenge**: Finding citizens within an income interval $[I_{min}, I_{max}]$ across a specific ward requires scanning an entire table in $O(N)$ time if unindexed.
* **The Solution**: A B+ Tree stores all data in leaf nodes linked via a doubly-linked list. The engine descends the tree in $O(\log_B N)$ steps to locate $I_{min}$, then sequentially iterates along the leaves in $O(K)$ steps to collect all qualifying records.

### C. Prefix Tree (Trie) for Vocational Trades
* **The Challenge**: String searching through thousands of citizen skill arrays causes severe performance degradation ($O(N \cdot S \cdot L)$).
* **The Solution**: Organizing skills into a Trie reduces candidate identification to $O(L)$ time, completely decoupling matching speed from total population size.

### D. Binary Indexed Tree (Fenwick Tree) for Ward Food Balances
* **The Challenge**: Calculating total foodgrain reserves across a contiguous block of wards (e.g., Wards 5 through 15) requires $O(W)$ addition per query, which is too slow for real-time sensor streams and automated supply chains.
* **The Solution**: A Fenwick Tree maintains prefix sums using bitwise least significant bit operations (`ward += ward & -ward`), executing both stock modifications and range queries in $O(\log W)$ time.

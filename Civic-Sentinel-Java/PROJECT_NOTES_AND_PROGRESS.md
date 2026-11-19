# CIVIC-SENTINEL: Java Lab Learning Log & Viva Preparation Guide

**Project:** Civic-Sentinel (PBL / Java Programming & Data Structures Lab)  
**Developers:** Abhishek Bansal, Divyansh Agarwal, Arjun Bhardwaj  
**Faculty Guide:** Dr. Lalita Mishra  
**Course Code:** 15B17CI371 (Data Structures / Java Lab) — 2nd Year, 3rd Semester  

---

## 🗺️ System Architecture & Java Component Tracker

| Component | Java Class | Key Concept Covered | Complexity |
| :--- | :--- | :--- | :---: |
| **Intake Vocabulary** | `RecordType`, `CivicCategory`, `SeverityLevel`, `LifecycleState` | Strongly-Typed Java Enums, encapsulation with display fields. | $O(1)$ |
| **Abstract Base Record** | `BaseRecord.java` | **OOP Abstraction**: `abstract class`, protected attributes, pure abstract methods. | — |
| **Polymorphic Records** | `GrievanceRecord`, `SuggestionRecord`, `ComplimentRecord` | **OOP Inheritance & Polymorphism**: Method overriding (`@Override`), dynamic dispatch. | $O(1)$ |
| **Max-Heap Priority Scheduler** | `PriorityScheduler.java` | `java.util.PriorityQueue<BaseRecord>` + custom `Comparator<BaseRecord>`. | $O(\log N)$ |
| **Anti-Sybil Single-Vote Vault** | `AntiSybilVault.java` | `java.util.HashSet<String>` composite key deduplication. | $O(1)$ avg |
| **Deterministic Lifecycle FSM** | `LifecycleFSM.java` | Directed graph lifecycle state machine with validation rules. | $O(1)$ |
| **Politician Evaluation Engine** | `TelemetryEngine.java` | `java.util.TreeMap` (Red-Black BST), range queries via `subMap()`. | $O(\log M + K)$ |
| **Prefix Tag Trie** | `TagTrie.java` | Custom Prefix Tree, DFS autocomplete traversal. | $O(L + K)$ |
| **Inverted Keyword Index** | `DuplicateDetector.java` | `Map<String, List<Integer>>` tokenized duplicate detection. | $O(1)$ lookup |
| **Labor Absorption Trie** | `SkillTaxonomyTrie.java` | Vocational prefix tree matching unemployed candidates to projects. | $O(L)$ |
| **PDS Commodity Tracker** | `WardCommodityBIT.java` | Binary Indexed Tree (Fenwick Tree) with bitwise 1-indexed arithmetic. | $O(\log W)$ |
| **Targeted DBT Relief** | `KnapsackStimulusSolver.java` | 0/1 Knapsack Dynamic Programming 2D grid tabulation and backtracking. | $O(N \cdot W)$ |
| **Unified Bridge** | `UdaanUnifiedBridge.java` | Bi-directional facade connecting Field Portal and Master Economic Engine. | — |

---

## 💡 Top 10 Java Lab Viva Questions & Answers

### Q1: Why did we use `package civicsentinel;` instead of placing everything in the default package?
* **Concept:** Java Namespace & Modular Organization.
* **Explanation:**
  * Placing classes in a named package prevents naming collisions when integrating with external libraries or frameworks.
  * Classes within the same package have **package-private** access to each other, promoting encapsulation while avoiding bloated import statements.
  * In enterprise Java, all professional code is packaged under reverse domain names (e.g., `com.civicsentinel`).

---

### Q2: How does Java's `enum` differ from C++ `enum class`?
* **Concept:** Object-Oriented Enumerations.
* **Explanation:**
  * In C++, an `enum class` is simply a scoped type-safe wrapper around integer constants.
  * In Java, an `enum` is a **full-fledged class** that extends `java.lang.Enum`.
  * In `CivicCategory.java` and `SeverityLevel.java`, our enums have private constructor parameters, encapsulated instance fields (like `displayName`, `value`), and custom methods (`fromValue()`, `fromOrdinal()`).

---

### Q3: Why is `BaseRecord` an `abstract class` rather than an `interface`?
* **Concept:** Abstract Class vs. Interface in Java.
* **Explanation:**
  * An **interface** defines a contract without holding instance state (before Java 8, no method bodies; in Java 8+, default methods but no instance fields).
  * An **abstract class** can define **shared state variables** (`id`, `category`, `wardId`, `citizenId`, `timestamp`) and constructor initialization logic that all children inherit directly (`super(...)`).
  * `BaseRecord` enforces the contract for `calculatePriorityScore()` and `displaySummary()` while reusing shared state, making an abstract class the correct design choice.

---

### Q4: How is Polymorphism demonstrated during runtime execution?
* **Concept:** Dynamic Method Dispatch (Runtime Polymorphism).
* **Explanation:**
  * The `PriorityScheduler` holds a `PriorityQueue<BaseRecord>`.
  * When the priority comparator invokes `record.calculatePriorityScore()`, Java examines the **actual runtime object type** (whether `GrievanceRecord` or `SuggestionRecord`) and executes the specific overridden subclass formula:
    * For a grievance: `Severity * 3.5 + Upvotes * 0.50 + 1.5`
    * For a suggestion: `FeasibilityVotes * 0.60 + BeneficiariesWeight * 0.40 + 1.0`
  * The scheduler needs zero `if-else` or `instanceof` checks to calculate the score!

---

### Q5: Why is `java.util.PriorityQueue` a Min-Heap by default, and how did we turn it into a Max-Heap?
* **Concept:** Heap Property & Java Comparators.
* **Explanation:**
  * In Java, `PriorityQueue` orders elements by their natural ordering (`Comparable`) or a custom `Comparator`. By default, the smallest element is at the root (Min-Heap).
  * To create a **Binary Max-Heap**, we supplied a custom comparator:
    ```java
    public static class RecordPriorityComparator implements Comparator<BaseRecord> {
        @Override
        public int compare(BaseRecord a, BaseRecord b) {
            // Descending order: b compared to a
            return Double.compare(b.calculatePriorityScore(), a.calculatePriorityScore());
        }
    }
    ```
  * Returning a positive integer when `b.score > a.score` causes higher-scored records to rise to the root ($O(1)$ peek).

---

### Q6: Why did we choose `java.util.TreeMap` for `TelemetryEngine` and what data structure backs it?
* **Concept:** Balanced Search Tree (Red-Black Tree).
* **Explanation:**
  * A `HashMap` provides $O(1)$ average access but is completely unordered; finding records between `"2026-07"` and `"2026-10"` would require an $O(M)$ full table scan.
  * `java.util.TreeMap` is backed by a self-balancing **Red-Black Tree**.
  * It maintains elements in sorted order of keys with guaranteed $O(\log M)$ time for insertion, deletion, and lookup.
  * It provides the `subMap(fromKey, true, toKey, true)` method, which performs **range queries** in $O(\log M + K)$ time where $K$ is the number of months in the window.

---

### Q7: How does `AntiSybilVault` prevent duplicate voting in $O(1)$ time?
* **Concept:** Hash Table Deduplication.
* **Explanation:**
  * For every vote cast, a composite key is generated: `citizenId + "::" + recordId`.
  * The key is checked against a `HashSet<String>`.
  * `HashSet.contains()` computes the string's hash code and checks the bucket array in $O(1)$ average time.
  * If found, the vote is immediately rejected. If not found, it is inserted in $O(1)$ and the record's upvote count is incremented.

---

### Q8: What is a Binary Indexed Tree (Fenwick Tree) and why is it better than a prefix-sum array for ward food grain reserves?
* **Concept:** Fenwick Tree (`WardCommodityBIT`).
* **Explanation:**
  * A simple array takes $O(1)$ for updates, but $O(W)$ for range sum queries.
  * A prefix-sum array takes $O(1)$ for range queries, but $O(W)$ for every point update.
  * A **Fenwick Tree** uses bitwise least significant bits (`x & -x`) to balance both operations:
    * **Point Update (`addStock`)**: $O(\log W)$
    * **Range Query (`rangeStock`)**: $O(\log W)$
  * In a high-frequency grain rationing network with 20+ wards, this ensures real-time stockout tracking without locking the system.

---

### Q9: How does the 0/1 Knapsack Dynamic Programming solver optimize welfare relief?
* **Concept:** Constrained Optimization via Tabulation.
* **Explanation:**
  * **Objective:** Select a subset of vulnerable households to maximize overall community survival utility subject to:
    $$\sum \text{Grant}_i \le \text{Relief Budget } B$$
  * We construct a 2D table `dp[N+1][W+1]` where `N` is eligible households and `W` is budget in discrete units.
  * Recurrence relation:
    $$\text{dp}[i][w] = \max(\text{dp}[i-1][w], \text{dp}[i-1][w - \text{weight}_{i-1}] + \text{value}_{i-1})$$
  * After filling the table in $O(N \cdot W)$ time, we backtrack from `dp[N][W]` to identify the exact citizens receiving relief.

---

### Q10: How does the deterministic Finite State Machine (FSM) protect against administrative fraud?
* **Concept:** State Transition Invariants.
* **Explanation:**
  * Valid lifecycle edges:
    $$\text{OPEN} \longrightarrow \text{IN\_PROGRESS} \longrightarrow \text{RESOLVED} \longrightarrow \text{VERIFIED}$$
  * `LifecycleFSM.java` rejects any illegal edge:
    * A ticket cannot transition to `RESOLVED` directly from `OPEN` (skipping the contractor assignment and budget allocation).
    * A ticket cannot transition to `IN_PROGRESS` with zero or negative budget.
    * A ticket cannot transition to `VERIFIED` until municipal workers mark it `RESOLVED` and verified citizens endorse it with compliments.

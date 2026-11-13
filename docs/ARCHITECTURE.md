# CIVIC-SENTINEL: Economic & Welfare Engine Architecture

## 1. System Vision & Paradigm
The **Economic Engine** of CIVIC-SENTINEL serves as the computational backbone that models, monitors, and optimizes citizen socio-economic vitality. It operates independently of the political/administrative evaluation layer, serving as the high-throughput data and algorithmic core that:
1. Ingests and maintains multidimensional citizen demographic and economic metrics.
2. Bubbles citizen crises up to municipal administration via sector-specific priority queues.
3. Automatically triggers targeted monetary, fiscal, and labor-absorption policies.
4. Supplies verified, mathematically proven poverty reduction deltas ($\Delta \text{BPL}$) to evaluate administration performance.

---

## 2. High-Level Data Flow

```
+-------------------------------------------------------------------------+
|                      CITIZEN SOCIO-ECONOMIC INGESTION                   |
+-------------------------------------------------------------------------+
                                     |
           +-------------------------+-------------------------+
           v                                                   v
+-----------------------+                           +---------------------+
| In-Memory Hash Table  |                           | Multidimensional    |
| (O(1) Profile Access) |                           | Poverty Index (MPI) |
+-----------------------+                           +---------------------+
           |                                                   |
           v                                                   v
+-----------------------+                           +---------------------+
| B+ Tree Range Index   |                           | Red-Black BST       |
| (Demographic Scans)   |                           | (Sorted Vulnerable) |
+-----------------------+                           +---------------------+
                                     |
                                     v
+-------------------------------------------------------------------------+
|                  CITIZEN ECONOMIC GRIEVANCES & VOTING                   |
|     (Anti-Sybil Deduplication via Hash Set: citizen_id ^ (issue << 32))  |
+-------------------------------------------------------------------------+
                                     |
        +----------------------------+----------------------------+
        |                            |                            |
        v                            v                            v
+--------------------+      +--------------------+      +--------------------+
| Unemployment Heap  |      | PDS Food Heap      |      | Debt Usury Heap    |
| (Binary Max-Heap)  |      | (Binary Max-Heap)  |      | (Binary Max-Heap)  |
+--------------------+      +--------------------+      +--------------------+
        |                            |                            |
        +----------------------------+----------------------------+
                                     |
                                     v
+-------------------------------------------------------------------------+
|                  FRONT-OF-QUEUE AUTONOMOUS POLICY ENGINE                |
|                 (Root Evaluation vs. Critical Threshold)                |
+-------------------------------------------------------------------------+
                                     |
        +----------------------------+----------------------------+
        |                            |                            |
        v                            v                            v
+--------------------+      +--------------------+      +--------------------+
| Labor Absorption   |      | Emergency Buffer   |      | Targeted DBT Relief|
| (Trie Skill Match  |      | Influx via Fenwick |      | (0/1 Knapsack DP   |
| + Candidate Heap)  |      | Tree (O(log W))    |      | Budget Optimizer)  |
+--------------------+      +--------------------+      +--------------------+
                                     |
                                     v
+-------------------------------------------------------------------------+
|             MONTHLY MACROECONOMIC AUDIT TELEMETRY (RED-BLACK BST)       |
|   Computes: Δ BPL Households, Δ Average Income, Δ Unemployment Rate      |
|   Feeds: Administrative Rating = 0.35 * Grievance + 0.35 * ΔPoverty ...  |
+-------------------------------------------------------------------------+
```

---

## 3. Component Breakdown

### A. Citizen & Vulnerability Registry (`Citizen.hpp`)
* **Container**: `std::unordered_map<uint64_t, CitizenProfile>`
* **Role**: Primary key-value registry of citizen demographics.
* **Secondary Index**: `std::multimap<double, uint64_t, std::greater<double>>` (Red-Black BST) providing continuous, real-time ordering by vulnerability.

### B. Sectoral Grievance Scheduling (`EconomicGrievance.hpp`)
* **Container**: Four `std::priority_queue<EconomicGrievance, ..., GrievanceComparator>` instances.
* **Priority Formulation**:
  $$\text{Priority} = (0.45 \cdot \text{AggregatedMPI}) + (0.35 \cdot \text{Upvotes}) + (0.20 \cdot (\text{CurrentTick} - \text{Timestamp}))$$
* **Aging Invariant**: Prevents queue starvation, guaranteeing older issues bubble to the root over time.

### C. Vocational Skill Taxonomy (`SkillTaxonomyTrie.hpp`)
* **Container**: Prefix Tree (Trie).
* **Role**: Instant $O(L)$ retrieval of citizens qualified in specific trades (e.g., masonry, plumbing, electrical).
* **Labor Matching**: Feeds matched candidates into a candidate max-heap combining poverty score and spatial proximity.

### D. Food Security Telemetry (`WardCommodityBIT.hpp`)
* **Container**: Binary Indexed Tree (Fenwick Tree).
* **Role**: Real-time tracking of fair-price shop (PDS) food stocks across municipal wards.
* **Capabilities**: $O(\log W)$ point additions and $O(\log W)$ prefix/range queries.

### E. Emergency Stimulus Optimizer (`KnapsackStimulus.hpp`)
* **Technique**: 0/1 Knapsack Dynamic Programming.
* **Role**: When treasury releases relief budget $B$, selects the subset of impoverished households that yields maximum social welfare utility.

### F. Macroeconomic Audit Telemetry (`MacroTelemetry.hpp`)
* **Container**: `std::map<uint32_t, MonthlyMacroTelemetry>` (Red-Black BST).
* **Role**: Maintains immutable chronological snapshots of economic health to calculate $\Delta \text{BPL}$ across governance cycles.

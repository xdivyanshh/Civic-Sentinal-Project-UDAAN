package civicsentinel;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.TreeMap;

/**
 * Master Economic & Welfare Engine for CIVIC-SENTINEL.
 * 
 * Orchestrates:
 * 1. Citizen Demographic Ingestion & MPI Calculation
 * 2. In-Memory Range Queries (Simulating B+ Tree Leaf Scans)
 * 3. Anti-Sybil Vote Deduplication
 * 4. Sectoral Grievance Priority Heaps (Unemployment, PDS, Debt, Inflation)
 * 5. Autonomous Root-to-Policy Triggers (Public Works, Grain Influx, Microcredit)
 * 6. Trie-driven Labor Absorption & Spatial Candidate Placement
 * 7. 0/1 Knapsack Dynamic Programming for Targeted DBT Relief
 * 8. Fenwick Tree for Real-Time Ward Food Supply Accounting
 * 9. Chronological Macro Telemetry Logging in a Red-Black BST
 */
public class MasterEconomicEngine {
    private long internalClockTicks = 1000L;
    private final int totalWards;

    // 1. Data Registries
    private final Map<Long, CitizenProfile> citizenRegistry;
    // Multimap: MPI score (descending) -> list of Citizen IDs
    private final TreeMap<Double, List<Long>> mpiVulnerabilityTree;
    private final Set<Long> antiSybilVotes; // (citizen_id ^ (issue_id << 32))
    private final SkillTaxonomyTrie skillTrie;
    private final WardCommodityBIT pdsRationStock;
    private final MacroTelemetryEngine telemetryEngine;

    // Cumulative stats
    private int totalJobsPlacedSession = 0;
    private double totalStimulusDisbursedSession = 0.0;
    private double totalPdsDistributedSession = 0.0;

    // 2. Sectoral Priority Queues (Binary Max-Heaps)
    private final PriorityQueue<EconomicGrievance> unemploymentHeap;
    private final PriorityQueue<EconomicGrievance> pdsFoodHeap;
    private final PriorityQueue<EconomicGrievance> debtCrisisHeap;
    private final PriorityQueue<EconomicGrievance> inflationHeap;

    public MasterEconomicEngine(int numWards) {
        this.totalWards = numWards;
        this.citizenRegistry = new HashMap<>();
        this.mpiVulnerabilityTree = new TreeMap<>(Collections.reverseOrder());
        this.antiSybilVotes = new HashSet<>();
        this.skillTrie = new SkillTaxonomyTrie();
        this.pdsRationStock = new WardCommodityBIT(numWards);
        this.telemetryEngine = new MacroTelemetryEngine();

        Comparator<EconomicGrievance> comparator = (a, b) ->
                Double.compare(b.priority_score(internalClockTicks), a.priority_score(internalClockTicks));

        this.unemploymentHeap = new PriorityQueue<>(comparator);
        this.pdsFoodHeap = new PriorityQueue<>(comparator);
        this.debtCrisisHeap = new PriorityQueue<>(comparator);
        this.inflationHeap = new PriorityQueue<>(comparator);

        // Seed baseline grain stock across wards (e.g., 20,000 kg each)
        for (int w = 1; w <= totalWards; ++w) {
            pdsRationStock.addStock(w, 20000L);
        }
    }

    public MasterEconomicEngine() {
        this(20);
    }

    public void advanceClock(long ticks) {
        internalClockTicks += ticks;
    }

    public long getClock() {
        return internalClockTicks;
    }

    // ------------------------------------------------------------------------
    // Citizen Demographic Ingestion & Vulnerability Indexing
    // ------------------------------------------------------------------------
    public void registerCitizen(CitizenProfile profile) {
        if (profile == null) return;
        citizenRegistry.put(profile.citizen_id, profile);
        double mpi = profile.compute_mpi();

        mpiVulnerabilityTree.computeIfAbsent(mpi, k -> new ArrayList<>()).add(profile.citizen_id);

        for (String skill : profile.skills) {
            skillTrie.insertSkill(skill, profile.citizen_id);
        }
    }

    public CitizenProfile getCitizen(long citizenId) {
        return citizenRegistry.get(citizenId);
    }

    public int getCitizenCount() {
        return citizenRegistry.size();
    }

    // ------------------------------------------------------------------------
    // Demographic Range Query (Simulating B+ Tree Leaves over Incomes)
    // Complexity: O(log_B N + K) in B+ Tree storage
    // ------------------------------------------------------------------------
    public List<Long> queryCitizensByIncomeRange(double minIncome, double maxIncome, int targetWard) {
        List<Long> matchedIds = new ArrayList<>();
        for (Map.Entry<Long, CitizenProfile> kv : citizenRegistry.entrySet()) {
            long id = kv.getKey();
            CitizenProfile citizen = kv.getValue();
            if (citizen.monthly_income >= minIncome && citizen.monthly_income <= maxIncome) {
                if (targetWard == -1 || citizen.ward_id == targetWard) {
                    matchedIds.add(id);
                }
            }
        }
        return matchedIds;
    }

    public List<Long> queryCitizensByIncomeRange(double minIncome, double maxIncome) {
        return queryCitizensByIncomeRange(minIncome, maxIncome, -1);
    }

    // ------------------------------------------------------------------------
    // Top-K Vulnerability Extractor
    // ------------------------------------------------------------------------
    public List<Long> getTopVulnerableCitizens(int k) {
        List<Long> result = new ArrayList<>();
        int count = 0;
        for (List<Long> ids : mpiVulnerabilityTree.values()) {
            for (Long id : ids) {
                if (count >= k) return result;
                result.add(id);
                count++;
            }
        }
        return result;
    }

    // ------------------------------------------------------------------------
    // Anti-Sybil Grievance Voting & Queue Insertion
    // Complexity: O(1) deduplication, O(log K) heap push
    // ------------------------------------------------------------------------
    public boolean lodgeOrVoteGrievance(long citizenId, int issueId, EconomicSector sector,
                                        int wardId, String description) {
        long voteToken = citizenId ^ (((long) issueId) << 32);
        if (antiSybilVotes.contains(voteToken)) {
            System.out.println("  [ANTI-SYBIL REJECTED] Citizen #" + citizenId
                    + " has already cast a vote for Issue #" + issueId + "!");
            return false;
        }
        antiSybilVotes.add(voteToken);

        double voterMpi = 10.0;
        if (citizenRegistry.containsKey(citizenId)) {
            voterMpi = citizenRegistry.get(citizenId).compute_mpi();
        }

        EconomicGrievance grievance = new EconomicGrievance(
                issueId, sector, wardId, description, 1, voterMpi, internalClockTicks
        );

        switch (sector) {
            case UNEMPLOYMENT_SPIKE:
                unemploymentHeap.offer(grievance);
                break;
            case PDS_FOOD_SECURITY:
                pdsFoodHeap.offer(grievance);
                break;
            case DEBT_USURY_CRISIS:
                debtCrisisHeap.offer(grievance);
                break;
            case MARKET_INFLATION:
                inflationHeap.offer(grievance);
                break;
        }

        System.out.println("  [VOTE LOGGED] Citizen #" + citizenId + " endorsed Issue #" + issueId
                + " in " + sector.getDisplayName() + " (Ward #" + wardId + ")");
        return true;
    }

    // ------------------------------------------------------------------------
    // Labor-Absorbing Public Works Allocation (Trie Search + Max-Heap Ranking)
    // Complexity: O(L) trie lookup + O(C log C) candidate ranking
    // ------------------------------------------------------------------------
    public int allocatePublicWorksJobs(String requiredSkill, int projectWard, int vacancies, double monthlyWage) {
        System.out.println("\n>>> [LABOR ABSORPTION DRIVE ACTIVATED]");
        System.out.printf(Locale.US,
                "  Requisition: %d '%s' positions in Ward #%d | Monthly Wage: Rs.%.2f%n",
                vacancies, requiredSkill, projectWard, monthlyWage);

        List<Long> candidatePool = skillTrie.querySkill(requiredSkill);
        if (candidatePool.isEmpty()) {
            System.out.println("  (!) No registered citizens found with vocational skill: " + requiredSkill);
            return 0;
        }

        // Candidate Max-Heap: Combines Vulnerability (MPI) and Ward Proximity
        class CandidateMatch {
            final long id;
            final double matchScore;

            CandidateMatch(long id, double matchScore) {
                this.id = id;
                this.matchScore = matchScore;
            }
        }

        PriorityQueue<CandidateMatch> candidateHeap = new PriorityQueue<>(
                (a, b) -> Double.compare(b.matchScore, a.matchScore)
        );

        for (long cid : candidatePool) {
            CitizenProfile c = citizenRegistry.get(cid);
            if (c == null || c.employment_status == 2) continue; // Skip steadily employed

            int wardDist = Math.abs(c.ward_id - projectWard);
            double proximityWeight = 1.0 / (wardDist + 1.0);
            double score = (c.compute_mpi() * 0.70) + (proximityWeight * 35.0);
            candidateHeap.offer(new CandidateMatch(cid, score));
        }

        int hired = 0;
        while (!candidateHeap.isEmpty() && hired < vacancies) {
            long chosenId = candidateHeap.poll().id;
            CitizenProfile worker = citizenRegistry.get(chosenId);

            worker.monthly_income += monthlyWage;
            worker.employment_status = 2; // Upgraded to stable employment
            worker.is_bpl = (worker.monthly_income < 8000.0);

            // Re-index updated vulnerability in Red-Black tree
            double newMpi = worker.compute_mpi();
            mpiVulnerabilityTree.computeIfAbsent(newMpi, k -> new ArrayList<>()).add(chosenId);

            System.out.printf(Locale.US,
                    "  -> Placed Citizen #%d (Ward #%d) | New Monthly Income: Rs.%.2f | New MPI: %.2f | BPL Status: %s%n",
                    chosenId, worker.ward_id, worker.monthly_income, newMpi, (worker.is_bpl ? "YES" : "NO"));
            hired++;
            totalJobsPlacedSession++;
        }

        System.out.println("  [OK] Total Qualified Workers Absorbed: " + hired + "/" + vacancies);
        return hired;
    }

    // ------------------------------------------------------------------------
    // Emergency Targeted Direct Benefit Transfer (DBT) via 0/1 Knapsack DP
    // ------------------------------------------------------------------------
    public void executeTargetedDbt(int targetWard, double reliefBudget) {
        System.out.println("\n>>> [TARGETED DIRECT BENEFIT TRANSFER (DBT) STIMULUS]");
        System.out.printf(Locale.US,
                "  Allocating Rs.%.2f across vulnerable households in Ward #%d using 0/1 Knapsack%n",
                reliefBudget, targetWard);

        List<Long> eligibleCandidates = queryCitizensByIncomeRange(0.0, 10000.0, targetWard);
        if (eligibleCandidates.isEmpty()) {
            System.out.println("  No eligible households below threshold in Ward #" + targetWard);
            return;
        }

        KnapsackStimulusSolver.DisbursementResult result =
                KnapsackStimulusSolver.optimizeDbt(eligibleCandidates, citizenRegistry, reliefBudget);

        for (int i = 0; i < result.selectedCitizenIds.size(); ++i) {
            long cid = result.selectedCitizenIds.get(i);
            double grant = result.allocatedAmounts.get(i);

            CitizenProfile citizen = citizenRegistry.get(cid);
            citizen.monthly_income += grant;
            citizen.debt_obligation = Math.max(0.0, citizen.debt_obligation - (grant * 0.60)); // Relief clears usurious debt
            citizen.is_bpl = (citizen.monthly_income < 8000.0);

            double newMpi = citizen.compute_mpi();
            mpiVulnerabilityTree.computeIfAbsent(newMpi, k -> new ArrayList<>()).add(cid);

            System.out.printf(Locale.US,
                    "  -> Grant of Rs.%.2f credited to Citizen #%d | Remaining Debt: Rs.%.2f | New MPI: %.2f%n",
                    grant, cid, citizen.debt_obligation, newMpi);
        }

        totalStimulusDisbursedSession += result.totalDisbursed;
        System.out.printf(Locale.US,
                "  [OK] Knapsack Optimization Complete: Disbursed Rs.%.2f | Social Welfare Utility Max: %d%n",
                result.totalDisbursed, result.totalUtilityGained);
    }

    // ------------------------------------------------------------------------
    // Autonomous Macro Policy Trigger Check at Heap Roots
    // ------------------------------------------------------------------------
    public void evaluateMacroPolicyTriggers(double criticalThreshold) {
        System.out.println("\n===========================================================");
        System.out.printf(Locale.US, "  EVALUATING QUEUE ROOTS (CRITICAL THRESHOLD: %.2f)%n", criticalThreshold);
        System.out.println("===========================================================");

        // 1. Food Security Root Inspection
        if (!pdsFoodHeap.isEmpty()) {
            EconomicGrievance topPds = pdsFoodHeap.peek();
            double score = topPds.priority_score(internalClockTicks);
            System.out.printf(Locale.US,
                    "  [PDS HEAP ROOT] Issue #%d (Ward #%d) Priority: %.2f%n",
                    topPds.issue_id, topPds.ward_id, score);

            if (score >= criticalThreshold) {
                System.out.println("  >>> AUTONOMOUS TRIGGER: Critical Food Insecurity in Ward #" + topPds.ward_id + "!");
                // Fenwick tree point update: Add 15,000 kg buffer grain
                pdsRationStock.addStock(topPds.ward_id, 15000L);
                totalPdsDistributedSession += 15000L;
                System.out.printf(Locale.US,
                        "  [OK] Dispatched 15,000 kg buffer stock. Current Ward #%d Reserve: %d kg%n",
                        topPds.ward_id, pdsRationStock.getWardStock(topPds.ward_id));
                pdsFoodHeap.poll(); // Issue addressed
            }
        }

        // 2. Unemployment Spike Root Inspection
        if (!unemploymentHeap.isEmpty()) {
            EconomicGrievance topUnemp = unemploymentHeap.peek();
            double score = topUnemp.priority_score(internalClockTicks);
            System.out.printf(Locale.US,
                    "  [UNEMPLOYMENT ROOT] Issue #%d (Ward #%d) Priority: %.2f%n",
                    topUnemp.issue_id, topUnemp.ward_id, score);

            if (score >= criticalThreshold) {
                System.out.println("  >>> AUTONOMOUS TRIGGER: Deploying Civic Construction Drive in Ward #" + topUnemp.ward_id + "!");
                allocatePublicWorksJobs("masonry", topUnemp.ward_id, 3, 9500.0);
                unemploymentHeap.poll(); // Issue addressed
            }
        }

        // 3. Debt Usury Root Inspection
        if (!debtCrisisHeap.isEmpty()) {
            EconomicGrievance topDebt = debtCrisisHeap.peek();
            double score = topDebt.priority_score(internalClockTicks);
            System.out.printf(Locale.US,
                    "  [DEBT CRISIS ROOT] Issue #%d (Ward #%d) Priority: %.2f%n",
                    topDebt.issue_id, topDebt.ward_id, score);

            if (score >= criticalThreshold) {
                System.out.println("  >>> AUTONOMOUS TRIGGER: Deploying Zero-Interest Emergency Micro-Credit in Ward #" + topDebt.ward_id + "!");
                executeTargetedDbt(topDebt.ward_id, 8000.0);
                debtCrisisHeap.poll(); // Issue addressed
            }
        }
    }

    // ------------------------------------------------------------------------
    // Ward-Level Commodity Range Query (Fenwick Tree)
    // ------------------------------------------------------------------------
    public long queryRegionalGrainStock(int leftWard, int rightWard) {
        return pdsRationStock.rangeStock(leftWard, rightWard);
    }

    // ------------------------------------------------------------------------
    // Monthly Macroeconomic Audit Recording (Red-Black BST Telemetry)
    // ------------------------------------------------------------------------
    public void recordMonthlyTelemetry(long monthId) {
        int bplCount = 0;
        int unempCount = 0;
        double totalIncome = 0.0;

        for (CitizenProfile c : citizenRegistry.values()) {
            if (c.is_bpl) bplCount++;
            if (c.employment_status == 0) unempCount++;
            totalIncome += c.monthly_income;
        }

        double avgIncome = citizenRegistry.isEmpty() ? 0.0 : (totalIncome / citizenRegistry.size());
        double unempRate = citizenRegistry.isEmpty() ? 0.0 : (((double) unempCount / citizenRegistry.size()) * 100.0);

        MonthlyMacroTelemetry snapshot = new MonthlyMacroTelemetry(
                monthId,
                citizenRegistry.size(),
                bplCount,
                avgIncome,
                unempRate,
                totalJobsPlacedSession,
                totalStimulusDisbursedSession,
                totalPdsDistributedSession
        );

        telemetryEngine.recordSnapshot(snapshot);
        System.out.println("\n>>> [TELEMETRY COMMITTED TO RED-BLACK BST FOR CYCLE " + monthId + "]");
        snapshot.display();
    }

    public double getPovertyReductionDelta(long startMonth, long endMonth) {
        return telemetryEngine.computePovertyReductionDelta(startMonth, endMonth);
    }

    public void displayAuditTrail() {
        telemetryEngine.displayAuditTrail();
    }
}

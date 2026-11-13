#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
#include <memory>
#include <cmath>
#include <iomanip>
#include <algorithm>

#include "Citizen.hpp"
#include "EconomicGrievance.hpp"
#include "SkillTaxonomyTrie.hpp"
#include "WardCommodityBIT.hpp"
#include "KnapsackStimulus.hpp"
#include "MacroTelemetry.hpp"

/**
 * @brief Master Economic & Welfare Engine for CIVIC-SENTINEL.
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
class MasterEconomicEngine {
private:
    uint64_t internal_clock_ticks = 1000;
    int total_wards = 20;

    // 1. Data Registries
    std::unordered_map<uint64_t, CitizenProfile> citizen_registry;
    std::multimap<double, uint64_t, std::greater<double>> mpi_vulnerability_tree; // Red-Black BST
    std::unordered_set<uint64_t> anti_sybil_votes;                                // (citizen_id ^ (issue_id << 32))
    SkillTaxonomyTrie skill_trie;
    WardCommodityBIT pds_ration_stock;
    MacroTelemetryEngine telemetry_engine;

    // Cumulative stats
    int total_jobs_placed_session = 0;
    double total_stimulus_disbursed_session = 0.0;
    double total_pds_distributed_session = 0.0;

    // 2. Sectoral Priority Queues (Binary Max-Heaps)
    std::priority_queue<EconomicGrievance, std::vector<EconomicGrievance>, GrievanceComparator> unemployment_heap;
    std::priority_queue<EconomicGrievance, std::vector<EconomicGrievance>, GrievanceComparator> pds_food_heap;
    std::priority_queue<EconomicGrievance, std::vector<EconomicGrievance>, GrievanceComparator> debt_crisis_heap;
    std::priority_queue<EconomicGrievance, std::vector<EconomicGrievance>, GrievanceComparator> inflation_heap;

public:
    explicit MasterEconomicEngine(int num_wards = 20) 
        : total_wards(num_wards),
          pds_ration_stock(num_wards),
          unemployment_heap(GrievanceComparator(internal_clock_ticks)),
          pds_food_heap(GrievanceComparator(internal_clock_ticks)),
          debt_crisis_heap(GrievanceComparator(internal_clock_ticks)),
          inflation_heap(GrievanceComparator(internal_clock_ticks)) 
    {
        // Seed baseline grain stock across wards (e.g., 20,000 kg each)
        for (int w = 1; w <= total_wards; ++w) {
            pds_ration_stock.add_stock(w, 20000);
        }
    }

    void advance_clock(uint64_t ticks = 100) {
        internal_clock_ticks += ticks;
    }

    uint64_t get_clock() const {
        return internal_clock_ticks;
    }

    // ------------------------------------------------------------------------
    // Citizen Demographic Ingestion & Vulnerability Indexing
    // ------------------------------------------------------------------------
    void register_citizen(const CitizenProfile& profile) {
        citizen_registry[profile.citizen_id] = profile;
        double mpi = profile.compute_mpi();
        mpi_vulnerability_tree.insert({mpi, profile.citizen_id});

        for (const auto& skill : profile.skills) {
            skill_trie.insert_skill(skill, profile.citizen_id);
        }
    }

    const CitizenProfile* get_citizen(uint64_t citizen_id) const {
        auto it = citizen_registry.find(citizen_id);
        if (it != citizen_registry.end()) return &(it->second);
        return nullptr;
    }

    size_t get_citizen_count() const {
        return citizen_registry.size();
    }

    // ------------------------------------------------------------------------
    // Demographic Range Query (Simulating B+ Tree Leaves over Incomes)
    // Complexity: O(log_B N + K) in B+ Tree storage
    // ------------------------------------------------------------------------
    std::vector<uint64_t> query_citizens_by_income_range(double min_income, double max_income, int target_ward = -1) const {
        std::vector<uint64_t> matched_ids;
        for (const auto& [id, citizen] : citizen_registry) {
            if (citizen.monthly_income >= min_income && citizen.monthly_income <= max_income) {
                if (target_ward == -1 || citizen.ward_id == target_ward) {
                    matched_ids.push_back(id);
                }
            }
        }
        return matched_ids;
    }

    // ------------------------------------------------------------------------
    // Top-K Vulnerability Extractor (Red-Black BST begin() iterator)
    // ------------------------------------------------------------------------
    std::vector<uint64_t> get_top_vulnerable_citizens(size_t k) const {
        std::vector<uint64_t> result;
        size_t count = 0;
        for (auto it = mpi_vulnerability_tree.begin(); it != mpi_vulnerability_tree.end() && count < k; ++it, ++count) {
            result.push_back(it->second);
        }
        return result;
    }

    // ------------------------------------------------------------------------
    // Anti-Sybil Grievance Voting & Queue Insertion
    // Complexity: O(1) deduplication, O(log K) heap push
    // ------------------------------------------------------------------------
    bool lodge_or_vote_grievance(uint64_t citizen_id, uint32_t issue_id, EconomicSector sector, 
                                 int ward_id, const std::string& description) 
    {
        uint64_t vote_token = citizen_id ^ (static_cast<uint64_t>(issue_id) << 32);
        if (anti_sybil_votes.count(vote_token)) {
            std::cout << "  [ANTI-SYBIL REJECTED] Citizen #" << citizen_id 
                      << " has already cast a vote for Issue #" << issue_id << "!\n";
            return false;
        }
        anti_sybil_votes.insert(vote_token);

        double voter_mpi = 10.0;
        if (citizen_registry.count(citizen_id)) {
            voter_mpi = citizen_registry[citizen_id].compute_mpi();
        }

        EconomicGrievance grievance{issue_id, sector, ward_id, description, 1, voter_mpi, internal_clock_ticks};

        switch (sector) {
            case EconomicSector::UNEMPLOYMENT_SPIKE:
                unemployment_heap.push(grievance);
                break;
            case EconomicSector::PDS_FOOD_SECURITY:
                pds_food_heap.push(grievance);
                break;
            case EconomicSector::DEBT_USURY_CRISIS:
                debt_crisis_heap.push(grievance);
                break;
            case EconomicSector::MARKET_INFLATION:
                inflation_heap.push(grievance);
                break;
        }

        std::cout << "  [VOTE LOGGED] Citizen #" << citizen_id << " endorsed Issue #" << issue_id 
                  << " in " << to_string(sector) << " (Ward #" << ward_id << ")\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // Labor-Absorbing Public Works Allocation (Trie Search + Max-Heap Ranking)
    // Complexity: O(L) trie lookup + O(C log C) candidate ranking
    // ------------------------------------------------------------------------
    int allocate_public_works_jobs(const std::string& required_skill, int project_ward, int vacancies, double monthly_wage) {
        std::cout << "\n>>> [LABOR ABSORPTION DRIVE ACTIVATED]\n"
                  << "  Requisition: " << vacancies << " '" << required_skill 
                  << "' positions in Ward #" << project_ward 
                  << " | Monthly Wage: Rs." << std::fixed << std::setprecision(2) << monthly_wage << "\n";

        std::vector<uint64_t> candidate_pool = skill_trie.query_skill(required_skill);
        if (candidate_pool.empty()) {
            std::cout << "  (!) No registered citizens found with vocational skill: " << required_skill << "\n";
            return 0;
        }

        // Candidate Max-Heap: Combines Vulnerability (MPI) and Ward Proximity
        struct CandidateMatch {
            uint64_t id;
            double match_score;
            bool operator<(const CandidateMatch& other) const {
                return match_score < other.match_score;
            }
        };
        std::priority_queue<CandidateMatch> candidate_heap;

        for (uint64_t cid : candidate_pool) {
            auto& c = citizen_registry[cid];
            if (c.employment_status == 2) continue; // Skip citizens who are already steadily employed

            int ward_dist = std::abs(c.ward_id - project_ward);
            double proximity_weight = 1.0 / (ward_dist + 1.0);
            double score = (c.compute_mpi() * 0.70) + (proximity_weight * 35.0);
            candidate_heap.push({cid, score});
        }

        int hired = 0;
        while (!candidate_heap.empty() && hired < vacancies) {
            uint64_t chosen_id = candidate_heap.top().id;
            candidate_heap.pop();

            auto& worker = citizen_registry[chosen_id];
            worker.monthly_income += monthly_wage;
            worker.employment_status = 2; // Upgraded to stable employment
            worker.is_bpl = (worker.monthly_income < 8000.0);

            // Re-index updated vulnerability in Red-Black tree
            mpi_vulnerability_tree.insert({worker.compute_mpi(), chosen_id});

            std::cout << "  -> Placed Citizen #" << chosen_id << " (Ward #" << worker.ward_id 
                      << ") | New Monthly Income: Rs." << worker.monthly_income 
                      << " | New MPI: " << std::fixed << std::setprecision(2) << worker.compute_mpi() 
                      << " | BPL Status: " << (worker.is_bpl ? "YES" : "NO") << "\n";
            hired++;
            total_jobs_placed_session++;
        }

        std::cout << "  ✓ Total Qualified Workers Absorbed: " << hired << "/" << vacancies << "\n";
        return hired;
    }

    // ------------------------------------------------------------------------
    // Emergency Targeted Direct Benefit Transfer (DBT) via 0/1 Knapsack DP
    // ------------------------------------------------------------------------
    void execute_targeted_dbt(int target_ward, double relief_budget) {
        std::cout << "\n>>> [TARGETED DIRECT BENEFIT TRANSFER (DBT) STIMULUS]\n"
                  << "  Allocating Rs." << std::fixed << std::setprecision(2) << relief_budget 
                  << " across vulnerable households in Ward #" << target_ward << " using 0/1 Knapsack\n";

        std::vector<uint64_t> eligible_candidates = query_citizens_by_income_range(0.0, 10000.0, target_ward);
        if (eligible_candidates.empty()) {
            std::cout << "  No eligible households below threshold in Ward #" << target_ward << "\n";
            return;
        }

        auto result = KnapsackStimulusSolver::optimize_dbt(eligible_candidates, citizen_registry, relief_budget);

        for (size_t i = 0; i < result.selected_citizen_ids.size(); ++i) {
            uint64_t cid = result.selected_citizen_ids[i];
            double grant = result.allocated_amounts[i];

            auto& citizen = citizen_registry[cid];
            citizen.monthly_income += grant;
            citizen.debt_obligation = std::max(0.0, citizen.debt_obligation - (grant * 0.60)); // Relief clears usurious debt
            citizen.is_bpl = (citizen.monthly_income < 8000.0);

            mpi_vulnerability_tree.insert({citizen.compute_mpi(), cid});

            std::cout << "  -> Grant of Rs." << grant << " credited to Citizen #" << cid 
                      << " | Remaining Debt: Rs." << citizen.debt_obligation 
                      << " | New MPI: " << citizen.compute_mpi() << "\n";
        }

        total_stimulus_disbursed_session += result.total_disbursed;
        std::cout << "  ✓ Knapsack Optimization Complete: Disbursed Rs." << result.total_disbursed 
                  << " | Social Welfare Utility Max: " << result.total_utility_gained << "\n";
    }

    // ------------------------------------------------------------------------
    // Autonomous Macro Policy Trigger Check at Heap Roots
    // ------------------------------------------------------------------------
    void evaluate_macro_policy_triggers(double critical_threshold) {
        std::cout << "\n===========================================================\n";
        std::cout << "  EVALUATING QUEUE ROOTS (CRITICAL THRESHOLD: " << critical_threshold << ")\n";
        std::cout << "===========================================================\n";

        // 1. Food Security Root Inspection
        if (!pds_food_heap.empty()) {
            auto top_pds = pds_food_heap.top();
            double score = top_pds.priority_score(internal_clock_ticks);
            std::cout << "  [PDS HEAP ROOT] Issue #" << top_pds.issue_id << " (Ward #" << top_pds.ward_id 
                      << ") Priority: " << std::fixed << std::setprecision(2) << score << "\n";

            if (score >= critical_threshold) {
                std::cout << "  >>> AUTONOMOUS TRIGGER: Critical Food Insecurity in Ward #" << top_pds.ward_id << "!\n";
                // Fenwick tree point update: Add 15,000 kg buffer grain
                pds_ration_stock.add_stock(top_pds.ward_id, 15000);
                total_pds_distributed_session += 15000;
                std::cout << "  ✓ Dispatched 15,000 kg buffer stock. Current Ward #" << top_pds.ward_id 
                          << " Reserve: " << pds_ration_stock.get_ward_stock(top_pds.ward_id) << " kg\n";
                pds_food_heap.pop(); // Issue addressed
            }
        }

        // 2. Unemployment Spike Root Inspection
        if (!unemployment_heap.empty()) {
            auto top_unemp = unemployment_heap.top();
            double score = top_unemp.priority_score(internal_clock_ticks);
            std::cout << "  [UNEMPLOYMENT ROOT] Issue #" << top_unemp.issue_id << " (Ward #" << top_unemp.ward_id 
                      << ") Priority: " << std::fixed << std::setprecision(2) << score << "\n";

            if (score >= critical_threshold) {
                std::cout << "  >>> AUTONOMOUS TRIGGER: Deploying Civic Construction Drive in Ward #" << top_unemp.ward_id << "!\n";
                allocate_public_works_jobs("masonry", top_unemp.ward_id, 3, 9500.0);
                unemployment_heap.pop(); // Issue addressed
            }
        }

        // 3. Debt Usury Root Inspection
        if (!debt_crisis_heap.empty()) {
            auto top_debt = debt_crisis_heap.top();
            double score = top_debt.priority_score(internal_clock_ticks);
            std::cout << "  [DEBT CRISIS ROOT] Issue #" << top_debt.issue_id << " (Ward #" << top_debt.ward_id 
                      << ") Priority: " << std::fixed << std::setprecision(2) << score << "\n";

            if (score >= critical_threshold) {
                std::cout << "  >>> AUTONOMOUS TRIGGER: Deploying Zero-Interest Emergency Micro-Credit in Ward #" << top_debt.ward_id << "!\n";
                execute_targeted_dbt(top_debt.ward_id, 8000.0);
                debt_crisis_heap.pop(); // Issue addressed
            }
        }
    }

    // ------------------------------------------------------------------------
    // Ward-Level Commodity Range Query (Fenwick Tree)
    // ------------------------------------------------------------------------
    int64_t query_regional_grain_stock(int left_ward, int right_ward) const {
        return pds_ration_stock.range_stock(left_ward, right_ward);
    }

    // ------------------------------------------------------------------------
    // Monthly Macroeconomic Audit Recording (Red-Black BST Telemetry)
    // ------------------------------------------------------------------------
    void record_monthly_telemetry(uint32_t month_id) {
        int bpl_count = 0;
        int unemp_count = 0;
        double total_income = 0.0;

        for (const auto& [id, c] : citizen_registry) {
            if (c.is_bpl) bpl_count++;
            if (c.employment_status == 0) unemp_count++;
            total_income += c.monthly_income;
        }

        double avg_income = citizen_registry.empty() ? 0.0 : (total_income / citizen_registry.size());
        double unemp_rate = citizen_registry.empty() ? 0.0 : ((static_cast<double>(unemp_count) / citizen_registry.size()) * 100.0);

        MonthlyMacroTelemetry snapshot{
            month_id,
            static_cast<int>(citizen_registry.size()),
            bpl_count,
            avg_income,
            unemp_rate,
            total_jobs_placed_session,
            total_stimulus_disbursed_session,
            total_pds_distributed_session
        };

        telemetry_engine.record_snapshot(snapshot);
        std::cout << "\n>>> [TELEMETRY COMMITTED TO RED-BLACK BST FOR CYCLE " << month_id << "]\n";
        snapshot.display();
    }

    double get_poverty_reduction_delta(uint32_t start_month, uint32_t end_month) const {
        return telemetry_engine.compute_poverty_reduction_delta(start_month, end_month);
    }

    void display_audit_trail() const {
        telemetry_engine.display_audit_trail();
    }
};

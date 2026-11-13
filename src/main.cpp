#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "EconomicEngine.hpp"

void print_banner() {
    std::cout << "========================================================================\n";
    std::cout << "          CIVIC-SENTINEL: ECONOMIC & WELFARE ENGINE (PROJECT UDAAN)     \n";
    std::cout << "  Democratic Accountability, Citizen Ingestion & Macroeconomic Policy   \n";
    std::cout << "========================================================================\n\n";
}

int main() {
    print_banner();

    // Instantiate Master Engine with 20 Wards
    MasterEconomicEngine engine(20);

    // ========================================================================
    // SCENARIO 1: CITIZEN DEMOGRAPHIC INGESTION & MPI CALCULATION
    // ========================================================================
    std::cout << "[SCENARIO 1] Ingesting Citizen Profiles (Multidimensional Indicators)...\n";
    
    // Register citizens across Wards 1 to 5
    engine.register_citizen({1001, 3, 3500.0, 5, 30000.0, 4, {"masonry", "construction"}, 0, true});
    engine.register_citizen({1002, 3, 4200.0, 3, 15000.0, 2, {"masonry", "carpentry"}, 1, true});
    engine.register_citizen({1003, 3, 18000.0, 1, 0.0, 1, {"data-entry", "accounting"}, 2, false});
    engine.register_citizen({1004, 4, 2900.0, 6, 45000.0, 5, {"construction", "labor"}, 0, true});
    engine.register_citizen({1005, 4, 5500.0, 2, 8000.0, 2, {"plumbing", "welding"}, 1, true});
    engine.register_citizen({1006, 2, 3100.0, 4, 50000.0, 4, {"tailoring", "weaving"}, 0, true});
    engine.register_citizen({1007, 2, 4800.0, 3, 20000.0, 3, {"handicraft", "weaving"}, 1, true});
    engine.register_citizen({1008, 1, 25000.0, 1, 0.0, 1, {"management", "it"}, 2, false});

    std::cout << "  ✓ Total Registered Citizens: " << engine.get_citizen_count() << "\n\n";

    // ========================================================================
    // SCENARIO 2: DEMOGRAPHIC RANGE SCAN (B+ TREE SIMULATION)
    // ========================================================================
    std::cout << "[SCENARIO 2] Executing B+ Tree Demographic Range Query...\n";
    std::cout << "  Query: All citizens with Income in [Rs.0, Rs.6000] across all wards\n";
    auto low_income_group = engine.query_citizens_by_income_range(0.0, 6000.0);
    for (uint64_t cid : low_income_group) {
        auto c = engine.get_citizen(cid);
        if (c) c->display();
    }
    std::cout << "\n";

    // ========================================================================
    // SCENARIO 3: BASELINE MACROECONOMIC TELEMETRY (CYCLE 202611)
    // ========================================================================
    std::cout << "[SCENARIO 3] Recording Baseline Macroeconomic Snapshot (Red-Black BST)...\n";
    engine.record_monthly_telemetry(202611);

    // ========================================================================
    // SCENARIO 4: SECTORAL GRIEVANCES & ANTI-SYBIL DEDUPLICATION
    // ========================================================================
    std::cout << "\n[SCENARIO 4] Lodging Grievances across Sectoral Max-Heaps...\n";
    
    // Grievance 1: Severe Food Shortage in Ward 3
    engine.lodge_or_vote_grievance(1001, 801, EconomicSector::PDS_FOOD_SECURITY, 3, "Fair price shop empty for 3 weeks; grain ration exhausted.");
    engine.lodge_or_vote_grievance(1002, 801, EconomicSector::PDS_FOOD_SECURITY, 3, "Confirming empty grain storage in Ward 3.");

    // Anti-Sybil test: Duplicate vote attempt by Citizen 1001
    std::cout << "\n  Testing Anti-Sybil Protection (Duplicate Vote Injection):\n";
    engine.lodge_or_vote_grievance(1001, 801, EconomicSector::PDS_FOOD_SECURITY, 3, "Duplicate vote malicious injection.");

    // Grievance 2: Unemployment Spike in Ward 4
    engine.lodge_or_vote_grievance(1004, 802, EconomicSector::UNEMPLOYMENT_SPIKE, 4, "Factory closure led to mass day-wage layoffs in Ward 4.");

    // Grievance 3: Predatory Usury / Debt Crisis in Ward 2
    engine.lodge_or_vote_grievance(1006, 803, EconomicSector::DEBT_USURY_CRISIS, 2, "Informal loan sharks seizing assets from slum artisans.");

    // Advance clock to trigger starvation aging
    std::cout << "\n  Advancing system clock ticks by 150 to demonstrate Aging Factor in Heap...\n";
    engine.advance_clock(150);

    // ========================================================================
    // SCENARIO 5: AUTONOMOUS POLICY TRIGGER EVALUATION AT QUEUE ROOTS
    // ========================================================================
    std::cout << "\n[SCENARIO 5] Autonomous Macro Policy Triggers via Queue Roots...\n";
    engine.evaluate_macro_policy_triggers(45.0);

    // ========================================================================
    // SCENARIO 6: REGIONAL COMMODITY INVENTORY (FENWICK TREE QUERY)
    // ========================================================================
    std::cout << "\n[SCENARIO 6] Regional Foodgrain Stock Telemetry via Fenwick Tree...\n";
    int64_t ward3_stock = engine.query_regional_grain_stock(3, 3);
    int64_t sector_stock = engine.query_regional_grain_stock(1, 5);
    std::cout << "  - Ward #3 Grain Reserve (After Emergency Influx) : " << ward3_stock << " kg\n";
    std::cout << "  - Contiguous Sector Wards [1..5] Total Reserves : " << sector_stock << " kg\n";

    // ========================================================================
    // SCENARIO 7: TARGETED DIRECT BENEFIT TRANSFER (DBT) VIA 0/1 KNAPSACK
    // ========================================================================
    std::cout << "\n[SCENARIO 7] Executing Targeted DBT Stimulus via 0/1 Knapsack...\n";
    engine.execute_targeted_dbt(4, 6000.0);

    // ========================================================================
    // SCENARIO 8: POST-INTERVENTION AUDIT & POVERTY REDUCTION DELTA
    // ========================================================================
    std::cout << "\n[SCENARIO 8] Recording Post-Intervention Macroeconomic Snapshot (Cycle 202612)...\n";
    engine.record_monthly_telemetry(202612);

    // Calculate delta for administrative accountability rating
    double delta_bpl = engine.get_poverty_reduction_delta(202611, 202612);
    std::cout << "\n========================================================================\n";
    std::cout << "  ADMINISTRATIVE EVALUATION FEEDBACK DELTA                              \n";
    std::cout << "========================================================================\n";
    std::cout << "  Calculated Poverty Reduction Delta (Cycle 202611 -> 202612): " 
              << std::fixed << std::setprecision(2) << delta_bpl << "%\n";
    std::cout << "  This delta is fed directly into the Administrative Rating Engine:\n";
    std::cout << "  Score Contribution = 0.35 * PovertyReductionDelta (" << (0.35 * delta_bpl) << " pts)\n";
    std::cout << "========================================================================\n";

    // Display the full audit trail from the Red-Black BST
    engine.display_audit_trail();

    std::cout << "\n>>> [CIVIC-SENTINEL ECONOMIC ENGINE SIMULATION COMPLETED SUCCESSFULLY]\n";
    return 0;
}

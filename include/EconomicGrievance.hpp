#pragma once
#include <iostream>
#include <string>
#include <cstdint>

/**
 * @brief Sectoral classification of macroeconomic crises.
 * Ensures domain-separated priority queues so different crises receive
 * specialized autonomous fiscal/monetary interventions.
 */
enum class EconomicSector {
    UNEMPLOYMENT_SPIKE = 0, // Chronic or seasonal joblessness
    PDS_FOOD_SECURITY  = 1, // Fair Price Shop grain shortages / supply-chain failure
    DEBT_USURY_CRISIS  = 2, // Predatory lending, micro-debt insolvency
    MARKET_INFLATION   = 3  // Price gouging or essential commodity inflation
};

inline std::string to_string(EconomicSector sector) {
    switch (sector) {
        case EconomicSector::UNEMPLOYMENT_SPIKE: return "UNEMPLOYMENT_SPIKE";
        case EconomicSector::PDS_FOOD_SECURITY:  return "PDS_FOOD_SECURITY";
        case EconomicSector::DEBT_USURY_CRISIS:  return "DEBT_USURY_CRISIS";
        case EconomicSector::MARKET_INFLATION:   return "MARKET_INFLATION";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Citizen Economic Grievance Node.
 * Represents an issue submitted by verified citizens with dynamic priority ranking.
 */
struct EconomicGrievance {
    uint32_t issue_id;
    EconomicSector sector;
    int ward_id;
    std::string description;
    uint32_t verified_upvotes;
    double aggregated_mpi;         // Sum of MPI of all endorsing citizens
    uint64_t timestamp;            // Epoch tick when issue was lodged

    /**
     * @brief Computes priority score combining vulnerability, consensus, and starvation aging.
     * 
     * Formula:
     *   Priority = (0.45 * aggregated_mpi) + (0.35 * verified_upvotes) + (0.20 * (current_tick - timestamp))
     * 
     * - aggregated_mpi prevents affluent wards from dominating queue roots.
     * - verified_upvotes preserves community consensus.
     * - (current_tick - timestamp) guarantees starvation prevention (aging factor).
     */
    double priority_score(uint64_t current_tick) const {
        double urgency = (aggregated_mpi * 0.45) + (verified_upvotes * 0.35);
        double aging_escalation = (current_tick >= timestamp) ? (current_tick - timestamp) * 0.20 : 0.0;
        return urgency + aging_escalation;
    }
};

/**
 * @brief Comparator for Binary Max-Heap priority scheduling.
 */
struct GrievanceComparator {
    uint64_t current_tick;
    explicit GrievanceComparator(uint64_t tick = 0) : current_tick(tick) {}

    bool operator()(const EconomicGrievance& a, const EconomicGrievance& b) const {
        return a.priority_score(current_tick) < b.priority_score(current_tick); // Max-Heap
    }
};

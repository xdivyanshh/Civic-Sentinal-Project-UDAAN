#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cstdint>
#include <iomanip>

/**
 * @brief Monthly Macroeconomic Snapshot.
 * Captures ward and municipal level socio-economic telemetry for administrative audit.
 */
struct MonthlyMacroTelemetry {
    uint32_t month_id;              // e.g., 202610, 202611
    int total_population;
    int bpl_households;
    double average_monthly_income;
    double unemployment_rate;
    int jobs_placed_count;
    double emergency_stimulus_disbursed;
    double pds_grain_distributed_kg;

    void display() const {
        std::cout << "  Snapshot Month            : " << month_id << "\n"
                  << "  Total Population Monitored : " << total_population << "\n"
                  << "  BPL Household Count       : " << bpl_households << "\n"
                  << "  Average Monthly Income    : Rs." << std::fixed << std::setprecision(2) << average_monthly_income << "\n"
                  << "  Unemployment Rate         : " << unemployment_rate << "%\n"
                  << "  Jobs Placed (Public Works): " << jobs_placed_count << "\n"
                  << "  Stimulus Relief Disbursed : Rs." << emergency_stimulus_disbursed << "\n"
                  << "  PDS Grain Distributed     : " << pds_grain_distributed_kg << " kg\n";
    }
};

/**
 * @brief Macroeconomic Telemetry Engine using Balanced Search Trees (Red-Black BST via std::map).
 * 
 * Provides O(log M) insertion and chronological range queries across monthly evaluation cycles.
 * Used by Chapter 3's rating equation:
 * Rating = 0.35 * GrievanceScore + 0.35 * PovertyReductionDelta + 0.30 * EconomicActivityGrowth
 */
class MacroTelemetryEngine {
private:
    std::map<uint32_t, MonthlyMacroTelemetry> telemetry_bst; // Red-Black BST

public:
    void record_snapshot(const MonthlyMacroTelemetry& snapshot) {
        telemetry_bst[snapshot.month_id] = snapshot;
    }

    bool get_snapshot(uint32_t month_id, MonthlyMacroTelemetry& out_snapshot) const {
        auto it = telemetry_bst.find(month_id);
        if (it != telemetry_bst.end()) {
            out_snapshot = it->second;
            return true;
        }
        return false;
    }

    /**
     * @brief Computes poverty reduction delta between two evaluation months.
     * Complexity: O(log M)
     */
    double compute_poverty_reduction_delta(uint32_t start_month, uint32_t end_month) const {
        auto it_start = telemetry_bst.find(start_month);
        auto it_end = telemetry_bst.find(end_month);

        if (it_start == telemetry_bst.end() || it_end == telemetry_bst.end()) {
            return 0.0;
        }

        double start_bpl = it_start->second.bpl_households;
        double end_bpl = it_end->second.bpl_households;

        if (start_bpl == 0) return 0.0;

        // Percentage reduction in BPL households: positive value indicates poverty reduction
        return ((start_bpl - end_bpl) / start_bpl) * 100.0;
    }

    /**
     * @brief Displays chronological audit trail for all recorded cycles.
     */
    void display_audit_trail() const {
        std::cout << "\n===========================================================\n";
        std::cout << "   CHRONOLOGICAL MACROECONOMIC AUDIT TRAIL (RED-BLACK BST) \n";
        std::cout << "===========================================================\n";
        for (const auto& kv : telemetry_bst) {
            const auto& month = kv.first;
            const auto& data = kv.second;
            std::cout << ">>> CYCLE: " << month << "\n";
            data.display();
            std::cout << "-----------------------------------------------------------\n";
        }
    }
};

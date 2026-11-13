#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include "Citizen.hpp"

/**
 * @brief 0/1 Knapsack Dynamic Programming Solver for Targeted Direct Benefit Transfers (DBT).
 * 
 * Based on Collins Ayoo's (IntechOpen) social protection model:
 * When emergency fiscal stimulus budget B is constrained, the administration must
 * select beneficiaries to maximize overall community survival utility without
 * exceeding the budget ceiling.
 */
class KnapsackStimulusSolver {
public:
    struct DisbursementResult {
        std::vector<uint64_t> selected_citizen_ids;
        std::vector<double> allocated_amounts;
        double total_disbursed;
        int total_utility_gained;
    };

    /**
     * @brief Solves the 0/1 Knapsack problem for emergency welfare cash grants.
     * 
     * @param candidates Vector of citizen IDs eligible for relief.
     * @param citizen_registry Hash map containing full citizen profiles.
     * @param budget Total municipal relief funds available (INR).
     * @param unit_scale Discretization unit for DP grid (default 1000 INR).
     * @return DisbursementResult Structure containing chosen beneficiaries and financial adjustments.
     */
    static DisbursementResult optimize_dbt(
        const std::vector<uint64_t>& candidates,
        const std::unordered_map<uint64_t, CitizenProfile>& citizen_registry,
        double budget,
        double unit_scale = 1000.0) 
    {
        DisbursementResult result{ {}, {}, 0.0, 0 };
        int N = static_cast<int>(candidates.size());
        int W_capacity = static_cast<int>(budget / unit_scale);

        if (N == 0 || W_capacity <= 0) return result;

        // Weight = cost in discrete units; Value = social utility (based on MPI & dependents)
        std::vector<int> weights(N);
        std::vector<int> values(N);
        std::vector<double> actual_grants(N);

        for (int i = 0; i < N; ++i) {
            const auto& profile = citizen_registry.at(candidates[i]);
            // Grant size scales with dependents: e.g., 2 units + 1 unit per dependent
            int units_needed = std::max(1, 2 + profile.dependents);
            weights[i] = units_needed;
            actual_grants[i] = units_needed * unit_scale;
            values[i] = static_cast<int>(profile.compute_mpi() * (1 + profile.dependents * 0.2));
        }

        // 2D DP Table: dp[i][w] = max utility considering first i candidates with capacity w
        std::vector<std::vector<int>> dp(N + 1, std::vector<int>(W_capacity + 1, 0));

        for (int i = 1; i <= N; ++i) {
            for (int w = 0; w <= W_capacity; ++w) {
                if (weights[i - 1] <= w) {
                    dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // Backtracking to find chosen beneficiaries
        int rem_w = W_capacity;
        for (int i = N; i > 0 && rem_w > 0; --i) {
            if (dp[i][rem_w] != dp[i - 1][rem_w]) {
                result.selected_citizen_ids.push_back(candidates[i - 1]);
                result.allocated_amounts.push_back(actual_grants[i - 1]);
                result.total_disbursed += actual_grants[i - 1];
                rem_w -= weights[i - 1];
            }
        }

        result.total_utility_gained = dp[N][W_capacity];
        return result;
    }
};

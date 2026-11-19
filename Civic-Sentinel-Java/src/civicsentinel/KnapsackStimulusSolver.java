package civicsentinel;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * 0/1 Knapsack Dynamic Programming Solver for Targeted Direct Benefit Transfers (DBT).
 * 
 * Based on Collins Ayoo's (IntechOpen) social protection model:
 * When emergency fiscal stimulus budget B is constrained, the administration must
 * select beneficiaries to maximize overall community survival utility without
 * exceeding the budget ceiling.
 */
public class KnapsackStimulusSolver {

    public static class DisbursementResult {
        public List<Long> selectedCitizenIds;
        public List<Double> allocatedAmounts;
        public double totalDisbursed;
        public int totalUtilityGained;

        public DisbursementResult() {
            this.selectedCitizenIds = new ArrayList<>();
            this.allocatedAmounts = new ArrayList<>();
            this.totalDisbursed = 0.0;
            this.totalUtilityGained = 0;
        }
    }

    /**
     * Solves the 0/1 Knapsack problem for emergency welfare cash grants.
     * 
     * @param candidates List of citizen IDs eligible for relief.
     * @param citizenRegistry Hash map containing full citizen profiles.
     * @param budget Total municipal relief funds available (INR).
     * @param unitScale Discretization unit for DP grid (default 1000 INR).
     * @return DisbursementResult Structure containing chosen beneficiaries and financial adjustments.
     */
    public static DisbursementResult optimizeDbt(
            List<Long> candidates,
            Map<Long, CitizenProfile> citizenRegistry,
            double budget,
            double unitScale) {

        DisbursementResult result = new DisbursementResult();
        if (candidates == null || candidates.isEmpty() || citizenRegistry == null) {
            return result;
        }

        int N = candidates.size();
        int W_capacity = (int) (budget / unitScale);

        if (N == 0 || W_capacity <= 0) return result;

        // Weight = cost in discrete units; Value = social utility (based on MPI & dependents)
        int[] weights = new int[N];
        int[] values = new int[N];
        double[] actualGrants = new double[N];

        for (int i = 0; i < N; ++i) {
            CitizenProfile profile = citizenRegistry.get(candidates.get(i));
            if (profile == null) continue;
            // Grant size scales with dependents: e.g., 2 units + 1 unit per dependent
            int unitsNeeded = Math.max(1, 2 + profile.dependents);
            weights[i] = unitsNeeded;
            actualGrants[i] = unitsNeeded * unitScale;
            values[i] = (int) (profile.compute_mpi() * (1.0 + profile.dependents * 0.2));
        }

        // 2D DP Table: dp[i][w] = max utility considering first i candidates with capacity w
        int[][] dp = new int[N + 1][W_capacity + 1];

        for (int i = 1; i <= N; ++i) {
            for (int w = 0; w <= W_capacity; ++w) {
                if (weights[i - 1] <= w) {
                    dp[i][w] = Math.max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // Backtracking to find chosen beneficiaries
        int remW = W_capacity;
        for (int i = N; i > 0 && remW > 0; --i) {
            if (dp[i][remW] != dp[i - 1][remW]) {
                result.selectedCitizenIds.add(candidates.get(i - 1));
                result.allocatedAmounts.add(actualGrants[i - 1]);
                result.totalDisbursed += actualGrants[i - 1];
                remW -= weights[i - 1];
            }
        }

        result.totalUtilityGained = dp[N][W_capacity];
        return result;
    }

    public static DisbursementResult optimizeDbt(
            List<Long> candidates,
            Map<Long, CitizenProfile> citizenRegistry,
            double budget) {
        return optimizeDbt(candidates, citizenRegistry, budget, 1000.0);
    }
}

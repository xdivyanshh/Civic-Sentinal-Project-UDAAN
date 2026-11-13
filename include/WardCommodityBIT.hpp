#pragma once
#include <vector>
#include <cstdint>
#include <stdexcept>

/**
 * @brief Binary Indexed Tree (Fenwick Tree) for Ward Commodity & PDS Tracking.
 * 
 * Provides O(log W) point updates and O(log W) range queries across W municipal wards.
 * Essential for high-concurrency food grain monitoring, ration stockout detection,
 * and emergency buffer reallocation during food crises (ISPP Food Security dimension).
 */
class WardCommodityBIT {
private:
    int total_wards;
    std::vector<int64_t> bit_tree;

public:
    explicit WardCommodityBIT(int num_wards) 
        : total_wards(num_wards), bit_tree(num_wards + 1, 0) {}

    /**
     * @brief Adds or removes grain stock from a specific ward.
     * Complexity: O(log W)
     */
    void add_stock(int ward, int64_t delta_kg) {
        if (ward < 1 || ward > total_wards) return;
        for (; ward <= total_wards; ward += ward & -ward) {
            bit_tree[ward] += delta_kg;
        }
    }

    /**
     * @brief Computes cumulative grain stock from Ward 1 through Ward k.
     * Complexity: O(log W)
     */
    int64_t prefix_stock(int ward) const {
        if (ward > total_wards) ward = total_wards;
        int64_t sum = 0;
        for (; ward > 0; ward -= ward & -ward) {
            sum += bit_tree[ward];
        }
        return sum;
    }

    /**
     * @brief Computes total grain reserves in a contiguous ward sector [left_ward, right_ward].
     * Complexity: O(log W)
     */
    int64_t range_stock(int left_ward, int right_ward) const {
        if (left_ward < 1) left_ward = 1;
        if (right_ward > total_wards) right_ward = total_wards;
        if (left_ward > right_ward) return 0;
        return prefix_stock(right_ward) - prefix_stock(left_ward - 1);
    }

    /**
     * @brief Returns current stock in an isolated single ward.
     * Complexity: O(log W)
     */
    int64_t get_ward_stock(int ward) const {
        return range_stock(ward, ward);
    }

    int get_ward_count() const {
        return total_wards;
    }
};

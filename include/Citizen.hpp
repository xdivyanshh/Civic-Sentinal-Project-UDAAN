#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

/**
 * @brief Citizen Profile and Multidimensional Poverty Index (MPI) Model.
 * 
 * Incorporates multidimensional poverty indicators based on research from the
 * Indian School of Public Policy (ISPP) and Collins Ayoo (IntechOpen):
 * - Monetary Dimension: Monthly Income, Debt Burden
 * - Human Capital Dimension: Health Vulnerability, Vocational Skills
 * - Demographic Dimension: Dependent Ratio, Living Standard Status (BPL)
 */
struct CitizenProfile {
    uint64_t citizen_id;               // Unique Voter / Aadhaar Hash
    int ward_id;                       // Geospatial Municipal Ward ID (1 to W)
    double monthly_income;             // Direct monthly earnings (INR)
    int dependents;                    // Non-earning family members (children, elderly)
    double debt_obligation;            // Total outstanding formal/informal liabilities
    int health_vulnerability;          // Scale 1 (Good) to 5 (Severe chronic health burden)
    std::vector<std::string> skills;   // Categorized vocational skills
    int employment_status;             // 0: Unemployed, 1: Daily Wage / Seasonal, 2: Stable
    bool is_bpl;                       // Below Poverty Line flag

    /**
     * @brief Computes the Multidimensional Poverty Index (MPI) for the citizen.
     * Higher score indicates higher socio-economic vulnerability.
     */
    double compute_mpi() const {
        // 1. Income Inverse Factor: Lower income exponentially increases vulnerability
        double income_factor = (monthly_income <= 0) ? 100.0 : (10000.0 / (monthly_income + 50.0));
        
        // 2. Dependency Burden Factor
        double dependent_factor = dependents * 3.5;
        
        // 3. Debt Stress Ratio Factor (Debt to Income leverage)
        double debt_factor = (debt_obligation / (monthly_income + 100.0)) * 12.0;
        
        // 4. Chronic Health Burden Factor
        double health_factor = health_vulnerability * 4.0;
        
        // 5. Employment Insecurity Weight
        double employment_factor = (employment_status == 0) ? 25.0 : ((employment_status == 1) ? 10.0 : 0.0);

        return income_factor + dependent_factor + debt_factor + health_factor + employment_factor;
    }

    void display() const {
        std::cout << "Citizen #" << citizen_id 
                  << " | Ward " << ward_id 
                  << " | Income: Rs." << std::fixed << std::setprecision(2) << monthly_income
                  << " | Debt: Rs." << debt_obligation
                  << " | Dependents: " << dependents
                  << " | Status: " << (employment_status == 0 ? "Unemployed" : (employment_status == 1 ? "Daily-Wage" : "Stable"))
                  << " | MPI: " << compute_mpi()
                  << " | BPL: " << (is_bpl ? "YES" : "NO") << "\n";
    }
};

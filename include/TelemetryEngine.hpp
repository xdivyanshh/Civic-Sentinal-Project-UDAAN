#ifndef TELEMETRY_ENGINE_HPP
#define TELEMETRY_ENGINE_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

namespace CivicSentinel {

// Single monthly telemetry snapshot
struct MonthlyTelemetry {
    string monthKey; // Format: "YYYY-MM" (e.g. "2026-08")
    int grievancesReported;
    int grievancesResolved;
    double povertyReductionDelta;    // In % (e.g. +3.2%)
    double economicGrowthDelta;       // In % (e.g. +2.1%)
    double citizenSatisfactionScore;  // 0 to 100
};

// ============================================================================
// DSA CONCEPT: BALANCED SEARCH TREE (RED-BLACK TREE via std::map)
// Stores monthly telemetry sorted chronologically in O(log M) time.
// Enables O(log M + K) range queries via lower_bound and upper_bound.
// ============================================================================
class TelemetryEngine {
private:
    // Red-Black Tree mapping chronological DateKey ("YYYY-MM") -> MonthlyTelemetry
    map<string, MonthlyTelemetry> historicalTelemetry;

public:
    // Insert monthly log: O(log M)
    void logMonth(const MonthlyTelemetry& telemetry) {
        historicalTelemetry[telemetry.monthKey] = telemetry;
    }

    // Dynamic Range Query using BST lower_bound & upper_bound: O(log M + K)
    vector<MonthlyTelemetry> getRangeTelemetry(const string& startMonth, const string& endMonth) const {
        vector<MonthlyTelemetry> result;

        auto it = historicalTelemetry.lower_bound(startMonth);
        auto endIt = historicalTelemetry.upper_bound(endMonth);

        while (it != endIt) {
            result.push_back(it->second);
            ++it;
        }

        return result;
    }

    // ========================================================================
    // ALGORITHMIC POLITICIAN EVALUATION FORMULA (0 - 100 SCORECARD)
    // Rating = (0.35 * GrievanceScore) + (0.35 * PovertyDelta) + (0.30 * Satisfaction)
    // ========================================================================
    double calculatePoliticianScore(const string& startMonth, const string& endMonth) const {
        auto logs = getRangeTelemetry(startMonth, endMonth);
        if (logs.empty()) return 0.0;

        double totalResolutionRatio = 0.0;
        double totalPovertyDelta = 0.0;
        double totalSatisfaction = 0.0;

        for (const auto& log : logs) {
            double ratio = (log.grievancesReported > 0) 
                ? (static_cast<double>(log.grievancesResolved) / log.grievancesReported) * 100.0 
                : 100.0;
            totalResolutionRatio += min(100.0, ratio);
            totalPovertyDelta += log.povertyReductionDelta * 20.0; // Scaled to 100
            totalSatisfaction += log.citizenSatisfactionScore;
        }

        size_t n = logs.size();
        double avgResolution = totalResolutionRatio / n;
        double avgPoverty = min(100.0, max(0.0, totalPovertyDelta / n));
        double avgSatisfaction = totalSatisfaction / n;

        // Synopsis Formula: 35% Resolution + 35% Poverty Alleviation + 30% Public Satisfaction
        double finalScore = (0.35 * avgResolution) + (0.35 * avgPoverty) + (0.30 * avgSatisfaction);
        return finalScore;
    }

    void displayPoliticianAudit(const string& politicianName, const string& wardId, 
                                const string& startMonth, const string& endMonth) const {
        auto logs = getRangeTelemetry(startMonth, endMonth);

        cout << "\n========================================================" << endl;
        cout << "  POLITICIAN ACCOUNTABILITY AUDIT SCORECARD (0-100)    " << endl;
        cout << "========================================================" << endl;
        cout << " Representative : " << politicianName << endl;
        cout << " Jurisdiction   : " << wardId << endl;
        cout << " Audit Window   : " << startMonth << " to " << endMonth 
             << " (" << logs.size() << " Months Audited)" << endl;
        cout << "--------------------------------------------------------" << endl;

        for (const auto& log : logs) {
            cout << " [" << log.monthKey << "] Reported: " << setw(2) << log.grievancesReported 
                 << " | Resolved: " << setw(2) << log.grievancesResolved 
                 << " | Poverty Delta: +" << fixed << setprecision(1) << log.povertyReductionDelta << "%"
                 << " | Public Satisfaction: " << log.citizenSatisfactionScore << "/100" << endl;
        }

        double score = calculatePoliticianScore(startMonth, endMonth);
        cout << "--------------------------------------------------------" << endl;
        cout << " FINAL COMPOSITE DEMOCRATIC RATING: " << fixed << setprecision(2) << score << " / 100.00" << endl;

        // Democratic Grading Scale
        if (score >= 85.0)      cout << " PERFORMANCE GRADE: [A+] Exemplary Public Leadership" << endl;
        else if (score >= 70.0) cout << " PERFORMANCE GRADE: [B] Satisfactory Progress" << endl;
        else if (score >= 50.0) cout << " PERFORMANCE GRADE: [C] Moderate Public Deficit" << endl;
        else                    cout << " PERFORMANCE GRADE: [F] CRITICAL FAILURE - High Electoral Vulnerability" << endl;
        cout << "========================================================" << endl;
    }
};

} // namespace CivicSentinel

#endif // TELEMETRY_ENGINE_HPP

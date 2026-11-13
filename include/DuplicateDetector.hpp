#ifndef DUPLICATE_DETECTOR_HPP
#define DUPLICATE_DETECTOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

namespace CivicSentinel {

// ============================================================================
// DSA CONCEPT: INVERTED KEYWORD INDEX (HASH MAP)
// Maps tokenized complaint keywords -> vector of active issue IDs in each ward.
// Detects near-duplicates before ticket creation in O(1) keyword lookup time.
// ============================================================================
class DuplicateDetector {
private:
    // Inverted Index: "wardId::keyword" -> vector of Issue IDs
    unordered_map<string, vector<int>> keywordIndex;

    // Helper to tokenize title/description into clean lower-case keywords
    vector<string> extractKeywords(const string& text) const {
        vector<string> tokens;
        stringstream ss(text);
        string word;
        while (ss >> word) {
            string cleanWord = "";
            for (char ch : word) {
                if (isalnum(ch)) cleanWord += static_cast<char>(tolower(ch));
            }
            // Skip common stop-words and short words
            if (cleanWord.length() > 3 && 
                cleanWord != "this" && cleanWord != "that" && cleanWord != "near" && cleanWord != "with") {
                tokens.push_back(cleanWord);
            }
        }
        return tokens;
    }

public:
    // Index a newly created grievance
    void indexGrievance(int issueId, const string& wardId, const string& title) {
        vector<string> keywords = extractKeywords(title);
        for (const string& kw : keywords) {
            string compositeKey = wardId + "::" + kw;
            keywordIndex[compositeKey].push_back(issueId);
        }
    }

    // Check if similar issues exist in the same ward
    vector<int> findPotentialDuplicates(const string& wardId, const string& title) const {
        vector<string> keywords = extractKeywords(title);
        unordered_map<int, int> matchCounts; // issueId -> number of shared keywords

        for (const string& kw : keywords) {
            string compositeKey = wardId + "::" + kw;
            auto it = keywordIndex.find(compositeKey);
            if (it != keywordIndex.end()) {
                for (int id : it->second) {
                    matchCounts[id]++;
                }
            }
        }

        // Return issues that match at least 2 significant keywords
        vector<int> duplicateCandidates;
        for (const auto& pair : matchCounts) {
            if (pair.second >= 2) {
                duplicateCandidates.push_back(pair.first);
            }
        }
        return duplicateCandidates;
    }
};

} // namespace CivicSentinel

#endif // DUPLICATE_DETECTOR_HPP

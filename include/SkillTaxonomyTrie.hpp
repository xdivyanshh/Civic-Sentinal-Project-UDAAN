#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cctype>

/**
 * @brief Trie Node for Vocational Skill Taxonomy.
 * Allows instant O(L) retrieval of qualified citizen candidates where L is skill name length.
 */
struct TrieNode {
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    std::vector<uint64_t> qualified_citizen_ids;
    bool is_end_of_word = false;
};

/**
 * @brief Skill Taxonomy Prefix Tree (Trie).
 * Used by the Labor Absorption Engine to match public works and micro-enterprise
 * job requisitions to qualified local workers.
 */
class SkillTaxonomyTrie {
private:
    std::shared_ptr<TrieNode> root;

    std::string normalize(const std::string& str) const {
        std::string clean = "";
        for (char ch : str) {
            if (std::isalnum(static_cast<unsigned char>(ch)) || ch == '-' || ch == '_') {
                clean += std::tolower(static_cast<unsigned char>(ch));
            }
        }
        return clean;
    }

public:
    SkillTaxonomyTrie() : root(std::make_shared<TrieNode>()) {}

    /**
     * @brief Inserts a skill keyword associated with a citizen.
     * Complexity: O(L) where L is length of skill string.
     */
    void insert_skill(const std::string& raw_skill, uint64_t citizen_id) {
        std::string skill = normalize(raw_skill);
        if (skill.empty()) return;

        auto curr = root;
        for (char ch : skill) {
            if (!curr->children.count(ch)) {
                curr->children[ch] = std::make_shared<TrieNode>();
            }
            curr = curr->children[ch];
        }
        curr->is_end_of_word = true;
        curr->qualified_citizen_ids.push_back(citizen_id);
    }

    /**
     * @brief Queries all citizen IDs registered with a specific skill.
     * Complexity: O(L) where L is length of skill string.
     */
    std::vector<uint64_t> query_skill(const std::string& raw_skill) const {
        std::string skill = normalize(raw_skill);
        if (skill.empty()) return {};

        auto curr = root;
        for (char ch : skill) {
            if (!curr->children.count(ch)) return {};
            curr = curr->children.at(ch);
        }
        return curr->qualified_citizen_ids;
    }

    /**
     * @brief Checks if any skill exists matching the given prefix.
     */
    bool starts_with(const std::string& raw_prefix) const {
        std::string prefix = normalize(raw_prefix);
        auto curr = root;
        for (char ch : prefix) {
            if (!curr->children.count(ch)) return false;
            curr = curr->children.at(ch);
        }
        return true;
    }
};

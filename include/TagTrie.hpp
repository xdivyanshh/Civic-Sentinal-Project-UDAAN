#ifndef TAG_TRIE_HPP
#define TAG_TRIE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

namespace CivicSentinel {

// ============================================================================
// DSA CONCEPT: PREFIX TRIE (PREFIX TREE)
// Enables O(L) prefix search and autocomplete for civic complaint tags.
// ============================================================================
class TrieNode {
public:
    bool isEndOfWord;
    unordered_map<char, TrieNode*> children;

    TrieNode() : isEndOfWord(false) {}

    ~TrieNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

class TagTrie {
private:
    TrieNode* root;

    // Helper for DFS traversal to collect all matching words under prefix
    void collectAllWords(TrieNode* current, string currentPrefix, vector<string>& results) const {
        if (!current) return;

        if (current->isEndOfWord) {
            results.push_back(currentPrefix);
        }

        for (const auto& pair : current->children) {
            collectAllWords(pair.second, currentPrefix + pair.first, results);
        }
    }

public:
    TagTrie() {
        root = new TrieNode();
    }

    ~TagTrie() {
        delete root;
    }

    // Insert tag: O(L) where L is length of word
    void insert(const string& word) {
        if (word.empty()) return;

        TrieNode* current = root;
        for (char ch : word) {
            char lowerCh = static_cast<char>(tolower(ch));
            if (current->children.find(lowerCh) == current->children.end()) {
                current->children[lowerCh] = new TrieNode();
            }
            current = current->children[lowerCh];
        }
        current->isEndOfWord = true;
    }

    // Autocomplete query: O(L + K) where L is prefix length, K is results found
    vector<string> autocomplete(const string& prefix) const {
        vector<string> results;
        if (prefix.empty()) return results;

        TrieNode* current = root;
        for (char ch : prefix) {
            char lowerCh = static_cast<char>(tolower(ch));
            if (current->children.find(lowerCh) == current->children.end()) {
                return results; // Prefix not found
            }
            current = current->children[lowerCh];
        }

        // Collect all branches starting from this prefix node
        collectAllWords(current, prefix, results);
        return results;
    }
};

} // namespace CivicSentinel

#endif // TAG_TRIE_HPP

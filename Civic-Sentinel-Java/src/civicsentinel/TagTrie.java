package civicsentinel;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * ============================================================================
 * DSA CONCEPT: PREFIX TRIE (PREFIX TREE)
 * Enables O(L) prefix search and autocomplete for civic complaint tags.
 * ============================================================================
 */
public class TagTrie {

    public static class TagTrieNode {
        public boolean isEndOfWord;
        public Map<Character, TagTrieNode> children;

        public TagTrieNode() {
            this.isEndOfWord = false;
            this.children = new HashMap<>();
        }
    }

    private final TagTrieNode root;

    public TagTrie() {
        this.root = new TagTrieNode();
    }

    /**
     * Insert tag: O(L) where L is length of word
     */
    public void insert(String word) {
        if (word == null || word.isEmpty()) return;

        TagTrieNode current = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = Character.toLowerCase(word.charAt(i));
            current.children.putIfAbsent(ch, new TagTrieNode());
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;
    }

    /**
     * Autocomplete query: O(L + K) where L is prefix length, K is results found
     */
    public List<String> autocomplete(String prefix) {
        List<String> results = new ArrayList<>();
        if (prefix == null || prefix.isEmpty()) return results;

        TagTrieNode current = root;
        for (int i = 0; i < prefix.length(); i++) {
            char ch = Character.toLowerCase(prefix.charAt(i));
            if (!current.children.containsKey(ch)) {
                return results; // Prefix not found
            }
            current = current.children.get(ch);
        }

        // Collect all branches starting from this prefix node via DFS
        collectAllWords(current, prefix.toLowerCase(), results);
        return results;
    }

    private void collectAllWords(TagTrieNode current, String currentPrefix, List<String> results) {
        if (current == null) return;

        if (current.isEndOfWord) {
            results.add(currentPrefix);
        }

        for (Map.Entry<Character, TagTrieNode> entry : current.children.entrySet()) {
            collectAllWords(entry.getValue(), currentPrefix + entry.getKey(), results);
        }
    }
}

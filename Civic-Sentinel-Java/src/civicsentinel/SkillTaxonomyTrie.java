package civicsentinel;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Skill Taxonomy Prefix Tree (Trie).
 * Used by the Labor Absorption Engine to match public works and micro-enterprise
 * job requisitions to qualified local workers.
 * 
 * Allows instant O(L) retrieval of qualified citizen candidates where L is skill name length.
 */
public class SkillTaxonomyTrie {

    public static class SkillTrieNode {
        public Map<Character, SkillTrieNode> children = new HashMap<>();
        public List<Long> qualifiedCitizenIds = new ArrayList<>();
        public boolean isEndOfWord = false;
    }

    private final SkillTrieNode root;

    public SkillTaxonomyTrie() {
        this.root = new SkillTrieNode();
    }

    private String normalize(String str) {
        if (str == null) return "";
        StringBuilder clean = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            if (Character.isLetterOrDigit(ch) || ch == '-' || ch == '_') {
                clean.append(Character.toLowerCase(ch));
            }
        }
        return clean.toString();
    }

    /**
     * Inserts a skill keyword associated with a citizen.
     * Complexity: O(L) where L is length of skill string.
     */
    public void insertSkill(String rawSkill, long citizenId) {
        String skill = normalize(rawSkill);
        if (skill.isEmpty()) return;

        SkillTrieNode curr = root;
        for (int i = 0; i < skill.length(); i++) {
            char ch = skill.charAt(i);
            curr.children.putIfAbsent(ch, new SkillTrieNode());
            curr = curr.children.get(ch);
        }
        curr.isEndOfWord = true;
        curr.qualifiedCitizenIds.add(citizenId);
    }

    /**
     * Queries all citizen IDs registered with a specific skill.
     * Complexity: O(L) where L is length of skill string.
     */
    public List<Long> querySkill(String rawSkill) {
        String skill = normalize(rawSkill);
        if (skill.isEmpty()) return new ArrayList<>();

        SkillTrieNode curr = root;
        for (int i = 0; i < skill.length(); i++) {
            char ch = skill.charAt(i);
            if (!curr.children.containsKey(ch)) {
                return new ArrayList<>();
            }
            curr = curr.children.get(ch);
        }
        return new ArrayList<>(curr.qualifiedCitizenIds);
    }

    /**
     * Checks if any skill exists matching the given prefix.
     */
    public boolean startsWith(String rawPrefix) {
        String prefix = normalize(rawPrefix);
        SkillTrieNode curr = root;
        for (int i = 0; i < prefix.length(); i++) {
            char ch = prefix.charAt(i);
            if (!curr.children.containsKey(ch)) {
                return false;
            }
            curr = curr.children.get(ch);
        }
        return true;
    }
}

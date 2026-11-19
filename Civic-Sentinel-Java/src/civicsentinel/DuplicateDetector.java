package civicsentinel;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * ============================================================================
 * DSA CONCEPT: INVERTED KEYWORD INDEX (HASH MAP)
 * Maps tokenized complaint keywords -> list of active issue IDs in each ward.
 * Detects near-duplicates before ticket creation in O(1) keyword lookup time.
 * ============================================================================
 */
public class DuplicateDetector {
    // Inverted Index: "wardId::keyword" -> List of Issue IDs
    private final Map<String, List<Integer>> keywordIndex;

    public DuplicateDetector() {
        this.keywordIndex = new HashMap<>();
    }

    // Helper to tokenize title/description into clean lower-case keywords
    private List<String> extractKeywords(String text) {
        List<String> tokens = new ArrayList<>();
        if (text == null) return tokens;

        String[] words = text.split("\\s+");
        for (String word : words) {
            StringBuilder cleanWord = new StringBuilder();
            for (int i = 0; i < word.length(); i++) {
                char ch = word.charAt(i);
                if (Character.isLetterOrDigit(ch)) {
                    cleanWord.append(Character.toLowerCase(ch));
                }
            }
            String kw = cleanWord.toString();
            // Skip common stop-words and short words
            if (kw.length() > 3 &&
                !kw.equals("this") && !kw.equals("that") &&
                !kw.equals("near") && !kw.equals("with")) {
                tokens.add(kw);
            }
        }
        return tokens;
    }

    // Index a newly created grievance
    public void indexGrievance(int issueId, String wardId, String title) {
        List<String> keywords = extractKeywords(title);
        for (String kw : keywords) {
            String compositeKey = wardId + "::" + kw;
            keywordIndex.computeIfAbsent(compositeKey, k -> new ArrayList<>()).add(issueId);
        }
    }

    // Check if similar issues exist in the same ward
    public List<Integer> findPotentialDuplicates(String wardId, String title) {
        List<String> keywords = extractKeywords(title);
        Map<Integer, Integer> matchCounts = new HashMap<>(); // issueId -> number of shared keywords

        for (String kw : keywords) {
            String compositeKey = wardId + "::" + kw;
            List<Integer> ids = keywordIndex.get(compositeKey);
            if (ids != null) {
                for (int id : ids) {
                    matchCounts.put(id, matchCounts.getOrDefault(id, 0) + 1);
                }
            }
        }

        // Return issues that match at least 2 significant keywords
        List<Integer> duplicateCandidates = new ArrayList<>();
        for (Map.Entry<Integer, Integer> entry : matchCounts.entrySet()) {
            if (entry.getValue() >= 2) {
                duplicateCandidates.add(entry.getKey());
            }
        }
        return duplicateCandidates;
    }
}

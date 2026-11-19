package civicsentinel;

/**
 * ============================================================================
 * OOP PILLAR 1: ABSTRACTION
 * BaseRecord is an Abstract Base Class. It cannot be directly instantiated.
 * It establishes a common interface for Complaints, Compliments, and Suggestions.
 * ============================================================================
 */
public abstract class BaseRecord {
    // ========================================================================
    // OOP PILLAR 2: ENCAPSULATION
    // Internal state variables are protected from uncontrolled external modification.
    // ========================================================================
    protected int id;
    protected RecordType type;
    protected CivicCategory category;
    protected String title;
    protected String description;
    protected String wardId;
    protected String citizenId;
    protected long timestamp;

    /**
     * Parameterized Constructor
     */
    public BaseRecord(int id, RecordType type, CivicCategory category,
                      String title, String description, String wardId, String citizenId) {
        this.id = id;
        this.type = type;
        this.category = category;
        this.title = title;
        this.description = description;
        this.wardId = wardId;
        this.citizenId = citizenId;
        this.timestamp = System.currentTimeMillis() / 1000L;
    }

    // Encapsulated Getters
    public int getId() { return id; }
    public RecordType getType() { return type; }
    public CivicCategory getCategory() { return category; }
    public String getTitle() { return title; }
    public String getDescription() { return description; }
    public String getWardId() { return wardId; }
    public String getCitizenId() { return citizenId; }
    public long getTimestamp() { return timestamp; }

    // ========================================================================
    // PURE ABSTRACT METHODS (The Contract)
    // Every child class (GrievanceRecord, SuggestionRecord, etc.) MUST implement these!
    // ========================================================================
    public abstract double calculatePriorityScore();
    public abstract void displaySummary();
}

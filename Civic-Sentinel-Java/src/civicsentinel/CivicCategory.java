package civicsentinel;

/**
 * Municipal problem sectors.
 */
public enum CivicCategory {
    SANITATION("Sanitation & Waste Management"),
    ROADS_INFRASTRUCTURE("Roads & Civil Infrastructure"),
    WATER_SUPPLY("Drinking Water Supply & Drainage"),
    HEALTHCARE("Public Healthcare & Clinics"),
    ELECTRICITY("Power Grid & Street Lighting"),
    PUBLIC_TRANSPORT("Public Bus & Transit Network"),
    COMMERCE_MARKETS("Local Commercial Markets & Trade"),
    GENERAL_POLICY("General Civic Development Policy");

    private final String displayName;

    CivicCategory(String displayName) {
        this.displayName = displayName;
    }

    public String getDisplayName() {
        return displayName;
    }

    @Override
    public String toString() {
        return displayName;
    }

    public static CivicCategory fromOrdinal(int ordinal) {
        CivicCategory[] values = CivicCategory.values();
        if (ordinal >= 0 && ordinal < values.length) {
            return values[ordinal];
        }
        return GENERAL_POLICY;
    }
}

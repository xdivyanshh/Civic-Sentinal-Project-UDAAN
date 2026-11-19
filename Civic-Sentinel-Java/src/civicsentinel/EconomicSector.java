package civicsentinel;

/**
 * Sectoral classification of macroeconomic crises.
 * Ensures domain-separated priority queues so different crises receive
 * specialized autonomous fiscal/monetary interventions.
 */
public enum EconomicSector {
    UNEMPLOYMENT_SPIKE("UNEMPLOYMENT_SPIKE"), // Chronic or seasonal joblessness
    PDS_FOOD_SECURITY("PDS_FOOD_SECURITY"),   // Fair Price Shop grain shortages / supply-chain failure
    DEBT_USURY_CRISIS("DEBT_USURY_CRISIS"),   // Predatory lending, micro-debt insolvency
    MARKET_INFLATION("MARKET_INFLATION");     // Price gouging or essential commodity inflation

    private final String displayName;

    EconomicSector(String displayName) {
        this.displayName = displayName;
    }

    public String getDisplayName() {
        return displayName;
    }

    @Override
    public String toString() {
        return displayName;
    }
}

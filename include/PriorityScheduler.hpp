#ifndef PRIORITY_SCHEDULER_HPP
#define PRIORITY_SCHEDULER_HPP

#include <queue>
#include <vector>
#include <memory>
#include "BaseRecord.hpp"

using namespace std;

namespace CivicSentinel {

// ============================================================================
// DSA CONCEPT: CUSTOM COMPARATOR FOR BINARY MAX-HEAP
// The Max-Heap uses this functor to compare two polymorphic record pointers.
// In C++ priority_queue, returning true means 'a' has LESS priority than 'b'
// (so 'b' stays higher up towards the root).
// ============================================================================
struct RecordPriorityComparator {
    bool operator()(const shared_ptr<BaseRecord>& a, const shared_ptr<BaseRecord>& b) const {
        return a->calculatePriorityScore() < b->calculatePriorityScore();
    }
};

// ============================================================================
// OOP WRAPPER (ENCAPSULATION & ABSTRACTION)
// Outside code never touches the raw priority_queue directly.
// ============================================================================
class PriorityScheduler {
private:
    // Binary Max-Heap storing polymorphic smart pointers: O(N) space
    priority_queue<
        shared_ptr<BaseRecord>, 
        vector<shared_ptr<BaseRecord>>, 
        RecordPriorityComparator
    > maxHeap;

public:
    // Insert new grievance into Heap: O(log N)
    void schedule(shared_ptr<BaseRecord> record) {
        maxHeap.push(record);
    }

    // Inspect the top crisis without removing it: O(1)
    shared_ptr<BaseRecord> peekHighestPriority() const {
        if (maxHeap.empty()) return nullptr;
        return maxHeap.top();
    }

    // Extract the most urgent crisis for the municipal team to resolve: O(log N)
    shared_ptr<BaseRecord> popHighestPriority() {
        if (maxHeap.empty()) return nullptr;
        shared_ptr<BaseRecord> topRecord = maxHeap.top();
        maxHeap.pop();
        return topRecord;
    }

    bool isEmpty() const { return maxHeap.empty(); }
    size_t size() const { return maxHeap.size(); }
};

} // namespace CivicSentinel

#endif // PRIORITY_SCHEDULER_HPP
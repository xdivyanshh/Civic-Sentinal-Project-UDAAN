# CIVIC-SENTINEL: Project Learning Log & Chapter Progress

**Project:** Civic-Sentinel (PBL / Data Structures Lab)  
**Developers:** Divyansh Agarwal & Arjun Bhardwaj  
**Purpose:** Living reference document capturing all concepts discussed, questions answered, and chapter-by-chapter implementation milestones.

---

## 🗺️ Chapter-Wise Progress Tracker

| Chapter | Topic & Milestone | Status | Key Concepts Covered |
| :--- | :--- | :---: | :--- |
| **Chapter 1** | **Foundational Vocabulary & Environment Setup** | 🟡 *In Progress* | `Enums.hpp`, Namespaces, Header Guards, Compile-time safety. |
| **Chapter 2** | **Abstract Base Class & Domain Design** | ⚪ *Next* | `BaseRecord.hpp`, Abstraction (pure virtual), Encapsulation. |
| **Chapter 3** | **Concrete Records & Specialization** | ⚪ *Queued* | `GrievanceRecord.hpp`, Inheritance, Polymorphic priority scoring. |
| **Chapter 4** | **The Max-Heap Dynamic Priority Scheduler** | ⚪ *Queued* | `std::priority_queue`, Custom multi-factor comparator, O(log N) scheduling. |
| **Chapter 5** | **Anti-Sybil Deduplication Vault** | ⚪ *Queued* | `std::unordered_set`, Hash tables, O(1) single-vote integrity. |
| **Chapter 6** | **Finite State Machine (FSM) Lifecycle** | ⚪ *Queued* | Directed graph transitions (OPEN -> IN_PROGRESS -> RESOLVED -> VERIFIED). |
| **Chapter 7** | **Telemetry & Politician Evaluation Engine** | ⚪ *Queued* | `std::map` (Red-Black Tree), Range queries, 0–100 composite scorecard formula. |
| **Chapter 8** | **Field Portal Integration & Trie Search** | ⚪ *Queued* | Prefix Trie autocomplete, Inverted Index duplicate check, CLI HUD. |

---

## 💡 Question & Discussion Log

### Q1: Why did we use `namespace CivicSentinel`?
* **Concept:** Code surname / container.
* **Why it matters:** Prevents naming collisions. If another library or file has a common name like `State` or `Queue`, wrapping our code in `namespace CivicSentinel` ensures `CivicSentinel::LifecycleState` never clashes with outside code.

---

### Q2: What is `enum class`?
* **Concept:** A strongly-typed, scoped custom dropdown menu.
* **Why it matters:** Instead of using dangerous random integers (`0, 1, 2`) or error-prone strings (`"OPEN"`), an `enum class` forces a variable to accept *only* the specific choices you explicitly list out.

---

### Q3: What do the words under the enums represent?
* **Concept:** Enumerators (named integer constants).
* **Why it matters:** To humans, they read like English words (`LOW`, `CRITICAL`, `OPEN`). Behind the scenes, the computer assigns them sequential integer values (`1, 2, 3...`), giving you high speed without confusing "magic numbers."

---

### Q4: Why not just use strings instead of `enum class`? What happens if someone types `"red"` vs `"RED"`?
* **Concept:** **Compile-Time vs. Runtime Errors.**
* **The Difference:**
  * **With Strings:** Typing `"red"` instead of `"RED"` compiles fine. The code runs, the `if` check silently fails, and you get a hidden bug at **runtime** in front of your professor.
  * **With `enum class`:** Typing `SeverityLevel::red` causes a **compile-time error**. Red squiggly lines appear in VS Code immediately, and the compiler refuses to build until you fix it.
  * **Bonus:** You get instant IDE autocomplete (IntelliSense) when typing `SeverityLevel::`.

---

### Q5: What is `inline` and why is it used?
* **Concept:** Linker guard + performance optimization.
* **Why it matters:** 
  1. If a function is defined in a header file included by multiple `.cpp` files, `inline` tells the linker: *"Merge duplicate copies; do not throw a multiple definition error."*
  2. It hints to the CPU to paste the short function body directly where called instead of incurring function-call jump overhead.

---

### Q6: What are `#ifndef`, `#define`, and `#endif`? (Header Guards)
* **Concept:** Preprocessor Security Checkpoint.
* **Syntax:**
  ```cpp
  #ifndef ENUMS_HPP  // "If not defined ENUMS_HPP..."
  #define ENUMS_HPP  // "...then define it now"
  // ... your code ...
  #endif             // "...end of the guard block"
  ```
* **Why it matters:** Prevents duplicate compilation crashes. If two files both include `Enums.hpp`, the preprocessor pastes it the first time, defines the token, and completely skips it the second time.

---

### Q7: What is the difference between `.hpp` and `.cpp`?
* **The Restaurant Analogy:**
  * **`.hpp` (Header): The Menu.** Contains declarations—tells the world *what* exists (class layout, function prototypes, enums) without execution details.
  * **`.cpp` (Source): The Kitchen.** Contains implementation—the actual algorithms, loops, logic, and `main()`.
* **Why not put everything in `.cpp`?** If you `#include` a `.cpp` file in another `.cpp`, the compiler builds two copies of the same code and the linker crashes with `multiple definition of ...`. Headers allow Arjun and Divyansh to share blueprints without duplicating code.

---

*This document will be updated after every discussion and milestone.*

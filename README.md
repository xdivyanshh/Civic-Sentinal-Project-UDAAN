# CIVIC-SENTINEL

**An Automated Democratic Accountability, Citizen Grievance Prioritization & Regional Socio-Economic Growth Evaluation Engine**

Academic Project for **Data Structures Lab (15B17CI371)**  
Jaypee Institute of Information Technology (JIIT), Noida  
Semester 3, Batch B2

---

## 👥 Contributors & Branch Workflow

* **Divyansh Agarwal (`main` branch)**: Core Engine, Dynamic Priority Scheduler (Max-Heap), Anti-Sybil Hash Vault, Finite State Machine, and Politician Rating Engine.
* **Arjun Bhardwaj (`feature/field-portal` branch)**: Frontline Citizen Operations, Field Intake (Complaints, Compliments, Suggestions), Prefix Trie Autocomplete, and Duplicate Detection Index.

---

## 🛠️ Project Structure

```text
Civic-Sentinel/
├── include/
│   ├── Enums.hpp        # Core enumerations and system types
│   └── BaseRecord.hpp   # Abstract Base Class (Abstraction & Encapsulation)
├── src/
│   └── main.cpp         # System entry point
├── .gitignore
├── PROJECT_NOTES_AND_PROGRESS.md
└── README.md
```

---

## 🚀 How to Build & Run

Ensure you have MinGW / GCC installed:

```powershell
g++ -std=c++14 -I include src/main.cpp -o civic_sentinel.exe
./civic_sentinel.exe
```

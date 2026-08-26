# Cashier, Inventory & Billing Management System (C)

A modular Point of Sale (POS) and inventory management console application implemented in C[cite: 14]. The system coordinates user authentication, stock tracking, transaction processing, and sales ledgering using file-based flat-database persistence and custom formatted stream parsers.

---

### Architecture & System Modules

The application is architected into three functional tiers with role-based authorization:

text
               +----------------------------------------+
               |              Login Screen              |
               |  (3-Attempt Lockout & Credential Auth) |
               +-------------------+--------------------+
                                   |
                                   v
               +----------------------------------------+
               |               Main Menu                |
               +---------+--------------+---------------+
                         |              |               |
                         v              v               v
            +----------------+  +---------------+  +----------------+
            | User Mgmt Tier |  | Product Tier  |  |  Billing Tier  |
            | (RBAC Access)  |  | (Stock & Qty) |  | (Multi-Product)|
            +----------------+  +---------------+  +----------------+
                         |              |               |
                         +--------------+---------------+
                                        |
                                        v
                       +--------------------------------+
                       |   Custom Delimited File I/O    |
                       | (#//# Custom Record Packaging) |
                       +--------------------------------+

Key Capabilities
1- Role-Based Access Control (RBAC): Restricts high-privilege operations (such as user management and administrative audits) strictly to authorized access tiers[cite: 14, 15].
2- Defensive Input Parsing: A generalized manageInput() validation engine handles integer, floating-point, and string streams while flushing stdin buffer garbage to eliminate trailing newlines and overflow bugs.
3- Deterministic File Persistence: Records are serialized into delimited flat files (#//# delimiter) using streaming fscanf/fprintf operations, preventing in-memory data loss upon application exit[cite: 14, 15].
4- Multi-Item Invoice Generation: Generates pseudo-randomized collision-checked bill IDs, calculates compound multi-product transactions, and updates employee transaction metrics in real time[cite: 14, 15].

Module Hierarchy & Implementation DetailsSubsystemPrimary ResponsibilitiesCore File InterfacesAuthentication & RBACUser verification, 3-attempt brute-force protection, permission checking.  login(), check_Accessibility(), users.txt  User ManagementCRUD operations on employee records, authorization level mapping, salary tracking[cite: 14, 15].add_user(), delete_user(), update_user(), read_users()  Product & StockSKU validation, pricing modification, unit addition, inventory display[cite: 14, 15].add_product(), delete_product(), update_product(), products.txt  Billing & Sales EngineDynamic invoice creation, quantity checking, revenue calculation, historical receipt querying[cite: 14, 15].add_sale_bill(), show_sale_bills(), sale_bills.txt  [cite: 14, 15]

Data Models (struct Definition):
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity_in_storage;
} Product;

typedef struct {
    int id;
    char name[50];
    char phone[50];
    int access; // Binary access level flag
    char password[50];
    float salary;
} User;

typedef struct {
    int bill_no;
    char date_time[50];
    User user;
    Product product;
    float price;
} Bill;


Build Instructions:
# Clone the repository
git clone [https://github.com/your-username/cashier-inventory-billing-system-c.git](https://github.com/your-username/cashier-inventory-billing-system-c.git)
cd cashier-inventory-billing-system-c

# Compile with GCC
gcc src/main.c -o build/cashier_system.exe

# Run the binary
./build/cashier_system.exe


Academic Reference
Developed for NMJ11004: Computer Programming, Faculty of Electronic Engineering & Technology, Universiti Malaysia Perlis (UniMAP)[cite: 14].

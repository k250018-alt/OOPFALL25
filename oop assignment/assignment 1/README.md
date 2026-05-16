# A2-[StudentID] — Vehicle Marketplace System
### OOP Assignment 2 | PakWheels.com Replication in C++

---

## 📁 Repository Structure

```
A2-[StudentID]/
│
├── vehicle_marketplace.cpp     ← Complete single-file C++ source code
├── README.md                   ← This documentation file
```

---

## 🌐 Website Replicated: [PakWheels.com](https://www.pakwheels.com)

PakWheels is Pakistan's #1 automobile marketplace where sellers post vehicle ads,
buyers browse and purchase vehicles, and admins moderate all listings.

---

## 📌 Table of Contents

1. [Vehicle Listings / Inventory](#1-vehicle-listings--inventory)
2. [Search & Filter System](#2-search--filter-system)
3. [User Roles — Admin, Seller, Buyer](#3-user-roles--admin-seller-buyer)
4. [Messaging System](#4-messaging-system)
5. [Favourites / Saved Listings](#5-favourites--saved-listings)
6. [Listing Approval Workflow](#6-listing-approval-workflow)
7. [OOP Concept Mapping](#7-oop-concept-mapping)

---

## 1. Vehicle Listings / Inventory

### 🌐 PakWheels Screenshot


![PakWheels Used Cars Listings]([web screenshots/listing.png](https://github.com/k250018-alt/OOPFALL25/blob/9c958ca7a68c12f2053e5e2a3b39e29e042a56fc/oop%20assignment/assignment%201/web%20screenshots/listing.png))

> **What PakWheels shows on each listing card:**
> Make · Model · Year · Price (PKR) · Mileage (km) · Engine CC · Fuel Type · Transmission · City · Condition (New/Used)

---

### 💻 Code Snippet — Vehicle & Inventory Classes

The four inventory tabs on PakWheels (Used Cars, New Cars, Used Bikes, New Bikes)
are replicated using four inventory objects inside `MainMenu`:

```cpp
// Four inventory instances inside MainMenu — mirrors PakWheels' four tabs
Cars_Inventory* usedCars  = new Cars_Inventory(true,  "Used Cars");
Cars_Inventory* newCars   = new Cars_Inventory(false, "New Cars");
Bike_Inventory* usedBikes = new Bike_Inventory(true,  "Used Bikes");
Bike_Inventory* newBikes  = new Bike_Inventory(false, "New Bikes");
```

Each listing card's data fields are replicated in the `Car` class:

```cpp
class Car : public Vehicle {
    string brand;        // Make   (e.g. Honda, Toyota)
    int    mileage;      // Mileage in km
    int    numDoors;     // Body type indicator
    string transmission; // Manual / Automatic
    // Inherited from Vehicle:
    //   model, color, vehicleID (const), is_used, engine, price, year
};

class Engine {
    const string fuelType;           // Petrol / Diesel / Electric / Hybrid
    const string cylinderConfiguration;
    const int    numberOfCylinders;
    const string ignitionType;
    const double displacement;       // Engine CC (stored as litres)
    const int    horsepower;
};
```

Inventory owns its vehicles via dynamic allocation (composition):

```cpp
void addCar(const Car& car) {
    if (car.getIsUsed() != isUsed) {
        cout << "Condition mismatch.\n"; return;
    }
    cars[count++] = new Car(car);   // deep copy — inventory owns it
    cout << "Car added to " << inventoryName << ".\n";
}
```

---

### 🧠 Reasoning

- **Four separate inventory objects** mirror PakWheels' four distinct tabs. A condition check (`car.getIsUsed() != isUsed`) ensures a Used Car cannot be added to the New Cars inventory — replicating PakWheels' validation.
- **Composition** is used because when a listing is deleted on PakWheels, the vehicle data disappears too. Our inventory uses `new Car(car)` and deletes in the destructor, modelling that same ownership.
- **Engine as a value member** inside Vehicle means an engine cannot exist without a vehicle — true composition, matching real-world logic.

---

## 2. Search & Filter System

### 🌐 PakWheels Screenshot



![PakWheels Search Filter Sidebar](<img width="199" height="240" alt="image" src="https://github.com/user-attachments/assets/6c95f9d2-973f-4c07-98d9-4262e83d4c86" />
)

> **PakWheels live filter data (Feb 2025):**
> Make: Suzuki 439 | Toyota 246 | Honda 215 | Haval 180
> Transmission: Automatic 1,304 | Manual 262
> City: Lahore 434 | Karachi 310 | Islamabad 271

---

### 💻 Code Snippet — Filter Methods

```cpp
// Brand filter — mirrors PakWheels 'Make' sidebar
void filterByBrand(const string& brand) const {
    bool found = false;
    for (int i = 0; i < count; i++)
        if (cars[i] && cars[i]->matchesBrand(brand))
            { cars[i]->display(); found = true; }
    if (!found) cout << "No cars found for brand: " << brand << "\n";
}

// Price range — mirrors PakWheels 'Price Range' slider
void filterByPrice(double lo, double hi) const {
    bool found = false;
    for (int i = 0; i < count; i++)
        if (cars[i] && cars[i]->isInPriceRange(lo, hi))
            { cars[i]->display(); found = true; }
    if (!found) cout << "No cars in price $" << lo << "-$" << hi << "\n";
}

// Year range, Mileage range, Model — same pattern
void filterByYear(int lo, int hi)        const { ... }
void filterByMileage(int lo, int hi)     const { ... }
void filterByModel(const string& model)  const { ... }
```

System-wide search across all inventories (mirrors searching all listings):

```cpp
void MainMenu::searchCarsByBrand(const string& b) const {
    cout << "\n── New Cars ──\n";  newCars->filterByBrand(b);
    cout << "\n── Used Cars ──\n"; usedCars->filterByBrand(b);
}
```

Filter predicates live on the base `Vehicle` class:

```cpp
bool isInPriceRange(double lo, double hi) const { return price >= lo && price <= hi; }
bool isInYearRange(int lo, int hi)        const { return year  >= lo && year  <= hi; }
bool matchesModel(const string& m)        const { return model == m; }

// Car adds:
bool matchesBrand(const string& b)        const { return brand == b; }
bool isInMileageRange(int lo, int hi)     const { return mileage >= lo && mileage <= hi; }
```

---

### 🧠 Reasoning

- **Filter methods on the inventory class** match PakWheels' behaviour: filters operate at the results-list level, not on individual vehicles. The inventory iterates its collection and displays matches.
- **Predicate helpers on Vehicle** (`matchesBrand`, `isInPriceRange`) follow the Single Responsibility Principle — the vehicle knows its own data; the inventory decides what to show.
- **`const` correctness** on all filter methods ensures searching never accidentally modifies inventory data.

---

## 3. User Roles — Admin, Seller, Buyer

### 🌐 PakWheels Screenshot


![PakWheels Sell Car Page](<img width="861" height="547" alt="image" src="https://github.com/user-attachments/assets/5c8404c6-ab18-4be0-b5f1-b2aa4fa8b8b1" />
)
![PakWheels Buyer View](<img width="1236" height="531" alt="image" src="https://github.com/user-attachments/assets/5b166e70-79c8-4756-a8c0-7ebed7a79460" />
)

---

### 💻 Code Snippet — Inheritance Hierarchy

```cpp
class User {                          // Base — shared by all roles
protected:
    string name, email, password, phone, registeredDate;
    Inbox  inbox;                     // every user has an inbox (composition)
    static int totalUsers;            // system-wide count (static)
public:
    virtual void displayProfile() const = 0; // each role displays differently
    void receiveMessage(const Message& msg) { inbox.addMessage(msg); }
};

class Admin  : public User { /* approval, inventory management */ };
class Seller : public User { /* post ads, message buyers       */ };
class Buyer  : public User { /* browse, favourite, purchase    */ };
```

Admin approving/rejecting — mirrors PakWheels' 4-6 hour review:

```cpp
void Admin::approveListing(int listingID) {
    for (int i = 0; i < listingCount; i++)
        if (listings[i] && listings[i]->getListingID() == listingID)
            { listings[i]->approve(); actionsPerformed++; return; }
}

void Admin::rejectListing(int listingID, const string& reason) {
    for (int i = 0; i < listingCount; i++)
        if (listings[i] && listings[i]->getListingID() == listingID)
            { listings[i]->reject(reason); actionsPerformed++; return; }
}
```

Seller posting an ad — mirrors PakWheels' "Post an Ad" flow:

```cpp
// PakWheels flow: Register → Login → Post Ad → Fill form → Submit → Wait for review
// Our flow:       Create Seller → submitCarListing() → Admin reviews → approve/reject

Listing* MainMenu::submitCarListing(Seller& seller, const Car& car) {
    if (car.getIsUsed()) usedCars->addCar(car);
    else                 newCars->addCar(car);
    Listing* l = new Listing(car.getID(), "Car", seller.getName(), "2025-01-01");
    admin->registerListing(l);   // sent to admin review queue
    return l;
}
```

---

### 🧠 Reasoning

- **Inheritance over a role flag** — PakWheels has fundamentally different capabilities per role. A buyer cannot approve listings; a seller cannot inspect other sellers' cars. Inheritance enforces this at compile time — each subclass only exposes its own operations.
- **`virtual displayProfile()`** — polymorphism ensures each role's profile page looks different, matching how PakWheels shows different dashboards per user type.
- **`static int totalUsers`** — one counter shared across all User subclass instances, mirroring PakWheels' "3 million buyers/month" system-wide statistic.

---

## 4. Messaging System

### 🌐 PakWheels Screenshot


![PakWheels Send Message Button](<img width="324" height="271" alt="image" src="https://github.com/user-attachments/assets/4bafb607-fa89-402c-b4e8-0659d9c7b34a" />
)

> PakWheels pre-fills the message with: *"Is this still available?"*
> Messages are linked to the specific listing and delivered to seller's inbox.

---

### 💻 Code Snippet — Message & Inbox Classes

```cpp
class Message {
    const int    messageID;        // unique, auto-incremented via static counter
    const string senderName;       // who sent it (const — cannot be changed)
    const string receiverName;     // who receives it
    string       content;          // message body
    bool         isRead;           // read receipt (mirrors unread badge)
    string       timestamp;
    int          relatedVehicleID; // links message to specific listing
    static int   messageCount;     // global counter for unique IDs
};

class Inbox {
    Message* messages[maxMessages]; // owns Message objects (composition)
    int      count;
    int      unreadCount;           // mirrors unread badge in PakWheels app
public:
    void addMessage(const Message& msg) {
        messages[count++] = new Message(msg);
        unreadCount++;
    }
    void markAllRead()     { ... }
    void displayUnread()   { ... }
    void deleteMessage(int id) { ... }
};
```

Sending and receiving a message between Buyer and Seller:

```cpp
// Buyer sends — mirrors clicking 'Send Message' on PakWheels listing
void Buyer::sendMessage(const string& receiverName, const string& content,
                        const string& timestamp, User& receiver, int vehicleID) {
    Message msg(name, receiverName, content, timestamp, vehicleID);
    receiver.receiveMessage(msg);  // delivered directly to seller's inbox
}

// Usage in main():
buyer.sendMessage(seller.getName(),
    "Is the Civic #101 available? Can you negotiate?",
    "2025-01-10 10:00", seller, 101);

seller.sendMessage(buyer.getName(),
    "Yes it's available! Best price is $27,000.",
    "2025-01-10 10:30", buyer, 101);
```

---

### 🧠 Reasoning

- **`Inbox` as a composition member of `User`** — on PakWheels your inbox is permanently tied to your account. We model this as a value member `Inbox inbox` inside `User`. When the User is destroyed, the Inbox (and all its Messages) are destroyed too.
- **`relatedVehicleID` inside Message** — PakWheels always shows which listing a message was sent from. Storing the vehicle ID lets the system filter messages by vehicle and display context.
- **`const` sender/receiver names** — once a message is sent, who sent it and who received it can never change. `const string senderName` enforces this at the language level.

---

## 5. Favourites / Saved Listings

### 🌐 PakWheels Screenshot


![PakWheels Favourites Heart Icon](<img width="351" height="215" alt="image" src="https://github.com/user-attachments/assets/e1271f97-9f59-4ccb-ba94-4b2c1f875d65" />
)

> **From PakWheels App Store listing:**
> *"Save your favorite used cars/bikes ads to access them later"*
> *"Create alerts and get notified"* — price-drop notifications

---

### 💻 Code Snippet — Favorites Class

```cpp
class Favorites {
    int    savedIDs[maxVehicles];    // stores vehicle IDs — NOT pointers (aggregation)
    string notes[maxVehicles];       // personal note per saved vehicle
    int    count;
    string ownerName;
    bool   notifyOnPriceChange;      // mirrors PakWheels price-drop alerts
    static int totalFavoriteActions; // system-wide analytics

public:
    void addFavorite(int vehicleID, const string& note = "") {
        for (int i = 0; i < count; i++)
            if (savedIDs[i] == vehicleID) { cout << "Already in favorites.\n"; return; }
        savedIDs[count] = vehicleID;
        notes[count++]  = note;
        totalFavoriteActions++;
    }
    void removeFavorite(int vehicleID) { ... }
    bool isFavorite(int vehicleID) const { ... }  // mirrors filled vs empty heart icon
    void displayFavorites() const { ... }
};
```

Buyer owns Favorites (composition) and usage:

```cpp
class Buyer : public User {
    Favorites favorites;   // COMPOSITION — destroyed with Buyer
};

// Usage — mirrors clicking ♡ on PakWheels listings:
buyer.saveFavorite(101, "Daily use car — check price history");
buyer.saveFavorite(103, "Tesla dream car");
buyer.saveFavorite(102, "Backup option if Civic goes");

buyer.viewFavorites();      // mirrors 'My Favourites' dashboard page
buyer.removeFavorite(102);  // mirrors removing a saved listing
buyer.isFavorite(101);      // mirrors filled vs empty heart icon
```

---

### 🧠 Reasoning

- **Storing `int` IDs instead of `Vehicle*` pointers** — PakWheels favourites are references to listings, not copies. If the seller deletes the ad, the favourite reference still exists but the vehicle is gone. Storing IDs models this correctly: `findByID(savedID)` returns `nullptr` if removed — exactly how PakWheels behaves.
- **`notifyOnPriceChange` flag** — PakWheels lets users "Create alerts and get notified" when prices change. This flag per-instance models that a buyer can toggle notifications for their saved list.
- **`totalFavoriteActions` static** — mirrors PakWheels' system-wide analytics tracking how many saves have been made across all users.

---

## 6. Listing Approval Workflow

### 🌐 PakWheels Screenshot

![PakWheels Ad Review Process](<img width="1138" height="416" alt="image" src="https://github.com/user-attachments/assets/95f0b205-b7a9-49a1-8129-c5548f6acd5b" />
)

> **From PakWheels official documentation:**
> *"Your ad will be reviewed by team PakWheels and after reviewing, it will be visible within 4-6 hours."*

---

### 💻 Code Snippet — Listing Class & Approval Workflow

```cpp
enum class ListingStatus { PENDING, APPROVED, REJECTED };

class Listing {
    const int     listingID;        // permanent unique ID, auto-incremented
    int           vehicleID;
    string        vehicleType;      // "Car" or "Bike"
    string        sellerName;
    ListingStatus status;           // PENDING → APPROVED or REJECTED
    string        rejectionReason;  // filled when rejected
    static int    listingCount;     // global ID counter

public:
    void approve() {
        status = ListingStatus::APPROVED;
        cout << "Listing #" << listingID << " approved.\n";
    }
    void reject(const string& reason) {
        status = ListingStatus::REJECTED;
        rejectionReason = reason;
        cout << "Listing #" << listingID << " rejected. Reason: " << reason << "\n";
    }
};
```

Full approval workflow matching PakWheels' process:

```cpp
// STEP 1: Seller submits → status automatically = PENDING
Listing* l1 = system.submitCarListing(seller, civicNew);
Listing* l2 = system.submitCarListing(seller, corrolla);
Listing* l4 = system.submitBikeListing(seller, hondaUsed);

// STEP 2: Admin views the pending queue
admin.viewAllListings();
// Output:
// [Listing #1] Car ID:101  Seller: Bob  Status: Pending
// [Listing #2] Car ID:102  Seller: Bob  Status: Pending

// STEP 3: Admin approves or rejects
admin.approveListing(l1->getListingID()); // → Status: Approved
admin.approveListing(l2->getListingID()); // → Status: Approved
admin.rejectListing(l4->getListingID(), "Duplicate listing");
// Output: Listing #4 rejected. Reason: Duplicate listing

// STEP 4: Admin removes a live listing at any time
admin.removeCarFromInventory(system.getNewCars(), 103);
```

Aggregation between Admin and Listing:

```cpp
class Admin : public User {
    Listing* listings[maxVehicles]; // AGGREGATION — Admin references, does NOT own
    // MainMenu creates and deletes Listing objects
public:
    void registerListing(Listing* l) {   // receives pointer, doesn't own it
        if (listingCount < maxVehicles) listings[listingCount++] = l;
    }
};
```

---

### 🧠 Reasoning

- **`listingID` is `const int`** — PakWheels assigns a permanent AD ID that never changes even if rejected. `const int` set via `++listingCount` in the constructor enforces this — it cannot be modified after creation.
- **`enum class ListingStatus`** — strongly-typed enum prevents invalid status values. A listing can only be PENDING, APPROVED, or REJECTED — no other state is possible.
- **Aggregation between Admin and Listing** — on PakWheels the moderation team reviews listings but listings belong to the platform. If an admin account is deleted, listings remain. `Admin` holds `Listing*` pointers (aggregation) while `MainMenu` owns and deletes them.

---

## 7. OOP Concept Mapping

| OOP Concept | PakWheels Behaviour | Our Implementation |
|---|---|---|
| **Inheritance** | Different capabilities per user role | `User → Admin / Seller / Buyer` |
| **Polymorphism** | Listing card looks different for Car vs Bike | `display()` pure virtual in Vehicle, overridden in Car & Bike |
| **Composition** | Inbox tied to account; Engine part of vehicle | `User` owns `Inbox`; `Vehicle` owns `Engine` (value members) |
| **Aggregation** | Admin reviews listings but doesn't own them | `Admin` holds `Listing*` pointers; `MainMenu` owns/deletes them |
| **Static members** | "200,000+ listings", "3M buyers/month" | `totalCars`, `totalUsers`, `messageCount`, `listingCount` |
| **Const members** | Vehicle ID / Listing ID never change | `const int vehicleID`, `listingID`, `messageID` |
| **Const functions** | Browsing/searching doesn't modify listings | `display()`, `filterByBrand()`, `getID()` all `const` |
| **Array of objects** | List of results on search page | `Car* cars[100]` in inventory; `Message* msgs[]` in Inbox |
| **Encapsulation** | Seller cannot approve own listing | Private members; Admin-only `approve()`/`reject()` methods |
| **3 Constructors** | Different ways to create account/listing | Default, parameterized, copy ctors across all 15 classes |

---

## ⚙️ How to Compile & Run

```bash
g++ -std=c++17 vehicle_marketplace.cpp -o vehicle_marketplace
./vehicle_marketplace
```

**Expected output includes:**
- Seller submitting 4 listings
- Admin reviewing, approving 3, rejecting 1
- Admin adding vehicles directly
- All 4 inventories displayed
- Search by brand, price range, year range, mileage range
- Buyer saving 3 favourites with notes
- Buyer ↔ Seller messaging (2 messages exchanged)
- Buyer purchasing a car (budget deducted)
- Admin updating a price
- Admin removing a listing
- System stats: 3 users, 7 cars, 4 bikes, 4 messages, 4 listings

---

*OOP Assignment 2 — Vehicle Marketplace System (PakWheels replication)*

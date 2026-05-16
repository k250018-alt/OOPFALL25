#pragma once
#include <iostream>
#include <string>
#include "Cars_Inventory.h"
#include "Bike_Inventory.h"
#include "Favorites.h"
#include "Inbox.h"
#include "Listing.h"
using namespace std;

class User
{
protected:
    string name;
    string email;
    string password;
    string phone;
    string registeredDate;
    Inbox inbox;

    static int totalUsers;

public:
    User() : name("Unknown"), email("unknown@example.com"),
             password("0000"), phone("N/A"), registeredDate("N/A"),
             inbox("Unknown") { totalUsers++; }

    User(string name, string email, string password,
         string phone = "N/A", string date = "N/A") : name(name), email(email), password(password),
                                                      phone(phone), registeredDate(date),
                                                      inbox(name) { totalUsers++; }

    User(const User &other) : name(other.name), email(other.email), password(other.password),
                              phone(other.phone), registeredDate(other.registeredDate),
                              inbox(other.name) { totalUsers++; }

    virtual ~User() { totalUsers--; }

    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    string getRegisteredDate() const { return registeredDate; }
    static int getTotalUsers() { return totalUsers; }

    void setPhone(const string &p) { phone = p; }
    void setPassword(const string &p) { password = p; }

    void seeCarsInventory(const Cars_Inventory &inv) const
    {
        inv.displayCarsInventory();
    }

    void seeBikeInventory(const Bike_Inventory &inv) const
    {
        inv.displayBikeInventory();
    }

    void receiveMessage(const Message &msg)
    {
        inbox.addMessage(msg);
    }

    void viewInbox()
    {
        inbox.displayAll();
    }

    void viewInbox(const Inbox &otherInbox) const
    {
        otherInbox.displayAll();
    }

    Inbox &getInbox() { return inbox; }

    virtual void displayProfile() const
    {
        cout << "User: " << name << " | Email: " << email
             << " | Phone: " << phone << "\n";
    }
};
int User::totalUsers = 0;

class Admin : public User
{
    string adminLevel;
    bool canDeleteUsers;
    int actionsPerformed;
    Listing *listings[maxVehicles];
    int listingCount;

public:
    Admin() : User(), adminLevel("Moderator"),
              canDeleteUsers(false), actionsPerformed(0), listingCount(0)
    {
        for (int i = 0; i < maxVehicles; i++)
            listings[i] = nullptr;
    }

    Admin(string name, string email, string password,
          string level = "Moderator", bool canDelete = false) : User(name, email, password),
                                                                adminLevel(level), canDeleteUsers(canDelete),
                                                                actionsPerformed(0), listingCount(0)
    {
        for (int i = 0; i < maxVehicles; i++)
            listings[i] = nullptr;
    }

    string getAdminLevel() const { return adminLevel; }
    int getActionsPerformed() const { return actionsPerformed; }
    void setAdminLevel(const string &l) { adminLevel = l; }

    void addCarToInventory(Cars_Inventory &inv, const Car &car)
    {
        inv.addCar(car);
        actionsPerformed++;
    }
    void removeCarFromInventory(Cars_Inventory &inv, int vehicleID)
    {
        inv.removeCar(vehicleID);
        actionsPerformed++;
    }
    void updateCarInInventory(Cars_Inventory &inv, int vehicleID, const Car &updated)
    {
        inv.updateCar(vehicleID, updated);
        actionsPerformed++;
    }
    void addBikeToInventory(Bike_Inventory &inv, const Bike &bike)
    {
        inv.addBike(bike);
        actionsPerformed++;
    }
    void removeBikeFromInventory(Bike_Inventory &inv, int vehicleID)
    {
        inv.removeBike(vehicleID);
        actionsPerformed++;
    }
    void updateBikeInInventory(Bike_Inventory &inv, int vehicleID, const Bike &updated)
    {
        inv.updateBike(vehicleID, updated);
        actionsPerformed++;
    }

    void registerListing(Listing *listing)
    {
        if (listingCount < maxVehicles)
        {
            listings[listingCount++] = listing;
        }
    }

    void approveListing(int listingID)
    {
        for (int i = 0; i < listingCount; i++)
            if (listings[i] != nullptr && listings[i]->getListingID() == listingID)
            {
                listings[i]->approve();
                actionsPerformed++;
                return;
            }
        cout << "Listing #" << listingID << " not found.\n";
    }

    void rejectListing(int listingID, const string &reason)
    {
        for (int i = 0; i < listingCount; i++)
            if (listings[i] != nullptr && listings[i]->getListingID() == listingID)
            {
                listings[i]->reject(reason);
                actionsPerformed++;
                return;
            }
        cout << "Listing #" << listingID << " not found.\n";
    }

    void viewAllListings() const
    {
        cout << "\n── All Listings (" << listingCount << ") ──\n";
        for (int i = 0; i < listingCount; i++)
            if (listings[i] != nullptr)
                listings[i]->display();
    }

    void displayProfile() const override
    {
        User::displayProfile();
        cout << "Role: Admin | Level: " << adminLevel
             << " | Actions: " << actionsPerformed << "\n";
    }
};

class Seller : public User
{
    string sellerRating;
    int totalSales;
    bool isVerified;
    string businessName;
    string location;

public:
    Seller() : User(), sellerRating("Bronze"),
               totalSales(0), isVerified(false),
               businessName("N/A"), location("N/A") {}

    Seller(string name, string email, string password,
           string businessName = "N/A", string location = "N/A") : User(name, email, password),
                                                                   sellerRating("Bronze"), totalSales(0), isVerified(false),
                                                                   businessName(businessName), location(location) {}

    string getSellerRating() const { return sellerRating; }
    int getTotalSales() const { return totalSales; }
    bool getIsVerified() const { return isVerified; }
    string getBusinessName() const { return businessName; }
    void setVerified(bool v) { isVerified = v; }
    void setSellerRating(const string &r) { sellerRating = r; }

    void addCarToInventory(Cars_Inventory &inv, const Car &car)
    {
        inv.addCar(car);
    }

    void addBikeToInventory(Bike_Inventory &inv, const Bike &bike)
    {
        inv.addBike(bike);
    }

    void removeCarListing(Cars_Inventory &inv, int vehicleID)
    {
        inv.removeCar(vehicleID);
    }

    void removeBikeListing(Bike_Inventory &inv, int vehicleID)
    {
        inv.removeBike(vehicleID);
    }

    void sendMessage(const string &receiverName, const string &content,
                     const string &timestamp, Inbox &receiverInbox, int vehicleID = -1)
    {
        Message msg(name, receiverName, content, timestamp, vehicleID);
        receiverInbox.addMessage(msg);
        cout << "Message sent to " << receiverName << ".\n";
    }

    void recordSale() { totalSales++; }

    void displayProfile() const override
    {
        User::displayProfile();
        cout << "Role: Seller | Business: " << businessName
             << " | Sales: " << totalSales
             << " | Rating: " << sellerRating
             << " | Verified: " << (isVerified ? "Yes" : "No") << "\n";
    }
};

class Buyer : public User
{
    double budget;
    Favorites favorites;
    int purchasesCount;
    string preferredType;
    bool isSubscribed;

public:
    Buyer() : User(), budget(0.0), favorites(name, false),
              purchasesCount(0), preferredType("Any"), isSubscribed(false) {}

    Buyer(string name, string email, string password,
          double budget = 0.0, string preferredType = "Any") : User(name, email, password),
                                                               budget(budget), favorites(name, false),
                                                               purchasesCount(0), preferredType(preferredType), isSubscribed(false) {}

    double getBudget() const { return budget; }
    int getPurchasesCount() const { return purchasesCount; }
    string getPreferredType() const { return preferredType; }
    bool getIsSubscribed() const { return isSubscribed; }
    void setBudget(double b) { budget = b; }
    void setSubscribed(bool s) { isSubscribed = s; }
    void setPreferredType(const string &t) { preferredType = t; }

    void saveFavorite(int vehicleID, const string &note = "")
    {
        favorites.addFavorite(vehicleID, note);
    }

    void removeFavorite(int vehicleID)
    {
        favorites.removeFavorite(vehicleID);
    }

    bool isFavorite(int vehicleID) const
    {
        return favorites.isFavorite(vehicleID);
    }

    void viewFavorites() const
    {
        favorites.displayFavorites();
    }

    void proceedToBuyCar(Cars_Inventory &inv, int vehicleID)
    {
        Car *c = inv.findByID(vehicleID);
        if (c == nullptr)
        {
            cout << "Car not found.\n";
            return;
        }
        if (c->getPrice() > budget)
        {
            cout << "Budget insufficient ($" << budget << " < $" << c->getPrice() << ").\n";
            return;
        }
        budget -= c->getPrice();
        inv.removeCar(vehicleID);
        purchasesCount++;
        cout << "Car #" << vehicleID << " purchased successfully!\n";
    }

    void proceedToBuyBike(Bike_Inventory &inv, int vehicleID)
    {
        Bike *b = inv.findByID(vehicleID);
        if (b == nullptr)
        {
            cout << "Bike not found.\n";
            return;
        }
        if (b->getPrice() > budget)
        {
            cout << "Budget insufficient.\n";
            return;
        }
        budget -= b->getPrice();
        inv.removeBike(vehicleID);
        purchasesCount++;
        cout << "Bike #" << vehicleID << " purchased successfully!\n";
    }

    void sendMessage(const string &receiverName, const string &content,
                     const string &timestamp, Inbox &receiverInbox, int vehicleID = -1)
    {
        Message msg(name, receiverName, content, timestamp, vehicleID);
        receiverInbox.addMessage(msg);
        cout << "Message sent to " << receiverName << ".\n";
    }

    void displayProfile() const override
    {
        User::displayProfile();
        cout << "Role: Buyer | Budget: $" << budget
             << " | Purchases: " << purchasesCount
             << " | Preferred: " << preferredType << "\n";
    }
};
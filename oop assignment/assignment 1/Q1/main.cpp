#include <iostream>
#include "MainMenu.h"
using namespace std;

int main()
{
    cout << "╔═══════════════════════════════════════════╗\n";
    cout << "║      VEHICLE MARKETPLACE SYSTEM           ║\n";
    cout << "╚═══════════════════════════════════════════╝\n\n";

    Admin admin("Alice Admin", "alice@admin.com", "admin123", "Super", true);
    Seller seller("Bob Seller", "bob@dealer.com", "sell456", "Bob's Motors", "Karachi");
    Buyer buyer("Charlie Buyer", "charlie@buyer.com", "buy789", 75000.0, "Car");

    Engine petrolV4("Petrol", "V4", 4, "Electronic", 2.0, 180);
    Engine dieselI4("Diesel", "Inline-4", 4, "Compression", 1.8, 140);
    Engine electricE("Electric", "N/A", 0, "Electric", 0.0, 300);
    Engine bikeEngine("Petrol", "Single", 1, "Electronic", 0.4, 40);

    Car civicNew("Civic", "White", 101, false, petrolV4, 28000.0, 2024, "Honda", 0, 4, "Automatic");
    Car corrolla("Corolla", "Red", 102, true, dieselI4, 15000.0, 2020, "Toyota", 55000, 4, "Manual");
    Car tesla("Model 3", "Black", 103, false, electricE, 55000.0, 2024, "Tesla", 0, 4, "Automatic");
    Car usedHonda("City", "Blue", 104, true, petrolV4, 12000.0, 2018, "Honda", 80000, 4, "Manual");

    Bike yamahaNew("R15", "Red", 201, false, bikeEngine, 5000.0, 2024, "Yamaha", 0, "Sport", false);
    Bike hondaUsed("CB150", "Black", 202, true, bikeEngine, 2500.0, 2019, "Honda", 30000, "Cruiser", false);

    MainMenu system(&admin, "PakWheels Clone");
    system.registerSeller(&seller);
    system.registerBuyer(&buyer);

    cout << "\n[1] SELLER ADDS LISTINGS\n";
    Listing *l1 = system.submitCarListing(seller, civicNew);
    Listing *l2 = system.submitCarListing(seller, corrolla);
    Listing *l3 = system.submitBikeListing(seller, yamahaNew);
    Listing *l4 = system.submitBikeListing(seller, hondaUsed);

    cout << "\n[2] ADMIN REVIEWS LISTINGS\n";
    admin.viewAllListings();
    admin.approveListing(l1->getListingID());
    admin.approveListing(l2->getListingID());
    admin.approveListing(l3->getListingID());
    admin.rejectListing(l4->getListingID(), "Duplicate listing");

    cout << "\n[3] ADMIN ADDS CARS DIRECTLY\n";
    admin.addCarToInventory(system.getNewCars(), tesla);
    admin.addCarToInventory(system.getUsedCars(), usedHonda);

    cout << "\n[4] ALL INVENTORIES\n";
    system.displayAllInventories();

    cout << "\n[5] SEARCH BY BRAND: Honda\n";
    system.searchCarsByBrand("Honda");

    cout << "\n[6] SEARCH BY PRICE: $10,000 - $30,000\n";
    system.searchCarsByPrice(10000, 30000);

    cout << "\n[7] SEARCH BY YEAR: 2020-2025\n";
    system.searchCarsByYear(2020, 2025);

    cout << "\n[8] FILTER USED CARS BY MILEAGE: 40000 - 90000 km\n";
    system.getUsedCars().filterByMileage(40000, 90000);

    cout << "\n[9] BUYER SAVES FAVORITES\n";
    buyer.saveFavorite(101, "Want this for daily use");
    buyer.saveFavorite(103, "Tesla dream car");
    buyer.saveFavorite(102, "Backup option");
    buyer.viewFavorites();

    cout << "\n[10] BUYER SENDS MESSAGE TO SELLER\n";
    Message msg1(buyer.getName(), seller.getName(),
                 "Interested in Civic #101 - can you negotiate?", "2025-01-10 10:00", 101);
    seller.receiveMessage(msg1);

    Message reply(seller.getName(), buyer.getName(),
                  "Yes still available! Best price is $27,000.", "2025-01-10 10:30", 101);
    buyer.receiveMessage(reply);

    seller.viewInbox();
    buyer.viewInbox();

    cout << "\n[11] BUYER PURCHASES CAR\n";
    buyer.proceedToBuyCar(system.getNewCars(), 101);
    cout << "Buyer remaining budget: $" << buyer.getBudget() << "\n";

    cout << "\n[12] ADMIN UPDATES COROLLA PRICE\n";
    Car updatedCorolla("Corolla", "Red", 102, true, dieselI4, 14000.0, 2020, "Toyota", 55000, 4, "Manual");
    admin.updateCarInInventory(system.getUsedCars(), 102, updatedCorolla);

    cout << "\n[13] ADMIN REMOVES TESLA LISTING\n";
    admin.removeCarFromInventory(system.getNewCars(), 103);

    cout << "\n[14] USER PROFILES\n";
    admin.displayProfile();
    seller.displayProfile();
    buyer.displayProfile();

    cout << "\n[15] SYSTEM STATS\n";
    system.printSystemStats();

    cout << "\n╔═══════════════════════════════════════════╗\n";
    cout << "║          PROGRAM COMPLETE                 ║\n";
    cout << "╚═══════════════════════════════════════════╝\n";

    return 0;
}
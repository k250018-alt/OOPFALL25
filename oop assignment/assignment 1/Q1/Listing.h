#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class ListingStatus
{
    PENDING,
    APPROVED,
    REJECTED
};

class Listing
{
    const int listingID;
    int vehicleID;
    string vehicleType;
    string sellerName;
    ListingStatus status;
    string rejectionReason;
    string submittedDate;

    static int listingCount;

public:
    Listing() : listingID(++listingCount), vehicleID(-1), vehicleType("Unknown"),
                sellerName("Unknown"), status(ListingStatus::PENDING),
                rejectionReason(""), submittedDate("N/A") {}

    Listing(int vehicleID, string vehicleType, string sellerName, string date) : listingID(++listingCount), vehicleID(vehicleID), vehicleType(vehicleType),
                                                                                 sellerName(sellerName), status(ListingStatus::PENDING),
                                                                                 rejectionReason(""), submittedDate(date) {}

    int getListingID() const { return listingID; }
    int getVehicleID() const { return vehicleID; }
    string getVehicleType() const { return vehicleType; }
    string getSellerName() const { return sellerName; }
    string getSubmittedDate() const { return submittedDate; }
    string getRejectionReason() const { return rejectionReason; }
    ListingStatus getStatus() const { return status; }

    static int getListingCount() { return listingCount; }

    void approve()
    {
        status = ListingStatus::APPROVED;
        cout << "Listing #" << listingID << " approved.\n";
    }

    void reject(const string &reason)
    {
        status = ListingStatus::REJECTED;
        rejectionReason = reason;
        cout << "Listing #" << listingID << " rejected. Reason: " << reason << "\n";
    }

    bool isPending() const { return status == ListingStatus::PENDING; }
    bool isApproved() const { return status == ListingStatus::APPROVED; }

    void display() const
    {
        string statusStr = (status == ListingStatus::PENDING) ? "Pending" : (status == ListingStatus::APPROVED) ? "Approved"
                                                                                                                : "Rejected";
        cout << "  [Listing #" << listingID << "] "
             << vehicleType << " ID:" << vehicleID
             << "  Seller: " << sellerName
             << "  Status: " << statusStr << "\n";
        if (status == ListingStatus::REJECTED)
            cout << "    Reason: " << rejectionReason << "\n";
    }
};
int Listing::listingCount = 0;
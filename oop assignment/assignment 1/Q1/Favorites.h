#pragma once
#include <iostream>
#include "Vehicle.h"
using namespace std;

class Favorites
{
    int savedIDs[maxVehicles];
    int count;
    string ownerName;
    bool notifyOnPriceChange;
    string notes[maxVehicles];

    static int totalFavoriteActions;

public:
    Favorites() : count(0), ownerName("Unknown"), notifyOnPriceChange(false)
    {
        for (int i = 0; i < maxVehicles; i++)
        {
            savedIDs[i] = -1;
            notes[i] = "";
        }
    }

    Favorites(const string &owner, bool notify) : count(0), ownerName(owner), notifyOnPriceChange(notify)
    {
        for (int i = 0; i < maxVehicles; i++)
        {
            savedIDs[i] = -1;
            notes[i] = "";
        }
    }

    int getCount() const { return count; }
    string getOwner() const { return ownerName; }
    bool getNotify() const { return notifyOnPriceChange; }
    void setNotify(bool n) { notifyOnPriceChange = n; }

    static int getTotalFavoriteActions() { return totalFavoriteActions; }

    void addFavorite(int vehicleID, const string &note = "")
    {
        if (count >= maxVehicles)
        {
            cout << "Favorites list full.\n";
            return;
        }
        for (int i = 0; i < count; i++)
            if (savedIDs[i] == vehicleID)
            {
                cout << "Already in favorites.\n";
                return;
            }
        savedIDs[count] = vehicleID;
        notes[count] = note;
        count++;
        totalFavoriteActions++;
        cout << "Vehicle " << vehicleID << " added to favorites.\n";
    }

    void removeFavorite(int vehicleID)
    {
        for (int i = 0; i < count; i++)
        {
            if (savedIDs[i] == vehicleID)
            {
                for (int j = i; j < count - 1; j++)
                {
                    savedIDs[j] = savedIDs[j + 1];
                    notes[j] = notes[j + 1];
                }
                count--;
                savedIDs[count] = -1;
                notes[count] = "";
                cout << "Vehicle " << vehicleID << " removed from favorites.\n";
                return;
            }
        }
        cout << "Vehicle not found in favorites.\n";
    }

    bool isFavorite(int vehicleID) const
    {
        for (int i = 0; i < count; i++)
            if (savedIDs[i] == vehicleID)
                return true;
        return false;
    }

    void displayFavorites() const
    {
        if (count == 0)
        {
            cout << "No favorites saved.\n";
            return;
        }
        cout << "── Favorites for " << ownerName << " ──\n";
        for (int i = 0; i < count; i++)
            cout << "  Vehicle ID: " << savedIDs[i]
                 << "  Note: " << (notes[i].empty() ? "N/A" : notes[i]) << "\n";
    }
};
int Favorites::totalFavoriteActions = 0;
#include <iostream>
#include <string>
using namespace std;

const int MAX_USERS = 10; 

class SocialMedia {
private:
    string userNames[MAX_USERS]; 
    bool connections[MAX_USERS][MAX_USERS]; 
    int userCount; 

public:
    SocialMedia() 
    {
        userCount = 0;
        for (int i = 0; i < MAX_USERS; i++) 
        {
            for (int j = 0; j < MAX_USERS; j++) 
            {
                connections[i][j] = false; 
            }
        }
    }

    void addUser(string name) {
        if (userCount < MAX_USERS) {
            userNames[userCount] = name;
            userCount++;
            cout << "User '" << name << "' added successfully.\n";
        } else {
            cout << "Cannot add more users. Maximum limit reached.\n";
        }
    }

    void addConnection(string name1, string name2) {
        int index1 = findUserIndex(name1);
        int index2 = findUserIndex(name2);

        if (index1 != -1 && index2 != -1) {
            connections[index1][index2] = true;
            connections[index2][index1] = true;
            cout << "Connection added between '" << name1 << "' and '" << name2 << "'.\n";
        } else {
            cout << "One or both users not found.\n";
        }
    }

    void removeConnection(string name1, string name2) {
        int index1 = findUserIndex(name1);
        int index2 = findUserIndex(name2);

        if (index1 != -1 && index2 != -1) {
            connections[index1][index2] = false;
            connections[index2][index1] = false;
            cout << "Connection removed between '" << name1 << "' and '" << name2 << "'.\n";
        } else {
            cout << "One or both users not found.\n";
        }
    }

    void suggestFriends(string name) {
        int userIndex = findUserIndex(name);

        if (userIndex == -1) {
            cout << "User '" << name << "' not found.\n";
            return;
        }

        cout << "Friend suggestions for '" << name << "':\n";
        bool hasSuggestions = false;

        for (int i = 0; i < userCount; i++) {
            if (i != userIndex && !connections[userIndex][i]) { // Not already a friend
                int mutualCount = 0;
                for (int j = 0; j < userCount; j++) {
                    if (connections[userIndex][j] && connections[i][j]) {
                        mutualCount++; // Count mutual friends
                    }
                }
                if (mutualCount > 0) {
                    cout << "- " << userNames[i] << " (" << mutualCount << " mutual friends)\n";
                    hasSuggestions = true;
                }
            }
        }

        if (!hasSuggestions) {
            cout << "No suggestions available.\n";
        }
    }

    void displayConnections() {
        cout << "\nAll Connections:\n";
        for (int i = 0; i < userCount; i++) {
            cout << userNames[i] << " -> ";
            bool hasConnections = false;
            for (int j = 0; j < userCount; j++) {
                if (connections[i][j]) {
                    cout << userNames[j] << " ";
                    hasConnections = true;
                }
            }
            if (!hasConnections) {
                cout << "No connections";
            }
            cout << "\n";
        }
    }

    void findMutualFriends(string name1, string name2) {
        int index1 = findUserIndex(name1);
        int index2 = findUserIndex(name2);

        if (index1 == -1 || index2 == -1) {
            cout << "One or both users not found.\n";
            return;
        }

        cout << "Mutual friends between '" << name1 << "' and '" << name2 << "':\n";
        bool hasMutualFriends = false;
        for (int i = 0; i < userCount; i++) {
            if (connections[index1][i] && connections[index2][i]) {
                cout << "- " << userNames[i] << "\n";
                hasMutualFriends = true;
            }
        }

        if (!hasMutualFriends) {
            cout << "No mutual friends found.\n";
        }
    }

private:
    int findUserIndex(string name) {
        for (int i = 0; i < userCount; i++) {
            if (userNames[i] == name) {
                return i;
            }
        }
        return -1; // User not found
    }
};

int main() 
{
    SocialMedia sm;
    int choice;
    string name1, name2;

        do {
        cout << "\n--- Social Media Friend Suggestion System ---\n";
        cout << "1. Add User\n";
        cout << "2. Add Connection\n";
        cout << "3. Remove Connection\n";
        cout << "4. Suggest Friends\n";
        cout << "5. Display All Connections\n";
        cout << "6. Find Mutual Friends\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline once

        switch (choice) {
        case 1:
            cout << "Enter user name: ";
            getline(cin, name1);
            sm.addUser(name1);
            break;

        case 2:
            cout << "Enter first user name: ";
            getline(cin, name1);
            cout << "Enter second user name: ";
            getline(cin, name2);
            sm.addConnection(name1, name2);
            break;

        case 3:
            cout << "Enter first user name: ";
            getline(cin, name1);
            cout << "Enter second user name: ";
            getline(cin, name2);
            sm.removeConnection(name1, name2);
            break;

        case 4:
            cout << "Enter user name: ";
            getline(cin, name1);
            sm.suggestFriends(name1);
            break;

        case 5:
            sm.displayConnections();
            break;

        case 6:
            cout << "Enter first user name: ";
            getline(cin, name1);
            cout << "Enter second user name: ";
            getline(cin, name2);
            sm.findMutualFriends(name1, name2);
            break;

        case 7:
            cout << "Exiting program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 7);


    return 0;
}

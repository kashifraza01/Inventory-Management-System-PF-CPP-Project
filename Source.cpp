#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

// Structure banayi item ke liye
struct Item {
    string name;
    int quantity;
    double price;
};

// Input clear karne ka function,   Ye crash hone se bachata hai
void clearinput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// File se data load karna,  program start hote he file read hogi
void loadfromfile(vector<Item>& inventory) {
    ifstream file("inventory.txt");
    if (!file) {
        // Agar file exist nahi karti to simply return
        return;
    }
    Item i;
    while (getline(file, i.name)) {
        file >> i.quantity;
        file >> i.price;
        file.ignore(); // newline remove karne ke liye
        inventory.push_back(i);
    }
    file.close();
}

// Data ko file me save karna, program band hone se pehle save hoga
void savetofile(const vector<Item>& inventory) {
    ofstream file("inventory.txt");
    for (const auto& i : inventory) {
        file << i.name << endl;
        file << i.quantity << endl;
        file << i.price << endl;
    }
    file.close();
}


// Naya item add karna
void additem(vector<Item>& inventory) {
    Item newitem;

    cout << "\nitem ka naam enter karein: ";
    clearInput();
    getline(cin, newitem.name);

    cout << "quantity enter karein: ";
    while (!(cin >> newitem.quantity) || newitem.quantity < 0) {
        cout << "galat input,dubara quantity enter karein: ";
        clearInput();
    }
    cout << "price enter karein: ";
    while (!(cin >> newitem.price) || newitem.price < 0) {
        cout << "galat input, dubara price enter karein: ";
        clearInput();
    }
    inventory.push_back(newitem);
    cout << "\nItem successfully add ho gaya!\n";
}
// ======================
// Inventory display karna
// ======================
void displayinventory(const vector<Item>& inventory) {
    if (inventory.empty()) {
        cout << "\nInventory khali hai.\n";
        return;
    }
    cout << "\n========= Inventory List =========\n";
    cout << left << setw(20) << "Name"
         << setw(10) << "Qty"
         << setw(10) << "Price\n";
    cout << "-----------------------------------\n";
	
    for (const auto& i : inventory) {
        cout << left << setw(20) << i.name
             << setw(10) << i.quantity
             << "$" << fixed << setprecision(2) << i.price << endl;
    }
}
// ======================
// Item search karna
// ======================
void searchitem(const vector<Item>& inventory) {
    string name;
    cout << "\nsearch karne ke liye item ka naam enter karein: ";
    clearInput();
    getline(cin, name);
	
    for (const auto& i : inventory) {
        if (item.name == name) {
            cout << "\nItem mil gaya!\n";
            cout << "Name: " << i.name << endl;
            cout << "Quantity: " << i.quantity << endl;
            cout << "Price: $" << i.price << endl;
            return;
        }
    }
    cout << "item nahi mila \n";
}
// ======================
// Quantity update karna
// ======================
void updatequantity(vector<Item>& inventory) {
    string name;
    cout << "\nUpdate ke liye item ka naam enter karein: ";
    clearInput();
    getline(cin, name);

    for (auto& item : inventory) {
        if (item.name == name) {
            cout << "Nayi quantity enter karein: ";
            while (!(cin >> item.quantity) || item.quantity < 0) {
                cout << "galat input, dubara enter karein: ";
                clearInput();
            }
            cout << "Quantity update ho gayi!\n";
            return;
        }
    }
    cout << "item nahi mila \n";
}

// ======================
// Item delete karna
// ======================
void deleteitem(vector<Item>& inventory) {
    string name;
    cout << "\nDelete ke liye item ka naam enter karein: ";
    clearInput();
    getline(cin, name);

    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == name) {
            inventory.erase(it);
            cout << "Item delete ho gaya!\n";
            return;
        }
    }
    cout << "item nahi mila \n";
}
// ======================
// Username aur password fixed rakhe hain mene
// ======================
bool adminlogin() {
    string u,p;

    cout << "===== Admin Login =====\n";
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;
	
    // Simple hardcoded login
    if (u == "admin" && p == "1234") {
        cout << "\nLogin successful!\n";
        return true;
    } else {
        cout << "\ngalat username ya password enter kia h apne\n";
        return false;
    }
}
// ======================
// Main Function
// ======================
int main() {
    vector<Item> inventory;
    // File se purana data load hoga
    loadfromfile(inventory);
    // Pehle login hoga
    if (!adminlogin()) {
        return 0; // Agar login fail to program band
	}
	
    int choice;
    do {
        cout << "\n====== Inventory Management System ======\n";
        cout << "1. Add Item\n";
        cout << "2. Display Inventory\n";
        cout << "3. Search Item\n";
        cout << "4. Update Quantity\n";
        cout << "5. Delete Item\n";
        cout << "6. Exit\n";
        cout << "Choice enter karein: ";

        while (!(cin >> choice)) {
            cout << "Galat input. Dobara number enter karein: ";
            clearInput();
        }

        switch (choice) {
            case 1: additem(inventory); break;
            case 2: displayinventory(inventory); break;
            case 3: searchitem(inventory); break;
            case 4: updatequantity(inventory); break;
            case 5: deleteitem(inventory); break;
            case 6:
                savetofile(inventory); // Exit se pehle data save
                cout << "\nprogram band ho raha hai... \n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    return 0;
}


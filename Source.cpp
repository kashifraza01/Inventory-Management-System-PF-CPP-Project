#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

// yeh structure har item ki information store karega
struct item {
    string name;
    int quantity;
    double price;
};

// yeh function input stream ko clear karta hai,  agar user galat input de to program crash nahi karega
void clearinput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// yeh function string ko lowercase mein convert karta hai,  taake comparison case insensitive ho
string tolowercase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// program start hote hi file se data load hoga
void loadfromfile(vector<item>& inventory) {
    ifstream file("inventory.txt");

    // agar file exist nahi karti to simply return
    if (!file) return;

    item i;

    while (getline(file, i.name)) {
        file >> i.quantity;
        file >> i.price;
        file.ignore();
        inventory.push_back(i);
    }
    file.close();
}

// program band hone se pehle data file mein save hoga
void savetofile(const vector<item>& inventory) {
    ofstream file("inventory.txt");

    for (const auto& i : inventory) {
        file << i.name << endl;
        file << i.quantity << endl;
        file << i.price << endl;
    }
    file.close();
}

// naya item add karne ka function
void additem(vector<item>& inventory) {
    item newitem;

    cout << "\nitem ka naam enter karein: ";
    clearinput();
    getline(cin, newitem.name);

    cout << "quantity enter karein: ";
    while (!(cin >> newitem.quantity) || newitem.quantity < 0) {
        cout << "galat input, dubara quantity enter karein: ";
        clearinput();
    }

    cout << "price enter karein: ";
    while (!(cin >> newitem.price) || newitem.price < 0) {
        cout << "galat input, dubara price enter karein: ";
        clearinput();
    }

    inventory.push_back(newitem);
    cout << "\nitem successfully add ho gaya!\n";
}

// inventory display karne ka function
void displayinventory(const vector<item>& inventory) {
    if (inventory.empty()) {
        cout << "\ninventory khali hai.\n";
        return;
    }

    cout << "\n========= inventory list =========\n";
    cout << left << setw(20) << "name"
         << setw(10) << "qty"
         << setw(10) << "price\n";
    cout << "-----------------------------------\n";

    for (const auto& i : inventory) {
        cout << left << setw(20) << i.name
             << setw(10) << i.quantity
             << "$" << fixed << setprecision(2) << i.price << endl;
    }
}

// item search karne ka function
void searchitem(const vector<item>& inventory) {
    string name;

    cout << "\nsearch ke liye item ka naam enter karein: ";
    clearinput();
    getline(cin, name);

    // user input ko lowercase mein convert kar diya
    string searchname = tolowercase(name);

    for (const auto& i : inventory) {
        // har stored name ko bhi lowercase mein convert kar rahe hain
        if (tolowercase(i.name) == searchname) {
            cout << "\nitem mil gaya!\n";
            cout << "name: " << i.name << endl;
            cout << "quantity: " << i.quantity << endl;
            cout << "price: $" << i.price << endl;
            return;
        }
    }
    cout << "item nahi mila\n";
}

// quantity update karne ka function
void updatequantity(vector<item>& inventory) {
    string name;

    cout << "\nupdate ke liye item ka naam enter karein: ";
    clearinput();
    getline(cin, name);

    string searchname = tolowercase(name);

    for (auto& i : inventory) {
        if (tolowercase(i.name) == searchname) {
            cout << "nayi quantity enter karein: ";
            while (!(cin >> i.quantity) || i.quantity < 0) {
                cout << "galat input, dobara enter karein: ";
                clearinput();
            }
            cout << "quantity update ho gayi!\n";
            return;
        }
    }
    cout << "item nahi mila\n";
}

// item delete karne ka function
void deleteitem(vector<item>& inventory) {
    string name;

    cout << "\ndelete ke liye item ka naam enter karein: ";
    clearinput();
    getline(cin, name);

    string searchname = tolowercase(name);

    for (auto it=inventory.begin(); it!=inventory.end(); ++it) {
        if (tolowercase(it->name) == searchname) {
            inventory.erase(it);
            cout << "item delete ho gaya!\n";
            return;
        }
    }
    cout << "item nahi mila\n";
}

// simple admin login system
bool adminlogin() {
    string u, p;

    cout << "===== admin login =====\n";
    cout << "username: ";
    cin >> u;
    cout << "password: ";
    cin >> p;

    if (u == "admin" && p == "12345") {
        cout << "\nlogin successful!\n";
        return true;
    } else {
        cout << "\ngalat username ya password\n";
        return false;
    }
}

int main() {
    vector<item> inventory;

    // purana data file se load ho raha hai
    loadfromfile(inventory);
	
    // pehle login hoga
    if (!adminlogin()) return 0;
    int choice;
    do {
        cout << "\n====== inventory management system ======\n";
        cout << "1. add item\n";
        cout << "2. display inventory\n";
        cout << "3. search item\n";
        cout << "4. update quantity\n";
        cout << "5. delete item\n";
        cout << "6. exit\n";
        cout << "choice enter karein: ";
		
        while (!(cin >> choice)) {
            cout << "galat input. dobara number enter karein: ";
            clearinput();
        }

        switch (choice) {
            case 1: additem(inventory); break;
            case 2: displayinventory(inventory); break;
            case 3: searchitem(inventory); break;
            case 4: updatequantity(inventory); break;
            case 5: deleteitem(inventory); break;
            case 6:
                savetofile(inventory);
                cout << "\nprogram band ho raha hai...\n";
                break;
            default:
                cout << "invalid choice\n";
        }
    } while (choice != 6);
    return 0;
}

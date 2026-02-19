#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Item {
	string name;
	int quantity;
	double price;
};

void addItem(vector<Item>& inventory) {
	Item newItem;
	cout << "Enter item name: ";
	cin >> newItem.name;
	cout << "Enter item quantity: ";
	cin >> newItem.quantity;
	cout << "Enter item price: ";
	cin >> newItem.price;

	inventory.push_back(newItem);
	cout << "Item added successfully!\n";
}

void displayInventory(const vector<Item>& inventory) {
	if (inventory.empty()) {
		cout << "\nInventory is empty.\n";
		return;
	}

	cout << "\nInventory List:\n";
	for (const auto& item : inventory) {
		cout << "Item Name: " << item.name
			<< ", Quantity: " << item.quantity
			<< ", Price: $" << item.price << endl;
	}
}

void searchItem(const vector<Item>& inventory, const string& searchName) {
	bool found = false;
	for (const auto& item : inventory) {
		if (item.name == searchName) {
			cout << "Item Found: " << item.name
				<< ", Quantity: " << item.quantity
				<< ", Price: $" << item.price << endl;
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "Item not found.\n";
	}
}

void updateQuantity(vector<Item>& inventory, const string& itemName, int newQuantity) {
	bool found = false;
	for (auto& item : inventory) {
		if (item.name == itemName) {
			item.quantity = newQuantity;
			cout << "Quantity of " << itemName << " updated to " << newQuantity << endl;
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "Item not found.\n";
	}
}

void deleteItem(vector<Item>& inventory, const string& itemName) {
	auto it = inventory.begin();
	bool found = false;

	while (it != inventory.end()) {
		if (it->name == itemName) {
			inventory.erase(it);
			cout << "Item " << itemName << " has been deleted from the inventory.\n";
			found = true;
			break;
		}
		++it;
	}

	if (!found) {
		cout << "Item not found.\n";
	}
}

int main() {
	vector<Item> inventory;

	int choice;
	do {
		cout << "\n=== Inventory Management System ===\n";
		cout << "1. Add item\n";
		cout << "2. Display inventory\n";
		cout << "3. Search item by name\n";
		cout << "4. Update item quantity\n";
		cout << "5. Delete item\n";
		cout << "6. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			addItem(inventory);
			break;
		case 2:
			displayInventory(inventory);
			break;
		case 3: {
			string searchName;
			cout << "Enter item name to search: ";
			cin >> searchName;
			searchItem(inventory, searchName);
			break;
		}
		case 4: {
			string itemName;
			int newQuantity;
			cout << "Enter item name to update quantity: ";
			cin >> itemName;
			cout << "Enter new quantity: ";
			cin >> newQuantity;
			updateQuantity(inventory, itemName, newQuantity);
			break;
		}
		case 5: {
			string itemName;
			cout << "Enter item name to delete: ";
			cin >> itemName;
			deleteItem(inventory, itemName);
			break;
		}
		case 6:
			cout << "Exiting program. Goodbye!\n";
			break;
		default:
			cout << "Invalid choice! Please try again.\n";
		}
	} while (choice != 6);

	return 0;
}

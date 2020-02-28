#include <iostream>
using namespace std;

#include "ItemToPurchase.h"

ItemToPurchase::ItemToPurchase(string name, string description, int price, int qty) {
    itemName = name;
    itemDescription = description;
    itemPrice = price;
    itemQty = qty;
}

void ItemToPurchase::SetName(string name) { itemName = name; }
string ItemToPurchase::GetName() { return itemName; }

void ItemToPurchase::SetDescription(string description) { itemDescription = description; }
string ItemToPurchase::GetDescription() { return itemDescription; }

void ItemToPurchase::SetPrice(int price) { itemPrice = price; }
int ItemToPurchase::GetPrice() { return itemPrice; }

void ItemToPurchase::SetQuantity(int qty) { itemQty = qty; }
int ItemToPurchase::GetQuantity() { return itemQty; }

void ItemToPurchase::PrintItemCost() {
    cout << itemName << " " << itemQty << " @ $" << itemPrice << " = $" << itemPrice * itemQty << endl;;
}
void ItemToPurchase::PrintItemDescription() {
    cout << itemName << ": " << itemDescription << endl;
}
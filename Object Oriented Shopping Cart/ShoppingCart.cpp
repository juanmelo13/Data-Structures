#include <iostream>
using namespace std;

#include "ShoppingCart.h"

ShoppingCart::ShoppingCart(string cusName, string date) {
    customerName = cusName;
    currentDate = date;
}
ShoppingCart::ShoppingCart() {
    customerName = "none";
    currentDate = "January 1, 2016";
}

void ShoppingCart::AddItem(ItemToPurchase item) {
    cartItems.push_back(item);
}
void ShoppingCart::RemoveItem(string item) {
    bool found = false;

    for(unsigned int i = 0; i < static_cast<unsigned int>(cartItems.size()); i++) {
        if(cartItems[i].GetName() == item) {
            found = true;
            cartItems.erase(cartItems.begin() + i);
            break;
        }
    }

    if(!found)
        cout << "Item not found in cart. Nothing removed.\n";
}
void ShoppingCart::ModifyItem(ItemToPurchase item) {
    bool found = false;

    for(unsigned int i = 0; i < static_cast<unsigned int>(cartItems.size()); i++) {
        if(cartItems[i].GetName() == item.GetName()) {
            found = true;
            //cartItems[i].SetDescription(item.GetDescription());
            //cartItems[i].SetPrice(item.GetPrice());
            cartItems[i].SetQuantity(item.GetQuantity());
        }
    }

    if(!found)
        cout << "Item not found in cart. Nothing modified.\n";
}

unsigned int ShoppingCart::GetNumItemsInCart() {
    int cartTotal = 0;

    for(unsigned int i = 0; i < static_cast<unsigned int>(cartItems.size()); i++) {
        cartTotal += cartItems[i].GetQuantity();
    }

    return cartTotal;
}

int ShoppingCart::GetCostOfCart() {
    int cartTotal = 0;

    for(unsigned int i = 0; i < static_cast<unsigned int>(cartItems.size()); i++) {
        cartTotal += cartItems[i].TotalCost();
    }

    return cartTotal;
}

void ShoppingCart::PrintTotal() {
    cout << customerName << "'s Shopping Cart - " << currentDate << endl;
    cout << "Number of Items: " << GetNumItemsInCart() << endl << endl;
    if(GetNumItemsInCart() == 0) {
        cout << "SHOPPING CART IS EMPTY\n";
    } else {
        for(unsigned int i = 0; i < static_cast<unsigned int>(cartItems.size()); i++) {
            cartItems[i].PrintItemCost();
        }
    }
    cout << endl << "Total: $" << GetCostOfCart() << endl;
}
void ShoppingCart::PrintDescriptions() {
    cout << customerName << "'s Shopping Cart - " << currentDate << endl;
    cout << endl << "Item Descriptions" << endl;
    if(GetNumItemsInCart() == 0) {
        cout << "SHOPPING CART IS EMPTY\n";
        return;
    } else {
        for(unsigned int i = 0; i < static_cast<unsigned int>(cartItems.size()); i++) {
            cartItems[i].PrintItemDescription();
        }
    }
}

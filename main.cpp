#include <iostream>
#include <string>
using namespace std;

#include "ItemToPurchase.h"
#include "ShoppingCart.h"

void PrintMenu(ShoppingCart cart) {
    char selection;
    string name, description;
    int price, qty;
    ItemToPurchase item;

    while(selection != 'q') {
        cout << "\nMENU\n" << "a - Add item to cart\n";
        cout << "d - Remove item from cart\n";
        cout << "c - Change item quantity\n";
        cout << "i - Output items' descriptions\n";
        cout << "o - Output shopping cart\n";
        cout << "q - Quit\n";

        COME_IF_INVALID:
        cout << endl << "Choose an option:";
        cin >> selection;

        cin.ignore();
        
        switch (selection) {
        case 'a':
            cout << "\nADD ITEM TO CART\n";
            cout << "Enter the item name:\n";
            getline(cin, name);
            item.SetName(name);

            cout << "Enter the item description:\n";
            getline(cin, description);
            item.SetDescription(description);

            cout << "Enter the item price:\n";
            cin >> price;
            item.SetPrice(price);

            cout << "Enter the item quantity:\n";
            cin >> qty;
            item.SetQuantity(qty);

            cart.AddItem(item);

            break;
        case 'd':
            cout << "\nREMOVE ITEM FROM CART\n";
            cout << "Enter name of item to remove:\n";
            getline(cin, name);

            cart.RemoveItem(name);
            
            break;
        case 'c':
            cout << "\nCHANGE ITEM QUANTITY\n";
            cout << "Enter the item name:\n";
            getline(cin, name);
            item.SetName(name);

            cout << "Enter the new quantity:" << endl;
            cin >> qty;
            item.SetQuantity(qty);

            cart.ModifyItem(item);

            break;
        case 'i':
            cout << "\nOUTPUT ITEMS' DESCRIPTIONS\n";
            cart.PrintDescriptions();

            break;
        case 'o':
            cout << "\nOUTPUT SHOPPING CART\n";
            cart.PrintTotal();

            break;
        case 'q':
            cout << endl;
            break;
        default:
            goto COME_IF_INVALID;
        }
    }
}

int main() {
    string inputName, inputDate;

    cout << "Enter customer's name:\n";
    getline(cin, inputName);

    cout << "Enter today's date:\n";
    getline(cin, inputDate);

    cout << endl << "Customer name: " << inputName << endl;
    cout << "Today's date: " << inputDate << endl;

    ShoppingCart cart1(inputName, inputDate);

    PrintMenu(cart1);

    return 0;
}
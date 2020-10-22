#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <string>
#include <vector>
using namespace std;

#include "ItemToPurchase.h"

class ShoppingCart {
    public:
        ShoppingCart(string cusName, string date);
        ShoppingCart();

        string GetCustomerName() {return customerName;}
        string GetDate() {return currentDate;}

        void AddItem(ItemToPurchase item);
        void RemoveItem(string item);
        void ModifyItem(ItemToPurchase item);

        unsigned int GetNumItemsInCart();

        int GetCostOfCart();
        
        void PrintTotal();
        void PrintDescriptions();
    private:
        string customerName, currentDate;
        vector <ItemToPurchase> cartItems;
};

#endif

#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

#include <string>
using namespace std;

class ItemToPurchase {
    public:
        ItemToPurchase(string name = "none", string description = "none", int price = 0, int qty = 0);
        
        void SetName(string name);
        void SetDescription(string description);
        void SetPrice(int price);
        void SetQuantity(int qty);

        string GetName();
        string GetDescription();
        int GetPrice();
        int GetQuantity();
        int TotalCost() {return itemQty * itemPrice;}

        void PrintItemCost();
        void PrintItemDescription();
    private:
        string itemName, itemDescription;
        int itemPrice, itemQty;
   
};   

#endif

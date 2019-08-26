#ifndef INVENTORY
#define INVENTORY

#include <map>
#include <iostream>
#include <string>
#include <memory>

#include "item.h"
#include "itemlist.h"
#include "wearable.h"


class Inventory
{
    public:
        Inventory(int space = 10);
        bool addItem(Item & item);
        bool removeItem(const std::string name);
        bool useItem(const std::string name);
        Item getItem(const std::string name);

        friend std::ostream & operator <<(std::ostream & os, const Inventory & inv);

    private:
        int m_Space;
        std::multimap<std::string,Item> m_Items;
        
    

};

#endif
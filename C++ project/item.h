#ifndef ITEM
#define ITEM

#include <iostream>
#include <string>
//#include "player.h"

class Item
{
    public:
        Item();
        Item(std::string name, int amount);
        std::string getName();
        int useItem();

    friend std::ostream operator << (std::ostream & os, const Item & i);

    private:
        std::string m_Name;
        int m_AmountToHeal;

};

#endif
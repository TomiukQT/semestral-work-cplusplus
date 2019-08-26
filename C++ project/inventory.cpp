#include "inventory.h"



Inventory::Inventory(int space):
m_Space(space)
{      
}

/**
 * @brief Add item to inventory
 * 
 * @param item is item which will be added.
 * @return true if adding was succeful.
 * @return false if there is no space.
 */
bool Inventory::addItem(Item & item)
{
    if(m_Items.size() < (unsigned)m_Space)
    {
        std::string name = item.getName();
        m_Items.emplace(name,item);
        return true;
    }
    else
        return false;
}

/**
 * @brief remove item from inventory.
 * @param name is name of the Item
 * @return true if removing was succesful 
 * @return false if removing wasn't succesful
 */
bool Inventory::removeItem(const std::string name)
{
    if(m_Items.count(name) == 0)
        return false;
    else
    {
        auto it = m_Items.find(name);
        m_Items.erase(it);
        return true;    
    }
    
}

/**
 * @brief get item from inventory by name.
 * 
 * @param name is name of item which we want.
 * @return Item is found item. Return Item("Nothing",0) if there is no item named "name";.
 */
Item Inventory::getItem(const std::string name)
{
    if(m_Items.count(name) == 0)
    {
        Item i("Nothing",0);
        return i;
    }
    auto it = m_Items.find(name);
    return it->second;
}

std::ostream & operator<<(std::ostream & os, const Inventory & inv)
{
    os << "====INVENTORY====" << std::endl;
    for (auto it = inv.m_Items.begin(); it != inv.m_Items.end(); ++it) 
    {
       Item i = it->second;
       os << i.getName() << " :" << i.useItem() << std::endl;
    }
    
    return os;
}
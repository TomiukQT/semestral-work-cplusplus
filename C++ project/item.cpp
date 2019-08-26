#include "item.h"

Item::Item()
{}

Item::Item(std::string name,int amount):
m_Name(name), m_AmountToHeal(amount)
{
}

/**
 * @brief get name of Item. 
 * 
 * @return std::string is name of the Item.
 */
std::string Item::getName()
{
    return m_Name;
}

/**
 * @brief get amount of HP, which will be healed.
 * 
 * @return int is amount of HP.
 */
int Item::useItem()
{
    return m_AmountToHeal;
}


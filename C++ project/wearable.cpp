#include "wearable.h"

Wearable::Wearable():
m_Name("Nothing"),m_Type(Nothing)
{}

Wearable::Wearable(ArmorType type):
m_Name("Nothing"),m_Type(type)
{}

Wearable::Wearable(std::string name,ArmorType type):
m_Name(name),m_Type(type)
{}
/**
 * @brief return type converted to string. 
 */
std::string TypeToString(ArmorType type)
{
    switch(type)
    {
        case Helmet:
            return "Helmet";
        case Chestplate:
            return "Chestplate";
        case Boots:
            return "Boots";
        case Shield:
            return "Shield";
        case Nothing:
            return "Nothing";
        case Weap:
            return "Weapon";
    }
    return "NOTHING";
}

/**
 * @brief Overloaded operator << for printing Wearable.
 * 
 * @param os is output stream.
 * @param w is Wearable object, which we want to print.
 * @return std::ostream& is outputstream.
 */
std::ostream & operator<<(std::ostream & os, const Wearable & w)
{
    return w.print(os);
}
/**
 * @brief get type of Wearable.
 * 
 * @return ArmorType is type of Wearable.
 */
ArmorType Wearable::getType()
{
    return m_Type;
}

/**
 * @brief get name of Wearable.
 * @return std::string is the name of Wearable
 */
std::string Wearable::getName()
{
    return m_Name;
}
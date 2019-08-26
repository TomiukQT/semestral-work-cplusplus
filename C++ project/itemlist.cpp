#include "itemlist.h"

//=============WEAPON===============

Weapon::Weapon():
Wearable(Weap),m_Damage(0)
{}


Weapon::Weapon(std::string name, int damage):
Wearable(name,Weap),m_Damage(damage)
{}

/**
 * @brief get damage of weapon. 
 */
void Weapon::getBonus(int & damage,int & armor, int & str, int & dex,int & vit)
{
    damage = m_Damage;
}

/**
 * @brief print the Weapon.
 * 
 * @param os is output stream.
 * @return std::ostream& is output stream.
 */
std::ostream & Weapon::print(std::ostream & os) const
{
    os << m_Name << std::endl;
    os << "Damage:" << m_Damage << std::endl;
    return os;
}

//==============ARMOR================

Armor::Armor(ArmorType type):
Wearable(type), m_Armor(0), m_Strength(0), m_Dexterity(0), m_Vitality(0)
{}
Armor::Armor(std::string name,ArmorType type, int armor,int str, int dex, int vit):
Wearable(name,type), m_Armor(armor), m_Strength(str), m_Dexterity(dex), m_Vitality(vit)
{}

/**
 * @brief get armor points. 
 */
void Armor::getBonus(int & damage,int & armor, int & str, int & dex,int & vit)
{
    armor += m_Armor;
    str += getStatsBonus().at(0);
    dex += getStatsBonus().at(1);
    vit += getStatsBonus().at(2);

}

/**
 * @brief get array of bonuses of armor.
 */
std::vector<int> Armor::getStatsBonus()
{
    std::vector<int> bonuses;
    bonuses.emplace_back(m_Strength);
    bonuses.emplace_back(m_Dexterity);
    bonuses.emplace_back(m_Vitality);
    return bonuses;
}

/**
 * @brief print the Armor.
 * 
 * @param os is output stream. 
 * @return std::ostream& is output stream.
 */
 std::ostream & Armor::print(std::ostream & os) const
{
    os << TypeToString(m_Type) << ": " << m_Name << std::endl;
    os << "Armor: " << m_Armor << std::endl;
    if(m_Strength != 0 || m_Dexterity != 0 || m_Vitality != 0)
        os << "Bonuses: ";
    if(m_Strength != 0)
        os << "+" << m_Strength << " STRENGTH,";
    if(m_Dexterity != 0)
        os << "+" << m_Dexterity << " DEXTERITY,";
    if(m_Vitality != 0)
        os << "+" << m_Vitality << " VITALITY";
   // os << std::endl;

    return os;
    
}



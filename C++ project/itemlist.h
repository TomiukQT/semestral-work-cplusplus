#ifndef ITEMLIST
#define ITEMLIST

#include <vector>
#include <iostream>
#include <utility>

//#include "player.h"
//#include "item.h"
#include "wearable.h"


class Weapon : public Wearable
{
    public:
        Weapon();
        Weapon(std::string name, int damage);
        std::vector<int> getStatsBonus();
        void getBonus(int & damage,int & armor, int & str, int & dex,int & vit); 

        std::ostream & print(std::ostream & os) const;
    private:
        int m_Damage;
};

class Armor : public Wearable
{
    public:
        Armor(ArmorType type);
        Armor(std::string name, ArmorType type, int armor,int str = 0, int dex = 0, int vit = 0);
        void getBonus(int & damage,int & armor, int & str, int & dex,int & vit);
        std::vector<int> getStatsBonus();

        std::ostream & print(std::ostream & os) const;
    
    private:
        int m_Armor;
        int m_Strength;
        int m_Dexterity;
        int m_Vitality;

};

#endif
#ifndef PLAYER
#define PLAYER

#include "person.h"
#include "wearable.h"
#include "itemlist.h"
#include "inventory.h"

//class Inventory;

class Player : public Person
{
    public:
        Player();
        Player(std::string name,int hp, int lvl, int damage, int armor, int strength, int vitality,int dexterity);
        void talk();

        void getXp(int amount);
        void levelUp();
        void addStrength(int amount = 1);
        void addVitality(int amount = 1);
        void addItem(Item i);
        void heal();
        void healHp(int amount);
        //void switchWeapon(Weapon w);
        void switchArmor(Wearable * w);
        void getBonuses();

        void printEquip();
        std::string getPlayer();

        int attack(Person & p);
        int getDamage(int damage);

    private:
        int m_Xp;
        int m_Armor;
        int m_Strength;
        int m_Vitality;
        int m_Dexterity;
        int m_BonusStrength;
        int m_BonusVitality;
        int m_BonusDexterity;
        //Inventory
        Inventory m_Inventory;
        std::map<ArmorType,std::shared_ptr<Wearable>> m_Slots;
        Weapon m_Weapon;

};

#endif
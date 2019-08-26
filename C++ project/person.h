#ifndef PERSON
#define PERSON

#include <string>
#include <iostream>


class Person
{
    public:
        Person();
        Person(std::string name, int hp, int lvl, int damage);
        int attack(Person & p);
        int getDamage(int damage);
        bool isAlive();
        std::string getName();
        
        friend std::ostream & operator << (std::ostream & os, const Person & p);
        

    protected:
        std::string m_Name;
        int m_Hp;
        int m_MaxHp;
        int m_Lvl;
        int m_Damage;


};

#endif
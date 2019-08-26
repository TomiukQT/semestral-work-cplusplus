#ifndef ENEMY
#define ENEMY

#include "person.h"
#include "wearable.h"


#pragma once

class Enemy : public Person
{
    public:
        Enemy(std::string name, int hp, int lvl, int damage,int armor);
        void attack(int damage);


    private:
        int m_Armor;


};

#endif
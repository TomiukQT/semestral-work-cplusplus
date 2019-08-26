#include <cstdlib> 
#include <ctime> 
#include "enemy.h"


Enemy::Enemy(std::string name, int hp, int lvl, int damage,int armor):
Person(name,hp,lvl,damage), m_Armor(armor)
{

}



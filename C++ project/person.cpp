#include "person.h"

Person::Person()
{

}


Person::Person(std::string name, int hp, int lvl, int damage):
m_Name(name),m_Hp(hp),m_Lvl(lvl),m_Damage(damage)
{
    m_MaxHp = hp;
}

/**
 * @brief Checking if Person is alive.
 * 
 * @return true if yes.
 * @return false if not.
 */
bool Person::isAlive()
{
    return m_Hp > 0;
}
/**
 * @brief Method to take damage.
 * 
 * @param damage is amout of raw damage dealt. 
 */
int Person::getDamage(int damage)
{
    m_Hp -= damage;
    return damage;
}

/**
 * @brief Method to attack another Person(player, enemy, etc.).
 * 
 * @param p is Person to attack.
 */
int Person::attack(Person & p)
{
   return p.getDamage(m_Damage);
}
/**
 * @brief return Name of Person.
 * 
 * @return std::string name.
 */
std::string Person::getName()
{
    return m_Name;
}
/**
 * @brief overloaded operator << for Person. Format: NAME[current_hp/max_hp] 
 */
std::ostream & operator << (std::ostream & os, const Person & p)
{
    os << p.m_Name << " [ " << p.m_Hp << " / " << p.m_MaxHp << " ] ";
    return os;
}
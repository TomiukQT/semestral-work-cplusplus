#include "player.h"

std::map<ArmorType,std::shared_ptr<Wearable>> SlotsInit()
{
    std::map<ArmorType,std::shared_ptr<Wearable>> slots;
    Armor h(Helmet);
    Armor ch(Chestplate);
    Armor s(Shield);
    Armor b(Boots);
    Weapon w("Bare hands",1);
   

    slots.emplace(Helmet,std::make_shared<Armor>(h));
    slots.emplace(Chestplate,std::make_shared<Armor>(ch));
    slots.emplace(Shield,std::make_shared<Armor>(s));
    slots.emplace(Boots,std::make_shared<Armor>(b));
    slots.emplace(Weap,std::make_shared<Weapon>(w));

    
    
    return slots;
}




Player::Player()
{}

Player::Player(std::string name,int hp, int lvl, int damage, int armor, int strength, int vitality,int dexterity):
Person(name,hp,lvl,damage),m_Armor(armor),m_Strength(strength),m_Vitality(vitality),m_Dexterity(dexterity)
{
    m_Slots = SlotsInit();
    Weapon w("Bare hands",1);
    m_Weapon = w;

    Item i("Healing potion",20);
    m_Inventory.addItem(i);
    getBonuses();
}


void Player::getXp(int amount)
{
    m_Xp += amount;
    if(m_Xp >= 100)
    {
        m_Xp-=100;
        levelUp();
    }
}

void Player::levelUp()
{
    m_Lvl++;
    addStrength();
    addVitality();

}

void Player::addStrength(int amount)
{
    m_Strength += amount;
}

void Player::addVitality(int amount)
{
    m_Vitality += amount;
}

/**
 * @brief Add amount to Hp
 * 
 * @param amount is amount of hp which will be added to actuall amount of HP
 */
void Player::healHp(int amount)
{
    if(m_Hp + amount > m_MaxHp)
        m_Hp = m_MaxHp;
    else
        m_Hp += amount;

    std::cout << "Healed +" << amount << " HP" << std::endl;
    std::cout << "Your HP: "<< " [ " << m_Hp << " / " << m_MaxHp << " ] " << std::endl;
}

/**
 * @brief switch weapon with currently equipped weapon.
 * 
 * @param w is weapon, which will be switched.
 */
/*
void Player::switchWeapon(Weapon w)
{
    m_Weapon = w;
    auto it = m_Slots.find(Weap);
    it->second = std::make_shared<Weapon>(w);
    getBonuses();
}
*/
/**
 * @brief switch armor with currently equipped.
 *  
 * @param a is armor, which will be switched.
 */
void Player::switchArmor(Wearable *  a)
{
    auto it = m_Slots.find(a->getType());

    if(a->getType() != Weap)
    {
        it->second = std::make_shared<Armor>(a);
    }
    else
        it->second = std::make_shared<Weapon>(a);
    getBonuses();
}

/**
 * @brief print player equipment to std::cout. 
 */
void Player::printEquip()
{
    std::cout << std::endl << "========EQUIP=======" << std::endl;
    std::cout << m_Weapon << std::endl;

    for (auto it = m_Slots.begin(); it != m_Slots.end(); ++it) 
    {
        std::cout << (it->second) << std::endl;
    }

    std::cout << m_Inventory << std::endl;
    std::cout << "========EQUIP=======" << std::endl;
}

/**
 * @brief get Player object as string for saving the game progress.
 * 
 * @return std::string is Player converted to string
 */
std::string Player::getPlayer()
{
    std::string s = m_Name;
    s.append("\n");
    s.append(std::to_string(m_Hp));
    s.append("\n");
    s.append(std::to_string(m_Strength));
    s.append("\n");
    s.append(std::to_string(m_Vitality));
    s.append("\n");
    s.append(std::to_string(m_Dexterity));
    s.append("\n");
    s.append(m_Weapon.getName());
    for (auto it = m_Slots.begin(); it != m_Slots.end(); ++it) 
    {
        s.append("\n");
        s.append(it->second->getName());
    }
    return s;
}

/**
 * @brief Try to find potion in inventory and heal player.
 * 
 */
void Player::heal()
{
    Item i = m_Inventory.getItem("Healing potion");
    if (i.getName() != "Nothing")
    {
        healHp(i.useItem());
        m_Inventory.removeItem("Healing potion");
    }

}

/**
 * @brief add Item to inventory
 * 
 * @param i is item which will be added.
 */
void Player::addItem(Item i)
{
    m_Inventory.addItem(i);
}
/**
 * @brief Get all bonuses from all items equipped.
 * 
 */
void Player::getBonuses()
{
    
    m_Armor = 0;
    m_BonusStrength = 0;
    m_BonusVitality = 0;
    m_BonusDexterity = 0;
    
    for (auto it = m_Slots.begin(); it != m_Slots.end(); ++it) 
    {   
       it -> second -> getBonus(m_Damage,m_Armor,m_BonusStrength,m_BonusVitality,m_BonusDexterity);        
    }
    
}

/**
 * @brief Method to attack another Person(player, enemy, etc.).
 * 
 * @param p is Person to attack.
 */
int Player::attack(Person & p)
{
    int dmg = m_Damage + m_Strength + m_BonusStrength;
    return p.getDamage(dmg);
}

/**
 * @brief Method to take damage.
 * 
 * @param damage is amout of raw damage dealt. 
 */
int Player::getDamage(int damage)
{
    int dmg = damage - m_Armor - m_Vitality;
    m_Hp -= dmg;
    return dmg;
}

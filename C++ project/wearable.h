#ifndef WEARABLE
#define WEARABLE

enum ArmorType{Helmet,Chestplate,Shield,Boots,Nothing,Weap};

#include <string>
#include <vector>
#include <iostream>

class Wearable
{
    public:
        Wearable();
        Wearable(ArmorType type);
        Wearable(std::string name, ArmorType type);
        virtual void getBonus(int & damage,int & armor, int & str, int & dex,int & vit) = 0;
        virtual std::vector<int> getStatsBonus() = 0;
         ArmorType getType();
        std::string getName();
        virtual std::ostream & print(std::ostream & os) const = 0; 
    protected:
        std::string m_Name;
        ArmorType m_Type;


        friend std::ostream & operator<<(std::ostream & os, const Wearable & w);

};

std::string TypeToString(ArmorType type);

#endif
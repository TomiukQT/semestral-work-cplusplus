#ifndef BOOK
#define BOOK

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <random>
#include <chrono>


#include "person.h"
#include "enemy.h"
#include "wearable.h"
#include "item.h"
#include "itemlist.h"


struct Edge
{
    int m_Src;
    int m_Dest;
    Edge(int src,int dest)
    {
        m_Src = src;
        m_Dest = dest;
    }
};

struct Page
{   
    bool isFightingPage = false;
    std::string text;
    std::vector<std::string> options;
};


class Book
{
    public:
        Book();
        Book(const std::vector<Page> & pages,const std::vector<Edge> & edges,const std::map<std::string,Enemy> & enemies,
        const std::map<std::string,std::shared_ptr<Wearable>> & wearables, int n);
        std::string print(const int atPage)const;
        void insertOption(const int atPage,const std::string text);
        int chooseOption(const int choice);
        Enemy & getEnemy(std::string name);
        Page & getPage(const int index);
        std::shared_ptr<Wearable> getRandomWearable();
        std::shared_ptr<Wearable> getWearable(std::string name);
        int getCurrentPosition() const;

        std::vector<std::vector<int>> m_AdjacmentList;


    private:
        std::vector<Page> m_Pages;
        std::map<std::string,Enemy> m_Enemies;
        //std::map<std::string,std::shared_ptr<Item>> m_Items;
        std::map<std::string,std::shared_ptr<Wearable>> m_Wearables;
        int m_CurrPosition;

       
        


        
        std::mt19937 m_RandomGen;

};

#endif
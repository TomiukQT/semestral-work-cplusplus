#ifndef GAMEMANAGER
#define GAMEMANAGER

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib> 
#include <ctime>

#include "player.h"
#include "book.h"


enum GameState{GAME_OVER,WON,RUN,OVER,READING, FIGHTING};

class GameManager
{
    public:
      GameManager(Book & b,std::string fileName);
      void newPlayer();
      GameState fight(Person & enemy);
      int chooseOption();
      int chooseOption(int choice);
      int read(const int currPos);
      GameState getState();
      void command(std::string commandText);
      void saveData();
      bool loadData(int & position);



    private:
        GameState m_State;
        Player m_Player;
        Book m_Book;

        std::string m_Version;
        
};



#endif
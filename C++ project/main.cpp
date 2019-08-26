#include<iostream>

#include "loader.h"
#include "gamemanager.h"

void printCredits()
{
    std::cout << "Made by Tomáš Valenta" << std::endl;
    std::cout << "Thank you for playing" << std::endl;
}

void showMenu()
{
    std::cout << "GAMEBOOK" << std::endl;
    std::cout << "========" << std::endl;

    std::cout << "1.) Play Game" << std::endl;
    std::cout << "2.) Load Game" << std::endl;
    std::cout << "3.) Show Credits" << std::endl;
    std::cout << "4.) Quit Game" << std::endl;

}

int chooseFromMenu()
{
    int choice;
    std::string s;
    while(true)
    {
        std::cout << "Your choice: ";
        std::cin >> s;

        try
        {
            choice = std::stoi(s);
        }
        catch(std::invalid_argument const & e)
        {
            if(std::cin.eof())
                std::cin.clear();
            continue;
        }

        return choice;

    }
}


int main (void)
{

    Loader l;
    Book b;

    std::string fileName = "examples/in0.txt";

    if(!l.load(fileName,b))
    {
        std::cout << "Missing file or low permissions. :( " << std::endl;
        return 1;
    }
    GameManager gameManager(b,fileName);
     int currPos = 0;


    while(true)
    {
        showMenu();
        int choice = chooseFromMenu();
        if(choice == 1)
        {
            gameManager.newPlayer();
            break;
        }
        else if (choice == 2)
        {
            std::cout << "Loading game" << std::endl;
            if(gameManager.loadData(currPos))
                break;
        }
        else if(choice == 3)
            printCredits();
        else if(choice == 4)
            return 0;
    }



    
   // std::cout << currPos << std::endl;
    
    
   
    bool isGame = true;
   // int choice;

    
    
    while(isGame)
    {
        int pos = gameManager.read(currPos);
        if(pos >= 0)
        {
            currPos = gameManager.chooseOption(1);
            continue;
        }
        if(gameManager.getState() == OVER)
            break;
        
        currPos = gameManager.chooseOption();
         if(gameManager.getState() == OVER)
            break;
        //std::cout << currPos << std::endl;   
    }

    printCredits();

    return 0;
}
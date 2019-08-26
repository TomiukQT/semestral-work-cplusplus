#include "gamemanager.h"
    

/**
 * @brief Convert string to lower case.
 * 
 * @param s is input string.
 * @return std::string is output string convereted to lower case.
 */
std::string strToLower(std::string & s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

/**
 * @brief Get the yes or no answer.
 * 
 * @return int 1 is for yes, 0 for no.
 */
int getYesNoAnswer()
{
    std::string choice;
    while(true)
    {
        std::cin >> choice;
        if(std::cin.eof())
        {
            std::cin.clear();
            continue;
        }

        strToLower(choice);
        if(choice == "yes" || choice == "y" || choice == "true" || choice == "1")
            return 1;
        else if(choice == "no" || choice == "n" || choice == "false" || choice == "0")
            return 0;

    }
    return -1;
}

/**
 * @brief Construct a new Game Manager:: Game Manager object
 * 
 */
GameManager::GameManager(Book & b,std::string fileName):
m_Book(b),m_Version(fileName)
{}

/**
 * @brief Create a new player.
 * 
 */
void GameManager::newPlayer()
{
    std::string name,s;
    int str = 0, vit = 0, dex = 0,points = 15;
    std::cout << "Create your character:" << std::endl;
    while(true)
    {
        std::cout << "Choose name: ";
        std::cin >> name;

        if(std::cin.eof())
        {
            std::cin.clear();
            std::cout << std::endl;
        }
        else
            break;
    }

    std::cout << "Set your attributes (Strength,Vitality,Dexterity)" << std::endl;
    while(true)
    {  
        std::cout << "You have " << points <<  " points" << std::endl;
        std::cout << "Set strength: ";
        std::cin >> s;
        try
        {   
            str = std::stoi(s);
            if(str > points || str < 0)
                continue;
            else
            {
                points -= str;
                break;
            }
                
        }
        catch(std::invalid_argument const & e)
        {
            if(std::cin.eof())
                std::cin.clear();
            continue;
        }

    }

    //VITALITY

    while(true)
    {  
        std::cout << "You have " << points <<  " points" << std::endl;
        std::cout << "Set vitality: ";
        std::cin >> s;
        try
        {   
            vit = std::stoi(s);
    
            if(vit > points || vit < 0)
                continue;
            else
            {
                points -= vit;
                break;
            }
                
        }
        catch(std::invalid_argument const & e)
        {
            if(std::cin.eof())
                std::cin.clear();
            continue;
        }

    }

    //DEXTERITY

    while(true)
    {  
        std::cout << "You have " << points <<  " points" << std::endl;
        std::cout << "Set dexterity: ";
        std::cin >> s;
        try
        {   
            dex = std::stoi(s);
            if(dex > points || dex < 0)
                continue;
            else
            {
                points -= dex;
                break;
            }
                
        }
        catch(std::invalid_argument const & e)
        {
            if(std::cin.eof())
                std::cin.clear();
            continue;
        }

    }


     
    Player p(name,100,1,10,0,str,vit,dex);
    m_Player = p;
    srand((unsigned)time(0));

    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
}

/**
 * @brief fighting loop, until one of the objects is not alive.
 * 
 * @param enemy is Enemy which are player attacking. 
 * @return GameState is result of fight (Gameover or won).
 */
GameState GameManager::fight(Person & enemy)
{
    std::string choice;
    while(true)
    {
        while(true)
        {
            std::cout << "What will you do?" << std::endl;
            std::cin >> choice;

            if(std::cin.eof())
            {
                std::cin.clear();
                std::cout << std::endl;
                continue;
            }

            strToLower(choice);
            command(choice);
            if(choice == "attack")
            {
                std::cout << m_Player << " is attacking " << enemy <<  "and causing " << m_Player.attack(enemy) << " damage." << std::endl;
                break;
            }
            /*
            else if (choice == "run")
            {
                if(rand()%4 == 0)
                {
                    return RUN;
                }
                break;
            }
            */
        }
       
        
        if(!enemy.isAlive())
        {
            std::cout << "You won the fight!" << std::endl;
            Item i("Healing potion",20);
            m_Player.addItem(i);
            return WON;
        }
       
        std::cout << enemy << " is attacking " << m_Player <<  " and causing " << enemy.attack(m_Player) << " damage." << std::endl;
        if(!m_Player.isAlive())
        {
            std::cout << "You died!" << std::endl;
            return GAME_OVER;
            
        }
    }
}

/**
 * @brief choose number from selection.
 * 
 * @return int number of page, which was selected.
 */
int GameManager::chooseOption()
{
    std::string s;
    int pos,choice;

    
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

            command(s);
            if(m_State == OVER)
                return -1;
            continue;
        }
        
        

        pos = m_Book.chooseOption(choice);
        if( pos != -9895)
            return pos;

    }
    
}
/**
 * @brief choose option in book.
 * 
 * @param choice is number of option.
 * @return int number of page, which was selected.
 */
int GameManager::chooseOption(int choice)
{
        int pos;
        pos = m_Book.chooseOption(choice);
        if( pos != -9895)
            return pos;
        return 0;
}
/**
 * @brief print text or start fight between player and enemy.
 * 
 * @param currPos is current position. 
 */
int GameManager::read(const int currPos)
{
    std::string text = m_Book.getPage(currPos).text;
    std::string firstWord = text.substr(0, text.find(' '));
    if(firstWord == "ATTACK")
    {
        std::string enemyName = text.substr(text.find(' '));
        enemyName = enemyName.substr(1);
        std::cout << enemyName << "is attacking!" << std::endl;
        GameState state = fight(m_Book.getEnemy(enemyName));
        if(state == GAME_OVER)
        {
            m_State = OVER;
            return -2;
        }
        else if (state == WON)
        {
            //drop items
            if(rand()%1 == 0)
            {

                 std::shared_ptr<Wearable> w = m_Book.getRandomWearable();
                 std::cout << "Dropped: "<< (*w) << std::endl;
                 std::cout << "Want to take it? (y/n): " ;//<< std::endl;

                 if(getYesNoAnswer())
                 {
                     m_Player.switchArmor((w.get()));
                     /*
                     if(w->getType() == Weap)
                     {
                         //Weapon * wep = dynamic_cast<Weapon *>(w.get());
                         m_Player.switc(w.get());
                     }
                     else if(w->getType() != Weap || w->getType() != Nothing)
                     {
                         //Armor * a = dynamic_cast<Armor *>(w.get());
                         m_Player.switchArmor((w.get()));
                         
                     }
*/                        
                 }
            }
            else
            {
                std::cout << "Nothing dropped." << std::endl;
            }
            return m_Book.m_AdjacmentList[currPos].at(0);     
        }
    }
    else
    {
        m_Book.print(currPos);
        return -1;
    }
    return -1;
}

/**
 * @brief Get game state
 * 
 * @return GameState is current game state.
 */
GameState GameManager::getState()
{
    return m_State;
}

/**
 * @brief Procces string and execute command.
 * 
 * @param commandText is input from console.
 */
void GameManager::command(std::string commandText)
{
    commandText = strToLower(commandText);

    if(commandText == "inventory")
        m_Player.printEquip();
    else if(commandText == "help" || strToLower(commandText) == "?")
    {
        std::cout << "Available commands: " << std::endl;
        std::cout << "inventory: write your gear and inventory" << std::endl;
        std::cout << "help or ?: write these hints. " << std::endl;
        std::cout << "attack: attack the enemy " << std::endl;
        std::cout << "yes or y or 1 or true: yes " << std::endl;
        std::cout << "no or n or 0 or false: no" << std::endl;
        std::cout << "quit or q: to quit without saving" << std::endl;
        std::cout << "save: to save game" << std::endl;
        std::cout << "heal: to heal yourself if you have potions" << std::endl;
    }
    else if(commandText == "quit" || commandText == "q")
        m_State = OVER;
    else if(commandText == "save")
        saveData();
    else if(commandText == "heal")
        m_Player.heal();

}

/**
 * @brief save important datas to file save.txt. Next time game progress
 * could be loaded.
 */
void GameManager::saveData()
{
    std::ofstream ofs("examples/save.txt",std::ios::out);
    //save game file name
    //save player
    ofs << m_Version << std::endl << m_Player.getPlayer() << std::endl;
    
    //save pos
    ofs<< m_Book.getCurrentPosition();
}

/**
 * @brief load data from file save.txt.
 * 
 * @return true if loading was succesful
 * @return false if loading was unsucceful (file doesn't exist,low privilegies,..)
 */
bool GameManager::loadData(int & position)
{
    std::ifstream ifs("examples/save.txt",std::ios::in);
    if(!ifs.is_open() || ifs.fail())
        return false;

    std::string file,name,itemName;
    int hp,str,vit,dex,pos;
    ifs >> file;
    if(file != m_Version)
        return false;
    ifs >> name;
    ifs >> hp >> str >> vit >> dex;
    Player p(name,100,1,10,0,str,vit,dex);
    std::getline(ifs,itemName);
    std::getline(ifs,itemName);

    if(itemName != "Bare hands")
    {
         
        
    }
    for (size_t i = 0; i < 4; i++)
    {
        
        std::getline(ifs,itemName);
        if(itemName != "Nothing")
        {

                p.switchArmor(m_Book.getWearable(itemName).get());
        }
    }
    
    ifs >> pos;
    position = pos;
    m_Player = p;
    
    

    return true;
}





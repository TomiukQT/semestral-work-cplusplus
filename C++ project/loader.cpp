#include "loader.h"

/**
 * @brief Construct a new Loader:: Loader object
 * 
 */
Loader::Loader()
{}

/**
 * @brief read source node from ifstream
 * 
 * @param ifs is ifstream with loaded file.
 * @param srcNode is number of node. Output parameter.
 * @param text is text of the node. Output paramter.
 */
void getSrcNode(std::ifstream & ifs,int & srcNode, std::string & text)
{
  char c;
  ifs >> c >> srcNode >> c;
  std::getline(ifs,text,'\n');
  std::getline(ifs,text,'\n');
}
/**
 * @brief load Enemies from file
 * 
 * @param ifs is ifstream with loaded file.
 * @param enemies is array of enemies. Output parameter.
 */
void loadEnemies(std::ifstream & ifs, std::map<std::string,Enemy> & enemies)
{
  std::string name,s;
  int hp,lvl,damage,armor;
  do
  {
    std::getline(ifs,name);
    std::getline(ifs,name);
    ifs  >> hp >> lvl >> damage >> armor >> s;
    //std::cout << name << hp << std::endl;
    Enemy e(name,hp,lvl,damage,armor);
    enemies.emplace(name,e);
  }
  while(s != "===");
  
}
/**
 * @brief Load weapons from file.
 * 
 * @param ifs is opened file. 
 * @param wearables is array of all Wearables.
 */
void loadWeapons(std::ifstream & ifs,std::map<std::string,std::shared_ptr<Wearable>> & wearables)
{
  std::string name,s;
  int damage;
  do
  {
    //std::getline(ifs,name);
    std::getline(ifs,name);
    std::getline(ifs,name);
    ifs >> damage >> s;
    //std::cout << name << damage << std::endl;
    Weapon w(name,damage);
    wearables.emplace(name,std::make_shared<Weapon>(w));
  }
  while(s != "===");
}

/**
 * @brief convert string to ArmorType
 * 
 * @param type is string, which should be converted. 
 * @return ArmorType is ArmorType, which was converted from string. 
 */
ArmorType StringToType(const std::string type)
{
  if(type == "Helmet")
    return Helmet;
  else if(type == "Chestplate")
    return Chestplate;
  else if(type == "Shield")
    return Shield;
  else if(type == "Boots")
    return Boots;
  
  return Nothing;
}

/**
 * @brief load wearables from file.
 * 
 * @param ifs is opened file. 
 * @param wearables is array of all Wearables.
 */
void loadWearables(std::ifstream & ifs,std::map<std::string,std::shared_ptr<Wearable>> & wearables)
{
  std::string name,s,type;
  int armor,str,dex,vit;
  char c;
  do
  {
    std::getline(ifs,name);
    std::getline(ifs,name);
    //std::cout << name << std::endl;
    ifs >> type >> armor >> str >> c >> dex >> c >> vit >> s;
    //std::cout << name << armor <<" " << str<<dex<<vit<<std::endl;

    ArmorType typ = StringToType(type);
    Armor a (name,typ,armor,str,dex,vit);
    wearables.emplace(name,std::make_shared<Armor>(a));
  }
  while(s != "===");
}


/**
 * @brief Loads data from file with specified formatting and creates Book(layout).
 * 
 * @param fileName is name of file.
 * @param book is actual book loaded from file. Output parameter.
 * @return true if loading was succesful.
 * @return false if loading was unsuccesful.
 */
bool Loader::load(std::string fileName, Book & book)
{

  std::ifstream ifs(fileName,std::ios::in);
  if(!ifs.is_open() || ifs.fail())
  {
    return false;
  }

  char c;
  int srcNode,destNode;
  std::string flag,text,optText;

  std::vector<Page> pages;
  std::vector<Edge> edges;
  
  std::map<std::string,Enemy> enemies;
  std::map<std::string,std::shared_ptr<Item>> items;
  std::map<std::string,std::shared_ptr<Wearable>> wearables;

  while(flag != "LOCATIONS")
  {
    ifs >> flag;
    if(flag == "ENEMIES")
      loadEnemies(ifs,enemies);
    if(flag == "WEAPONS")
      loadWeapons(ifs,wearables);
    if(flag == "WEARABLES")
      loadWearables(ifs,wearables);
  }
 

  while(!ifs.eof())
  {

    Page p;
    getSrcNode(ifs,srcNode,text);
    p.text = text;
    std::string firstWord = text.substr(0, text.find(" "));
    if(firstWord == "ATTACK")
    {
      p.isFightingPage = true;
    }
    
    //std::cout << srcNode << std::endl;
    //std::cout << text << std::endl;

    while(ifs >> c)
    {
      
      if(c == '-')
        break;

      ifs >> destNode;
      ifs >> c;
      std::getline(ifs,optText,'\n');
      //std::cout << destNode << optText << std::endl;
      p.options.emplace_back(optText);
      Edge e(srcNode,destNode);
      edges.emplace_back(e);    
    }



    pages.emplace_back(p);
    ifs >> c;
    std::getline(ifs,text,'\n');
    ifs.peek();
    
  }

  
  int count = (int)edges.size();
  Book bo(pages,edges,enemies,wearables,count);
  book = bo;


    return true;
}
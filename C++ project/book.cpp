#include "book.h"

Book::Book()
{}
/**
 * @brief Construct a new Book object
 * 
 * @param pages is array of pages of book which contain text and vector of options.
 * @param edges is array of edges of graph which are connecting nodes of graph
 * @param enemies is array of enemies readed from file.
 * @param wearables is array of wearablem readed from file.
 * @param n is count of nodes.
 */
Book::Book(const std::vector<Page> & pages ,const std::vector<Edge> & edges,const std::map<std::string,Enemy> & enemies,
const std::map<std::string,std::shared_ptr<Wearable>> & wearables, int n):
m_Pages(pages),m_Enemies(enemies),m_Wearables(wearables),m_CurrPosition(0)
{
    m_AdjacmentList.resize(n);
    for(unsigned i = 0; i < edges.size(); i++)
    {
        Edge e = edges.at(i);
        m_AdjacmentList[e.m_Src].emplace_back(e.m_Dest);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    m_RandomGen = gen;
}
/**
 * @brief Print page of book with all options.
 * 
 * @param atPage is number of page which will be printed,
 * @return std::string is builded string from page.
 */
std::string Book::print(const int atPage) const
{
    std::cout  << m_Pages.at(atPage).text << std::endl;
    for(unsigned i = 0; i < m_AdjacmentList[atPage].size(); i++)
    {
        
        std::cout << i+1<< ") "<< m_Pages[atPage].options[i] << std::endl; 
    }
    return "asd";
    
}

/**
 * @brief Insert option to page.
 * 
 * @param atPage is number of page to which will be inserted the option.
 * @param text is text of the option.
 */
void Book::insertOption(const int atPage,const std::string text)
{
    m_Pages.at(atPage).options.emplace_back(text);
}


/**
 * @brief check bounds and choose option from current Page.
 * 
 * @param choice is number of option that player want to choose ?
 * @return int is number of next page.
 */
int Book::chooseOption(const int choice)
{
    if(choice > 0 && choice <= (int)m_AdjacmentList.at(m_CurrPosition).size())
    {
        m_CurrPosition = m_AdjacmentList.at(m_CurrPosition).at(choice-1);
       // std::cout << "Current position: " << m_CurrPosition << std::endl;
        return m_CurrPosition;
    }
    else 
        return -9895;
}

/**
 * @brief Get enemy identified by name.
 * 
 * @param index is index of enemy.
 * @return Enemy& is enemy of chosen name.
 */
Enemy & Book::getEnemy(std::string name)
{
    return m_Enemies.at(name);
}

Page & Book::getPage(const int index)
{
    return m_Pages.at(index);
}

/**
 * @brief get random Wearable from all Wearables.
 * 
 * @return std::shared_ptr<Wearable> is pointer to random Wearable.
 */
std::shared_ptr<Wearable> Book::getRandomWearable()
{   
    int ran = m_RandomGen() % (m_Wearables.size());
    int counter = 0;
    for (auto it = m_Wearables.begin(); it != m_Wearables.end(); ++it) 
    {
        if (counter == ran)
            return it->second;
        counter++;  
    }
    return nullptr;
}

/**
 * @brief get Wearable by name.
 * 
 * @param name is name of wanted Wearable.
 * @return std::shared_ptr<Wearable> is pointer on wanted Wearable.
 */
std::shared_ptr<Wearable> Book::getWearable(std::string name)
{
    return m_Wearables.at(name);
}

/**
 * @brief Get current position in Book (graph).
 * @return int is current position.
 */
int Book::getCurrentPosition() const
{
    return m_CurrPosition;
}


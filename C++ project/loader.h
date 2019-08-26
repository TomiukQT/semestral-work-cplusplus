#ifndef LOADER
#define LOADER


#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include "book.h"



class Loader
{
    public:
        Loader();
        bool load(std::string fileName,Book & book);
        bool loadData();
};

#endif
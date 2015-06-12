/* 
 * File:   GlobalImages.cpp
 * Author: Qb
 * 
 * Created on 2 kwiecień 2015, 20:52
 */

#include <fstream>

#include "GlobalImages.h"

GlobalImages::GlobalImages() {
    getImages();
}

GlobalImages::~GlobalImages()
{
}

Image* GlobalImages::getByName(std::string name)
{
    Image *temp = imageMap[name];
    return temp;
}

void GlobalImages::getImages()
{
    std::fstream file;
    file.open("fixtures/imagesMap.txt", std::ios::in);
    std::string name;
    std::string imagePath;
    while(!file.eof())
    {
        file >> imagePath >> name;
        Image *newImage = new Image(imagePath, true);
        newImage->state = NORMAL;
        imageMap.insert(std::pair<std::string, Image*>(name, newImage));
    }
}
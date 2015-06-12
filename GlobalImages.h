/* 
 * File:   GlobalImages.h
 * Author: Qb
 *
 * Created on 2 kwiecień 2015, 20:52
 */

#ifndef GLOBALIMAGES_H
#define	GLOBALIMAGES_H
#include "Image.h"
#include <map>

class GlobalImages {
public:
    GlobalImages();
    ~GlobalImages();
    void getImages();
    Image *getByName(std::string name);
private:
    std::map<std::string, Image*> imageMap;
};

#endif	/* GLOBALIMAGES_H */


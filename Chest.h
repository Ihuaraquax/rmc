/* 
 * File:   Chest.h
 * Author: Qb
 *
 * Created on 28 luty 2015, 15:03
 */

#ifndef CHEST_H
#define	CHEST_H
#include "UsableObject.h"
#include "Image.h"
#include "Coordinates.h"
#include "Obstacle.h"
#include <fstream>

class Chest : public Entity, public UsableObject {
public:
    Chest();
    virtual ~Chest();
    
    void update();
    void display();
    void displayContent();
    void loadContent(int index, int type, int value);
    void use();
    
    int getSelectedField();
    int getContentType(int index);
    int getContentValue(int index);
    bool isOpen() const;
    int getSelectedContent() const;
    
    bool isFieldNotEmpty(int index);
    void swapContent(int firstContentIndex, int secondContentIndex);
    void save(std::fstream &savefile);
private:
    Coordinates *backgroundCoords;
    Coordinates **contentCoords;
    Image *backgroundImage;
    Image **contentImages;
    
    int chestSize;
    int *contentType;
    int *contentValue;

    bool open;
    int selectedContent;
};

#endif	/* CHEST_H */


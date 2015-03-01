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
private:
    Coordinates *backgroundCoords;
    Coordinates **contentCoords;
    Image *backgroundImage;
    Image **contentImages;
    
    int chestSize;
    int *contentType;
    int *contentValue;

    bool open;
};

#endif	/* CHEST_H */


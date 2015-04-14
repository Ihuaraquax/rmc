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
    void displayPlan();
    void displayContent();
    void loadContent(int index, int type, int value);
    void use();
    void setRandom();
    
    int getSelectedField();
    int getContentType(int index);
    int getContentValue(int index);
    bool isOpen() const;
    int getSelectedContent() const;
    void setStartingTile();
    
    bool isFieldNotEmpty(int index);
    void swapContent(int firstContentIndex, int secondContentIndex);
    void save(std::fstream &file);
    void load(std::fstream &file);
    void executeAgony();
    bool isBarricade();
    
    static Entity *CreateChest(double X, double Y);
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


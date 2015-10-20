/* 
 * File:   Console.h
 * Author: Qb
 *
 * Created on 3 maj 2015, 13:42
 */

#ifndef CONSOLE_H
#define	CONSOLE_H
#include "Entity.h"
#include "UsableObject.h"

class Console : public Entity, public UsableObject {
public:
    Console();
    Console(const Console& orig);
    virtual ~Console();
    void use();
    void setRandomCoords();
    void setStartingTile();
    static Entity *CreateConsole(double X, double Y);
    void save(std::fstream& file);
    void load(std::fstream& savefile);
    void executeAgony();
    void highlight();
    
    static void end();
    static void mouseControl();
private:
    static double offsetX, offsetY;
};

#endif	/* CONSOLE_H */


/* 
 * File:   Button.h
 * Author: Qb
 *
 * Created on 4 listopad 2014, 22:28
 */

#ifndef BUTTON_H
#define	BUTTON_H
#include "Coordinates.h"
#include "Image.h"

class Button {
public:
    Button();
    Button(const Button& orig);
    virtual ~Button();
    bool isHover();
    void display();
    void update();
    void changeCoordinates(Coordinates *panelCoords);
private:
    Coordinates * coords;
    Image *image;
    bool active;
    int action;
    bool pressed;
    void execute();
    void makeAction();
};

#endif	/* BUTTON_H */


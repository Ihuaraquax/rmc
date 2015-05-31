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
    Button(int action);
    Button(const Button& orig);
    virtual ~Button();
    void display();
    void update();
    void execute();
private:
    Coordinates * coords;
    Image *image;
    int action;
    void makeAction();
};

#endif	/* BUTTON_H */


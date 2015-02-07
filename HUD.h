/* 
 * File:   HUD.h
 * Author: Qb
 *
 * Created on 8 luty 2015, 00:10
 */

#ifndef HUD_H
#define	HUD_H
#include "Image.h"
#include "Coordinates.h"

class HUD {
public:
    HUD();
    virtual ~HUD();
    void update();
    void display();
private:
    Image *background;
    Coordinates *coords;
};

#endif	/* HUD_H */


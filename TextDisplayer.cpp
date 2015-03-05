/* 
 * File:   TextDisplayer.cpp
 * Author: Qb
 * 
 * Created on 5 marzec 2015, 17:56
 */

#include "TextDisplayer.h"
#include "globalVariables.h"

void TextDisplayer::displayInt(double X, double Y, int toDisplay)
{
        char text[100];
        itoa(toDisplay ,text, 10);
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, text);
}

void TextDisplayer::displayText(double X, double Y, std::string text)
{
    char toDisplay[100];
    strcpy(toDisplay, text.c_str());
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, toDisplay);
}
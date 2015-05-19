/* 
 * File:   globalVariables.h
 * Author: Qb
 *
 * Created on 5 lipiec 2014, 21:54
 */

#ifndef GLOBALVARIABLES_H
#define	GLOBALVARIABLES_H


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/events.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <cmath>
#include "Session.h"
#include "GameSubstateEnum.h"
#include "LogLevels.h"
#include "GlobalImages.h"

enum GAME_STATE
{
    MENU, GAME_START, GAME, END, WIN
};

struct Variables
{
    static ALLEGRO_DISPLAY *display;
    static int RES_WIDTH;
    static int RES_HEIGHT;
    static const float fps;
    
    static ALLEGRO_BITMAP *MouseCoursor;
    static ALLEGRO_FONT *basicFont;
    static double offsetX;
    static double offsetY;
    static float ScaleX;
    static float ScaleY;
    static double scale;
    
    static ALLEGRO_KEYBOARD_STATE key_state;
    static ALLEGRO_MOUSE_STATE mouse_state;
    static double mouse_x;
    static double mouse_y;
    
    static ALLEGRO_EVENT_QUEUE *event_queue;
    static ALLEGRO_TIMER *timer;
    static Session *session;
    static GAME_STATE status;
    static int currentFrame;
    
    static const int damageTypeCount;
    
    static const int tilesPerRoom;
    static const int tileSize;
    
    static LogLevel log;
    
    static GAME_SUBSTATE substate;
    
    static GlobalImages *images;
    static bool isMonsterShoot;
    void static giveFactors(double angle, double &x_factor, double &y_factor)
     {
     x_factor = cos(((angle - 90)* M_PI) / 180 );
     y_factor = sin(((angle - 90)* M_PI) / 180 );
     }
    double static proximity(double x1, double y1, double x2, double y2)
    {        
      double a = x1, b = x2, c = y1, d = y2;
      return sqrt(pow(a - b, 2) + pow(c - d, 2));
    }
    
    double static squaredProximity(double x1, double y1, double x2, double y2)
    {
        return pow(x1 - x2, 2) + pow(y1 - y2, 2);
    }
    
    double static getAngle(double x1, double y1, double x2, double y2)
    {
        double angle;
        double dX, dY;
        dX = x2 - x1;
        dY = y1 - y2;
        angle = 180 + (atan(dX/dY) * 180 / M_PI);
        if(y2 <= y1)angle += 180;
        return angle;
    }
};
#endif	/* GLOBALVARIABLES_H */


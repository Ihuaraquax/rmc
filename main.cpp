/* 
 * File:   main.cpp
 * Author: Qb
 *
 * Created on 16 listopad 2014, 12:52
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/events.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "globalVariables.h"
#include "Session.h"
#include "Console.h"
using namespace std;


int  Variables::RES_WIDTH = 1024;
int  Variables::RES_HEIGHT = 768;
const float  Variables::fps = 120;

double  Variables::offsetX = 0;
double  Variables::offsetY = 0;
float  Variables::ScaleX = 1;
float  Variables::ScaleY = 1;

ALLEGRO_KEYBOARD_STATE  Variables::key_state;
ALLEGRO_MOUSE_STATE  Variables::mouse_state;
double  Variables::mouse_x;
double  Variables::mouse_y;

GAME_STATE  Variables::status = GAME;
Session *Variables::session;

ALLEGRO_EVENT_QUEUE *Variables::event_queue;
ALLEGRO_TIMER *Variables::timer;
ALLEGRO_DISPLAY *Variables::display;
ALLEGRO_FONT *Variables::basicFont;

ALLEGRO_BITMAP *Variables::MouseCoursor;

MainGameState Session::gameState = MAP;
GAME_SUBSTATE Variables::substate = game;

int const Variables::damageTypeCount = 6;

int const Variables::tilesPerRoom = 40;
int const Variables::tileSize = 50;
int Variables::currentFrame = 0;
bool Variables::isMonsterShoot = true;

LogLevel Variables::log = none;
GlobalImages *Variables::images;
double Variables::scale = 1;
bool Variables::skillRedistributionAviable = false;

double Console::offsetX = 0;
double Console::offsetY = 0;

Entity *Variables::currentProjectile = NULL;

int main(int argc, char** argv) {
    Variables::session = new Session();
    Variables::session->create();
    
    srand(time(NULL));
    
    Variables::session->loop();
    
    delete Variables::session;
    return 0;
}

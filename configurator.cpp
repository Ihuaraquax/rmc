/* 
 * File:   configurator.cpp
 * Author: Qb
 * 
 * Created on 16 listopad 2014, 12:31
 */

#include "configurator.h"
#include "globalVariables.h"

configurator::configurator() {
}

void configurator::config()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    Variables::timer = al_create_timer(1.0 / Variables::fps);
    Variables::event_queue = al_create_event_queue();
//    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    Variables::display = al_create_display(Variables::RES_WIDTH, Variables::RES_HEIGHT);
    al_register_event_source(Variables::event_queue, al_get_timer_event_source(Variables::timer));
    al_register_event_source(Variables::event_queue, al_get_keyboard_event_source());
    float x = Variables::RES_WIDTH;
    float y = Variables::RES_HEIGHT;
    x /= 1024;
    y /= 768;
    Variables::ScaleX = x;
    Variables::ScaleY = y;
    srand(time(NULL));
    al_start_timer(Variables::timer);
    Variables::MouseCoursor = al_load_bitmap("images/coursor.png");
    al_convert_mask_to_alpha(Variables::MouseCoursor, al_map_rgb(255,0,255));
    ALLEGRO_MOUSE_CURSOR *temp = al_create_mouse_cursor(Variables::MouseCoursor, 16, 16);
    al_set_mouse_cursor(Variables::display, temp);
    Variables::basicFont = al_load_ttf_font("pirulen.ttf",14,0 );
}
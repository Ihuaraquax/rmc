/* 
 * File:   Image.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:27
 */

#include "Image.h"
#include "globalVariables.h"

Image::Image(std::string path, bool isMask) {
    image = al_load_bitmap(path.c_str());
    if(isMask)al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
    imageCenterX = al_get_bitmap_width(image)/2;
    imageCenterY = al_get_bitmap_height(image)/2;
    this->state = BASIC;
    imagePath = path;
}

Image::~Image() {
    al_destroy_bitmap(image);
}

void Image::display(Coordinates* coords){
    switch(state)
    {
        case BASIC:
            displayBasic(coords);
            break;
        case NORMAL:
            displayNormal(coords);
            break;
        case REPEATING:
            displayMultiples(coords);
            break;
        case CUT:
            displayCut(coords);
            break;
        case UI:
            displayUI(coords);
            break;
            
    }
}

void Image::displayCut(Coordinates* coords)
{    
    double X = (coords->X + coords->width/2 - Variables::offsetX) * Variables::ScaleX * Variables::scale;
    double Y = (coords->Y + coords->height/2 - Variables::offsetY) * Variables::ScaleY * Variables::scale;
    ALLEGRO_BITMAP *cutImage = al_create_sub_bitmap(image, 0, 0, coords->width, coords->height);
    double angle = (coords->angle *M_PI)/ 180;
    al_draw_scaled_rotated_bitmap(image, imageCenterX, 
            imageCenterY, X, Y, Variables::ScaleX * Variables::scale, Variables::ScaleY * Variables::scale, angle, 0);
    al_destroy_bitmap(cutImage);
}

void Image::displayMultiples(Coordinates* coords)
{
    
    //calculate now so that it wont be necessary later
    int rowCount = floor(coords->height/(imageCenterY)) /2;
    int colCount = floor(coords->width/(imageCenterX)) /2;
    
    //initialiaze cutCoordinates
    Coordinates *temp = new Coordinates();
    temp->angle = 0;
    temp->X = coords->X;
    temp->Y = coords->Y;
    temp->height = imageCenterY * 2;
    
    //display most of image, besides rightmost and lowermost side, 
    //that could potetialy be cut
    for(int i = 0; i < rowCount; i++)
    {
        temp->width = imageCenterX * 2;
        temp->X = coords->X;
        for(int j = 0; j < colCount; j++)
        {
            displayNormal(temp);
            temp->X += temp->width;
        }
        temp->width = coords->width - (temp->width * colCount);
        displayCut(temp);
        temp->Y += temp->height;
    }
    
    // display lowermost side besides last piece
    temp->X = coords->X;
    temp->height = coords->height - (temp->height * rowCount);
    temp->width = imageCenterX * 2;
    for(int i = 0; i < colCount; i++)
    {
        displayCut(temp);
        temp->X += temp->width;
    }
    
    //display last piece
    temp->width = coords->width - temp->width * colCount;
    displayCut(temp);
}

void Image::displayBasic(Coordinates* coords)
{
    al_draw_bitmap(image, coords->X - Variables::offsetX,
            coords->Y - Variables::offsetY, 0);
}

void Image::displayNormal(Coordinates* coords)
{
    double X = (coords->X + coords->width/2 - Variables::offsetX) * Variables::ScaleX * Variables::scale;
    double Y = (coords->Y + coords->height/2 - Variables::offsetY) * Variables::ScaleY * Variables::scale;
    double angle = (coords->angle *M_PI)/ 180;
    al_draw_scaled_rotated_bitmap(image, imageCenterX, 
            imageCenterY, X, Y, Variables::ScaleX * Variables::scale, Variables::ScaleY * Variables::scale, angle, 0);
}

void Image::displayUI(Coordinates* coords)
{
    al_draw_bitmap(image, coords->X, coords->Y, 0);
}

std::string Image::getImagePath() const {
    return imagePath;
}
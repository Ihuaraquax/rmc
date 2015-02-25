/* 
 * File:   Image.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:27
 */

#include "Image.h"
#include "globalVariables.h"

Image::Image(int count, std::string paths[], bool isMask) {
    this->images = new ALLEGRO_BITMAP*[count];
    this->imageCount = count;
    this->currentImage = 0;
    this->imageCenterX = new int[count];
    this->imageCenterY = new int[count];
    for(int i = 0; i < count; i++)
    {
        images[i] = al_load_bitmap(paths[i].c_str());
        if(isMask)al_convert_mask_to_alpha(images[i], al_map_rgb(255,0,255));
        imageCenterX[i] = al_get_bitmap_width(images[i])/2;
        imageCenterY[i] = al_get_bitmap_height(images[i])/2;
    }
    this->order = LOOP;
    this->state = BASIC;
}

Image::~Image() {
    for(int i = 0; i < imageCount; i++)
    {
        al_destroy_bitmap(images[i]);
    }
    delete []images;
    delete imageCenterX;
    delete imageCenterY;
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
    if(order == LOOP)
    {
        currentImage++;
        currentImage %= imageCount;
    }
    if(order == RANDOM)
    {
        currentImage = rand()%imageCount;
    }
}

void Image::displayCut(Coordinates* coords)
{    
    ALLEGRO_BITMAP *cutImage = al_create_sub_bitmap(images[currentImage], 0, 0, coords->width, coords->height);
    al_draw_bitmap(cutImage, coords->X - Variables::offsetX, coords->Y - Variables::offsetY, 0);
    al_destroy_bitmap(cutImage);
}

void Image::displayMultiples(Coordinates* coords)
{
    
    //calculate now so that it wont be necessary later
    int rowCount = floor(coords->height/(imageCenterY[currentImage] *2 * Variables::ScaleX));
    int colCount = floor(coords->width/(imageCenterX[currentImage]*2* Variables::ScaleX));
    
    //initialiaze cutCoordinates
    Coordinates *temp = new Coordinates();
    temp->X = coords->X;
    temp->Y = coords->Y;
    temp->height = imageCenterY[currentImage] * 2;
    
    //display most of image, besides rightmost and lowermost side, 
    //that could potetialy be cut
    for(int i = 0; i < rowCount; i++)
    {
        temp->width = imageCenterX[currentImage] * 2;
        temp->X = coords->X;
        for(int j = 0; j < colCount; j++)
        {
            displayBasic(temp);
            temp->X += temp->width;
        }
        temp->width = coords->width - (temp->width * colCount);
        displayCut(temp);
        temp->Y += temp->height;
    }
    
    // display lowermost side besides last piece
    temp->X = coords->X;
    temp->height = coords->height - (temp->height * rowCount);
    temp->width = imageCenterX[currentImage] * 2;
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
    al_draw_bitmap(images[currentImage], coords->X - Variables::offsetX,
            coords->Y - Variables::offsetY, 0);
}

void Image::displayNormal(Coordinates* coords)
{
    double angle = (coords->angle *M_PI)/ 180;
    al_draw_scaled_rotated_bitmap(images[currentImage], 
            imageCenterX[currentImage], imageCenterY[currentImage], 
            coords->X + (coords->width/2) - Variables::offsetX, coords->Y + (coords->height/2) - Variables::offsetY, 
            Variables::ScaleX, Variables::ScaleY, angle, 0);
}

void Image::displayUI(Coordinates* coords)
{
    al_draw_bitmap(images[currentImage], coords->X, coords->Y, 0);
}

void Image::nextImage()
{
    currentImage++;
    currentImage %= imageCount;
}

void Image::specificImage(int imageNo)
{
    currentImage = imageNo;
    currentImage %= imageCount;
}
/* 
 * File:   Animation.cpp
 * Author: Qb
 * 
 * Created on 21 maj 2015, 19:35
 */

#include "Animation.h"
#include "globalVariables.h"

Animation::Animation() {
    currentImage = 0;
    imageCount = 0;
    images = NULL;
    timer = 0;
    delay = 0;
}

Animation::~Animation() {
    for(int i = 0; i < this->imageCount; i++)delete images[i];
    delete []images;
}


void Animation::setAnimation(std::string file, int frameWidth, int frameHeight)
{
    ALLEGRO_BITMAP *image = al_load_bitmap(file.c_str());
    int width = al_get_bitmap_width(image);
    int height = al_get_bitmap_height(image);
    imageCount = (width/frameWidth) * (height/frameHeight);
    images = new Image*[imageCount];
    for(int i = 0; i < height/frameHeight; i++)
    {
        for(int j = 0; j < width/frameWidth; j++)
        {
            ALLEGRO_BITMAP *cutImage = al_create_sub_bitmap(image, j * frameWidth, i * frameHeight, frameWidth, frameHeight);
            images[currentImage] = new Image(cutImage, true); 
            images[currentImage]->state = NORMAL;
            currentImage++;
        }
    }
    imageCount = currentImage;
    currentImage = 0;
//    al_destroy_bitmap(image);
}

void Animation::display(Coordinates* coords)
{
    images[currentImage]->display(coords);
    timer++;
    if(timer >= delay)
    {
        timer = 0;
        currentImage++;
    }
    if(currentImage == imageCount)currentImage = 0;
}
void Animation::setDelay(int delay)
{
    this->delay = delay;
}
void Animation::setDuration(int seconds)
{
    this->delay = (seconds * Variables::fps) / imageCount;
}
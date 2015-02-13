/* 
 * File:   Weapon.cpp
 * Author: Qb
 * 
 * Created on 6 styczeń 2015, 12:50
 */

#include "Weapon.h"
#include "globalVariables.h"
#include "Projectile.h"
#include "WeaponLoader.h"

Weapon::Weapon() {
    ammoMax = 100;
    ammoCurrent = 100;
    reloadSpeed = 120;
    damage = 10;
    cooldown = 20;
    timeToShoot = 0;
    reloading = false;
    damageType = normal;
    defaultTargetSize = 10;
    currentTargetSize = 10;
    targetSizeIncrement = 15;
    targetSizeDecrement = 2;
    targetSizeIncrementSlowDownPoint = 30;
    range = -1;
    displayPaths = "images/weaponImage.png";
    projectileCount = 1;
    name = "test";
}

void Weapon::update()
{
    if(timeToShoot > 0)timeToShoot--;
    if(ammoCurrent == 0 && !reloading)reload();
    if(timeToShoot == 0 && reloading)
    {
        ammoCurrent = ammoMax;
        reloading = false;
    }
    if(Variables::currentFrame % 3 == 0)if(currentTargetSize > defaultTargetSize)
    {
        currentTargetSize -= targetSizeDecrement;
        if(currentTargetSize < defaultTargetSize)currentTargetSize = defaultTargetSize;
    }
}

void Weapon::shoot(Coordinates *shooterCoords, Coordinates *targetCoords, int team)
{
    if(!reloading && timeToShoot == 0)
    {
        ammoCurrent--;
        timeToShoot = cooldown;
        for(int i = 0; i < projectileCount; i++)
        {
            Entity *bullet = new Projectile();
            int angle = getAngle(shooterCoords, targetCoords);
            dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage, damageType, angle, team, range);
            Variables::session->getAllEntities()->addEntity(bullet);
        }
        currentTargetSize += targetSizeIncrement - (currentTargetSize / targetSizeIncrementSlowDownPoint);
    }
}

void Weapon::reload()
{
    timeToShoot = reloadSpeed;
    reloading = true;
}

double Weapon::getAngle(Coordinates* shooterCoords, Coordinates* targetCoords)
{
    double tX = targetCoords->X, tY = targetCoords->Y, dX, dY;
    int distance = rand()%this->currentTargetSize;
    double factorX, factorY;
    Variables::giveFactors(rand()%360, factorX, factorY);
    tX += distance * factorX;
    tY += distance * factorY;
    dX = (tX - 8) - (shooterCoords->X - Variables::offsetX);
    dY = (shooterCoords->Y - Variables::offsetY) - (tY - 8);
    double angle = 180 + (atan(dX/dY) * 180 / M_PI);
    if(tY <= (shooterCoords->Y - Variables::offsetY))angle += 180;
    if(tX > shooterCoords->X && angle > 260 && angle < 280)angle -= 180;
    if(tX < shooterCoords->X && angle < 100 && angle > 70)angle += 180;
    return angle;
}

int Weapon::getCurrentTargetSize() const {
    return currentTargetSize;
}

int Weapon::getAmmoCurrent() const {
    return ammoCurrent;
}

int Weapon::getAmmoMax() const {
    return ammoMax;
}

std::string Weapon::getDisplayPaths() const {
    return displayPaths;
}
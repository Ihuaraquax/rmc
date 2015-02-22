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
    ammoMax = 1;
    ammoCurrent = 1;
    reloadSpeed = 0;
    damage = 0;
    cooldown = 0;
    timeToShoot = 0;
    reloading = false;
    damageType = normal;
    defaultTargetSize = 1;
    currentTargetSize = 1;
    targetSizeIncrement = 1;
    targetSizeDecrement = 1;
    targetSizeIncrementSlowDownPoint = 10;
    range = 0;
    displayPaths = "images/noWeapon.png";
    projectileCount = 0;
    name = "noWeapon";
    criticalChance = 10;
    criticalDamage = 2;
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

void Weapon::shoot(Coordinates *shooterCoords, Coordinates *targetCoords, int team, int shooterCriticalChance, double shooterCriticalDamage, double accuracy)
{
    if(!reloading && timeToShoot == 0)
    {
        ammoCurrent--;
        timeToShoot = cooldown;
        for(int i = 0; i < projectileCount; i++)
        {
            bool critical = rand()%100 < criticalChance + shooterCriticalChance;
            Entity *bullet = new Projectile();
            int angle = getAngle(shooterCoords, targetCoords);
            if(critical)dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage * (criticalDamage + shooterCriticalDamage), damageType, angle, team, range);
            else dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage, damageType, angle, team, range);
            Variables::session->getAllEntities()->addEntity(bullet);
        }
        double increment = (targetSizeIncrement - accuracy) - (currentTargetSize / targetSizeIncrementSlowDownPoint);
        if(increment > 0)currentTargetSize += increment;
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
    int distance = rand()%(int)ceil(this->currentTargetSize);
    double factorX, factorY;
    Variables::giveFactors(rand()%360, factorX, factorY);
    tX += distance * factorX;
    tY += distance * factorY;
    dX = (tX - 8) - (shooterCoords->X - Variables::offsetX);
    dY = (shooterCoords->Y - Variables::offsetY) - (tY - 8);
    double angle = 180 + (atan(dX/dY) * 180 / M_PI);
    if(tY <= (shooterCoords->Y - Variables::offsetY))angle += 180;
    if(tX > shooterCoords->X - Variables::offsetX && angle > 260 && angle < 280)angle -= 180;
    if(tX < shooterCoords->X - Variables::offsetX && angle < 100 && angle > 70)angle += 180;
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

std::string Weapon::getName() const {
    return name;
}
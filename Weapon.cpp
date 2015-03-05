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
#include "Player.h"
#include "ProjectileFactory.h"

Weapon::Weapon() {
    weaponId = -1;
    ammoMax = 1;
    ammoCurrent = 0;
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
    range = -1;
    displayPaths = "images/noWeapon.png";
    projectileCount = 0;
    name = "noWeapon";
    criticalChance = 10;
    criticalDamage = 2;
    reloadable = false;
    playerIsWielder = false;
    ammoType = -1;
}

void Weapon::update()
{
    if(timeToShoot > 0)timeToShoot--;
    if(ammoCurrent == 0 && !reloading)reload();
    if(timeToShoot == 0 && reloading && reloadable)
    {
        if(playerIsWielder)
        {
            Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
            if(player->getAmmo(ammoType) > this->ammoMax) ammoCurrent = ammoMax;
            else ammoCurrent = player->getAmmo(ammoType);
            player->addAmmo(-ammoCurrent, ammoType);
            if(player->getAmmo(ammoType) == 0)reloadable = false;
        }
        else ammoCurrent = ammoMax;
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
            Entity *bullet = ProjectileFactory::provideProjectile(weaponId, 0);
            int angle = getAngle(shooterCoords, targetCoords);
            if(critical)dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage * (criticalDamage + shooterCriticalDamage), damageType, angle, team, range);
            else dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage, damageType, angle, team, range);
            if(weaponId == 33)dynamic_cast<Projectile*>(bullet)->setRange(Variables::proximity(shooterCoords->X - Variables::offsetX, shooterCoords->Y - Variables::offsetY, targetCoords->X, targetCoords->Y) - 30);
            if(shooterCoords == targetCoords)
            {
                bullet->getCoords()->angle = shooterCoords->angle + (rand()%40 - 20);
                Variables::giveFactors(bullet->getCoords()->angle, bullet->getCoords()->speedX, bullet->getCoords()->speedY);
                double speed = 0.0 + rand()% 20;
                speed /=10;
                speed += 4;
                bullet->getCoords()->speedX *= speed + 15;
                bullet->getCoords()->speedY *= speed + 15;
            }
            Variables::session->getAllEntities()->addEntity(bullet);
        }
        double increment = (targetSizeIncrement - accuracy) - (currentTargetSize / targetSizeIncrementSlowDownPoint);
        if(increment > 0)currentTargetSize += increment;
    }
}

void Weapon::reload()
{
    if(reloadable)timeToShoot = reloadSpeed;
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

void Weapon::setReloadable(bool reloadable) {
    this->reloadable = reloadable;
}

void Weapon::setPlayerIsWielder(bool playerIsWielder) {
    this->playerIsWielder = playerIsWielder;
}

int Weapon::getAmmoType() const {
    return ammoType;
}

void Weapon::setAmmoCurrent(int ammoCurrent) {
    this->ammoCurrent = ammoCurrent;
}

int Weapon::getWeaponId() const {
    return weaponId;
}

void Weapon::setRange(int range) {
    this->range = range;
}
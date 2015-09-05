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
#include "LightSource.h"

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
    criticalChance = 1;
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
        decreaseAmmo();
        reloading = false;
    }
    if(Variables::currentFrame % 3 == 0)if(currentTargetSize > defaultTargetSize)
    {
        currentTargetSize -= targetSizeDecrement;
        if(currentTargetSize < defaultTargetSize)currentTargetSize = defaultTargetSize;
    }
}

void Weapon::decreaseAmmo()
{
    int ammoToLoad = ammoMax;
    if(playerIsWielder && Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[16] == 0)
    {
        Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
        if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[22] == 1)ammoToLoad = 1;
        if(player->getAmmo(ammoType) > ammoToLoad) ammoCurrent = ammoToLoad;
        else ammoCurrent = player->getAmmo(ammoType);
        player->addAmmo(-ammoCurrent, ammoType);
        if(player->getAmmo(ammoType) == 0)reloadable = false;
    }
    else ammoCurrent = ammoToLoad;
}

void Weapon::shoot(Coordinates *shooterCoords, Coordinates *targetCoords, int team, int shooterCriticalChance, double shooterCriticalDamage, double accuracy)
{
    double incrementModificator = 1;
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[23] == 1)incrementModificator = 3;
    else if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[24] == 1)incrementModificator = 0.3;
    if(shooterCoords == targetCoords) this->shootMIRV(shooterCoords, team);
    else
    {
        if(!reloading && timeToShoot == 0)
        {
            ammoCurrent--;
            timeToShoot = cooldown;
            for(int i = 0; i < projectileCount; i++)
            {
                bool critical = rand()%100 < criticalChance + shooterCriticalChance;
                if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[25] == 1)critical = true;
                else if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[26] == 1)critical = false;
                Entity *bullet = ProjectileFactory::provideProjectile(weaponId, 0);
                int angle = getAngle(shooterCoords, targetCoords);
                if(critical)dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage * (criticalDamage + shooterCriticalDamage), damageType, angle, team, range);
                else dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage, damageType, angle, team, range);
                if(weaponId == 33)dynamic_cast<Projectile*>(bullet)->setRange(Variables::proximity(shooterCoords->X - Variables::offsetX, shooterCoords->Y - Variables::offsetY, targetCoords->X, targetCoords->Y) - 30);
                Variables::session->getAllEntities()->addEntity(bullet);
                Variables::currentProjectile = bullet;
            }
            double increment = (targetSizeIncrement - accuracy) - (currentTargetSize / targetSizeIncrementSlowDownPoint);
            if(increment > 0)currentTargetSize += (increment * incrementModificator);
//            createBlast(shooterCoords);
        }
    }
}

void Weapon::shoot(Coordinates* shooterCoords, int team, int shooterCriticalChance, double shooterCriticalDamage, double accuracy)
{
    shooterCoords->X += shooterCoords->width/2;
    shooterCoords->Y += shooterCoords->height/2;
    if(!reloading && timeToShoot == 0)
    {
        ammoCurrent--;
        timeToShoot = cooldown;
        for(int i = 0; i < projectileCount; i++)
        {
            bool critical = rand()%100 < criticalChance + shooterCriticalChance;
            Entity *bullet = ProjectileFactory::provideProjectile(weaponId, 0);
            int angle = (shooterCoords->angle - rand()%20) + 10;
            if(critical)dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage * (criticalDamage + shooterCriticalDamage), damageType, angle, team, range);
            else dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage, damageType, angle, team, range);
            Variables::session->getAllEntities()->addEntity(bullet);
            Variables::currentProjectile = bullet;
        }
        double increment = (targetSizeIncrement - accuracy) - (currentTargetSize / targetSizeIncrementSlowDownPoint);
        if(increment > 0)currentTargetSize += increment;
//        createBlast(shooterCoords);
    }
    shooterCoords->X -= shooterCoords->width/2;
    shooterCoords->Y -= shooterCoords->height/2;
}

void Weapon::shootMIRV(Coordinates *shooterCoords, int team)
{
    for(int i = 0; i < projectileCount; i++)
    {
        Entity *bullet = ProjectileFactory::provideProjectile(weaponId, 0);
        dynamic_cast<Projectile*>(bullet)->setValues(shooterCoords, damage, damageType, 0, team, range);
        bullet->getCoords()->angle = shooterCoords->angle + (rand()%40 - 20);
        Variables::giveFactors(bullet->getCoords()->angle, bullet->getCoords()->speedX, bullet->getCoords()->speedY);
        double speed = 0.0 + rand()% 20;
        speed /=10;
        speed += 4;
        bullet->getCoords()->speedX *= speed + 15;
        bullet->getCoords()->speedY *= speed + 15;
        Variables::session->getAllEntities()->addEntity(bullet);
    }
}

void Weapon::reload()
{
    if(reloadable)
    {
        if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[14] == 1)timeToShoot = reloadSpeed *0.2;
        else if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[15] == 1)timeToShoot = reloadSpeed *1.8;
        else timeToShoot = reloadSpeed;
    }
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

void Weapon::setDamageType(DAMAGE_TYPE damageType) {
    this->damageType = damageType;
}

void Weapon::createBlast(Coordinates *shooterCoords)
{
    LightSource *source = new LightSource("images/bigLight.png");
    double sX, sY;
    Variables::giveFactors(shooterCoords->angle, sX, sY);
    source->getCoords()->X = shooterCoords->X + (20 *sX);
    source->getCoords()->Y = shooterCoords->Y + (20 *sY);
    source->setTime(5);
    source->increaseTileLightValue();
    Variables::session->getMap()->getAllLightSources()->addSource(source);
}
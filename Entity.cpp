/* 
 * File:   Entity.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:37
 */

#include "Entity.h"
#include "Coordinates.h"
#include "Image.h"
#include "globalVariables.h"
#include "ModuleTile.h"
#include "CollisionDetector.h"
#include "TimedBuffer.h"
#include "DistanceBuffer.h"
#include "BloodSplatter.h"
#include "WeaponLoader.h"
#include "Projectile.h"

Entity::Entity() {
    armor = 0;
    elementalResists = new double[Variables::damageTypeCount];
    for(int i = 0; i < Variables::damageTypeCount; i++)this->elementalResists[i] = 0.0;
    aiValue = 0;
    maximumHealth = health;
    criticalChance = 0;
    criticalDamage = 0;
    accuracy = 0;
    bufferList = NULL;
    bleeds= false;
    shape = rectangle;
    health = 1;
    maximumHealth = 1;
    criticalChance = 0;
    criticalDamage = 0;
    teamId = 0;
    threatLevel = 0;
    for(int i = 0; i < Variables::damageTypeCount; i++)elementalResists[i] = 0;
    possessedWeapons = 0;
    image = NULL;
    planCoords = new Coordinates();
}

Entity::~Entity() {
    delete coords;
    image = NULL;
}

void Entity::display(){
    image->display(coords);
}

void Entity::move(double X, double Y){
    
    double speedX = this->coords->speedX + this->getValueOfBuffer(0);
    double speedY = this->coords->speedY + this->getValueOfBuffer(0);
    
    ModuleTile *currentTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    
    this->coords->X += X * speedX;
    ModuleTile *newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(newTile != NULL)
    {
        if(CollisionDetector::isAnyCollision(newTile, this))
        {
            this->coords->X -= X * speedX;
        }
    }
    else
    {
        this->coords->X -= X * speedX;
    }
    
    
    this->coords->Y += Y * speedY;
    newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(newTile != NULL)
    {
    if(CollisionDetector::isAnyCollision(newTile, this))
    {
        this->coords->Y -= Y * speedY;
    }
    }
    else
    {
        this->coords->Y -= Y * speedY;
    }
    
    newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(currentTile != newTile)
    {
        currentTile->deleteFromEntityList(this);
        currentTile->addToThreatLevel(-threatLevel);
        newTile->addToEntityList(this);
        newTile->addToThreatLevel(threatLevel);
    }
}

void Entity::update(){
    
}


Coordinates* Entity::getCoords() const {
    return coords;
}

int Entity::getHealth() const {
    return health;
}

void Entity::getHit(int damage, int damageType)
{
    double *table = Variables::session->getMap()->getCurrentModule()->getModificatorsTable();
    if(table[58] != 0 && damageType == 1)damageType = 3;
    if(table[59] != 0 && damageType == 3)damageType = 4;
    if(table[60] != 0 && damageType == 4)damageType = 2;
    if(table[61] != 0 && damageType == 2)damageType = 1;
    double resist = 1-elementalResists[damageType];
    if(table[63] != 0)resist = this->getSmallestResistance();
    if(table[27+damageType] != 0)resist = 1;
    int damageInflicted = (damage - armor) * resist;
    if(damageInflicted < 0)damageInflicted = 0;
    else if (bleeds)
    {
        Decal *decal = new BloodSplatter(coords->X, coords->Y);
        Variables::session->getMap()->getCurrentModule()->getAllDecals()->addDecal(decal);
    }
    health -= damageInflicted;
}

void Entity::attack(int weapon)
{
    if(weapons[weapon]->getWeaponId() != -1)weapons[weapon]->shoot(coords, targetCoords, teamId, criticalChance, criticalDamage, accuracy);
    if(Variables::currentProjectile != NULL)
    {
        dynamic_cast<Projectile*>(Variables::currentProjectile)->setShooter(this);
        Variables::currentProjectile = NULL;
    }
}

int Entity::getTeamId() const {
    return teamId;
}

void Entity::setStartingTile()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToEntityList(this);
}


bool Entity::isProjectile()
{
    return false;
}

bool Entity::isBarricade()
{
    return false;
}

int Entity::getAiValue() const {
    return aiValue;
}

void Entity::executeAgony()
{
    
}

int Entity::getArmor() const {
    return armor;
}

void Entity::heal(int healAmount)
{
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[77] == 1)healAmount *= 1.8;
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[18] != 0)this->getHit(healAmount, normal);
    else
    {
        this->health += healAmount;
        if(this->health > this->maximumHealth) health = maximumHealth;
    }
}

double Entity::getValueOfBuffer(int type)
{
    double result = 0;
    templateList<GenericBuffer> *buffers = this->bufferList;
    while(buffers != NULL)
    {
        if(buffers->data->GetBuffType() == type)result += buffers->data->GetBuffValue();
        buffers = buffers->next;
    }
    buffers = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->getBufferList();
    
    while(buffers != NULL)
    {
        if(buffers->data->GetBuffType() == type)
        {
            DistanceBuffer *distanceBuffer = static_cast<DistanceBuffer*>(buffers->data);
            if(distanceBuffer->isInRange(coords->X, coords->Y))result += buffers->data->GetBuffValue();
        }
        buffers = buffers->next;
    }
    return result;
}

void Entity::updateBuffers()
{
    templateList<GenericBuffer> *buffers = this->bufferList;
    while(buffers != NULL)
    {
        static_cast<TimedBuffer*>(buffers->data)->SetBuffTime(static_cast<TimedBuffer*>(buffers->data)->GetBuffTime()-1);
        if(static_cast<TimedBuffer*>(buffers->data)->GetBuffTime() == 0)
        {
            templateList<GenericBuffer> *toDelete = buffers;
            buffers = buffers->next;
            if(toDelete != bufferList)this->bufferList->findPrevious(toDelete->data)->next = buffers;
            else bufferList = buffers;
            delete toDelete->data;
            delete toDelete;
        }
        else buffers = buffers->next;
    }
}

void Entity::addBuffer(GenericBuffer* buffer)
{
    templateList<GenericBuffer> *newBuffer = new templateList<GenericBuffer>();
    newBuffer->data = buffer;
    newBuffer->next = bufferList;
    bufferList = newBuffer;
}

void Entity::setCoords(double X, double Y)
{
    coords->X = X;
    coords->Y = Y;
}

EntityShape Entity::getShape() const {
    return shape;
}

void Entity::adaptToModificators()
{
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[3] != 0)
    {
        this->health *= 0.5;
        this->maximumHealth *= 0.5;
    }
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[4] != 0)
    {
        this->health *= 2;
        this->maximumHealth *= 2;
    }
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[5] != 0)
    {
        this->coords->speedX *= 1.5;
        this->coords->speedY *= 1.5;
    }
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[6] != 0)
    {
        this->coords->speedX *= 0.65;
        this->coords->speedY *= 0.65;
    }
}

double Entity::getSmallestResistance()
{
    double result = this->elementalResists[0];
    for(int i = 0; i < Variables::damageTypeCount; i++)
        if(this->elementalResists[i] < result)result = this->elementalResists[i];
    return result;
}

void Entity::save(std::fstream& file)
{
    
}

void Entity::load(std::fstream& savefile)
{
    
}

void Entity::saveGeneric(std::fstream& file)
{    
    file << health << ' ' << coords->X << ' ' << coords->Y << ' ' << coords->angle
         << ' ' << coords->speedX << ' ' << coords->speedY << ' ' << maximumHealth  << ' ' << aiValue << ' ' << criticalChance  << ' ' <<  criticalDamage;
    file << ' ' << teamId << ' ' << threatLevel << ' ';
    for(int i = 0; i < Variables::damageTypeCount; i++)file << elementalResists[i] << ' ';
    if(bleeds)file << 1 << ' ';
    else file << 0 << ' ';
    file << possessedWeapons << ' ';
    for(int i = 0; i < possessedWeapons; i++)file << weapons[i]->getWeaponId() << ' ' << weapons[i]->getAmmoCurrent() << ' ';
}

void Entity::loadGeneric(std::fstream& file)
{
    file >> health >> coords->X >> coords->Y >> coords->angle >> coords->speedX >> coords->speedY >> maximumHealth  >> aiValue >> criticalChance  >>  criticalDamage;
    file >> teamId >> threatLevel;
    for(int i = 0; i < Variables::damageTypeCount; i++)file >> elementalResists[i];
    int bleedsValue;
    file >> bleedsValue;
    file >> possessedWeapons;
    int weaponIds[possessedWeapons];
    int weaponsAmmos[possessedWeapons];
    for(int i = 0; i < possessedWeapons; i++)
    {
        file >> weaponIds[i] >> weaponsAmmos[i];
        weapons[i] = new Weapon();
        WeaponLoader::loadWeapon(weapons[i], weaponIds[i]);
        weapons[i]->setAmmoCurrent(weaponsAmmos[i]);
    }
    this->setStartingTile();
}

void Entity::displayPlan()
{
    
}

void Entity::setPlanCoords(int X, int Y)
{
    planCoords->X = coords->X + X * (Variables::tileSize * Variables::tilesPerRoom + 100);
    planCoords->Y = coords->Y + Y * (Variables::tileSize * Variables::tilesPerRoom + 100);
    planCoords->angle = coords->angle;
    planCoords->width = coords->width;
    planCoords->height = coords->height;
}

void Entity::RCUse()
{
    
}

Entity* Entity::getIgnoreCollisionEntity() const {
    return ignoreCollisionEntity;
}

void Entity::setIgnoreCollisionEntity(Entity* ignoreCollisionEntity) {
    this->ignoreCollisionEntity = ignoreCollisionEntity;
}

Coordinates* Entity::getPlanCoords() const {
    return planCoords;
}

int Entity::getModuleThreatLevel() const {
    return moduleThreatLevel;
}

std::string Entity::getEntityType()
{
    return "BASIC_ENTITY";
}
/* 
 * File:   AllEntities.cpp
 * Author: Qb
 * 
 * Created on 16 listopad 2014, 11:31
 */

#include "AllEntities.h"
#include "Player.h"
#include "Monster.h"
#include "Turret.h"
#include "globalVariables.h"
#include "Obstacle.h"
#include "Chest.h"
#include "Spawner.h"
#include "DistanceBuffer.h"
#include "BuffRod.h"
#include "ExplosiveBarrel.h"
#include "RemoteCharges.h"
#include "ObstacleDoor.h"
#include "DoorFactory.h"
#include "Explosives.h"
#include "Key.h"
#include "Lock.h"
#include "Console.h"
#include "ModuleDoor.h"
#include "ModuleDoorEntities.h"
#include <iostream>
  
AllEntities::AllEntities() {
    remoteCharges = NULL;
    threatLevel = 0;
    virtualThreatLevel = 100;
    maxThreatLevel = 300;
    moduleDoors = new ModuleDoorEntities();
    possibleMonsterTypes.push_back(rand()%3);
    possibleMonsterTypes.push_back(rand()%3);
    threatLevelIncrement = 0;
    difficultyLevel = 0;
}

void AllEntities::init()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->setStartingTile();
    }
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        dynamic_cast<AllowanceObject*>(temp)->setUsableTiles();
    }
    player = NULL;
    DoorFactory::createDoors();
    createChests();
    createTurrets();
    createConsoles();
    recreateSpawners();
    createObstacles();
    spawnMonstersFromSpawners();
}
AllEntities::~AllEntities()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        delete temp;
    }
    player = NULL;
}

void AllEntities::createChests()
{
    for(int i = 0; i < 0; i++)
    {
        Entity *chest = Chest::CreateChest(0,0);
        chest->setStartingTile();
        this->addEntity(chest);
    }
}

void AllEntities::createTurrets()
{
    for(int i = 0; i < 0; i++)
    {
        int X = Variables::tileSize + rand()%(Variables::tileSize * (Variables::tilesPerRoom - 2));
        int Y = Variables::tileSize + rand()%(Variables::tileSize * (Variables::tilesPerRoom - 2));
        X -= X%Variables::tileSize;
        Y -= Y%Variables::tileSize;
        Entity *turret = Turret::CreateTurret(X,Y);
        turret->setStartingTile();
        this->addEntity(turret);
    }
}

void AllEntities::createConsoles()
{
    for(int i = 0; i < 1; i++)
    {
        int X = Variables::tileSize + rand()%(Variables::tileSize * (Variables::tilesPerRoom - 2));
        int Y = Variables::tileSize + rand()%(Variables::tileSize * (Variables::tilesPerRoom - 2));
        X -= X%Variables::tileSize;
        Y -= Y%Variables::tileSize;        
        Entity *console = Console::CreateConsole(X,Y);
        console->setStartingTile();
        entityList.push_back(console);
    } 
}


void AllEntities::display()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->display();
    }
    if(player != NULL)player->display();
}

void AllEntities::update()
{
    if(Variables::log == full)std::cout << " AllEntities Update ";
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->update();
    }
    player->update();
    if(Variables::log == full)std::cout << " AllEntities Update end ";
    deleteDead();
    if(Variables::log == full)std::cout << " AllEntities Delete ";
}

void AllEntities::collisions()
{
    
}

void AllEntities::loadFile()
{
    
}

void AllEntities::loadNew()
{
    
}

void AllEntities::addEntity(Entity* newEntity)
{
    entityList.push_back(newEntity);
    threatLevel += newEntity->getModuleThreatLevel();
    this->applyModifiers(newEntity);
}

void AllEntities::deleteEntity(Entity* toDelete)
{
    this->threatLevel -= toDelete->getModuleThreatLevel();
    if(toDelete->getEntityType() == "SPAWNER"){
        for(std::vector<Entity*>::iterator i = spawnerList.begin(); i != spawnerList.end(); ++i)
        {
            Entity *temp = *i;
            if(temp == toDelete){
                spawnerList.erase(i);
                this->virtualThreatLevel -= dynamic_cast<Spawner*>(temp)->getThreatLevel();
                break;
            }
        }
    }
    entityList.remove(toDelete);
}

Entity* AllEntities::getPlayer() const {
    return player;
}

void AllEntities::deleteDead()
{
    std::list<Entity*>::iterator i = entityList.begin();
    while (i != entityList.end())
    {
        Entity *toDelete = *i;
        if(toDelete != NULL)if(toDelete->getHealth() <= 0)
        {
            toDelete->executeAgony();
            if(toDelete == player)Variables::status = END;
            if(toDelete->isProjectile() == false)
            {
                ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(toDelete->getCoords()->X,toDelete->getCoords()->Y);
                if(tile != NULL)
                {
                    tile->deleteFromEntityList(toDelete);
                }
            }
            entityList.erase(i++);
            delete toDelete;
        }
        i++;
    }
}

void AllEntities::createObstacles()
{
    for(int i = 3; i < Variables::tilesPerRoom - 3; i++)
        for(int j = 3; j < Variables::tilesPerRoom - 3; j++)
        {
            bool isObstacle = (rand()%Variables::tileSize == 0);
            if(isObstacle && Variables::session->getMap()->getCurrentModule()->getModuleTileAt(i * Variables::tileSize, j * Variables::tileSize)->getObstacle() == NULL)
            {
                Entity *obstacle;
                if(rand()%5 == 0)obstacle = ExplosiveBarrel::CreateBarrel(i * Variables::tileSize, j * Variables::tileSize);
                else obstacle = Obstacle::CreateObstacle(i * Variables::tileSize, j * Variables::tileSize);
                Variables::session->getMap()->getCurrentModule()->getModuleTileAt(i * Variables::tileSize, j * Variables::tileSize)->setObstacle(obstacle);
                this->addEntity(obstacle);
            }
        }
}

void AllEntities::addRemoteCharge(Entity* toAdd)
{
    templateList<Entity> *newCharge = new templateList<Entity>();
    newCharge->data = toAdd;
    newCharge->next = remoteCharges;
    remoteCharges = newCharge;
    addEntity(toAdd);
}

bool AllEntities::deleteRemoteCharge(int signalId)
{
    bool result = false;
    templateList<Entity> *temp = remoteCharges;
    while(temp != NULL)
    {
        if(dynamic_cast<RemoteCharges*>(temp->data)->getSignalId() == signalId)
        {
            result = true;
            templateList<Entity> *toDelete = temp;
            temp = temp->next;
            if(temp != remoteCharges) { remoteCharges->findPrevious(toDelete->data)->next = temp; }
            toDelete->data->executeAgony();
            deleteEntity(toDelete->data);
        }
        else temp = temp->next;
    }
    return result;
}

void AllEntities::applyModifiers(Entity* newEntity)
{
    newEntity->adaptToModificators();
}

void AllEntities::setPlayer(Entity* player) {
    this->player = player;
    Variables::offsetX = player->getCoords()->X - Variables::RES_WIDTH/2;
    Variables::offsetY = player->getCoords()->Y - (Variables::RES_HEIGHT - 100)/2;
}

void AllEntities::save(std::fstream& file)
{
    file << "AE" << std::endl;
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->save(file);
    }
    file << "END" << std::endl;
}

bool AllEntities::isOnList(Entity* entity)
{
    bool result = false;
    
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        if(temp == entity)result = true;
    }
    return result;
}

void AllEntities::load(std::fstream& file)
{
    std::string fileInput;
    do{
        file >> fileInput;
        Entity *newEntity = NULL;
        if(fileInput == "CH")newEntity = Chest::CreateChest(-1, -1);
        if(fileInput == "TU")newEntity = Turret::CreateTurret(-1, -1);
        if(fileInput == "RC")newEntity = RemoteCharges::CreateCharges(-1, -1);
        if(fileInput == "OD")newEntity = ObstacleDoor::CreateObstacleDoor(-1, -1);
        if(fileInput == "WA")newEntity = Obstacle::CreateObstacle(-1, -1);
        if(fileInput == "CW")newEntity = Obstacle::CreateObstacle(-1, -1);
        if(fileInput == "EB")newEntity = ExplosiveBarrel::CreateBarrel(-1, -1);
        if(fileInput == "SP")newEntity = Spawner::CreateSpawner(-1, -1);
        if(fileInput == "MO")newEntity = Monster::CreateMonster(-1, -1, 0);
        if(fileInput == "BR")newEntity = BuffRod::CreateBuffRod(-1, -1);
        if(fileInput == "EX")newEntity = Explosives::CreateExplosives(-1, -1);
        if(fileInput == "OB")newEntity = Obstacle::CreateObstacle(-1, -1);
        if(fileInput == "KH")newEntity = KeyHolder::CreateKeyHolder(-1, -1);
        if(fileInput == "LO")newEntity = Lock::CreateLock(-1, -1);
        if(fileInput == "CO")newEntity = Console::CreateConsole(-1,-1);
        
        if(newEntity != NULL)newEntity->load(file);
        if(fileInput == "RC")addRemoteCharge(newEntity);
        if(fileInput == "WA")dynamic_cast<Obstacle*>(newEntity)->setAsWall();
        if(fileInput == "CW")dynamic_cast<Obstacle*>(newEntity)->setAsCornerWall((newEntity->getCoords()->angle/90) + 2);
        
        if(newEntity != NULL)
        {
            newEntity->setStartingTile();
            addEntity(newEntity);
        }
    }while(fileInput != "END");
}

void AllEntities::displayPlan()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        if(temp->isBarricade() == true)temp->displayPlan();
    }
}

void AllEntities::setPlanCoords(int X, int Y)
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->setPlanCoords(X,Y);
    }
}

void AllEntities::createAllowanceObjects(int X, int Y)
{
    for(int i = 0; i < 1; i++)
    {
        Entity *object = AllowanceObject::createObject(400, 400, rand()%Variables::allowancObjectMaxCount);
        dynamic_cast<AllowanceObject*>(object)->setModuleCoords(X,Y);
        entityList.push_back(object);
    }
}

void AllEntities::createModuleDoor(int X, int Y)
{
    double moduleSize = Variables::tileSize * (Variables::tilesPerRoom - 1);
    if(X > 0)
    {
        Entity *doorLeft = ModuleDoor::CreateModuleDoor(0, Variables::tileSize * (Variables::tilesPerRoom/2 - 2), false);
        this->addEntity(doorLeft);
        doorLeft->setStartingTile();
        moduleDoors->SetLeftDoor(doorLeft);
    }
    if(X < Variables::session->getMap()->getModulesTableSize()-1)
    {
        Entity *doorRight = ModuleDoor::CreateModuleDoor(moduleSize, Variables::tileSize * (Variables::tilesPerRoom/2 - 2), false);
        doorRight->setStartingTile();
        this->addEntity(doorRight);
        moduleDoors->SetRightDoor(doorRight);
    }
    if(Y > 0)
    {
        Entity *doorUpper = ModuleDoor::CreateModuleDoor(Variables::tileSize * (Variables::tilesPerRoom/2 - 2), 0, true);
        doorUpper->setStartingTile();
        this->addEntity(doorUpper);
        moduleDoors->SetUpDoor(doorUpper);
    }
    if(Y < Variables::session->getMap()->getModulesTableSize()-1)
    {
        Entity *doorDown = ModuleDoor::CreateModuleDoor(Variables::tileSize * (Variables::tilesPerRoom/2 - 2), moduleSize, true);    
        doorDown->setStartingTile();    
        this->addEntity(doorDown);    
        moduleDoors->SetDownDoor(doorDown);
    }
}

void AllEntities::updateVirtualThreatLevel(bool currentModule)
{
    if(Variables::currentFrame == 0)
    {
        if(currentModule)
        {
            getMonstersFromAdjacentModules();
            spawnMonstersFromSpawners();
        }
        else
        {
            if(virtualThreatLevel < maxThreatLevel)virtualThreatLevel += threatLevelIncrement;
        }
    }
}

void AllEntities::getMonstersFromAdjacentModules()
{
    int moduleX = Variables::session->getMap()->getModuleX();
    int moduleY = Variables::session->getMap()->getModuleY();
    AllEntities *temp;
    if(moduleX > 0 && moduleDoors->GetLeftDoor() != NULL)
    {
        temp = Variables::session->getMap()->getAllEntities(moduleX-1,moduleY);
        if(temp != NULL && temp->virtualThreatLevel > temp->maxThreatLevel/2)
        {
            if(dynamic_cast<ModuleDoor*>(moduleDoors->GetLeftDoor())->isClosed() == false)
            {
                Entity *monster = temp->getMonsterFromModule(Variables::tileSize*2, Variables::tileSize * (Variables::tilesPerRoom/2));
                monster->setStartingTile();
                this->addEntity(monster);
            }
        }
    }
    if(moduleX < Variables::session->getMap()->getModulesTableSize() && moduleDoors->GetRightDoor() != NULL)
    {
        temp = Variables::session->getMap()->getAllEntities(moduleX+1,moduleY);
        if(temp != NULL && temp->virtualThreatLevel > temp->maxThreatLevel/2)
        {
            if(dynamic_cast<ModuleDoor*>(moduleDoors->GetRightDoor())->isClosed() == false)
            {
                Entity *monster = temp->getMonsterFromModule((Variables::tileSize * Variables::tilesPerRoom) - Variables::tileSize*2, Variables::tileSize * (Variables::tilesPerRoom/2));
                monster->setStartingTile();
                this->addEntity(monster);
            }
        }
    }
    if(moduleY > 0 && moduleDoors->GetUpDoor() != NULL)
    {
        temp = Variables::session->getMap()->getAllEntities(moduleX,moduleY-1);
        if(temp != NULL && temp->virtualThreatLevel > temp->maxThreatLevel/2)
        {
            if(dynamic_cast<ModuleDoor*>(moduleDoors->GetUpDoor())->isClosed() == false)
            {
                Entity *monster = temp->getMonsterFromModule(Variables::tileSize * (Variables::tilesPerRoom/2),Variables::tileSize*2);
                monster->setStartingTile();
                this->addEntity(monster);
            }
        }
    }
    if(moduleY < Variables::session->getMap()->getModulesTableSize() && moduleDoors->GetDownDoor() != NULL)
    {
        temp = Variables::session->getMap()->getAllEntities(moduleX,moduleY+1);
        if(temp != NULL && temp->virtualThreatLevel > temp->maxThreatLevel/2)
        {
            if(dynamic_cast<ModuleDoor*>(moduleDoors->GetDownDoor())->isClosed() == false)
            {
                Entity *monster = temp->getMonsterFromModule(Variables::tileSize * (Variables::tilesPerRoom/2),(Variables::tileSize * Variables::tilesPerRoom) - Variables::tileSize*2);
                monster->setStartingTile();
                this->addEntity(monster);
            }
        }
    }
}

void AllEntities::spawnMonstersFromSpawners()
{
    while(this->threatLevel < this->virtualThreatLevel)
    {
        for(int i = 0; i < this->spawnerList.size(); i++)
        {
            dynamic_cast<Spawner*>(spawnerList[i])->spawnMonster();
        }
    }
}

void AllEntities::setDifficultyLevel(int difficultyLevel) {
    this->difficultyLevel = difficultyLevel;
}

int AllEntities::getDifficultyLevel() const {
    return difficultyLevel;
}

Entity* AllEntities::getMonsterFromModule(double X, double Y)
{
    Entity *result;
    int index = rand()%spawnerList.size();
    result = dynamic_cast<Spawner*>(spawnerList[index])->getMonster(X, Y);
}

void AllEntities::recreateSpawners()
{
    for(int i = 0; i < 5 + difficultyLevel*2; i++)
    {
        Entity *spawner = Spawner::CreateSpawner(0,0);
        spawner->setStartingTile();
        dynamic_cast<Spawner*>(spawner)->setMonsterType(possibleMonsterTypes);
        this->addEntity(spawner);
        this->spawnerList.push_back(spawner);
        this->virtualThreatLevel += dynamic_cast<Spawner*>(spawner)->getThreatLevel();
    }
}

void AllEntities::increaseDifficultyLevel()
{
    difficultyLevel++;
}
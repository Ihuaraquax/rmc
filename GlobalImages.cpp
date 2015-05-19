/* 
 * File:   GlobalImages.cpp
 * Author: Qb
 * 
 * Created on 2 kwiecień 2015, 20:52
 */

#include "GlobalImages.h"

GlobalImages::GlobalImages() {
    std::string path = "";
    
    path = "images/BloodSplater01.png";
    bloodSplatter1 = new Image(path, true);
    bloodSplatter1->state = NORMAL;
    path = "images/BloodSplater02.png";
    bloodSplatter2 = new Image(path, true);
    bloodSplatter2->state = NORMAL;
    path = "images/BloodSplater03.png";
    bloodSplatter3 = new Image(path, true);
    bloodSplatter3->state = NORMAL;
    path = "images/BloodSplater04.png";
    bloodSplatter4 = new Image(path, true);
    bloodSplatter4->state = NORMAL;
    path = "images/BloodSplater05.png";
    bloodSplatter5 = new Image(path, true);
    bloodSplatter5->state = NORMAL;    
    
    path = "images/bufferRod.png";
    buffRod = new Image(path, true);
    buffRod->state = NORMAL;
    
    path = "images/monster1.png";
    monster1 = new Image(path, true);
    monster1->state = NORMAL;
    path = "images/monster2.png";
    monster2 = new Image(path, true);
    monster2->state = NORMAL;
    path = "images/monster3.png";
    monster3 = new Image(path, true);
    monster3->state = NORMAL;
    
    path = "images/spawner.png";
    spawner = new Image(path, true);
    spawner->state = NORMAL;
    
    path = "images/table.png";
    table = new Image(path, true);
    table->state = NORMAL;
    path = "images/tableDamaged1.png";
    damagedTable = new Image(path, true);
    damagedTable->state = NORMAL;
    path = "images/tableDamaged2.png";
    damagedTable2 = new Image(path, true);
    damagedTable2->state = NORMAL;
    
    path = "images/wall/stoneWall1.jpg";
    wall = new Image(path, true);
    wall->state = NORMAL;
    path = "images/wall/stoneWall1Damaged.jpg";
    damagedWall = new Image(path, true);
    damagedWall->state = NORMAL;
    path = "images/wall/stoneWall1Damaged2.jpg";
    damagedWall2 = new Image(path, true);
    damagedWall2->state = NORMAL;    
    
    path = "images/wall/cornerWall1.png";
    cornerWall = new Image(path, true);
    cornerWall->state = NORMAL;
    path = "images/wall/cornerWallDamaged.png";
    damagedCornerWall = new Image(path, true);
    damagedCornerWall->state = NORMAL;
    path = "images/wall/cornerWallDamaged2.png";
    damagedCornerWall2 = new Image(path, true);
    damagedCornerWall2->state = NORMAL;
    
    path = "images/bullet.png";
    projectile = new Image(path, true);
    projectile->state = NORMAL;
    
    path = "images/spaceMarker.png";
    planStepSpaceMarker = new Image(path, true);
    planStepSpaceMarker->state = NORMAL;
    path = "images/arrow.png";
    planStepArrow = new Image(path, true);
    planStepArrow->state = NORMAL;
    
    path = "images/pickUp.png";
    pickUp = new Image(path, true);
    pickUp->state = NORMAL;
    
    path = "images/console.png";
    console = new Image(path, true);
    console->state = NORMAL;
}

GlobalImages::~GlobalImages()
{
    delete table;
    delete damagedTable;
    delete damagedTable2;
    
    delete wall;
    delete damagedWall;
    delete damagedWall2;
    
    delete cornerWall;
    delete damagedCornerWall;
    delete damagedCornerWall2;
    
    delete monster1;
    delete monster2;
    delete monster3;
    
    delete buffRod;
    
    delete bloodSplatter1;
    delete bloodSplatter2;
    delete bloodSplatter3;
    delete bloodSplatter4;
    delete bloodSplatter5;
    
    delete spawner;
    delete projectile;
    
    delete planStepSpaceMarker;
    delete planStepArrow;
    
    delete pickUp;
    delete console;
}

Image* GlobalImages::getMonster3() const {
    return monster3;
}

Image* GlobalImages::getMonster2() const {
    return monster2;
}

Image* GlobalImages::getMonster1() const {
    return monster1;
}

Image* GlobalImages::getDamagedCornerWall() const {
    return damagedCornerWall;
}

Image* GlobalImages::getDamagedCornerWall2() const {
    return damagedCornerWall2;
}

Image* GlobalImages::getCornerWall() const {
    return cornerWall;
}

Image* GlobalImages::getDamagedWall2() const {
    return damagedWall2;
}

Image* GlobalImages::getDamagedWall() const {
    return damagedWall;
}

Image* GlobalImages::getWall() const {
    return wall;
}

Image* GlobalImages::getDamagedTable2() const {
    return damagedTable2;
}

Image* GlobalImages::getDamagedTable() const {
    return damagedTable;
}

Image* GlobalImages::getTable() const {
    return table;
}

Image* GlobalImages::getBloodSplatter5() const {
    return bloodSplatter5;
}

Image* GlobalImages::getBloodSplatter4() const {
    return bloodSplatter4;
}

Image* GlobalImages::getBloodSplatter3() const {
    return bloodSplatter3;
}

Image* GlobalImages::getBloodSplatter2() const {
    return bloodSplatter2;
}

Image* GlobalImages::getBloodSplatter1() const {
    return bloodSplatter1;
}

Image* GlobalImages::getBuffRod() const {
    return buffRod;
}

Image* GlobalImages::getSpawner() const {
    return spawner;
}

Image* GlobalImages::getProjectile() const {
    return projectile;
}

Image* GlobalImages::getPlanStepArrow() const {
    return planStepArrow;
}

Image* GlobalImages::getPlanStepSpaceMarker() const {
    return planStepSpaceMarker;
}

Image* GlobalImages::getPickUp() const {
    return pickUp;
}

Image* GlobalImages::getConsole() const {
    return console;
}
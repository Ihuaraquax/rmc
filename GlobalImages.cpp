/* 
 * File:   GlobalImages.cpp
 * Author: Qb
 * 
 * Created on 2 kwiecień 2015, 20:52
 */

#include "GlobalImages.h"

GlobalImages::GlobalImages() {
    std::string paths[] = {""};
    
    paths[0] = "images/BloodSplater01.png";
    bloodSplatter1 = new Image(1, paths, true);
    bloodSplatter1->state = NORMAL;
    paths[0] = "images/BloodSplater02.png";
    bloodSplatter2 = new Image(1, paths, true);
    bloodSplatter2->state = NORMAL;
    paths[0] = "images/BloodSplater03.png";
    bloodSplatter3 = new Image(1, paths, true);
    bloodSplatter3->state = NORMAL;
    paths[0] = "images/BloodSplater04.png";
    bloodSplatter4 = new Image(1, paths, true);
    bloodSplatter4->state = NORMAL;
    paths[0] = "images/BloodSplater05.png";
    bloodSplatter5 = new Image(1, paths, true);
    bloodSplatter5->state = NORMAL;    
    
    paths[0] = "images/bufferRod.png";
    buffRod = new Image(1, paths, true);
    buffRod->state = NORMAL;
    
    paths[0] = "images/monster1.png";
    monster1 = new Image(1, paths, true);
    monster1->state = NORMAL;
    paths[0] = "images/monster2.png";
    monster2 = new Image(1, paths, true);
    monster2->state = NORMAL;
    paths[0] = "images/monster3.png";
    monster3 = new Image(1, paths, true);
    monster3->state = NORMAL;
    
    paths[0] = "images/spawner.png";
    spawner = new Image(1, paths, true);
    spawner->state = NORMAL;
    
    paths[0] = "images/table.png";
    table = new Image(1, paths, true);
    table->state = NORMAL;
    paths[0] = "images/tableDamaged1.png";
    damagedTable = new Image(1, paths, true);
    damagedTable->state = NORMAL;
    paths[0] = "images/tableDamaged2.png";
    damagedTable2 = new Image(1, paths, true);
    damagedTable2->state = NORMAL;
    
    paths[0] = "images/wall/stoneWall1.jpg";
    wall = new Image(1, paths, true);
    wall->state = NORMAL;
    paths[0] = "images/wall/stoneWall1Damaged.jpg";
    damagedWall = new Image(1, paths, true);
    damagedWall->state = NORMAL;
    paths[0] = "images/wall/stoneWall1Damaged2.jpg";
    damagedWall2 = new Image(1, paths, true);
    damagedWall2->state = NORMAL;    
    
    paths[0] = "images/wall/cornerWall1.png";
    cornerWall = new Image(1, paths, true);
    cornerWall->state = NORMAL;
    paths[0] = "images/wall/cornerWallDamaged.png";
    damagedCornerWall = new Image(1, paths, true);
    damagedCornerWall->state = NORMAL;
    paths[0] = "images/wall/cornerWallDamaged2.png";
    damagedCornerWall2 = new Image(1, paths, true);
    damagedCornerWall2->state = NORMAL;
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
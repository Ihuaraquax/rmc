/* 
 * File:   GlobalImages.h
 * Author: Qb
 *
 * Created on 2 kwiecień 2015, 20:52
 */

#ifndef GLOBALIMAGES_H
#define	GLOBALIMAGES_H
#include "Image.h"

class GlobalImages {
public:
    GlobalImages();
    ~GlobalImages();
    Image* getMonster3() const;
    Image* getMonster2() const;
    Image* getMonster1() const;
    Image* getDamagedCornerWall() const;
    Image* getDamagedCornerWall2() const;
    Image* getCornerWall() const;
    Image* getDamagedWall2() const;
    Image* getDamagedWall() const;
    Image* getWall() const;
    Image* getDamagedTable2() const;
    Image* getDamagedTable() const;
    Image* getTable() const;
    Image* getBloodSplatter5() const;
    Image* getBloodSplatter4() const;
    Image* getBloodSplatter3() const;
    Image* getBloodSplatter2() const;
    Image* getBloodSplatter1() const;
    Image* getBuffRod() const;
    Image* getSpawner() const;
    Image* getProjectile() const;
    Image* getPlanStepArrow() const;
    Image* getPlanStepSpaceMarker() const;
    Image* getPickUp() const;
    Image* getConsole() const;
    
private:
    Image *table;
    Image *damagedTable;
    Image *damagedTable2;
    
    Image *wall;
    Image *damagedWall;
    Image *damagedWall2;
    
    Image *cornerWall;
    Image *damagedCornerWall;
    Image *damagedCornerWall2;
    
    Image *monster1;
    Image *monster2;
    Image *monster3;
    
    Image *buffRod;
    
    Image *bloodSplatter1;
    Image *bloodSplatter2;
    Image *bloodSplatter3;
    Image *bloodSplatter4;
    Image *bloodSplatter5;
    
    Image *spawner;
    Image *projectile;
    
    Image *planStepSpaceMarker;
    Image *planStepArrow;
    
    Image *pickUp;
    Image *console;
};

#endif	/* GLOBALIMAGES_H */


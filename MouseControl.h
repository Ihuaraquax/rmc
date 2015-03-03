/* 
 * File:   MouseControl.h
 * Author: Qb
 *
 * Created on 4 listopad 2014, 22:27
 */

#ifndef MOUSECONTROL_H
#define	MOUSECONTROL_H

class MouseControl {
public:
    MouseControl();
    void mouseActions();
private:
    void inventoryAction();
    void chestActions();
    
    int contentIndex;
    bool isLeftButtonPressed;
    bool fromChest;
};

#endif	/* MOUSECONTROL_H */


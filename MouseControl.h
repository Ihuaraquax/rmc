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
    bool onPress(int mosueKey);
    bool keyPressed[2];
};

#endif	/* MOUSECONTROL_H */


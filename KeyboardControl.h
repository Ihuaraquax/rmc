/* 
 * File:   KeyboardControl.h
 * Author: Qb
 *
 * Created on 4 listopad 2014, 22:27
 */

#ifndef KEYBOARDCONTROL_H
#define	KEYBOARDCONTROL_H

class KeyboardControl {
public:
    KeyboardControl();
    void keyboardActions();
    void gameKeyboardActions();
    bool isPressed(int key);
private:
    bool *pressedKeys;
};

#endif	/* KEYBOARDCONTROL_H */


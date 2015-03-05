/* 
 * File:   TextDisplayer.h
 * Author: Qb
 *
 * Created on 5 marzec 2015, 17:56
 */

#ifndef TEXTDISPLAYER_H
#define	TEXTDISPLAYER_H

#include <iostream>
class TextDisplayer {
public:
    void static displayText(double X, double Y, std::string text);
    void static displayInt(double X, double Y, int toDisplay);
private:

};

#endif	/* TEXTDISPLAYER_H */


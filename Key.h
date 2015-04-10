/* 
 * File:   Key.h
 * Author: Qb
 *
 * Created on 7 kwiecień 2015, 18:57
 */

#ifndef KEY_H
#define	KEY_H
#include "UsableObject.h"
#include "Entity.h"

class KeyHolder : public Entity, public UsableObject {
public:
    KeyHolder();
    void update();
    void display();
    void save(std::fstream &savefile);
    void load(std::fstream &savefile);
    void getHit(int damage, int damageType);
    static Entity *CreateKeyHolder(double X, double Y);
    void use();
private:
    Image *emptyImage;
    int keyValue;
    bool hasKey;
};

#endif	/* KEY_H */


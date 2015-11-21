/* 
 * File:   MapRuleChecker.h
 * Author: Adiutant
 *
 * Created on 21 listopad 2015, 15:36
 */

#ifndef MAPRULECHECKER_H
#define	MAPRULECHECKER_H

class MapRuleChecker {
public:
    /**
     * Zasady
     * -1: cokolwiek
     *  0: puste
     *  1: zajęte
     */
    static bool applyStandarizedRule(int x, int y, int rule[5][5]);
    /**
     * Zasady
     * -1: cokolwiek
     *  0: puste
     *  1: zajęte
     */
    static bool applyAnyRule(int x, int y, int **rule, int ruleSizeX, int ruleSizeY);
private:

};

#endif	/* MAPRULECHECKER_H */


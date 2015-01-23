/* 
 * File:   templateList.h
 * Author: Qb
 *
 * Created on 5 lipiec 2014, 21:55
 */

#ifndef TEMPLATELIST_H
#define	TEMPLATELIST_H


#include <iostream>

template <class T>
class templateList {
public:
    /**
     * basic constructor 
     * sets both data and next to NULL
     */
    templateList();
    
    /**
     * copy constructor
     * currently unused
     * @param orig - original object
     */
    templateList(const templateList& orig);
    
    /**
     * basic destructor
     */
    virtual ~templateList();
    
    /**
     * function that finds last object on list
     * @return last object on list
     */
    templateList *findLast();
    
    /**
     * function that searches for list node that has pointer to specific instace
     * @param toFind object that function is trying to find
     * @return templateList with toFind as data or NULL if toFind is not on list
     */
    templateList *find(T* toFind);
    
    /**
     * function that searches for list node that is previous to one containing 
     * required object
     * useful in deleting objects
     * @param toFind object that function is trying to find
     * @return templateList with toFind as next -> data or NULL if toFind is not on list
     */
    templateList *findPrevious(T *toFind);
    
    /**
     * pointer to object stored in list
     */
    T *data;
    
    /**
     * pointer to next node on list
     */
    templateList *next;
    
private:

};

template <class T>
templateList<T>::templateList() {
    data = NULL;
    next = NULL;
}

template <class T>
templateList<T>::templateList(const templateList& orig) {
}

template <class T>
templateList<T>::~templateList() {
    //if(data != NULL)delete data;
}

template <class T>
templateList<T> *templateList<T>::findLast()
{
    if(next == NULL) return this;
    return next -> findLast();
}

template <class T>
templateList<T> *templateList<T>::find(T* toFind)
{
    if(this == NULL)return NULL;
    if(data == toFind)return this;
    if(next == NULL)return NULL;
    return next -> find(toFind);
}

template <class T>
templateList<T> *templateList<T>::findPrevious(T *toFind)
{
    if(data == toFind)return this;
    if(next == NULL)return NULL;
    if(next -> data == toFind)return this;
    return next -> findPrevious(toFind);
}


#endif	/* TEMPLATELIST_H */


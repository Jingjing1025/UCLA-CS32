#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include <string>
#include <list>
using namespace std;
#include "GameWorld.h"
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class NanchenBlaster;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld()
    {
        cleanUp();
        
    }
    int init();   //initialize the Student World, and the objects in the world
    int move();   //Start the game and let each object do something in each tick
    void cleanUp();  //clean and free all objects in the world
    void addObjects(Actor* act);   //add objects to the world
    void removeDeadGameObjects();  //remove dead objects from the world
    void updateDisplayText();      //update the displayed text based on game status
    bool collide(Actor* a1, Actor* a2) const;   //return true if the two objects collide with each other
    bool projectileCollide(Actor* projectile, int Owner = 0);   //return true if the projectile collide with aliens or NanchenBlaster, or if NanchenBlaster collides with aliens
    void alienDestroyed() {numAlienDestroyed++; numCurrAlien--;}   //update the number of aliens destroyed so far and the number of current aliens in the world
    void alienOffScreen() {numCurrAlien--;}   //decrease the number of current aliens in the world if it flies off the screen
    int getAlienDestroyed () const {return numAlienDestroyed;}  //return the number of aliens destroyed
    bool needNewAlien ();   //return true if the formula suggests that new alien needs to be added
    void addAlien();    //add aliens if needed
    bool mayAttack(Actor*) const;    //return true if the alien is close to NanchenBlaster so that it may attack NanchenBlaster
    void incTorpedoes()     //increase NanchenBlaster's number of torpedoes when it picks up torpedo goodies
    { m_NB->increaseTorpedoes(); }
    void attack(Actor* a1, Actor *a2);   //perform attack actions
    void incPoints();    //increase NanchenBlaster's life points when it picks up goodies
    
private:
    list<Actor*> obj;
    NanchenBlaster* m_NB;
    int m_level;
    int numAlienDestroyed;
    int numCurrAlien;
};

#endif // STUDENTWORLD_H_



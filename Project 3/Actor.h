#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
using namespace std;

class StudentWorld;

////////////////////////////// Actor /////////////////////////////////////

class Actor : public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld);
    ~ Actor(){};

    //I use pure virtual function here because each derived class has its own implementation of doSomething. And I also want to prevent abstract class Actor being called and force the implementation of function doSomething
    virtual void doSomething()=0;
    
    //The below functions are not set to be virtual because they are used by all derived classes in similar ways
    int getID() const { return m_ID; }     //return what object it is
    int getPoints() const { return m_Points; }    //return object's life points
    void setPoints(int points) { m_Points = points; }   //set object's points
    void beingDamaged() { m_sufferDamage = true; }    //set object's status to "suffered damage"
    bool isAlive() const {return m_alive;}   //return true if the object is alive
    void setDead() { m_alive = false; }    //set object's status to dead
    
protected:
    bool offScreen(int x, int y) const;    //return true if the object is off screen
    void resetSuffer() {m_sufferDamage = false;}   //reset the object to "not suffered damage" after each tick
    
    //Functions to get info
    StudentWorld* getStudentWorld() const { return m_studentWorld; }  //get the StudentWorld so that functions in StudentWorld can be accessed
    bool sufferDamage() const { return m_sufferDamage; }  //return true if the object has suffered damage
    
private:
    bool m_alive;
    StudentWorld* m_studentWorld;
    int m_ID;
    int m_Points;
    bool m_sufferDamage;
    
};

////////////////////////////// Nanchenblaster /////////////////////////////////

class NanchenBlaster : public Actor
{
public:
    NanchenBlaster(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld);
    
    //NanchenBlaster does not have derived classes, so I didn't put vitrtual functions
    void increaseTorpedoes() { m_FlatTorpedo += 5; }     //increase the number of torpedoes NanchenBlaster has
    int getTorpedoes() const { return m_FlatTorpedo; }   //return the number of torpedoes NanchenBlaster has
    int getEnergyPoints() const { return m_energyPoints; }  // return the energy points (cabbages) NanchenBlaster has
    virtual void doSomething();  //NanchenBlaster's version of doSomething
    
private:
    int m_energyPoints;
    int m_FlatTorpedo;
};


////////////////////////////// Alien /////////////////////////////////////

class Alien : public Actor
{
public:
    Alien(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld, int points, double speed = 2.0)
    : Actor(imageID, startX, startY, dir, size, depth, stuWld), m_Speed(speed), m_dir(0), m_FlightPlan(0)
    {setPoints(points);}
    
protected:
    //obtain information
    int getMDir() const {return m_dir; }    //return the flight path direction of each Alien (direction marked by numbers)
    int getFlightPlan() {return m_FlightPlan; }   //return the flight path length of each Alien
    double getSpeed() { return m_Speed; }  //return the flight speed of each Alien
    
    //set variables
    void setMDir(int d) {m_dir = d;}     //set the flight path direction of each Alien
    void setFlightPlan(int Fplan) {m_FlightPlan = Fplan;}     //set the flight path length of each Alien
    void setSpeed(double speed) { m_Speed = speed;}    //return the flight speed of each Alien
    
    void doSomething();  //Alien's version of doSomething
    void move();   //let Alien move accordingly
    void Dead (Actor* a);  //let Alien act accordingly when it is dead. I did not use virtual because the aliens act similarly
    
private:
    int m_FlightPlan;
    double m_Speed;
    int m_dir;
};

class Smallgon : public Alien
{
public:
    Smallgon(double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld, int points, double speed = 2.0)
    : Alien (IID_SMALLGON, startX, startY, dir, size, depth, stuWld, points, speed) {}
};

class Smoregon : public Alien
{
public:
    Smoregon(double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld, int points, double speed = 2.0)
    : Alien (IID_SMOREGON, startX, startY, dir, size, depth, stuWld, points, speed) {}
private:
};

class Snagglegon : public Alien
{
public:
    Snagglegon(double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld, int points, double speed = 2.0)
    : Alien (IID_SNAGGLEGON, startX, startY, dir, size, depth, stuWld, points, speed) {setMDir(3);}
};

////////////////////////////// Star /////////////////////////////////////

class Star : public Actor
{
public:
    Star(double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld)
    : Actor(IID_STAR, startX, startY, dir, size, depth, stuWld){}
protected:
    virtual void doSomething();
    
};


////////////////////////////// Projectile /////////////////////////////////

class Projectile : public Actor
{
public:
    Projectile(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld, int owner)
    : Actor(imageID, startX, startY, dir, size, depth, stuWld){ m_Owner = owner; }
protected:
    void doSomething();  //Projectile's version of doSomething
    int getOwner() const  //return the owner of each projectile released
    { return m_Owner; }
private:
    int m_Owner;
};

class Cabbage : public Projectile
{
public:
    Cabbage(double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld, int owner = IID_NACHENBLASTER)
    : Projectile (IID_CABBAGE, startX, startY, dir, size, depth, stuWld, IID_NACHENBLASTER) {  m_Owner = owner; }
private:
    int m_Owner;
};

class Turnip : public Projectile
{
public:
    Turnip(double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld, int owner)
    : Projectile (IID_TURNIP, startX, startY, dir, size, depth, stuWld,IID_NACHENBLASTER) {  m_Owner = owner; }
private:
    int m_Owner;
};

class FlatulenceTorpedoes : public Projectile
{
public:
    FlatulenceTorpedoes(double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld, int owner)
    : Projectile (IID_TORPEDO, startX, startY, dir, size, depth, stuWld, owner) { m_Owner = owner; }
private:
    int m_Owner;
};


////////////////////////////// Explosion /////////////////////////////////////

class Explosion : public Actor
{
public:
    Explosion(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld)
    : Actor(imageID, startX, startY, dir, size, depth, stuWld){ m_Tick = 0;}
    virtual void doSomething();  //Explosion's version of doSomething
private:
    int m_Tick;
};


////////////////////////////// Goodies /////////////////////////////////////

class Goodies : public Actor
{
public:
    Goodies(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld)
    : Actor(imageID, startX, startY, dir, size, depth, stuWld){}
protected:
    void checkCollision(Actor* a);   //let goodies act accordinly if they collide with NanchenBlaster
    virtual void doSomething();   //goodies' version of doSomething
    
};

class RepairGoodies : public Goodies
{
public:
    RepairGoodies(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld)
    : Goodies(IID_REPAIR_GOODIE, startX, startY, dir, size, depth, stuWld){}
};

class ExtraLifeGoodies : public Goodies
{
public:
    ExtraLifeGoodies(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld)
    : Goodies(IID_LIFE_GOODIE, startX, startY, dir, size, depth, stuWld){}
};

class FlatulenceTorpedoGoodies : public Goodies
{
public:
    FlatulenceTorpedoGoodies(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld)
    : Goodies(IID_TORPEDO_GOODIE, startX, startY, dir, size, depth, stuWld){}
};

#endif // ACTOR_H_




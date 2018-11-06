#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;
#include <iostream>
#include <sstream>
#include <cmath>

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students: Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
    obj.clear();
    m_NB = nullptr;
    m_level = 1;
    numAlienDestroyed = 0;
}

int StudentWorld::init()
{
    numAlienDestroyed = 0;
    numCurrAlien = 0;
    m_NB = new NanchenBlaster(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, this);
    addObjects(m_NB);
    for (int i = 0; i<30; i++)
    {
        int x = randInt(0, VIEW_WIDTH-1);
        int y = randInt(0, VIEW_HEIGHT-1);
        double f = (randInt(5, 50));
        double size = f/100;
        addObjects(new Star(x,y,0,size,3, this));
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    if (needNewAlien())
        addAlien();
    
    for (auto p = obj.begin(); p!=obj.end();p++)
    {
        if ((*p)!=nullptr && (*p)->isAlive())
        {
            (*p)->doSomething();
            if (m_NB != nullptr && m_NB->getPoints()<0)
            {
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
            if (numAlienDestroyed == 6+(4*m_level))
            {
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }
    
    removeDeadGameObjects();
    updateDisplayText();
    
    //1/15 chance to add a star
    if (randInt(1, 15)==1)
    {
        int x = VIEW_WIDTH-1;
        int y = randInt(0, VIEW_HEIGHT);
        double f = (randInt(5, 50));
        double size = f/100;
        addObjects(new Star(x,y,0,size,3, this));
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    auto p = obj.begin();
    while (p != obj.end())
    {
        delete (*p);
        p++;
        obj.pop_front();
    }
}

void StudentWorld::addObjects(Actor* act)
{
    obj.push_back(act);
}

void StudentWorld::removeDeadGameObjects()
{
    auto p = obj.begin();
    while (p!=obj.end())
    {
        if (!(*p)->isAlive())
        {
            delete (*p);
            obj.erase(p);
            p = obj.begin();
        }
        p++;
    }
}

void StudentWorld::updateDisplayText()
{
    int lives = getLives();
    int scores = getScore();
    int level = getLevel();
    int torpedoes = m_NB->getTorpedoes();
    double health = m_NB->getPoints()/50.0*100;
    int cabbages = m_NB->getEnergyPoints()/30.0*100;
    
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(0);
    oss<<"Lives: " << lives << "  Health: " << health << "%  Score: " << scores << "  Level: " << level << "  Cabbages: " << cabbages << "%  Torpedoes: " << torpedoes;
    
    string s = oss.str();
    setGameStatText(s);
}

bool StudentWorld::collide(Actor* a1, Actor* a2) const
{
    if (a2 == nullptr)
        a2 = m_NB;
    int x1 = a1->getX();
    int x2 = a2->getX();
    int y1 = a1->getY();
    int y2 = a2->getY();
    int R1 = a1->getRadius();
    int R2 = a2->getRadius();
    double euclidian_dist = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    if (euclidian_dist < .75 * (R1 + R2))
        return true;
    return false;
}

bool StudentWorld::projectileCollide(Actor *projectile, int Owner)
{
    int ID = projectile->getID();
    switch (ID){
        case IID_CABBAGE:
        case IID_NACHENBLASTER:
            for (auto p = obj.begin(); p!=obj.end();p++)
            {
                if ((*p)->getID()==IID_SNAGGLEGON ||(*p)->getID()==IID_SMALLGON || (*p)->getID()==IID_SMOREGON)
                {
                    if (collide(projectile, *p))
                    {
                        attack(projectile, *p);
                        return true;
                    }
                }
            }
            return false;
        case IID_TURNIP:
            if (collide(projectile, m_NB))
            {
                attack(projectile, m_NB);
                return true;
            }
            return false;
        case IID_TORPEDO:
            if (Owner == IID_NACHENBLASTER)
            {
                for (auto p = obj.begin(); p!=obj.end();p++)
                {
                    if ((*p)->getID()==IID_SNAGGLEGON ||(*p)->getID()==IID_SMALLGON || (*p)->getID()==IID_SMOREGON)
                    {
                        if (collide(projectile, *p))
                        {
                            attack(projectile, *p);
                            return true;
                        }
                    }
                }
                return false;
            }
            else if (Owner == IID_SNAGGLEGON)
            {
                if (collide(projectile, m_NB))
                {
                    attack(projectile, m_NB);
                    return true;
                }
                return false;
            }
    }
    return false;
}

void StudentWorld::attack(Actor* a1, Actor *a2)
{
    int points = a2->getPoints();
    a2->beingDamaged();
    if (a1->getID()==IID_TORPEDO)
        a2->setPoints(points- 8);
    else if (a1->getID()==IID_CABBAGE || a1->getID()==IID_TURNIP)
        a2->setPoints(points - 2);
    else if (a1->getID()==IID_NACHENBLASTER)
    {
        a2->setPoints(points - 100);
        if (a2->getID()==IID_SNAGGLEGON)
            a1->setPoints(a1->getPoints()-15);
        else
            a1->setPoints(a1->getPoints()-5);
    }
}

int min(int i1, int i2)
{
    if (i1 < i2)
        return i1;
    return i2;
}

bool StudentWorld::needNewAlien()
{
    int D = numAlienDestroyed;
    int R = 6+(4*getLevel()) - D;
    int M = 4+(0.5*getLevel());
    if (numCurrAlien < min(M,R))
        return true;
    return false;
}

void StudentWorld::addAlien()
{
    int S1 = 60;
    int S2 = 20 + getLevel()*5;
    int S3 = 5 + getLevel()*10;
    int S = S1 + S2 + S3;
    int y = randInt(0, VIEW_HEIGHT-1);
    int rand = randInt(1, S);
    if (rand <= S1)
    {
        int points = 5*(1+(getLevel()-1)*0.1);
        addObjects(new Smallgon(VIEW_WIDTH-1, y, 0, 1.5, 1, this, points));
    }
    else if (rand <= S1 + S2)
    {
        int points = 5*(1+(getLevel()-1)*0.1);
        addObjects(new Smoregon(VIEW_WIDTH-1, y, 0, 1.5, 1, this, points));
    }
    else if (rand <= S)
    {
        int points = 10*(1+(getLevel()-1)*0.1);
        addObjects(new Snagglegon(VIEW_WIDTH-1, y, 0, 1.5, 1, this, points, 1.75));
    }
    numCurrAlien++;
}

bool StudentWorld::mayAttack(Actor* a) const 
{
    int NBx = m_NB->getX();
    int NBy = m_NB->getY();
    if (NBx <= a->getX())
    {
        if (a->getY()<=NBy+4 && a->getY() >= NBy-4)
            return true;
    }
    return false;
}

void StudentWorld::incPoints()    //increase NanchenBlaster's life points when it picks up goodies
{
    int curNB_Points = m_NB->getPoints();
    if (curNB_Points + 10 <= 50)
        m_NB->setPoints(curNB_Points + 10);
    else
        m_NB->setPoints(50);
}

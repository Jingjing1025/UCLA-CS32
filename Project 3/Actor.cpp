#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>

////////////////////////////// Actor /////////////////////////////////////

Actor::Actor (int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld)
: GraphObject(imageID, startX, startY, dir, size, depth), m_studentWorld(stuWld)
{
    m_alive = true;
    m_ID = imageID;
    m_sufferDamage = false;
}

bool Actor::offScreen(int x, int y) const
{
    if (x<0 || x>=VIEW_WIDTH || y<0 || y>=VIEW_HEIGHT)
        return true;
    return false;
}

NanchenBlaster::NanchenBlaster(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* stuWld)
: Actor(IID_NACHENBLASTER, startX, startY, dir, size, depth, stuWld)
{
    setPoints(50);
    m_energyPoints = 30;
    m_FlatTorpedo = 0;
}

////////////////////////////// Nanchenblaster /////////////////////////////////

void NanchenBlaster::doSomething()
{
    if (isAlive())
    {
        int key;
        if (getStudentWorld()->getKey(key))
        {
            if (key == KEY_PRESS_SPACE && m_energyPoints>=5)
            {
                m_energyPoints -= 5;
                getStudentWorld()->addObjects(new Cabbage(getX()+12, getY(), 0, 0.5, 1, getStudentWorld()));
                getStudentWorld()->playSound(SOUND_PLAYER_SHOOT);
            }
            else if (key == KEY_PRESS_TAB && m_FlatTorpedo>0)
            {
                m_FlatTorpedo --;
                getStudentWorld()->addObjects(new FlatulenceTorpedoes(getX()+12, getY(), 0, 0.5, 1, getStudentWorld(), IID_NACHENBLASTER));
                getStudentWorld()->playSound(SOUND_TORPEDO);
            }
            else if (key == KEY_PRESS_UP && !offScreen(getX(), getY()+6))
            {
                moveTo(getX(), getY()+6);
            }
            else if (key == KEY_PRESS_DOWN && !offScreen(getX(), getY()-6))
            {
                moveTo(getX(), getY()-6);
            }
            else if (key == KEY_PRESS_LEFT && !offScreen(getX()-6, getY()))
            {
                moveTo(getX()-6, getY());
            }
            else if (key == KEY_PRESS_RIGHT && !offScreen(getX()+6, getY()))
            {
                moveTo(getX()+6, getY());
            }
        }
        getStudentWorld()->projectileCollide(this);
        if (m_energyPoints<30)
            m_energyPoints ++;
    }
    return;
}


////////////////////////////// Star /////////////////////////////////////

void Star::doSomething()
{
    moveTo(getX()-1, getY());
    if (getX()<0)
        setDead();
}

////////////////////////////// Projectile /////////////////////////////////

void Projectile::doSomething()
{
    //if dead or move off the screen, do nothing
    if (!isAlive())
        return;
    if (getX()<0 || getX()>VIEW_WIDTH)
    {
        setDead();
        return;
    }
    else          //check and attack if there are collisions
    {
        if (getStudentWorld()->projectileCollide(this, m_Owner))
            setDead();
    }
    
    //if no collision, move to appropriate spots
    int dir = getDirection();
    if (getID()!=IID_TORPEDO)
        setDirection(dir+20);     //Torpedo does not rotate
    if (getID()==IID_CABBAGE)
        moveTo(getX()+8, getY());
    else if (getID()==IID_TURNIP)
        moveTo(getX()-6, getY());
    else if (getID()==IID_TORPEDO)
    {
        if (getOwner()==IID_NACHENBLASTER)
            moveTo(getX()+8, getY());
        if (getOwner()==IID_SNAGGLEGON)
            moveTo(getX()-8, getY());
    }
    
}

////////////////////////////// Alien /////////////////////////////////////

void Alien::doSomething()
{
    if (!isAlive())
        return;
    if (getX()<0)
    {
        setDead();
        getStudentWorld()->alienOffScreen();
        return;
    }
    if (sufferDamage())
    {
        if (getPoints()<=0)
            Dead(this);
        else
            getStudentWorld()->playSound(SOUND_BLAST);
        resetSuffer();
    }
    
    move();
    
    //May fire a turnip or torpedoes
    if (getStudentWorld()->mayAttack(this))
    {
        if (getID()!= IID_SNAGGLEGON)
        {
            int num = 20/getStudentWorld()->getLevel()+5;
            if (randInt(1, num) == 1)
            {
                getStudentWorld()->addObjects(new Turnip(getX()-14, getY(), 0, 0.5, 1, getStudentWorld(), IID_SMALLGON));
                getStudentWorld()->playSound(SOUND_ALIEN_SHOOT);
                return;
            }
        }
        else
        {
            int num = 15/getStudentWorld()->getLevel()+10;
            if (randInt(1, num) == 1)
            {
                getStudentWorld()->addObjects(new FlatulenceTorpedoes(getX()-14, getY(), 180, 0.5, 1, getStudentWorld(), IID_SNAGGLEGON));
                getStudentWorld()->playSound(SOUND_TORPEDO);
                return;
            }
        }
        
        //Smoregon may change direction
        if (getID()==IID_SMOREGON)
        {
            int num = 20/getStudentWorld()->getLevel()+5;
            if (randInt(1, num) == 1)
            {
                setMDir(1);      //set direction to Due Left
                setFlightPlan(VIEW_WIDTH);     //set Flight plan
                setSpeed(5.0);
            }
        }
    }
    
}

void Alien::move()
{
    if (getY()>=VIEW_HEIGHT-1)
    {
        moveTo(getX()-1, getY()-1);
        setMDir(3);
    }
    else if (getY()<=0)
    {
        moveTo(getX()-1, getY()+1);
        setMDir(2);
    }
    else if (getFlightPlan()==0 && getID()!=IID_SNAGGLEGON)   //snagglegon has designated intial movement direction
    {
        int dir = randInt(1, 3);
        switch (dir)
        {
            case 1: moveTo(getX()-1, getY()); break;
            case 2: moveTo(getX()-1, getY()+1); break;
            case 3: moveTo(getX()-1, getY()-1); break;
        }
        setMDir(dir);
        int random = randInt(1, 32);
        setFlightPlan(random);
    }
    else              //keep moving along the current dirction
    {
        if (getMDir()==1)
            moveTo(getX()-getSpeed(), getY());
        if (getMDir()==2)
            moveTo(getX()-getSpeed(), getY()+getSpeed());
        if (getMDir()==3)
            moveTo(getX()-getSpeed(), getY()-getSpeed());
        setFlightPlan(getFlightPlan()-1);
    }
}

void Alien::Dead(Actor* a)
{
    if (a->getID()!=IID_SNAGGLEGON)
        getStudentWorld()->increaseScore(250);
    else
        getStudentWorld()->increaseScore(1000);
    a->setDead();
    getStudentWorld()->playSound(SOUND_DEATH);
    getStudentWorld()->alienDestroyed();
    getStudentWorld()->addObjects(new Explosion(IID_EXPLOSION, getX(), getY(), 0, 1, 0, getStudentWorld()));
    
    //Smoregon may drop goodies
    if (getID()==IID_SMOREGON)
    {
        if (randInt(1, 3)==1)
        {
            if (randInt(1, 2)==1)
                getStudentWorld()->addObjects(new RepairGoodies(IID_REPAIR_GOODIE, getX(), getY(), 0, 0.5, 1, getStudentWorld()));
            else
                getStudentWorld()->addObjects(new FlatulenceTorpedoGoodies(IID_TORPEDO_GOODIE, getX(), getY(), 0, 0.5, 1, getStudentWorld()));
        }
    }
    
    //Snagglegon may drop Extra Life Goodies
    if (a->getID()==IID_SNAGGLEGON)
    {
        if (randInt(1, 6)==1)
        {
            getStudentWorld()->addObjects(new ExtraLifeGoodies(IID_LIFE_GOODIE, getX(), getY(), 0, 0.5, 1, getStudentWorld()));
        }
    }
}

////////////////////////////// Explosion /////////////////////////////////////

void Explosion::doSomething()
{
    m_Tick++;
    double size = getSize();
    setSize(size*1.5);
    if (m_Tick == 4)
        setDead();
}

////////////////////////////// Goodies /////////////////////////////////////

void Goodies::doSomething()
{
    if (!isAlive())
        return;
    if (offScreen(getX(), getY()))
    {
        setDead();
        return;
    }
    checkCollision(this);
    moveTo(getX()-0.75, getY()-0.75);
    checkCollision(this);
}

void Goodies::checkCollision(Actor* a)
{
    if (getStudentWorld()->collide(a, nullptr))
    {
        getStudentWorld()->increaseScore(100);
        a->setDead();
        getStudentWorld()->playSound(SOUND_GOODIE);
        
        switch (a->getID())
        {
            case IID_LIFE_GOODIE:
                getStudentWorld()->incLives();
                break;
            case IID_TORPEDO_GOODIE:
                getStudentWorld()->incTorpedoes();
                break;
            case IID_REPAIR_GOODIE:
                getStudentWorld()->incPoints();
                break;
        }
        return;
    }
}


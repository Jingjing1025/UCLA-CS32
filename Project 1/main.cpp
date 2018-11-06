//
//  main.cpp
//  Project 1
//
//  Created by Jingjing on 10/01/2018.
//  Copyright © 2018 Jingjing. All rights reserved.
//

#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>

#include "Game.h"

using namespace std;

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////

//#include "History.h"
//int main()
//{
//    History h(2, 2);
//    h.record(1, 1);
//    h.display();
//}
//A.
//..
//
//Program ended with exit code: 0

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "Flatulan.h"
//int main()
//{
//    Flatulan f(nullptr, 1, 1);
//}
//***** A Flatulan must be created in some City!

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "Player.h"
//int main()
//{
//    Player p(nullptr, 1, 1);
//}
//***** The player must be created in some City!

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "City.h"
//int main()
//{
//    City c(10, 18);
//    c.addPlayer(2, 2);
//    c.display();
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "globals.h"
//#include "Player.h"
//#include "City.h"
//int main()
//{
//    City c(10, 20);
//    Player p(&c, 2, 3);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "City.h"
//#include "Player.h"
//int main()
//{
//    City c(10, 20);
//    Player p(&c, 2, 3);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "Player.h"
//#include "City.h"
//int main()
//{
//    City c(10, 20);
//    Player p(&c, 2, 3);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "City.h"
//#include "History.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    City c(2, 3);
//    c.addPlayer(1, 2);
//    do
//    {
//        c.addFlatulan(2, 1);
//        c.preachToFlatulansAroundPlayer();
//    } while (c.nFlatulansAt(2, 1) == 0);
//    c.history().display();
//    cout << "===" << endl;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "Flatulan.h"
//#include "City.h"
//int main()
//{
//    City a(10, 20);
//    Player p(&a, 2, 3);
//    Flatulan f(&a, 1, 1);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "Player.h"
//#include "City.h"
//int main()
//{
//    City a(10, 20);
//    Player p(&a, 2, 3);
//    Flatulan f(&a, 1, 1);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "globals.h"
//#include "Flatulan.h"
//#include "Player.h"
//int main()
//{
//    City a(10, 10);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "History.h"
//int main()
//{
//    History h;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


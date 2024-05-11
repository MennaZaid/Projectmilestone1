#include "tiles.h"

Tiles::Tiles()
{
    map1tiles["Castle"] = QPixmap(":/map1/Castle.png");
    map1tiles["Fence"] = QPixmap(":/map1/fence_00.png");
    map1tiles["Fencehorizontal"] = QPixmap(":/map1/fence_01.png");
    map1tiles["Default"] = QPixmap(":/map1/green land.jpg");
    map1tiles["Cannon"] = QPixmap(":/map1/cannon.jpeg");


    /*map2tiles["Castle"] = QPixmap(":/Ice/IceCastle.png");
    map2tiles["Fence"] = QPixmap(":/Ice/wallvertical.png");
    map2tiles["Fencehorizontal"] = QPixmap(":/Ice/Wall.png");
    map2tiles["Default"] = QPixmap(":/Ice/GameBG.png");
    map2tiles["Cannon"] = QPixmap(":/Ice/flamethrower.png");*/



}


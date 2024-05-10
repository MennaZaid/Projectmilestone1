#include "tiles.h"

Tiles::Tiles()
{
    map1tiles["Castle"] = QPixmap(":/map1/Castle.png");
    map1tiles["Fence"] = QPixmap(":/map1/fence_00.png");
    map1tiles["Default"] = QPixmap(":/map1/green land.jpg");
    map1tiles["Cannon"] = QPixmap(":/map1/cannon.jpeg");

    map2land = QPixmap(":/map2/desert land.png");
    map2Castle = QPixmap(":/map2/SandCastle.png");
    map2Fence = QPixmap(":/map2/SandFence.png");
    map2Canon = QPixmap(":/map2/SandTower.png");


    map3land = QPixmap(":/map3/ice land.png");
    map3Castle = QPixmap(":/map3/IceCastle.png");
    map3Fence= QPixmap(":/map3/IceFence.png");
    map3Canon = QPixmap(":/map3/IceTower.png");
}


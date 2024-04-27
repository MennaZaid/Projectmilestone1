#include "node.h"

Node::Node(QPoint coords, Building *building) {
    this->building = building;
    this->coords = coords;
}

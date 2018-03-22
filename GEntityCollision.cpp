#include "GEntity.h"


std::vector<GEntityCollision>  GEntityCollision::EntityCollisonList;

GEntityCollision::GEntityCollision()
{
    entityA = NULL;
    entityB = NULL;
}

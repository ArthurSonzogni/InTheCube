#ifndef GAME_COLLISION_HPP
#define GAME_COLLISION_HPP

#include "game/Forme.hpp"

// return if a is in [b,c]
bool IsBetween(float a, float b, float c);

// return if [l1,r1] intersect [l2,r2]
bool IsCrossing(float l1, float r1, float l2, float r2);

// test if the Point m is on the right side of the vector ab
// return -1 on the left, 1 on the right, o if a b c are aligned
int Side(Point m, Point a, Point b);

int Sign(float x);

// test whether there are a collision between the two Rectangle r1 and r2
bool IsCollision(Rectangle r1, Rectangle r2);
bool IsCollision(Rectangle r, Point p);
bool IsCollision(Point p, Rectangle r);
bool IsCollision(Rectangle r, Line l);
bool IsCollision(Line l, Rectangle r);
bool IsCollision(Line l1, Line l2);
#endif /* GAME_COLLISION_HPP */

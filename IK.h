#ifndef IK_H
#define IK_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <FL/Fl.H>

#include "modelerglobals.h"
#include "modelerapp.h"

#define SQUARE(x) ((x) * (x))

inline double calculateTargetDiff(double targetX, double targetY, double targetZ, double x, double y, double z);

void moveLeftArm(double targetX, double targetY, double targetZ);
void moveRightArm(double targetX, double targetY, double targetZ);
#endif
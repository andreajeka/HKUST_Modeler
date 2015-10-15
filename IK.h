#ifndef IK_H
#define IK_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <FL/Fl.H>

#include "modelerglobals.h"
#include "modelerapp.h"

#define SQUARE(x) ((x) * (x))

inline double calculateTargetDiff(double tarX, double tarY, double tarZ, double x, double y, double z);

void moveLeftArm(double tarX, double tarY, double tarZ);
//can add more here later
#endif
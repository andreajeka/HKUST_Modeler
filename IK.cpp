#include "IK.h"

inline double calculateTargetDiff(double targetX, double targetY, double targetZ, double x, double y, double z) {
	return sqrt(SQUARE(targetX - x) + SQUARE(targetY - y) + SQUARE(targetZ - z));
}

void moveLeftArm(double targetX, double targetY, double targetZ) {
	double x0Pos = 0;
	double y0Pos = 0;
	double z0Pos = 0;
	double minDiff = INT_MAX;

	int xr1, yr1, xr2, yr2, xr3, yr3;
	const double length1 = 2.0;
	const double length2 = 2.0;
	const double length3 = 2.0;

	for (int y1 = -90; y1 <= -30; y1 += 10) {
		for (int x1 = -60; x1 <= 0; x1 += 10) {
			// 1 rad approx 57.3 deg
			double phi1 = (90 + y1) / 57.3;
			double theta1 = (90 + x1) / 57.3;
			double x1Pos = x0Pos - length1 * cos(phi1) * sin(theta1);
			double y1Pos = y0Pos + length1 * cos(theta1);
			double z1Pos = z0Pos + length1 * sin(phi1) * sin(theta1);

			for (int y2 = -70; y2 <= -10; y2 += 10) {
				for (int x2 = 20; x2 <= 80; x2 += 10) {
					double phi2 = (90 + y1 + y2) / 57.3;
					double theta2 = (90 + x1 + x2) / 57.3;
					double x2Pos = x1Pos - length2 * cos(phi2) * sin(theta2);
					double y2Pos = y1Pos + length2 * cos(theta2);
					double z2Pos = z1Pos + length2 * sin(phi2) * sin(theta2);

					for (int y3 = -50; y3 <= 10; y3 += 10) {
						for (int x3 = -10; x3 <= 50; x3 += 10) {
							double phi3 = (90 + y1 + y2 + y3) / 57.3;
							double theta3 = (90 + x1 + x2 + x3) / 57.3;
							double x3Pos = x2Pos - length3 * cos(phi3) * sin(theta3);
							double y3Pos = y2Pos + length3 * cos(theta3);
							double z3Pos = z2Pos + length3 * sin(phi3) * sin(theta3);
							double diff = calculateTargetDiff(targetX, targetY, targetZ, x3Pos, y3Pos, z3Pos);
							if (diff < minDiff) {
								minDiff = diff;
								xr1 = x1;
								yr1 = y1;
								xr2 = x2;
								yr2 = y2;
								xr3 = x3;
								yr3 = y3;
							}
						}
					}
				}
			}
		}
	}
	SETVAL(LEFTARMY, yr1);
	SETVAL(LEFTARMX, xr1);
	SETVAL(LEFTELBOWY, yr2);
	SETVAL(LEFTELBOWX, xr2);
	SETVAL(LEFTHANDX, xr3);
	Fl::redraw();
}

void moveRightArm(double targetX, double targetY, double targetZ) {
	double x0Pos = 0;
	double y0Pos = 0;
	double z0Pos = 0;
	double minDiff = INT_MAX;

	int xr1, yr1, xr2, yr2, xr3, yr3;
	const double length1 = 2.0;
	const double length2 = 2.0;
	const double length3 = 2.0;

	for (int y1 = -150; y1 <= -90; y1 += 10) {
		for (int x1 = -60; x1 <= 0; x1 += 10) {
			double phi1 = (90 + y1) / 57.3;
			double theta1 = (90 + x1) / 57.3;
			double x1Pos = x0Pos - length1 * cos(phi1) * sin(theta1);
			double y1Pos = y0Pos + length1 * cos(theta1);
			double z1Pos = z0Pos + length1 * sin(phi1) * sin(theta1);

			for (int y2 = 10; y2 <= 70; y2 += 10) {
				for (int x2 = 20; x2 <= 80; x2 += 10) {
					double phi2 = (90 + y1 + y2) / 57.3;
					double theta2 = (90 + x1 + x2) / 57.3;
					double x2Pos = x1Pos - length2 * cos(phi2) * sin(theta2);
					double y2Pos = y1Pos + length2 * cos(theta2);
					double z2Pos = z1Pos + length2 * sin(phi2) * sin(theta2);

					for (int y3 = -10; y3 <= 50; y3 += 10) {
						for (int x3 = -10; x3 <= 50; x3 += 10) {
							double phi3 = (90 + y1 + y2 + y3) / 57.3;
							double theta3 = (90 + x1 + x2 + x3) / 57.3;
							double x3Pos = x2Pos - length3 * cos(phi3) * sin(theta3);
							double y3Pos = y2Pos + length3 * cos(theta3);
							double z3Pos = z2Pos + length3 * sin(phi3) * sin(theta3);
							double diff = calculateTargetDiff(targetX, targetY, targetZ, x3Pos, y3Pos, z3Pos);
							if (diff < minDiff) {
								minDiff = diff;
								xr1 = x1;
								yr1 = y1;
								xr2 = x2;
								yr2 = y2;
								xr3 = x3;
								yr3 = y3;
							}
						}
					}
				}
			}
		}
	}
	SETVAL(RIGHTARMY, yr1);
	SETVAL(RIGHTARMX, xr1);
	SETVAL(RIGHTELBOWY, yr2);
	SETVAL(RIGHTELBOWX, xr2);
	SETVAL(RIGHTHANDX, xr3);
	Fl::redraw();
}
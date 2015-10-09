// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <math.h>

#include "modelerglobals.h"

#include "metaball.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char *label) : ModelerView(x, y, w, h, label) { }
	virtual void draw();

private:
	void drawHead();
	void drawNeck();

	void drawUpperTorso();
	void drawLowerTorso();

	void drawRightHandJoint();
	void drawUpperRightHand();
	void drawLowerRightHand();
	void drawRightHand();

	void drawLeftHandJoint();
	void drawUpperLeftHand();
	void drawLowerLeftHand();
	void drawLeftHand();

	void drawRightLegJoint();
	void drawUpperRightLeg();
	void drawLowerRightLeg();
	void drawRightFeet();

	void drawLeftLegJoint();
	void drawUpperLeftLeg();
	void drawLowerLeftLeg();
	void drawLeftFeet();

	void drawTail();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{
	return new SampleModel(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the sample model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix(); // push identity
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS)); // values set by the sliders

	drawHead();
	drawNeck();

	drawUpperTorso();
	drawLowerTorso();

	drawRightHandJoint();
	drawUpperRightHand();
	drawLowerRightHand();
	drawRightHand();

	drawLeftHandJoint();
	drawUpperLeftHand();
	drawLowerLeftHand();
	drawLeftHand();

	drawRightLegJoint();
	drawUpperRightLeg();
	drawLowerRightLeg();
	drawRightFeet();

	drawLeftLegJoint();
	drawUpperLeftLeg();
	drawLowerLeftLeg();
	drawLeftFeet();

	drawTail(); // handle the positioning and hierachical modeling of the tail

	if (VAL(METABALLSKIN)) {
		MetaBalls mb;
		mb.setUpGrid();
		mb.setUpMetaballs();
		mb.evalScalarField();
		mb.draw();
	}

	glPopMatrix();
}

void SampleModel::drawHead() {
	glPushMatrix();
	glTranslated(0, UPPER_TORSO_RADIUS + HEAD_RADIUS, 0);
	drawSphere(HEAD_RADIUS);
	glPopMatrix();
}
void SampleModel::drawNeck() {
	glPushMatrix();
	glTranslated(0, UPPER_TORSO_RADIUS + 0.1, 0);
	glScaled(0.4, 0.6, 0.4);
	glTranslated(-0.5, -0.5, -0.5);
	drawBox(1, 1, 1);
	glPopMatrix();
}
void SampleModel::drawUpperTorso() {
	glPushMatrix();
	drawSphere(UPPER_TORSO_RADIUS); // center at (0, 0, 0)
	glPopMatrix();
}
void SampleModel::drawLowerTorso() {
	glPushMatrix();
	glTranslated(0, -UPPER_TORSO_RADIUS, 0); // move down
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.4);
	drawCylinder(LOWER_TORSO_HEIGHT, 0.9, 0.8);
	glPopMatrix();
}
void SampleModel::drawRightHandJoint() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS, 0.6, 0);
	glRotated(20, 0.0, 0.0, 1.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glTranslated(0, 0, -0.2);
	drawCylinder(0.4, 0.2, 0.2);
	glPopMatrix();
}
void SampleModel::drawUpperRightHand() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS + 0.2, 0.8, 0);
	drawSphere(0.4);

	glTranslated(0.3, -0.6, 0);
	glRotated(20, 0.0, 0.0, 1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(1, 0.25, 0.25);
	glPopMatrix();
}
void SampleModel::drawLowerRightHand() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS + 0.7, -0.3, 0);
	drawSphere(0.2);

	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	drawCylinder(1.2, 0.25, 0.15);
	glPopMatrix();
}
void SampleModel::drawRightHand() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS + 0.7, -1.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.1);
	drawCylinder(0.4, 0.10, 0.05);
	glPopMatrix();
}
void SampleModel::drawLeftHandJoint() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS, 0.6, 0);
	glRotated(20, 0.0, 0.0, -1.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glTranslated(0, 0, -0.2);
	drawCylinder(0.4, 0.2, 0.2);
	glPopMatrix();
}
void SampleModel::drawUpperLeftHand() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS - 0.2, 0.8, 0);
	drawSphere(0.4);

	glTranslated(-0.3, -0.6, 0);
	glRotated(20, 0.0, 0.0, -1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(1, 0.25, 0.25);
	glPopMatrix();
}
void SampleModel::drawLowerLeftHand() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS - 0.7, -0.3, 0);
	drawSphere(0.2);

	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	drawCylinder(1.2, 0.25, 0.15);
	glPopMatrix();
}
void SampleModel::drawLeftHand() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS - 0.7, -1.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.1);
	drawCylinder(0.4, 0.10, 0.05);
	glPopMatrix();
}
void SampleModel::drawRightLegJoint() {
	glPushMatrix();
	glTranslated(0.5, -UPPER_TORSO_RADIUS - 0.4, 0);
	glRotated(48, 0.0, 0.0, 1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.3);
	drawCylinder(0.7, 0.2, 0.2);
	glPopMatrix();
}
void SampleModel::drawUpperRightLeg() {
	glPushMatrix();
	glTranslated(0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT, 0);
	drawSphere(0.3);

	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	drawCylinder(1.2, 0.35, 0.35);
	glPopMatrix();
}
void SampleModel::drawLowerRightLeg(){
	glPushMatrix();
	glTranslated(0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7, 0);
	drawSphere(0.3);

	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	drawCylinder(1.4, 0.35, 0.25);
	glPopMatrix();
}
void SampleModel::drawRightFeet() {
	glPushMatrix();
	glTranslated(0.9 + 0.2, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 1.3, 0.4);
	glRotated(30, 0.0, 1.0, 0.0);
	glTranslated(0, 0, -0.3);
	drawCylinder(0.6, 0.25, 0.1);
	glPopMatrix();
}
void SampleModel::drawLeftLegJoint() {
	glPushMatrix();
	glTranslated(-0.5, -UPPER_TORSO_RADIUS - 0.4, 0);
	glRotated(48, 0.0, 0.0, -1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.3);
	drawCylinder(0.7, 0.2, 0.2);
	glPopMatrix();
}
void SampleModel::drawUpperLeftLeg() {
	glPushMatrix();
	glTranslated(-0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT, 0);
	drawSphere(0.3);

	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	drawCylinder(1.2, 0.35, 0.35);
	glPopMatrix();
}
void SampleModel::drawLowerLeftLeg() {
	glPushMatrix();
	glTranslated(-0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7, 0);
	drawSphere(0.3);

	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	drawCylinder(1.4, 0.35, 0.25);
	glPopMatrix();
}
void SampleModel::drawLeftFeet() {
	glPushMatrix();
	glTranslated(-0.9 - 0.2, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 1.3, 0.4);
	glRotated(30, 0.0, -1.0, 0.0);
	glTranslated(0, 0, -0.3);
	drawCylinder(0.6, 0.25, 0.1);
	glPopMatrix();
}
void SampleModel::drawTail() {
	glPushMatrix();
	glTranslated(0, -UPPER_TORSO_RADIUS, -0.8);
	glTranslated(0, 0, -0.3);
	drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(50, -1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(40, -1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(10, -1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(5, -1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(5, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(10, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(15, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(20, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(0.6, 0.1, 0.1);
	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[TAILMOVEMENT] = ModelerControl("Tail Movement", 0, 100, 1, 0);
	controls[METABALLSKIN] = ModelerControl("Metaball Skin", 0, 1, 1, 0);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

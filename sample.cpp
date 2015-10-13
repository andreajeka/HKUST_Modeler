// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <math.h>

#include "modelerglobals.h"

#include "metaball.h"

#define PI 3.14159265

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char *label) : ModelerView(x, y, w, h, label) { }
	virtual void draw();

private:
	int iterator = 0;
	bool animate = false;
	
	int animUpperArmAngle;
	int animUpperLegAngle;
	int animLowerLegAngle;
	int animLeftFootAngle;
	int animRightFootAngle;

	void drawHead();
	void drawFace();
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
	void drawRightFoot();

	void drawLeftLegJoint();
	void drawUpperLeftLeg();
	void drawLowerLeftLeg();
	void drawLeftFoot();

	void drawTail();

	void animationIterator();
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

	animate = ModelerApplication::Instance()->GetAnimation();
	if (animate)
		animationIterator();

	glPushMatrix(); // push identity
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS)); // values set by the sliders

	setDiffuseColor(.940f, .816f, .811f);
	drawHead();
	
	setDiffuseColor(0, 0, 0);
	drawFace();

	setDiffuseColor(.940f, .816f, .811f);
	drawNeck();

	setDiffuseColor(COLOR_GREEN);
	drawUpperTorso();
	drawLowerTorso();

	setDiffuseColor(.940f, .816f, .811f);
	drawRightHandJoint();
	glPushMatrix();
	if (animate)
		glRotated(animUpperArmAngle, 1.0, 0, 0);
	drawUpperRightHand();
	drawLowerRightHand();
	drawRightHand();
	glPopMatrix();


	drawLeftHandJoint();
	glPushMatrix();
	if (animate)
		glRotated(-animUpperArmAngle, 1.0, 0, 0);
	drawUpperLeftHand();
	drawLowerLeftHand();
	drawLeftHand();
	glPopMatrix();


	drawRightLegJoint();
	drawUpperRightLeg();
	drawLowerRightLeg();
	drawRightFoot();

	drawLeftLegJoint();
	drawUpperLeftLeg();
	drawLowerLeftLeg();
	drawLeftFoot();

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
	if (VAL(TEXTURESKIN))
		drawTextureSphere(HEAD_RADIUS);
	else drawSphere(HEAD_RADIUS);
	glPopMatrix();
}

void SampleModel::drawFace() {
	glPushMatrix();
	
	// eyes
	glTranslated(0.2, UPPER_TORSO_RADIUS + HEAD_RADIUS + 0.3, 0.7);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.1);
	else drawSphere(0.1);
	glTranslated(-0.4, 0, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.1);
	else drawSphere(0.1);

	// nose
	setDiffuseColor(.940f, .816f, .811f);
	glTranslated( 0.2, -0.3, 0.1);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.1);
	else drawSphere(0.1);
	glPopMatrix();

	// mouth
	setDiffuseColor(1.0,0,0);
	glTranslated(-0.25, UPPER_TORSO_RADIUS + 0.3, 0.7);
	glRotated(20, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -0.05);
	if (VAL(TEXTURESKIN))
		drawTextureBox(0.5,0.3,0);
	else drawBox(0.5,0.3,0);
	glPopMatrix();
}

void SampleModel::drawNeck() {
	glPushMatrix();
	glTranslated(0, UPPER_TORSO_RADIUS + 0.1, 0);
	glScaled(0.4, 0.6, 0.4);
	glTranslated(-0.5, -0.5, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureBox(1, 1, 1);
	else drawBox(1, 1, 1);
	glPopMatrix();
}
void SampleModel::drawUpperTorso() {
	glPushMatrix();
	if (VAL(TEXTURESKIN))
		drawTextureSphere(UPPER_TORSO_RADIUS);
	else drawSphere(UPPER_TORSO_RADIUS); // center at (0, 0, 0)
	glPopMatrix();
}
void SampleModel::drawLowerTorso() {
	glPushMatrix();
	glTranslated(0, -UPPER_TORSO_RADIUS, 0); // move down
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.4);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(LOWER_TORSO_HEIGHT, 0.9, 0.8);
	else drawCylinder(LOWER_TORSO_HEIGHT, 0.9, 0.8);
	glPopMatrix();
}
void SampleModel::drawRightHandJoint() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS, 0.6, 0);
	glRotated(20, 0.0, 0.0, 1.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glTranslated(0, 0, -0.2);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.4, 0.2, 0.2);
	else drawCylinder(0.4, 0.2, 0.2);
	glPopMatrix();
}
void SampleModel::drawUpperRightHand() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS + 0.2, 0.8, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.4);
	else drawSphere(0.4);
	glTranslated(0.3, -0.6, 0);
	glRotated(20, 0.0, 0.0, 1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1, 0.25, 0.25);
	else drawCylinder(1, 0.25, 0.25);
	glPopMatrix();
}
void SampleModel::drawLowerRightHand() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS + 0.7, -0.3, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.2);
	else drawSphere(0.2);
	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1.2, 0.25, 0.15);
	else drawCylinder(1.2, 0.25, 0.15);
	glPopMatrix();
}
void SampleModel::drawRightHand() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS + 0.7, -1.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.1);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.4, 0.10, 0.05);
	else drawCylinder(0.4, 0.10, 0.05);
	glPopMatrix();
}
void SampleModel::drawLeftHandJoint() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS, 0.6, 0);
	glRotated(20, 0.0, 0.0, -1.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glTranslated(0, 0, -0.2);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.4, 0.2, 0.2);
	else drawCylinder(0.4, 0.2, 0.2);
	glPopMatrix();
}
void SampleModel::drawUpperLeftHand() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS - 0.2, 0.8, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.4);
	else drawSphere(0.4);

	glTranslated(-0.3, -0.6, 0);
	glRotated(20, 0.0, 0.0, -1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1, 0.25, 0.25);
	else drawCylinder(1, 0.25, 0.25);
	glPopMatrix();
}
void SampleModel::drawLowerLeftHand() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS - 0.7, -0.3, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.2);
	else drawSphere(0.2);

	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1.2, 0.25, 0.15);
	else drawCylinder(1.2, 0.25, 0.15);
	glPopMatrix();
}
void SampleModel::drawLeftHand() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS - 0.7, -1.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.1);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.4, 0.10, 0.05);
	else drawCylinder(0.4, 0.10, 0.05);
	glPopMatrix();
}
void SampleModel::drawRightLegJoint() {
	glPushMatrix();
	glTranslated(0.5, -UPPER_TORSO_RADIUS - 0.4, 0);
	glRotated(48, 0.0, 0.0, 1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.3);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.7, 0.2, 0.2);
	else drawCylinder(0.7, 0.2, 0.2);
	glPopMatrix();
}
void SampleModel::drawUpperRightLeg() {
	glPushMatrix();
	glTranslated(0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.3);
	else drawSphere(0.3);

	if (animate)
		glRotated(-animUpperLegAngle, 1.0, 0, 0);

	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	if (VAL(TEXTURESKIN)) {
		drawTextureCylinder(1.2, 0.35, 0.35);
		glTranslated(0, 0, 1.25);
		drawTextureSphere(0.3);
	}
	else {
		drawCylinder(1.2, 0.35, 0.35);
		glTranslated(0, 0, 1.25);
		drawSphere(0.3);
	}
	glPopMatrix();
}
void SampleModel::drawLowerRightLeg(){
	glPushMatrix();
	if (animate)
		glRotated(animLowerLegAngle, 1.0, 0, 0);
	glTranslated(0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.7);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1.4, 0.35, 0.25);
	else drawCylinder(1.4, 0.35, 0.25);
	glPopMatrix();
}
void SampleModel::drawRightFoot() {
	glPushMatrix();
	if (animate)
		glRotated(animLowerLegAngle, 1.0, 0, 0);
	glTranslated(0.9 + 0.2, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 1.3, 0.4);
	glRotated(30, 0.0, 1.0, 0.0);
	glTranslated(0, 0, -0.3);
	if (animate)
		glRotated(animRightFootAngle, 1.0, 0, 0);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.25, 0.1);
	else drawCylinder(0.6, 0.25, 0.1);
	glPopMatrix();
}
void SampleModel::drawLeftLegJoint() {
	glPushMatrix();
	glTranslated(-0.5, -UPPER_TORSO_RADIUS - 0.4, 0);
	glRotated(48, 0.0, 0.0, -1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.3);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.7, 0.2, 0.2);
	else drawCylinder(0.7, 0.2, 0.2);
	glPopMatrix();
}
void SampleModel::drawUpperLeftLeg() {
	glPushMatrix();
	glTranslated(-0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.3);
	else drawSphere(0.3);

	if (animate) 
		glRotated(animUpperLegAngle, 1.0, 0, 0);
	
	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	if (VAL(TEXTURESKIN)) {
		drawTextureCylinder(1.2, 0.35, 0.35);
		glTranslated(0, 0, 1.25);
		drawTextureSphere(0.3);
	}
	else {
		drawCylinder(1.2, 0.35, 0.35);
		glTranslated(0, 0, 1.25);
		drawSphere(0.3);
	}
	glPopMatrix();
}
void SampleModel::drawLowerLeftLeg() {
	glPushMatrix();
	if (animate)
		glRotated(-animLowerLegAngle, 1.0, 0, 0);
	glTranslated(-0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.7);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1.4, 0.35, 0.25);
	else drawCylinder(1.4, 0.35, 0.25);
	glPopMatrix();
}
void SampleModel::drawLeftFoot() {
	glPushMatrix();
	if (animate)
		glRotated(-animLowerLegAngle, 1.0, 0, 0);
	glTranslated(-0.9 - 0.2, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 1.3, 0.4);
	glRotated(30, 0.0, -1.0, 0.0);
	glTranslated(0, 0, -0.3);
	if (animate)
		glRotated(animLeftFootAngle, 1.0, 0, 0);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.25, 0.1);
	else drawCylinder(0.6, 0.25, 0.1);
	glPopMatrix();
}
void SampleModel::drawTail() {
	glPushMatrix();
	glTranslated(0, -UPPER_TORSO_RADIUS, -0.8);
	glTranslated(0, 0, -0.3);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(50, -1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(40, -1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(10, -1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(5, -1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(5, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(10, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(15, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);

	glRotated(VAL(TAILMOVEMENT), 1.0, 0.0, 0.0);
	glRotated(20, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(0.6, 0.1, 0.1);
	else drawCylinder(0.6, 0.1, 0.1);
	glPopMatrix();
}

void SampleModel::animationIterator() {
	if (iterator == 60) {
		iterator = 0;
	}

	if (iterator < 15) {
		animUpperLegAngle = -(iterator + 1) * 2;
		animUpperArmAngle = animUpperLegAngle / 3.5;
		if (iterator % 2 == 0)
			animLowerLegAngle = (iterator + 1 - 1);
		animLeftFootAngle = -iterator / 3;
		animRightFootAngle = (60 - iterator) / 2 + 10;
		++iterator;
		return;
	}
	else if (iterator < 30) {
		animUpperLegAngle = -(30 - iterator) * 2;
		animUpperArmAngle = animUpperLegAngle / 3.5;
		if (iterator % 2 == 0)
			animLowerLegAngle = (30 - iterator - 1);
		animLeftFootAngle = -iterator/3 + 10;
		animRightFootAngle = (45 - iterator) / 3 + 10;
		++iterator;
		return;
	}
	else if (iterator < 45) {
		animUpperLegAngle = (iterator - 29) * 2;
		animUpperArmAngle = animUpperLegAngle / 3.5;
		if (iterator % 2 == 0)
			animLowerLegAngle = -(iterator - 29 - 1);
		animLeftFootAngle = iterator/3 + 10;
		animRightFootAngle = (30 - iterator) / 3 + 10;
		++iterator;
		return;
	}
	else if (iterator < 60) {
		animUpperLegAngle = (60 - iterator) * 2;
		animUpperArmAngle = animUpperLegAngle / 3.5;
		if (iterator % 2 == 0)
			animLowerLegAngle = -(60 - iterator - 1);
		animLeftFootAngle = iterator/2 + 10;
		animRightFootAngle = (15 -iterator) / 3;
		++iterator;
		return;
	}
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
	controls[TEXTURESKIN] = ModelerControl("Texture Skin", 0, 1, 1, 0);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <FL/Fl.H>
#include <math.h>

#include "modelerglobals.h"
#include "metaball.h"

#define PI 3.14159265

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char *label) :
		ModelerView(x, y, w, h, label)
	{ 
	
	}
	virtual void draw();
	static SampleModel *instance;
private:
	int iterator = 0;
	bool animate = false;
	
	int animHeadAngle;
	int animUpperArmAngle;
	int animUpperLegAngle;
	int animLowerLegAngle;
	int animLeftFootAngle;
	int animRightFootAngle;

	void drawEyeBandana();
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

	void drawShell();

};

SampleModel *SampleModel::instance = NULL;

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

	if (VAL(NINJATURTLE))
		setDiffuseColor(COLOR_GREEN);
	else
		setDiffuseColor(.940f, .816f, .811f);

	if (animate)
		glRotated(animHeadAngle, 0.0, 1.0, 0.0);

	if (VAL(EYEBANDANA))
		drawEyeBandana();

	if (!VAL(NINJATURTLE))
		setDiffuseColor(.940f, .816f, .811f);
	drawHead();
	
	if (!VAL(NINJATURTLE)) {
		setDiffuseColor(0, 0, 0);
		drawFace();
		setDiffuseColor(.940f, .816f, .811f);
		drawNeck();
	}

	drawUpperTorso();
	drawLowerTorso();

	if (!VAL(NINJATURTLE))
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
	drawLeftLegJoint();

	drawUpperRightLeg();
	drawLowerRightLeg();
	drawRightFoot();

	drawUpperLeftLeg();
	drawLowerLeftLeg();
	drawLeftFoot();

	if (VAL(NINJATURTLE))
		drawShell();
	else
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

void SampleModel::drawEyeBandana() {
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(0, UPPER_TORSO_RADIUS + HEAD_RADIUS + 0.3, 0);
	drawTorus(0.3, 0.5);
	glPopMatrix();
	if (VAL(NINJATURTLE))
		setDiffuseColor(COLOR_GREEN);
	else
		setDiffuseColor(.940f, .816f, .811f);
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
	glPushMatrix();

	setDiffuseColor(1.0f, 0.0f, 0.0f);
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

	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS + 0.2, 0.8, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.4);
	else drawSphere(0.4);
	glPopMatrix();
}
void SampleModel::drawUpperRightHand() {
	glPushMatrix();
	glTranslated(UPPER_TORSO_RADIUS + 0.2, 0.8, 0);
	glRotated(VAL(RIGHTARMZ), 0, 0, 1.0);
	glRotated(VAL(RIGHTARMY), 0, -1.0, 0);
	glTranslated(0.3, -0.6, 0);
	glRotated(20, 0.0, 0.0, 1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	
	glTranslated(0, 0, -0.5);
	glRotated(VAL(RIGHTARMX), -1.0, 0, 0);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1, 0.25, 0.25);
	else drawCylinder(1, 0.25, 0.25);
}
void SampleModel::drawLowerRightHand() {

	// Undo transformations
	glTranslated(0, 0, 0.5);
	glRotated(-90, 1.0, 0.0, 0.0);
	glRotated(-20, 0.0, 0.0, 1.0);
	glTranslated(-0.3, 0.6, 0);
	glTranslated(-UPPER_TORSO_RADIUS - 0.2, -0.8, 0);

	glTranslated(UPPER_TORSO_RADIUS + 0.7, -0.3, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.2);
	else drawSphere(0.2);
	glRotated(VAL(RIGHTELBOWX), -1.0, 0, 0);
	glRotated(VAL(RIGHTELBOWY), 0, 1.0, 0);
	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1.2, 0.25, 0.15);
	else drawCylinder(1.2, 0.25, 0.15);
	
}
void SampleModel::drawRightHand() {
	
	// Undo transformations
	glTranslated(0, 0, 0.6);
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0, 0.7, 0);
	glTranslated(-UPPER_TORSO_RADIUS - 0.7, 0.3, 0);

	glTranslated(UPPER_TORSO_RADIUS + 0.7, -1.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.1);
	glRotated(VAL(RIGHTHANDX), -1.0, 0, 0);
	glRotated(VAL(RIGHTHANDZ), 0, 0, 1.0);
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

	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS - 0.2, 0.8, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.4);
	else drawSphere(0.4);
	glPopMatrix();
}
void SampleModel::drawUpperLeftHand() {
	glPushMatrix();
	glTranslated(-UPPER_TORSO_RADIUS - 0.2, 0.8, 0);
	glRotated(VAL(LEFTARMZ), 0, 0, 1.0);
	glRotated(VAL(LEFTARMY), 0, 1.0, 0);
	glTranslated(-0.3, -0.6, 0);
	glRotated(20, 0.0, 0.0, -1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	glRotated(VAL(LEFTARMX), 1.0, 0, 0);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1, 0.25, 0.25);
	else drawCylinder(1, 0.25, 0.25);
}
void SampleModel::drawLowerLeftHand() {

	// Undo Transformations
	glTranslated(0, 0, 0.5);
	glRotated(-90, 1.0, 0.0, 0.0);
	glRotated(-20, 0.0, 0.0, -1.0);
	glTranslated(0.3, 0.6, 0);
	glTranslated(UPPER_TORSO_RADIUS + 0.2, -0.8, 0);

	glTranslated(-UPPER_TORSO_RADIUS - 0.7, -0.3, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.2);
	else drawSphere(0.2);
	glRotated(VAL(LEFTELBOWX), -1.0, 0, 0);
	glRotated(VAL(LEFTELBOWY), 0, 1.0, 0);
	glTranslated(0, -0.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.6);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1.2, 0.25, 0.15);
	else drawCylinder(1.2, 0.25, 0.15);
}
void SampleModel::drawLeftHand() {
	
	// Undo Transformations
	glTranslated(0, 0, 0.6);
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0, 0.7, 0);
	glTranslated(UPPER_TORSO_RADIUS + 0.7, 0.3, 0);

	glTranslated(-UPPER_TORSO_RADIUS - 0.7, -1.7, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.1);
	glRotated(VAL(LEFTHANDX), -1.0, 0, 0);
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
	glRotated(VAL(RIGHTKNEE), -1.0, 0.0, 0.0);
	glRotated(VAL(RIGHTLEGX), -1.0, 0, 0);
	glRotated(VAL(RIGHTLEGZ), 0.0, 0, 1.0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.3);
	else drawSphere(0.3);

	if (animate) {
		glRotated(-animUpperLegAngle, 1.0, 0, 0);
		SETVAL(RIGHTKNEE, 0);
	}

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
}
void SampleModel::drawLowerRightLeg(){
	if (animate) {
		glRotated(animLowerLegAngle, 1.0, 0, 0);
		SETVAL(RIGHTKNEE, 0);
	}
	
	//Undo transformations
	glTranslated(0, 0, -1.25);
	glTranslated(0, 0, 0.6);
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0, 0.7, 0);
	glRotated(-VAL(RIGHTKNEE), -1.0, 0.0, 0.0);
	glTranslated(-0.9, UPPER_TORSO_RADIUS + LOWER_TORSO_HEIGHT, 0);

	glTranslated(0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 0.7, 0);
	glRotated(VAL(RIGHTKNEE) * 2, 1.0, 0.0, 0.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.7);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1.4, 0.35, 0.25);
	else drawCylinder(1.4, 0.35, 0.25);
}
void SampleModel::drawRightFoot() {
	
	if (animate) {
		glRotated(animLowerLegAngle, 1.0, 0, 0);
		SETVAL(RIGHTKNEE, 0);
	}

	// Undo transformations
	glTranslated(0, 0, 0.7);
	glRotated(-90, 1.0, 0.0, 0.0);
	glRotated(-VAL(RIGHTKNEE) * 2, 1.0, 0.0, 0.0);
	glTranslated(-0.9, UPPER_TORSO_RADIUS + LOWER_TORSO_HEIGHT + 0.7 + 0.7 + 0.7, 0);

	glTranslated(0.9 + 0.2, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 1.3, 0.4);
	glTranslated(0, 0, -VAL(RIGHTKNEE) / 50);
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

	glPushMatrix();
	glTranslated(-0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT, 0);
	if (VAL(TEXTURESKIN))
		drawTextureSphere(0.3);
	else drawSphere(0.3);
	glPopMatrix();
}
void SampleModel::drawUpperLeftLeg() {

	glPushMatrix();
	glTranslated(-0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT, 0);
	glRotated(VAL(LEFTKNEE), -1.0, 0.0, 0.0);
	glRotated(VAL(LEFTLEGX), -1.0, 0, 0);
	glRotated(VAL(LEFTLEGZ), 0.0, 0, 1.0);
	if (animate){
		glRotated(animUpperLegAngle, 1.0, 0, 0);
		SETVAL(LEFTKNEE, 0);
		SETVAL(LEFTLEGX, 0);
		SETVAL(LEFTLEGZ, 0);
	}

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

}
void SampleModel::drawLowerLeftLeg() {
	if (animate) {
		glRotated(-animLowerLegAngle, 1.0, 0, 0);
		SETVAL(LEFTKNEE, 0);
	}

	//Undo transformations
	glTranslated(0, 0, -1.25);
	glTranslated(0, 0, 0.6);
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0, 0.7, 0);
	glRotated(-VAL(LEFTKNEE), -1.0, 0.0, 0.0);
	glTranslated(0.9, UPPER_TORSO_RADIUS + LOWER_TORSO_HEIGHT, 0);


	glTranslated(-0.9, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 0.7, 0);
	glRotated(2 * VAL(LEFTKNEE), 1.0, 0.0, 0.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.7);
	if (VAL(TEXTURESKIN))
		drawTextureCylinder(1.4, 0.35, 0.25);
	else drawCylinder(1.4, 0.35, 0.25);
}
void SampleModel::drawLeftFoot() {
	if (animate) {
		glRotated(-animLowerLegAngle, 1.0, 0, 0);
		SETVAL(LEFTKNEE,0);
	}

	// Undo Transformations
	glTranslated(0, 0, 0.7);
	glRotated(-90, 1.0, 0.0, 0.0);
	glRotated(-VAL(LEFTKNEE) * 2, 1.0, 0.0, 0.0);
	glTranslated(0.9, UPPER_TORSO_RADIUS + LOWER_TORSO_HEIGHT + 0.7 + 0.7 + 0.7, 0);


	glTranslated(-0.9 - 0.2, -UPPER_TORSO_RADIUS - LOWER_TORSO_HEIGHT - 0.7 - 0.7 - 1.3, 0.4);
	glTranslated(0, 0, -VAL(LEFTKNEE) / 50);
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
		animHeadAngle = iterator;
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
		animHeadAngle = iterator;
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
		animHeadAngle = -iterator;
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
		animHeadAngle = -iterator;
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

void SampleModel::drawShell() {
	// draw the front
	setDiffuseColor(251.0 / 255, 193.0 / 255, 86.0 / 255);
	drawTriangle(0, 0.4 + 0.8, 1.0, 
				 0, 0.4, 1.3, 
				 1.1, 0.4 + 0.8 - 0.3, 0.7); // T1: top, bottom, right
	drawTriangle(0, 0.4 + 0.8, 1.0,
				 0, 0.4, 1.3,
				 -1.1, 0.4 + 0.8 - 0.3, 0.7); // T2: top, bottom, left
	drawTriangle(0, 0.4, 1.3,
				 1.1, 0.4 + 0.8 - 0.3, 0.7,
				 1.1, 0.4 + 0.8 - 0.3 - 0.8, 0.7); // T3: left, top, bottom
	drawTriangle(0, 0.4, 1.3,
				 -1.1, 0.4 + 0.8 - 0.3, 0.7,
				 -1.1, 0.4 + 0.8 - 0.3 - 0.8, 0.7); // T4: right, top, bottom
	drawTriangle(0, 0.4, 1.3,
				 1.1, 0.4 + 0.8 - 0.3 - 0.8, 0.7,
				 0, -1.0, 1.3); // T5: top, right, bottom
	drawTriangle(0, 0.4, 1.3,
				 -1.1, 0.4 + 0.8 - 0.3 - 0.8, 0.7,
				 0, -1.0, 1.3); // T6: top, left, bottom
	drawTriangle(1.1, 0.4 + 0.8 - 0.3 - 0.8, 0.7,
				 0, -1.0, 1.3,
				 1.1, -1.5, 0.7); // T7: top, left, right
	drawTriangle(-1.1, 0.4 + 0.8 - 0.3 - 0.8, 0.7,
				 0, -1.0, 1.3,
				 -1.1, -1.5, 0.7); // T8: top, right, left
	drawTriangle(0, -1.0, 1.3,
				 0, -1.9, 1.0,
				 1.1, -1.5, 0.7); // T9: top, bottom, right
	drawTriangle(0, -1.0, 1.3,
				 0, -1.9, 1.0,
				 -1.1, -1.5, 0.7); // T10: top, bottom, left

	// draw the back squares
	setDiffuseColor(14.0 / 255, 130.0 / 255, 74.0 / 255);
	drawTriangle(0.3, 0.7, -1.5,
				 -0.3, 0.7, -1.5,
				 0.3, 0.1, -1.5); // T11: left, right, bottom
	drawTriangle(0.3, 0.1, -1.5,
				 -0.3, 0.1, -1.5,
				 -0.3, 0.7, -1.5); // T12: left, right, top
	drawTriangle(0.3, 0.1, -1.5,
				 -0.3, 0.1, -1.5,
			 	 0.3, -0.5, -1.5); // T13: left, right, bottom
	drawTriangle(0.3, -0.5, -1.5,
				 -0.3, -0.5, -1.5,
				 -0.3, 0.1, -1.5); // T14: left, right, top
	drawTriangle(0.3, -0.5, -1.5,
				 -0.3, -0.5, -1.5,
				 0.3, -1.1, -1.5); // T15: left, right, bottom
	drawTriangle(0.3, -1.1, -1.5,
				 -0.3, -1.1, -1.5,
				 -0.3, -0.5, -1.5); // T16: left, right, top

	// draw the back top plates
	drawTriangle(0.3, 0.7, -1.5,
				 -0.3, 0.7, -1.5,
				 0.0, 1.2, -0.7); // T17: left, right, top
	drawTriangle(-0.3, 0.7, -1.5,
				-1.3, 1.0, -0.7,
				 0.0, 1.2, -0.7); // T18: left, right, top
	drawTriangle(1.3, 1.0, -0.7,
				 0.3, 0.7, -1.5,
				 0.0, 1.2, -0.7); // T19: left, right, top

	// draw the back bottom plates
	drawTriangle(0.3, -1.1, -1.5,
				-0.3, -1.1, -1.5,
				 0.0, -1.6, -0.7); // T20: left, right, bottom
	drawTriangle(-0.3, -1.1, -1.5,
				-1.3, -1.3, -0.7,
				0.0, -1.6, -0.7); // T21: left, right, bottom
	drawTriangle(1.3, -1.5, -0.7,
				 0.3, -1.1, -1.5,
				 0.0, -1.6, -0.7); // T22: left, right, bottom

	// draw the back side plates
	drawTriangle(1.3, 1.0, -0.7,
				 0.3, 0.7, -1.5,
				 1.3, -1.5, -0.7); // T23: left, right, bottom
	drawTriangle(1.3, -1.5, -0.7,
				 0.3, -1.1, -1.5,
				 0.3, 0.7, -1.5); // T24: left, right, top
	drawTriangle(-0.3, 0.7, -1.5,
				 -1.3, 1.0, -0.7,
				 -1.3, -1.3, -0.7); // T25: left, right, bottom
	drawTriangle(-0.3, -1.1, -1.5,
				 -1.3, -1.3, -0.7,
				 -0.3, 0.7, -1.5); // T26: left, right, top

	// draw the sides
	setDiffuseColor(140 / 255, 200.0 / 255, 65.0 / 255);
	drawTriangle(0, 0.4 + 0.8, 1.0,
				 1.1, 0.4 + 0.8 - 0.3, 0.7,
				 1.3, 1.0, -0.7); // T27
	drawTriangle(1.3, 1.0, -0.7,
				 0.0, 1.2, -0.7,
				 0, 0.4 + 0.8, 1.0); // T28
	drawTriangle(0, 0.4 + 0.8, 1.0,
				-1.1, 0.4 + 0.8 - 0.3, 0.7,
				0.0, 1.2, -0.7); // T29
	drawTriangle(-1.3, 1.0, -0.7,
				 0.0, 1.2, -0.7,
				 -1.1, 0.4 + 0.8 - 0.3, 0.7); // T30

	drawTriangle(-1.3, 1.0, -0.7,
				 -1.1, 0.4 + 0.8 - 0.3, 0.7,
				 - 1.3, -1.3, -0.7); // T31
	drawTriangle(-1.1, 0.4 + 0.8 - 0.3, 0.7,
				-1.1, -1.5, 0.7,
				-1.3, -1.3, -0.7); // T32

	drawTriangle(1.3, -1.5, -0.7,
				 0, -1.9, 1.0,
				 1.1, -1.5, 0.7); // T33
	drawTriangle(1.3, -1.5, -0.7,
				 0.0, -1.6, -0.7,
				 0, -1.9, 1.0); // T34
	drawTriangle(-1.3, -1.3, -0.7,
				0.0, -1.6, -0.7,
				 0, -1.9, 1.0); // T35
	drawTriangle(0, -1.9, 1.0,
				 -1.1, -1.5, 0.7,
				 -1.3, -1.3, -0.7); // T36
	drawTriangle(1.1, 0.4 + 0.8 - 0.3, 0.7,
				 1.1, -1.5, 0.7,
				 1.3, -1.5, -0.7); // T37
	drawTriangle(1.3, 1.0, -0.7,
				 1.1, 0.4 + 0.8 - 0.3, 0.7,
				 1.3, -1.5, -0.7); // T38
	
}


int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[RIGHTARMX] = ModelerControl("Right Arm Angle X", 0, 360, 1, 0);
	controls[RIGHTARMY] = ModelerControl("Right Arm Angle Y", 0, 360, 1, 0);
	controls[RIGHTARMZ] = ModelerControl("Right Arm Angle Z", 0, 360, 1, 0);
	controls[RIGHTELBOWX] = ModelerControl("Right Elbow Angle X", 0, 180, 1, 0);
	controls[RIGHTELBOWY] = ModelerControl("Spin Right Elbow", 0, 360, 1, 0);
	controls[RIGHTHANDX] = ModelerControl("Right Hand Angle X", 90, -90, 1, 0);
	controls[LEFTARMX] = ModelerControl("Left Arm Angle X", 0, 360, 1, 0);
	controls[LEFTARMY] = ModelerControl("Left Arm Angle Y", 0, 360, 1, 0);
	controls[LEFTARMZ] = ModelerControl("Left Arm Angle Z", 0, 360, 1, 0);
	controls[LEFTELBOWX] = ModelerControl("Left Elbow Angle X", 0, 180, 1, 0);
	controls[LEFTELBOWY] = ModelerControl("Spin Left Elbow", 0, 360, 1, 0);
	controls[LEFTHANDX] = ModelerControl("Left Hand Angle X", 90, -90, 1, 0);
	controls[LEFTLEGX] = ModelerControl("Left Leg Angle X", -60, 60, 1, 0);
	controls[LEFTLEGZ] = ModelerControl("Left Leg Angle Z", -80, 80, 1, 0);
	controls[RIGHTLEGX] = ModelerControl("Right Leg Angle X", -60, 60, 1, 0);
	controls[RIGHTLEGZ] = ModelerControl("Right Leg Angle Z", -80, 80, 1, 0);
	controls[LEFTKNEE] = ModelerControl("Left Knee", 0, 15, 1, 0);
	controls[RIGHTKNEE] = ModelerControl("Right Knee", 0, 15, 1, 0);
	controls[TAILMOVEMENT] = ModelerControl("Tail Movement", 0, 100, 1, 0);
	controls[METABALLSKIN] = ModelerControl("Metaball Skin", 0, 1, 1, 0);
	controls[TEXTURESKIN] = ModelerControl("Texture Skin", 0, 1, 1, 0);
	controls[NINJATURTLE] = ModelerControl("Ninja Turtle", 0, 1, 1, 0);
	controls[EYEBANDANA] = ModelerControl("Eye Bandana", 0, 1, 1, 0);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

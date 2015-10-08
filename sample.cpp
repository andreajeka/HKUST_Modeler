// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <math.h>

#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char *label) : ModelerView(x, y, w, h, label) { }
	virtual void draw();

private:
	void drawHead();
	void drawUpperTorso();
	void drawLowerTorso();
	void drawUpperRightHand();
	void drawLowerRightHand();
	void drawUpperLeftHand();
	void drawLowerLeftHand();
	void drawUpperRightLeg();
	void drawLowerRightLeg();
	void drawUpperLeftLeg();
	void drawLowerLeftLeg();
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
	//glPushMatrix(); // push identity
	//glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS)); // values set by the sliders

	drawHead();
	drawUpperTorso();
	drawLowerTorso();
	drawUpperRightHand();
	drawLowerRightHand();
	drawUpperLeftHand();
	drawLowerLeftHand();
	drawUpperRightLeg();
	drawLowerRightLeg();
	drawUpperLeftLeg();
	drawLowerLeftLeg();

	//glPopMatrix();
}

void SampleModel::drawHead() {
	glPushMatrix();
	glTranslated(0, 2.8, 0);
	drawSphere(1.5);
	glPopMatrix();
}
void SampleModel::drawUpperTorso() {
	glPushMatrix();
	glTranslated(-1.5, -1.5, -2.5 / 2); // box center at (0, 0, 0)
	drawBox(3, 3, 2.6);
	glPopMatrix();
}
void SampleModel::drawLowerTorso() {
	glPushMatrix();
	glTranslated(0, -1.5 - 0.5, 0); // move down by half box's height and half disc height
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, -0.5);
	drawCylinder(1, 1.3, 1.3);
	glPopMatrix();
}
void SampleModel::drawUpperRightHand() {
	glPushMatrix();
	glTranslated(1.5, -1.5 + 0.5, -0.5 / 2);
	drawBox(0.5, 1.5, 0.5);
	glPopMatrix();
}
void SampleModel::drawLowerRightHand() {
	glPushMatrix();
	glTranslated(1.6, -1.5 + 0.5 - 1.5, -0.25 / 2);
	drawBox(0.25, 1.5, 0.25);
	glPopMatrix();
}
void SampleModel::drawUpperLeftHand() {
	glPushMatrix();
	glTranslated(-1.5 - 0.5, -1.5 + 0.5, -0.5 / 2);
	drawBox(0.5, 1.5, 0.5);
	glPopMatrix();
}
void SampleModel::drawLowerLeftHand() {
	glPushMatrix();
	glTranslated(-1.6 - 0.25, -1.5 + 0.5 - 1.5, -0.25 / 2);
	drawBox(0.25, 1.5, 0.25);
	glPopMatrix();
}
void SampleModel::drawUpperRightLeg() {
	glPushMatrix();
	glTranslated(0.2, -4, -1.0 / 2);
	drawBox(1, 1.5, 1);
	glPopMatrix();
}
void SampleModel::drawLowerRightLeg(){
	glPushMatrix();
	glTranslated(0.3, -4 - 2, -0.5 / 2);
	drawBox(0.5, 2, 0.5);
	glPopMatrix();
}
void SampleModel::drawUpperLeftLeg() {
	glPushMatrix();
	glTranslated(-0.2 - 1, -4, -1.0 / 2);
	drawBox(1, 1.5, 1);
	glPopMatrix();
}
void SampleModel::drawLowerLeftLeg() {
	glPushMatrix();
	glTranslated(-0.3 - 0.5, -4 - 2, -0.5 / 2);
	drawBox(0.5, 2, 0.5);
	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

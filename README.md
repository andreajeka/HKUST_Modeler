# Modeler
First of all, you must come up with a character. This character can be composed solely of primitive shapes (box, generalized cylinder, sphere, and triangle).  It should use at least ten primitives and at least four levels of hierarchy. You must also use at least one each of the glTranslate(), glRotate() and glScale() calls to position these primitives in space (and you will probably use many of all of them!) You must also use glPushMatrix() and glPopMatrix() to nest your matrix transformations. The modeler skeleton provides functions for creating sliders and hooking them to different features of your model. You must add at least one of these as a control knob (slider, actually) for some joint/component of your model - have your character do some simple action as you scrub a slider back and forth. In addition, at least one of your controls must be tied to more than one joint/component; this knob will change the input to some function that determines how several parts of your model can move. For example, in a model of a human, you might have a slider that straightens a leg by extending both the knee and hip joints.

In the Camera class, the function called applyViewingTransform() uses gluLookAt() to perform a viewing transform that effectively moves the camera to the specified position and orientation. You are required to implement your own version of gluLookAt() using any method (i.e. the standard transformations (glTranslate, glRotate, glScale), matrix construction) as long as you are not using the gluLookAt itself. Add a function to the Camera class with the following prototype:

void Camera::lookAt(double *eye, double *at, double *up)

where eye, at and up are each 3 element arrays that specify the position of the camera, the point it is looking at and the up vector in world co-ordinates. Using these arguments, your function should apply a series of translations and rotations (or construct a matrix) that effectively moves the camera to the specified position and orientation.

You are required to complete two bells (or equivalent) from the list below. Feel free to come up with your own ideas and pass them by us. If they're cool, we'll count them as bells and whistles.

Other than these requirements, you have complete artistic freedom on this, so be creative!

1. [x] BASIC REQUIREMENTS

#####Bells and Whistles (Extra features for extra points):
One bell is worth two whistles.

1. [ ] ![whistle](http://i.imgur.com/VYSixYv.gif) Change the default light source to illuminate your scene more dramatically.

2. [ ] ![whistle](http://i.imgur.com/VYSixYv.gif) Allow for adjustable levels of detail for your character. You will need to add a UI control for this.

3. [ ] ![whistle](http://i.imgur.com/VYSixYv.gif) Come up with another whistle and implement it.  A whistle is something that extends the use of one of the things you are already doing.  It is part of the basic model construction, but extended or cloned and modified in an interesting way.

4. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif) Use a texture map on all or part of your character. (The safest way to do this is to implement your own primitives inside your model file that do texture mapping.)

5. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif) Build a complex shape as a set of polygonal faces, using the "triangle" primitive to render them.

6. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif) Make an additional "animated" sequence your character can perform.  Although you can try to use a timed callback "add_idle" (see here for more information), an easier solution is just to increment values each time your model's draw() function is called. If you use the menu option to turn on animation, your draw() function will be executed at around 30 times per second.

7. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif) Add some widgets that control adjustable parameters to your model so that you can create individual-looking instances of your character.  Try to make these actually different individuals, not just "the red guy" and "the blue guy."

8. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)Add a "Frame All" feature that would change the position of the camera such that your model is entirely visible in the model window, regardless of the pose and location of your model.

9. [ ] ![bell+whistle](http://i.imgur.com/BxHJUfG.gif)The camera code has a constrained up vector -- modify the code to (1) handle camera twists (the framework is already there) and (2) to come up with an intuitive way for the user to twist the camera via mouse control.

10. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Add a function in your model file for drawing a new type of primitive. The following examples will definitely garner two bells ; if you come up with your own primitive, you will be awarded one or two bells based on its coolness. 1) Extruded surface - given two curves, create a surface by sweeping one curve along the path defined by the other curve. 2) Surfaces of rotation - given a curve and a rotation axis, sweep out a surface by rotating the curve around the axis. 3) Torus.

11. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) (Variable) Use some sort of procedural modeling (such as an L-system) to generate all or part of your character. Have parameters of the procedural modeler controllable by the user via control widgets.

12. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) In addition to mood cycling, have your character react differently to UI controls depending on what mood they are in.  Again, there is some weight in this item because the character reactions are supposed to make sense in a story telling way.  Think about the mood that the character is in, think about the things that you might want the character to do, and then provide a means for expressing and controlling those actions.

13. [x] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) One difficulty with hierarchical modeling using primitives is the difficulty of building "organic" shapes. It's difficult, for instance, to make a convincing looking human arm because you can't really show the bending of the skin and bulging of the muscle using cylinders and spheres. There has, however, been success in building organic shapes using metaballs. Implement your hierarchical model and "skin" it with metaballs. Hint: look up "marching cubes" and "marching tetrahedra" --these are two commonly used algorithms for volume rendering. Here is a demo application by Joe Hall and Eugene Hsu that shows metaballs in action.

14. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)You might notice after building your model that it's difficult to have very "goal-oriented" motion. Given a model of a human, for instance, if the goal is to move the hand to a certain coordinate, we might have to change the shoulder angle, elbow angle -- maybe even the angle of the knees if the feet are constrained to one position. Implement a method, given a set of position constraints like
left foot is at (1,0,2)
right foot is at (3,0,4)
left hand is at (7,8,2)
that computes the intermediate angles necessary such that all constrains are satisfied (or, if the constraints can not be satisfied, the square of the distance violations is minimized). For an additional  ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) 4 bells, make sure that all angle constraints are satisfied as well. In your model, for instance, you might have a slider that constrains the elbow angle between 30 and 180 degrees.  Look here for some related material.

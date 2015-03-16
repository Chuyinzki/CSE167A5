#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <stdint.h>

#include "Window.h"
#include "Matrix4.h"
#include "main.h"

using namespace std;


int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
double colour[3] = { 0.0, 0.0, 0.0 };
int type = 0;

bool Window::bounding = false;
int howManyRobots = 30;
int sidezy = 0;
int inzy = -5;
int upity = 0;
bool a = false;
bool c = false;
int frame = 0, time, timebase = 0;

Vector3 lastPoint;

int movement;
const int ROTATE = 0;
const int ZOOM = 1;


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	displayCallback();         // call display routine to show the cube
}


//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  //cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(sidezy, upity, inzy);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

  switch (type){
  case 0:{
	  Globals::objB.draw();
	  break;
	  }

  case 1:{
	  Globals::objD.draw();
	  break;
  }
  }
 

  glFlush();  
  glutSwapBuffers();
}

void Window::keyboardCallback(unsigned char key, int x, int y) {
	//std::cout << "key " << key << std::endl;

	//Esc key
	if (key == 27) exit(0);

	//p for army key
	if (key == 'p') a = !a;

	//w key
	if (key == 'w') inzy++;

	//s key
	if (key == 's') inzy--;

	//a key
	if (key == 'a') sidezy++;

	//d key
	if (key == 'd') sidezy--;

	//i key
	if (key == 'i') upity--;

	//k key
	if (key == 'k') upity++;

	//y key
	if (key == 'y'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(0, -3, 0);
			Globals::objB.getMatrix() = rotate*temp;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(0, -3, 0);
			Globals::objD.getMatrix() = rotate*temp;
			break;
		}
		}

	}

	//Y key
	if (key == 'Y'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(0, 3, 0);
			Globals::objB.getMatrix() = rotate*temp;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(0, 3, 0);
			Globals::objD.getMatrix() = rotate*temp;
			break;
		}
		}
	}

	//x key
	if (key == 'x'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(-3, 0, 0);
			Globals::objB.getMatrix() = rotate*temp;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(-3, 0, 0);
			Globals::objD.getMatrix() = rotate*temp;
			break;
		}
		}
	}

	//X key
	if (key == 'X'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(3, 0, 0);
			Globals::objB.getMatrix() = rotate*temp;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(3, 0, 0);
			Globals::objD.getMatrix() = rotate*temp;
			break;
		}
		}

	}

	//z key
	if (key == 'z'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(0, 0, 3);
			Globals::objB.getMatrix() = rotate*temp;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(0, 0, 3);
			Globals::objD.getMatrix() = rotate*temp;
			break;
		}
		}

	}

	//Z key
	if (key == 'Z'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(0, 0, -3);
			Globals::objB.getMatrix() = rotate*temp;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeTranslate(0, 0, -3);
			Globals::objD.getMatrix() = rotate*temp;
			break;
		}
		}
	}

	//s key
	if (key == 's'){
		Matrix4 temp, scale;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			scale = Matrix4();
			scale.makeScale(1.1, 1.1, 1.1);
			Globals::objB.getMatrix() = temp*scale;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			scale = Matrix4();
			scale.makeScale(1.1, 1.1, 1.1);
			Globals::objD.getMatrix() = temp*scale;
			break;
		}
		}
	}

	//S key
	if (key == 'S'){
		Matrix4 temp, scale;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			scale = Matrix4();
			scale.makeScale(0.9, 0.9, 0.9);
			Globals::objB.getMatrix() = temp*scale;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			scale = Matrix4();
			scale.makeScale(0.9, 0.9, 0.9);
			Globals::objD.getMatrix() = temp*scale;
			break;
		}
		}
	}

	//o key
	if (key == 'O'){

		Matrix4 temp, orbit;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			orbit = Matrix4();
			orbit.makeRotateZ(-10.0);
			Globals::objB.getMatrix() = orbit*temp;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			orbit = Matrix4();
			orbit.makeRotateZ(-10.0);
			Globals::objD.getMatrix() = orbit*temp;
			break;
		}
		}
	}

	//o key
	if (key == 'o'){
		Matrix4 temp, orbit;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			orbit = Matrix4();
			orbit.makeRotateZ(10.0);
			Globals::objB.getMatrix() = orbit*temp;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			orbit = Matrix4();
			orbit.makeRotateZ(10.0);
			Globals::objD.getMatrix() = orbit*temp;
			break;
		}
		}
	}

	//h key
	if (key == 'h'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeRotateX(10.0);
			Globals::objB.getMatrix() = temp*rotate;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeRotateX(10.0);
			Globals::objD.getMatrix() = temp*rotate;
			break;
		}
		}
	}

	//H key
	if (key == 'H'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeRotateX(-10.0);
			Globals::objB.getMatrix() = temp*rotate;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeRotateX(-10.0);
			Globals::objD.getMatrix() = temp*rotate;
			break;
		}
		}
	}

	//j key
	if (key == 'j'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeRotateY(10.0);
			Globals::objB.getMatrix() = temp*rotate;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeRotateY(10.0);
			Globals::objD.getMatrix() = temp*rotate;
			break;
		}
		}
	}

	//J key
	if (key == 'J'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
			//object Bunny
			temp = Globals::objB.getMatrix();
			rotate = Matrix4();
			rotate.makeRotateY(-10.0);
			Globals::objB.getMatrix() = temp*rotate;
			break;
		}

		case 1:{
			//object Dragon
			temp = Globals::objD.getMatrix();
			rotate = Matrix4();
			rotate.makeRotateY(-10.0);
			Globals::objD.getMatrix() = temp*rotate;
			break;
		}
		}
	}

	Window::reshapeCallback(Window::width, Window::height);

}

void Window::keyboardCallbackSpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:{
		//Bunny
		type = 0;
		break;
	}

	case GLUT_KEY_F2:{
		//Dragon
		type = 1;
		break;
	}
	}
}

//
// Utility routine to calculate the 3D position of a
// projected unit vector onto the xy-plane. Given any
// point on the xy-plane, we can think of it as the projection
// from a sphere down onto the plane. The inverse is what we
// are after.
//

Vector3 Window::trackBallMapping(int x, int y)
{
	Vector3 v;
	float d;
	v.set(((2.0*x - Window::width) / Window::width), ((Window::height - 2.0*y) / Window::height), 0.0);
	d = v.length();
	d = (d<1.0) ? d : 1.0;
	v.set(v.get(0), v.get(1), sqrtf(1.001 - d*d));
	v.normalize(); // Still need to normalize, since we only capped d, not v.
	return v;
}

//
// The OnLButtonDown method of the View class is called whever the
// left mouse button is depressed. We simply save the point and
// set the current interaction state to the trackball. Future
// calls to OnMouseMove will check the current state.
//

//void Window::MouseFunc(int button, int state, int x, int y){
//	// Turn on user interactive rotations.
//	// As the user moves the mouse, the scene will rotate.
//
//	if (button == GLUT_LEFT_BUTTON){
//		movement = ROTATE;
//		// Map the mouse position to a logical sphere location.
//		// Keep it in the class variable lastPoint.
//
//		lastPoint = trackBallMapping(x, y);
//
//		// Make sure we are modifying the MODELVIEW matrix
//
//		glMatrixMode(GL_MODELVIEW);
//	}
//
//	if (button == GLUT_RIGHT_BUTTON){
//		movement = ZOOM;
//		// Map the mouse position to a logical sphere location.
//		// Keep it in the class variable lastPoint.
//
//		lastPoint = trackBallMapping(x, y);
//
//		// Make sure we are modifying the MODELVIEW matrix
//
//		glMatrixMode(GL_MODELVIEW);
//	}
//
//}
//
//void Window::MotionFunc(int xx, int yy)
//{
//	// Handle any necessary mouse movements
//	Vector3 direction;
//	float pixel_diff;
//	float rot_angle, zoom_factor;
//	Vector3 curPoint;
//
//	switch (movement)
//	{
//
//	case ROTATE: // Left-mouse button is being held down
//	{
//		curPoint = trackBallMapping(xx, yy); // Map the mouse position to a logical
//		// sphere location.
//		direction = curPoint - lastPoint;
//		float velocity = direction.length();
//		if (velocity > 0.0001) // If little movement - do nothing.
//		{
//			// Rotate about the axis that is perpendicular to the great circle connecting the mouse movements.
//			Vector3 rotAxis;
//			rotAxis = rotAxis.cross(lastPoint, curPoint);
//			rot_angle = velocity;
//			
//			rotAxis.normalize();
//			Matrix4 rotator;
//			rotator.makeRotate(rot_angle, rotAxis);
//
//			// If we want to see it, we need to force the system to redraw the scene.
//			//Invalidate(TRUE);
//			draw();
//		}
//		break;
//	}
//
//	case ZOOM: // Right-mouse button is being held down
//
//		// Zoom into or away from the scene based upon how far the 
//		// mouse moved in the x-direction.
//		// This implementation does this by scaling the eye-space.
//		// This should be the first operation performed by the GL_PROJECTION matrix.
//		// 1. Calculate the signed distance
//		// a. movement to the left is negative (zoom out).
//		// b. movement to the right is positive (zoom in).
//		// 2. Calculate a scale factor for the scene s = 1 + a*dx
//		// 3. Call glScalef to have the scale be the first transformation.
//		
//		pixel_diff = xx - lastPoint.get(0);
//		zoom_factor = 1.0 + pixel_diff * m_ZOOMSCALE;
//		glScalef(zoom_factor, zoom_factor, zoom_factor);
//		
//		// Set the current point, so the lastPoint will be saved properly below . 
//		curPoint.set((float)xx, (float) yy, 0.0);
//		
//		// If we want to see it, we need to force the system to redraw the scene.
//		//Invalidate(TRUE);
//		draw();
//		break;
//	}
//
//	//
//	// Save the location of the current point for the next movement.
//	//
//	lastPoint = curPoint;
//	CView::OnMouseMove(nFlags, point);
//
//}
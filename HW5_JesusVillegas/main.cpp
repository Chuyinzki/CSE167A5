
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Matrix4.h"
#include "main.h"
#include "Camera.h"
#include "FileObj2.h"

using namespace std;

namespace Globals
{
	Camera camera;
	FileObj2 objB("C:\\Users\\Chuyinzkiz\\Documents\\UCSD 2014\\CSE 167\\HW5_JesusVillegas\\HW5_JesusVillegas\\bunny.obj");
	FileObj2 objD("C:\\Users\\Chuyinzkiz\\Documents\\UCSD 2014\\CSE 167\\HW5_JesusVillegas\\HW5_JesusVillegas\\dragon.obj");
};

int main(int argc, char *argv[])
{
float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 100.0 };
float position[] = { 0.0, 10.0, 1.0, 0.0 };	// lightsource position

glutInit(&argc, argv);      	      	      // initialize GLUT
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
glutInitWindowSize(Window::width, Window::height);      // set initial window size
glutCreateWindow("OpenGL Cube");    	      // open window and set window title

glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
glDisable(GL_CULL_FACE);		// disable backface culling to render both sides of polygons
glShadeModel(GL_SMOOTH);             	      // set shading to smooth
glMatrixMode(GL_PROJECTION);

// Generate material properties:
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glEnable(GL_COLOR_MATERIAL);

// Generate light source:
glLightfv(GL_LIGHT0, GL_POSITION, position);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);

// Install callback functions:
glutDisplayFunc(Window::displayCallback);
glutReshapeFunc(Window::reshapeCallback);
glutIdleFunc(Window::idleCallback);
glutKeyboardFunc(Window::keyboardCallback);
glutSpecialFunc(Window::keyboardCallbackSpecial);
//glutMouseFunc(Window::MouseFunc);
//glutMotionFunc(Window::MotionFunc);


Globals::camera = Camera(Vector3(0, 1, 5), Vector3(0, 0, 0), Vector3(0, 5, 0));

// Initialize cube matrix:

glutMainLoop();
return 0;
}

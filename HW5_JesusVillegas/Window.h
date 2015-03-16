#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Camera.h"

class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	          // window size
	static bool bounding;

	static Vector3 trackBallMapping(int x, int y);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboardCallback(unsigned char key, int x, int y);
	static void keyboardCallbackSpecial(int key, int x, int y);
	static void MouseFunc(int button, int state, int x, int y);
	static void MotionFunc(int x, int y);
};

#endif


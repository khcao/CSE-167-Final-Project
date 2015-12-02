#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Drawable.h"
#include "Vector3.h"
class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyPress(unsigned char, int, int);
	static void fKeyPress(int, int, int);
	//static void centerAndScale(Drawable *);
};

#endif



// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H
#include "RectStash.h"
#include "glut_window.h"

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
    enum MenuEv { evOption0};
    float _markx, _marky;
    int _w, _h;

	RectStash stash;
	bool hit;
	float offsetx, offsety;

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void windowToScene ( float& x, float &y );
	void newrects();

   private : // functions derived from the base class
    virtual void handle ( const Event& e, bool & done );
    virtual void draw ();
    virtual void resize ( int w, int h );
	virtual void idle (bool & done);
	//virtual void scores(int scor);
 };

#endif // APP_WINDOW_H


#include <iostream>
#include "app_window.h"
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static double ballmove = .04;
static int z = 0;
static int score;
static int score2;
time_t initial = time(&initial);
time_t now = time(&now);
char print[4]= {'0'};
void scores()
{
	glColor3f( 1, 1, 1 );
	glRasterPos2f( -.93,.65 );
	itoa(score,print,10);
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24,print[0]);
}
void time()
{	time_t now = time(&now);
	double difference = difftime(now,initial);
	glColor3f( 1, 1, 1 );
	glRasterPos2f( 0,.65 );
	itoa(difference,print,10);
	print[3] = 's';
	for(int i = 0; i < 4;i++)
	{
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24,print[i]);
	}
}
void scores2()
{
	glColor3f( 1, 1, 1 );
	glRasterPos2f( .876,.65 );
	itoa(score2,print,10);
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24,print[0]);
}
void AppWindow::newrects()
{
   _markx = 0;
   _marky = 0;
	stash.add(new Rect(-0.9, 0.02, 0.05, 0.4, 1, 1,1));// topleftcorner(x,y),width, height
	stash.add(new Rect(0.84, 0.02, 0.05, 0.4, 1, 1, 1));
	stash.add(new Rect(0, 0.74, 0.017, 0.025,1, 1, 0));
	stash.rect[2]->directionx = 1;
	stash.rect[2]->directiony = 1;
	stash.add(new Rect(-.0251, .02, 0.05, 0.4, 1, 1, 1));
	stash.rect[3]->directiony = 1;
	stash.add(new Rect(-.13,-.16, 0.27, 0.078, 1, 1, 1));
	stash.rect[4]->directionx = 1;
	score= 0;
	score2= 0;
}
AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   addMenuEntry ( "Reset", evOption0 );
   newrects();
 }

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene ( float& x, float &y )
 {
   x = (2.0f*(x/float(_w))) - 1.0f;
   y = 1.0f - (2.0f*(y/float(_h)));
 }

// Called every time there is a window event
void AppWindow::handle ( const Event& e, bool & done )
 {
   bool rd=true;

   if ( e.type==Keyboard ) 
    switch ( e.key )
    { 
		case ' ': // space bar
		std::cout << "Space pressed.\n";
			_markx = 1.5;
			_marky = 1.5;
			redraw();
			break;
		/*case 'w':
			if((stash.rect[1]->y+=.04) >= 0.58)
			 {
				stash.rect[1]->y = .58;
				std::cout<< stash.rect[1]->y << endl; 
				 rd = true;
				 redraw();
				break;
			 }
			 std::cout<< stash.rect[1]->y << endl; break;*/
		/*case 's':
			if((stash.rect[1]->y-=.04) <= -0.54)
			{
				stash.rect[1]->y = -0.54;
				std::cout<< stash.rect[1]->y << endl; 
				break;
			 }
			std::cout<< stash.rect[1]->y << endl; break;*/
		case 27: // Esc was pressed
			exit(1);
	}

 
   if ( e.type==Menu )
    { std::cout<<"RESET"<<std::endl;
	  if(e.menuev == 0)
	  {
		stash.del();
		newrects();
		done = false;
		initial = time(&initial);
		now = time(&now);
	  }

      rd=false; // no need to redraw
    }


   const float incy=0.09f;
   if ( e.type==SpecialKey )
    switch ( e.key )
    {  
	  case GLUT_KEY_UP:    
		  if((stash.first()->y+=incy) >= 0.58)
		  {
			  stash.first()->y = .58;
			  //std::cout<< stash.first()->y << endl; 
			  break;
		  }
		 // std::cout<< stash.first()->y << endl; break;
		  break;
      case GLUT_KEY_DOWN: 
		  if((stash.first()->y-=incy) <= -0.54)
		  {
			  stash.first()->y = -0.54;
			 // std::cout<< stash.first()->y << endl; 
			  break;
		  }
		// std::cout<< stash.first()->y << endl; break;
		  break;
      default: rd=true; //  redraw
	}
   if (rd) redraw(); // ask the window to be rendered when possible
}

void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }
void AppWindow::idle (bool & done)
{
	 if(score>=9 || score2 >=9)
	 {
		 cout << "done(before): " << done << endl;
		 done = true; 
		 cout << "done(after): " << done << endl;
	 }
	// else
		//done = true;
	if((stash.rect[1]->y - (stash.rect[1]->height/2)) > (stash.rect[2]->y -(stash.rect[1]->height/2) ))
	{	
		if( (stash.rect[1]->y - (stash.rect[1]->height/2) -.04) > (stash.rect[2]->y -(stash.rect[1]->height/2) ) )
		{
			if((stash.rect[1]->y-=.04) < -.54)
				stash.rect[1]->y = -.54;
		}
	}
	else if((stash.rect[1]->y - (stash.rect[1]->height/2)) < (stash.rect[2]->y -(stash.rect[2]->height/2) ))
	{
		if( (stash.rect[1]->y - (stash.rect[1]->height/2) +.04) < (stash.rect[2]->y -(stash.rect[2]->height/2) ))
		{
			if((stash.rect[1]->y+=.04) > .58)
				stash.rect[1]->y = .58;
		}

	}
		if(stash.rect[2]->directionx == 1)
		{	
			for(int i = 0;i <5;i++)
			{
				if (i == 2)
					continue;
				if((stash.rect[2]->x+.04) >= .871)
				{
					stash.rect[2]->x+=.04;
					z=stash.rect[2]->x-.871;
					stash.rect[2]->x = 0.871;
					score++;
					std::cout << "score: " << score << endl;
					draw();
					stash.rect[2]->x +=z;
					stash.rect[2]->directionx= -stash.rect[2]->directionx;
					//std::cout<< stash.rect[2]->x << endl;
					break;
				}
				else if(((((stash.rect[2]->y)+ballmove) >= ((stash.rect[i]->y)-(stash.rect[i]->height)-.04))||(((stash.rect[2]->y)-(stash.rect[2]->height)+ballmove) >= ((stash.rect[i]->y)-(stash.rect[i]->height)-.04))) && ((((stash.rect[2]->y)+ballmove) <= (stash.rect[i]->y)-.04)||(((stash.rect[2]->y)-(stash.rect[2]->height)+ballmove) <=((stash.rect[i]->y)-.04))) && (((stash.rect[2]->x)+ballmove <= (stash.rect[i]->x)+stash.rect[i]->width) || ((stash.rect[2]->x)+(stash.rect[2]->width)+ballmove <= (stash.rect[i]->x)+stash.rect[i]->width))&&((stash.rect[2]->x)+ballmove >= (stash.rect[i]->x)|| ((stash.rect[2]->x)+(stash.rect[2]->width)+ballmove >= stash.rect[i]->x)) &&( (stash.rect[i]->directiony) == -1 || i == 1))
				{
					//stash.rect[2]->x+=.04;
					//z=stash.rect[2]->x-stash.rect[i]->x;
					stash.rect[2]->x = (stash.rect[i]->x)-stash.rect[2]->width;
					draw();
					stash.rect[2]->directionx= -stash.rect[2]->directionx;
					//std::cout<< stash.rect[2]->x << endl;
					break;
				}
				else if(((((stash.rect[2]->y)+ballmove) >= ((stash.rect[i]->y)-(stash.rect[i]->height))+.04)||(((stash.rect[2]->y)-(stash.rect[2]->height)+ballmove) >= ((stash.rect[i]->y)-(stash.rect[i]->height)))) && (((stash.rect[2]->y)+ballmove) <= (stash.rect[i]->y)+.04||(((stash.rect[2]->y)-(stash.rect[2]->height)+ballmove) <=(stash.rect[i]->y))) && (((stash.rect[2]->x)+ballmove <= (stash.rect[i]->x)+stash.rect[i]->width) || ((stash.rect[2]->x)+(stash.rect[2]->width)+ballmove <= (stash.rect[i]->x)+stash.rect[i]->width))&&((stash.rect[2]->x)+ballmove >= (stash.rect[i]->x)|| ((stash.rect[2]->x)+(stash.rect[2]->width)+ballmove >= stash.rect[i]->x)) &&( (stash.rect[i]->directiony) == 1 || i == 1))
				{
					//stash.rect[2]->x+=.04;
					//z=stash.rect[2]->x-stash.rect[i]->x;
					stash.rect[2]->x = (stash.rect[i]->x)-stash.rect[2]->width;
					draw();
					stash.rect[2]->directionx= -stash.rect[2]->directionx;
					//std::cout<< stash.rect[2]->x << endl;
					break;
				}
				else if (i == 4)
					stash.rect[2]->x+=.04;
			}
		}
		else if(stash.rect[2]->directionx == -1 )
		{
			for(int i = 0;i <5;i++)
			{
				if((stash.rect[2]->x-.04) <= -0.93)
				{
					stash.rect[2]->x-=.04;
					z=stash.rect[2]->x-(-.93);
					stash.rect[2]->x = -0.93;
					score2+=1;
					std::cout << "score2: " << score2 << endl;
					draw();
					stash.rect[2]->x -=z;
					stash.rect[2]->directionx= -stash.rect[2]->directionx;
					break;
				}
				else if(((stash.rect[2]->y)-ballmove) >= ((stash.rect[i]->y)-(stash.rect[i]->height) -.04) && ((stash.rect[2]->y)-ballmove) <= (stash.rect[i]->y)-.04 && (stash.rect[2]->x)-ballmove <= (stash.rect[i]->x)+stash.rect[i]->width && (stash.rect[2]->x)-ballmove >= (stash.rect[i]->x) &&((stash.rect[i]->directiony) == -1 || i == 0))
				{
					//stash.rect[2]->x+=.04;
					//z=stash.rect[2]->x-stash.rect[i]->x;
					stash.rect[2]->x = (stash.rect[i]->x)+stash.rect[i]->width;
					draw();
					stash.rect[2]->directionx= -stash.rect[2]->directionx;
					//std::cout<< stash.rect[2]->x << endl;
					break;
				}
				else if(((stash.rect[2]->y)-ballmove) >= ((stash.rect[i]->y)-(stash.rect[i]->height) +.04) && ((stash.rect[2]->y)-ballmove) <= (stash.rect[i]->y)+.04 && (stash.rect[2]->x)-ballmove <= (stash.rect[i]->x)+stash.rect[i]->width && (stash.rect[2]->x)-ballmove >= (stash.rect[i]->x) &&( (stash.rect[i]->directiony) == 1 || i == 0))
				{
					//stash.rect[2]->x+=.04;
					//z=stash.rect[2]->x-stash.rect[i]->x;
					stash.rect[2]->x = (stash.rect[i]->x)+stash.rect[i]->width;
					draw();
					stash.rect[2]->directionx= -stash.rect[2]->directionx;
					//std::cout<< stash.rect[2]->x << endl;
					break;
				}
				else if (i == 4)
					stash.rect[2]->x-=.04;

			}
	}
	 if(stash.rect[2]->directiony == 1)
	{

		/*for(int i = 0;i <5;i++)
		{
			if(i == 2)
				continue;*/
			if((stash.rect[2]->y+=ballmove) >= 0.58)
			{
				//stash.rect[2]->y+=ballmove;
				z=stash.rect[2]->y-.58;
				stash.rect[2]->y = 0.58;
				draw();
				stash.rect[2]->y +=z;
				stash.rect[2]->directiony= -stash.rect[2]->directiony;
			//	break;
			
			}
			/*else if(((stash.rect[2]->y)+ballmove) >= ((stash.rect[i]->y)-(stash.rect[i]->height)) && ((stash.rect[2]->y)+ballmove) <= (stash.rect[i]->y) && (stash.rect[2]->x) <= (stash.rect[i]->x)+stash.rect[i]->width && (stash.rect[2]->x) >= (stash.rect[i]->x) && stash.rect[2]->directionx ==1)
			{
				
				break;
			
			}*/
		//	else if(i == 4)
		//		stash.rect[2]->y+=ballmove;
		//}
	}
	 else if(stash.rect[2]->directiony == -1)
    {
		if((stash.rect[2]->y-=ballmove) <= -0.90)
		{
			z=stash.rect[2]->y-(-.90);
			stash.rect[2]->y = -0.90;
			draw();
			stash.rect[2]->y -=z;
			stash.rect[2]->directiony= -stash.rect[2]->directiony;
		}
		
	}
	if(stash.rect[3]->directiony == 1)
	{
		if((stash.rect[3]->y+=.04) >= 0.58)
		{
			stash.rect[3]->y = 0.58;
			//std::cout<< stash.rect[3]->y << endl; 
			stash.rect[3]->directiony= -stash.rect[3]->directiony;
		}
	}
	else if(stash.rect[3]->directiony == -1)
    {
		if((stash.rect[3]->y-=.04) <= -0.54)
		{
				stash.rect[3]->y = -0.54;
				//std::cout<< stash.rect[3]->y << endl; 
				stash.rect[3]->directiony = -stash.rect[3]->directiony;
		}
	}
	 if(stash.rect[4]->directionx == 1)
	{
		if((stash.rect[4]->x+=.04) >= 0.13)
		{
			stash.rect[4]->x = 0.13;
			//std::cout<< stash.rect[4]->x << endl; 
			stash.rect[4]->directionx= -stash.rect[4]->directionx;
		}
	}
	else if(stash.rect[4]->directionx == -1)
    {
		if((stash.rect[4]->x-=.04) <= -0.4)
		{
				stash.rect[4]->x = -0.4;
				//std::cout<< stash.rect[4]->x << endl; 
				stash.rect[4]->directionx= -stash.rect[4]->directionx;
		}
		
	}
}
// here we will redraw the scene according to the current state of the application.
void AppWindow::draw ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Clear the trasnformation stack
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   /* you may use GL_POLYGON for generic *convex* polygons, like this:
   glBegin( GL_POLYGON );
   glColor3f ( ... );
   glVertex2d ( ... );
   glVertex2d ( ... );
   glVertex2d ( ... );
   glVertex2d ( ... );
   glEnd();*/
	scores();
	scores2();
	time();
   for(std::vector<Rect*>::iterator i = stash.rect.begin(); i != stash.rect.end(); ++i) 
   {	
		glLineWidth(3);
		glBegin( GL_LINES );
		glColor3d(1, 1, 1);
		glVertex2d(-.93,.58);
		glVertex2d((.871 +  0.05),.58);
		glVertex2d((.871 +  0.05),(-.54-0.4));
		glVertex2d(-.93,(-.54-0.4));
		glVertex2d(-.93,.58);
		glVertex2d(-.93,(-.54-0.4));
		glVertex2d((.871 +  0.05),.58);
		glVertex2d((.871 +  0.05),(-.54-0.4));
		glEnd();
		glBegin( GL_POLYGON );
		glColor3f((*i)->r, (*i)->g, (*i)->b);
		glVertex2d((*i)->x, (*i)->y);
		glVertex2d((*i)->x + (*i)->width, (*i)->y);
		glVertex2d((*i)->x + (*i)->width, (*i)->y - (*i)->height);
		glVertex2d((*i)->x, (*i)->y - (*i)->height);
		glEnd();
		/*if((*i)->selected) 
		{
			glLineWidth(3);
			glBegin( GL_LINES );
			glColor3d(0.0, 1.0, 1.0);
			glVertex2d((*i)->x, (*i)->y);
			glVertex2d((*i)->x + (*i)->width, (*i)->y);
			glVertex2d((*i)->x + (*i)->width, (*i)->y);
			glVertex2d((*i)->x + (*i)->width, (*i)->y - (*i)->height);
			glVertex2d((*i)->x + (*i)->width, (*i)->y - (*i)->height);
			glVertex2d((*i)->x, (*i)->y - (*i)->height);
			glVertex2d((*i)->x, (*i)->y - (*i)->height);
			glVertex2d((*i)->x, (*i)->y);
			glEnd();
		}*/
   }
   // Swap buffers
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}


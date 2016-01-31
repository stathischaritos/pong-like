#ifndef BALL_H
#define BALL_H
#define GLFW_DLL
#include <GL/glfw.h>
#include "vector.h"



//This class can be used to simulate the edges of any polygon.
//in the pong clone i use it to create the player and the walls.
class edge  
{
public:
	
		bool isPlayer;

		vector start , end , unit1, unit2,unit3;
		float length;

		/*The Constructor takes the start and end of the edge and calculates
		the length and two unit vectors. "unit1" is the unit vector parallel to the edge
		and unit2 is perpendicular. */
		edge( vector st = vector(0,0,0) , vector en = vector(0.5f,0.5f,0.5f),bool isplayer=0)
		{
			start = st;
			end = en; 
			unit1 = (end-start);
			unit1.normalise();
			unit3 = start.vecprod(unit1).normal();
			if(unit3.z>0)unit2 =unit3.vecprod(unit1);
			else unit2 =unit1.vecprod(unit3);
			unit2.normalise();
			length = (end-start).len();
			isPlayer=isplayer;
		}
		
		void draw()
		{
			//I use a triangle fan to draw an rectangle of width 0.05
			glBegin(GL_LINES);
			glVertex3f(start.x, start.y,0);    
			glVertex3f( end.x , end.y  , 0); 

			//If you want to see where the unit2 vector is:
			//glColor3f(	1,0,0);
			//glLineWidth(4);
			//glVertex3f(start.x, start.y,0); 
			//glVertex3f(start.x+unit2.x/5.0f, start.y+unit2.y/5.0f,0); 
			//glColor3f(	1,1,1);
            
            glEnd();
		}

		//A simple function to move the player.
		void move(vector &speed, float &DT)
		{
			start +=speed*DT;
			end +=speed*DT;
		}
		void MoveStart(vector &n)
		{
			start=n;
			end=start+unit1*length;
		}
		void rotate(float degrees,vector axis)
		{
			unit1.rotate(degrees,axis);
			unit2.rotate(degrees,axis);
			//unit1.normalise();
			//unit2.normalise();
		
			end=start+unit1*length;
		}








};






//This class represents the pong ball.
class pball
{
public:

		vector position;
		vector velocity;
		float radius;
	
		pball(vector pos = vector(0,0,0), vector vel = vector(0,1,0),float R=0.05)
		{
			position = pos;
			velocity = vel;
			radius = R;
		}

		
		void move(float &DT)
		{
			position += velocity*DT;
		}


		/*The bounce function checks for collision with an edge 
		and calculates the speed if a collision occurs.
		The collision calculations could have been made simpler 
		since the ball only collides with edges that are parallel to
		either the X or Y axis. But this way i can later add more 
		functionality to the game ( like angled obstacles or player rotation) without 
		having to change the functions.*/
		void bounce( edge & p )
		{
			vector a = position-p.start;
			vector b = position - p.end;
			vector c;
			
			//if the ball is somewhere above the player
			//then the projection(dot product) of vector "a" on "unit1"
			//will be >0 and less than the length.

			if(a*p.unit1>=0&&a*p.unit1<=p.length)
			{
				//if the distance is less than the radius, and the closing velocity is negative 
				if(fabs(a*p.unit2)<=radius&&velocity*p.unit2<0)
				{
					/*If i wanted true collison i would just reverse the velocity 
					component that is perpendicular to the edge.*/
					velocity-=p.unit2*((velocity*p.unit2)*2);
					/*But in games like Pong and Arcanoid the velocity after 
					the collision with the player depends on where the ball hits.
					This way the player can control the direction of the ball.
					But i also have to check if the ball collides with the player or 
					a wall.*/
					/*if(p.isPlayer)
					{

					 I find a point just below the player , wich i call c from "center" ,
					and the resulting velocity always points outwards of that center point.
					c = (p.start+p.end)*0.5f;
					c -= p.unit2*p.length*0.2f;
					c = (position-c).normal();
					velocity = c*2.0f;
					}
					else velocity-=p.unit2*((velocity*p.unit2)*2);*/
				}
				//else if(a*p.unit2<radius&&velocity*p.unit2<0&&a*p.unit2<0) velocity+=p.unit2*((velocity*p.unit2)*2);

										
			}

			//If the ball colides with either the start or the end:
			else if (a*p.unit2>0&&a.len()<radius && velocity *a.normal()<0)
			{
				velocity-=a.normal()*((velocity*a.normal())*2);
			}
			else if (b*p.unit2>0&&b.len()<radius && velocity * b.normal()<0)
			{
				velocity-=b.normal()*((velocity*b.normal())*2);
			}

		}


		//The Draw function actually makes a regular polygon with 36 sides.
		void draw()
		{
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(position.x, position.y,0.0);
			for (float angle = 0 ; angle<=360; angle +=10 )glVertex3f(position.x + sin(angle*(2*3.14/360)) * radius, position.y + cos(angle*(2*3.14/360)) * radius,0.0);
			glEnd();
		}


};



class block
{
public:

	edge ab , bc , cd , da;
	block(vector a , vector b , vector c , vector d)
	{
		ab = edge(a,b,0);
		bc = edge(b,c,0);
		cd = edge(c,d,0);
		da = edge(d,a,0);
	}

	void move(vector &speed, float &DT)
	{
		ab.move(speed,DT);
		bc.move(speed,DT);
		cd.move(speed,DT);
		da.move(speed,DT);
	}

	void draw()
	{
		ab.draw();
		bc.draw();
		cd.draw();
		da.draw();
	}

	void rotate(float theta, vector axis)
	{
		ab.rotate(theta,axis);
		bc.rotate(theta,axis);
		bc.MoveStart(ab.end);
		cd.rotate(theta,axis);
		cd.MoveStart(bc.end);
		da.rotate(theta,axis);
		da.MoveStart(cd.end);
	}

};





#endif
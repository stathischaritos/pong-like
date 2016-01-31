#include <stdlib.h>
#include "parts.h"
#include "textglut.h"

//Hide the Console Window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")



int main( void )
{
	//Initialise the Ball , the player, and the walls
	pball *ball=new pball;
	ball->velocity=vector(1.4f,1.8f,0);
	edge wall(vector(0.950f, 0.95f, 0),vector(-0.95f, 0.95f, 0),0);
	edge wallleft(vector(-0.95f, 0.95f, 0),vector(-0.95f, -0.95f, 0),0);
	edge wallright(vector(0.95f, -0.95f, 0),vector(0.95f, 0.95f, 0),0);
	block player(vector(0.2f, -0.95f, 0),vector(-0.2f, -0.95f, 0),vector(-0.2f, -0.85f, 0),vector(0.2f, -0.85f, 0));

	//DeltaTime variable and a useful boolean for when you
	//controling the game states.
	bool game = 0;
	float DT;
	

	string s = "PRESS 'D' TO START THE GAME ";
	string d = "CONTROL WITH 'A' AND 'S'";
	
	
	int running = GL_TRUE;
	// Initialize GLFW
	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE ) ;

	// Open an OpenGL window
	if( !glfwOpenWindow( 500,500, 0,0,0,0,0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	glfwSetWindowTitle( "''ping-PONG''" );  


// Main loop
	while( running )
	{

		glClear( GL_COLOR_BUFFER_BIT );
		
		//Calculate the DeltaTime
		//The function is in "vector.h" and it uses the clock() function.
		DeltaTime(DT);
		
		

		//Move the player around with 'A' and 'S'
		if(glfwGetKey('A'))
		{
			player.move(vector(-1,0,0),DT);
		}

		//Rotate using 'X' and 'Z'
		if(glfwGetKey('X'))
		{
			player.rotate(1,vector(0,0,1));
		}
		if(glfwGetKey('Z'))
		{
			player.rotate(-1,vector(0,0,1));
		}

		if(glfwGetKey('S'))
		{
			player.move(vector(1,0,0),DT);
		}

		//if(player.start.x<-1.0f) player.MoveStart(vector(1.4f,-0.95f,0));
		//if(player.start.x>1.4f) player.MoveStart(vector(-1.0f,-0.95f,0));


        //If you havent lost the point yet game = 1 
		if (game)
		{
			
		    
			//delete the ball if it goes behind the payer
			//and set game = 0 to stop.
			if(ball->position.y<-1.0f)
			{
				delete ball;
				game=0;
			}
			//Else continue moving the ball around
			else
			{
				ball->move(DT);
				ball->bounce(wall);
				ball->bounce(wallleft);
				ball->bounce(wallright);
				ball->bounce(player.ab);
				ball->bounce(player.bc);
				ball->bounce(player.cd);
				ball->bounce(player.da);
				ball->draw();
				
			}
		}
		//If the game has stoped and you press 'D'
		//the game restarts with a new ball!
		else 
		{
			text(s,150,300);
			text(d,150,250);
			
			if(glfwGetKey('D'))
		    {
			ball = new pball;
			ball->position=vector(0,0,0);
			ball->velocity=vector(1.4f,1.8f,0);
			game = 1;
			}
		}



		//Draw the Board and the player.
		wall.draw();
		wallleft.draw();
		wallright.draw();
		player.draw();

		// Swap front and back rendering buffers
		glfwSwapBuffers();
		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
		glfwGetWindowParam( GLFW_OPENED );
	}
	
	
	// Close window and terminate GLFW
	glfwTerminate();
	// Exit program
	exit( EXIT_SUCCESS );
}


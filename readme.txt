“pingPONG”


Description:

This is a very simple  ping pong (table tennis) game made using OpenGL and C++.  It is basically a PONG  clone , but not in the classic format, and at the moment there is no opponent , only a wall.




Base Mechanics: 

Move the player (racket) left and right using the buttons ‘A’ and ‘S’.




Gameplay Mechanics:

If the ball passes behind the player , you lose the game.

If the player moves out of the boarders , he reappears on the  other side.

The balls direction changes depending on where on the player it hits.



Features:

OpenGL window using GLFW.

Minimal text screen made with Glut.

Ball-Edge Collision Detection to simulate the player and the Walls that are on the board.





Source Code :

The source code includes the following files:

main.cpp : Where the main() function is.
vector.h : My 3D vector class, plus a Delta Time Calculator using the clock() function.
textglut.h : Render a string using glut.The easiest way to use text with OpenGL.
parts.h : The Edge and Ball classes that i used to make the game.

To compile it needs a proper GLFW set-up,  and GLUT.

Release Build:

The Release Build includes the pingPong.exe , the GLFW.dll so as to not use the static GLFW library, and the glut32.dll.  I have tried it on 2  other computers , one running Windows 7 , and one running Windows XP as mine.
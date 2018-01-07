# marvinGround
testing for sdl with c++

Things to do next if you're interested:

	split up into several files
		-minimize global variables by passing by reference,
		Update makefile

	implement a character object
		-If you want to try this, look at SDL_Rect objects on the wiki (very good page) 
		and how I manipulated the attributes in my mario game. Look at how I checked 
		for inputs for mario there as well. (doesn't need to implement the acceleration 
		equations though, as this would be a top-down game, like zelda. This
		just needs a way to
		check if the key is down or up, and change the characters x and y position by adding or subtracting
		some velocity variable each iteration of the screen loop before the screen refreshes at the end
		of each iteration of the screen loop. And lastly, 
		look at the process in the loadMap() function in our all.cpp file to see
		just how the screen could be refreshed in every single iteration of the screen
		loop. Right now, it only occurs once in the outer game loop (while quit == false)
		 when I load up the map using the loadMap() function.

	implement a second screen
		-as easy as creating a new case in the loadMap() function, and changing the 
		screenNumber as well as the changeScreen boolean value on some defined event
		during the screen loop. This will exit out of the screen loop, and reload a
		different picture.

	implement animation using a spritesheet
		-spritesheet will be added to the resources folder at some point
	

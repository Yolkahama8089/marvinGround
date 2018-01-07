#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//*******************
//LOADTEXTURE.CPP
//*******************

SDL_Texture* loadTexture( std::string path, SDL_Renderer* gameRenderer )
{
  //this will contain an image before being returned
  SDL_Texture* newTexture = NULL;

  //creates a surface from chosen image file
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if (loadedSurface == NULL)
  {
    printf("surface load error %s\n", IMG_GetError() );
  }

  //creates a texture from the surface from the image
  newTexture = SDL_CreateTextureFromSurface( gameRenderer, loadedSurface );
  if (newTexture == NULL)
  {
    printf("texture create from surface error: %s\n", SDL_GetError());
  }

  //deallocates surface
  SDL_FreeSurface (loadedSurface);

  //returns the loaded image as a texture
  return newTexture;
}

//*******************
//LOADMAP.CPP
//*******************
void loadMap(int screenNumber, SDL_Renderer* gameRenderer, SDL_Window* gameWindow, SDL_Texture* backgroundTexture)
{
  //decides what screen to render based on screenNumber
  switch (screenNumber)
  {
    case 0:
      //clear screen

      if (SDL_RenderClear( gameRenderer) < 0 )
      {
        printf("render clear err: %s\n", SDL_GetError() );
      }


      //load background texture
      backgroundTexture = loadTexture( "resources/backgroundGrass.png", gameRenderer );
      if (backgroundTexture == NULL)
      {
         printf(" background Texture load error \n");
      }

      //Render the background texture to the screen
      SDL_RenderCopy( gameRenderer, backgroundTexture, NULL, NULL );

      //Update screen
      SDL_RenderPresent( gameRenderer );

      break;
  }

}

//*******************
//init.cpp
//*******************
bool init(SDL_Window* & gameWindow, SDL_Renderer* & gameRenderer)
{
  //success flag
  bool success = true;

  //initialize sdl
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    printf("sdl init error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    //set texture filtering to linear
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1") )
    {
      printf( "liner filtering not enables!\n" );
    }


  else
  {

    //create window
    gameWindow = SDL_CreateWindow( "marvin", 30, 30, 1280, 960, SDL_WINDOW_SHOWN );
    
    if (gameWindow == NULL)
    {
      printf("window create error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {

      //Create renderer for window
      gameRenderer = SDL_CreateRenderer( gameWindow, -1, SDL_RENDERER_ACCELERATED );
      if (gameRenderer == NULL)
      {
         printf("renderer create error: %s\n", SDL_GetError() );
         success = false;
      }

      else
      {

         //initialize renderer color
         SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

         //Initialize PNG loading
         int imgFlags = IMG_INIT_PNG;

         if ( !( IMG_Init( imgFlags ) & imgFlags ) )
         {
           printf("SDL_image err: %s\n", IMG_GetError() );
           success = false;
         }
      }
    }
  }
  }
  
  return success;
}

//*******************
//checkInput.cpp
//*******************
void checkInput( SDL_Event e, bool* changeScreenPointer, int gameScreen, bool* quitPointer )
{
  //when the event poll contains something (i.e doesn't equal 0)
  while(SDL_PollEvent( &e ) != 0)
  {
     //check if it was the user quitting
     if(e.type == SDL_QUIT)
     {
       //set conditions to break from screen loop and game loop
       *quitPointer = true;
       *changeScreenPointer = true;
     }
  }
}

//*******************
//close.cpp
//*******************
void close(SDL_Window* gameWindow, SDL_Renderer* gameRenderer, SDL_Texture* backgroundTexture)
{
  //free all the global pointers and destroy our sdl objects
  SDL_DestroyWindow( gameWindow );
  gameWindow = NULL;

  SDL_DestroyRenderer( gameRenderer );
  gameRenderer = NULL;

  SDL_DestroyTexture( backgroundTexture );
  backgroundTexture = NULL;
  
}

//*******************
//VARIABLES
//*******************
//variables we'll be using
  //a way to tell our program what screen to render
  int screenNumber = 0;

  //a way to tell our program what character behavior to use
  int saveNumber = 0;

  const int screenWidth = 1280;
  const int screenHeight = 960;

  //our window we will render to
  SDL_Window* gameWindow = NULL;

  //our renderer we will be using
  SDL_Renderer* gameRenderer = NULL;

  //will contain our background texture for any current screen
  SDL_Texture* backgroundTexture = NULL;

  //checks if user is changing screen
  bool changeScreen = false;
  bool* changeScreenPointer = &changeScreen;


//**********************
//ENTRY.CPP
//**********************
int main(int argc, char* args[] )
{
  //initialize sdl, our renderer, and our image loader (and checks for error)
  bool success = init(gameWindow, gameRenderer);
  if (success == false)
  {
    printf("Initialization error");
  }
  printf("Hello 1\n");
  
  //main game loop preperations
    //Event handler
    SDL_Event e;

    //quit flag
    bool quit = false;
    bool* quitPointer = &quit;

  printf("Hello 2\n");

  //main game loop
  while (quit == false)
  {
    //Load background bases on screen
    loadMap( screenNumber, gameRenderer, gameWindow, backgroundTexture );

    printf("Hello 3\n");

    //starts our screen loop
    while (changeScreen == false)
    {
    //   printf("changeScreen = %d\n", changeScreen );
       //checks for input each frame
       checkInput( e, changeScreenPointer, screenNumber, quitPointer );
       //manages fps
       SDL_Delay(1000/60);
  //       printf("Hello 4\n\n");
    }
  }
  

  //frees resources before closing
  close(gameWindow, gameRenderer, backgroundTexture);

  //all good
  return 0;
}

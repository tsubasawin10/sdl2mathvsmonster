/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
enum keyPressUpSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
bool init();
bool loadMedia();
void close();

SDL_Surface* loadSurface(std::string path);
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;
SDL_Surface* gKeyPressSurface = [KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

bool init()
{
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    return success;
}
bool loadMedia()
{
    bool success;

    gHelloWorld = SDL_LoadBMP("preview.bmp");
    if(gHelloWorld == NULL)
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}
void close()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

int main( int argc, char* args[] )
{
    if(!init())
    {
        printf("initialize faile\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("fail to load media!\n");
        }
        else
        {
            bool quit = false;
            SDL_Event e;

            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
                            break;

                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
                            break;

                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
                            break;

                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
                            break;

                            default:
                                gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                SDL_BlitSurface(gCurrentSurface,NULL,gScreenSurface,NULL);

                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    close();
    return 0;
}
SDL_Surface* loadSurface(std::string path){
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL)
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
}


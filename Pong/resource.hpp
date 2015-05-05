#include <iostream>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

using namespace std;

class ResourceManager {
public:
  SDL_Texture* getSurface(const std::string& name) {
    return this->getSurface(name.c_str());
  }
  SDL_Texture* getSurface(const char* name);
  TTF_Font* getFont(const char* name, unsigned int size);


	ResourceManager() {
		cache = new map<string, SDL_Texture*>();
    int imgFlags = IMG_INIT_PNG;
    if ( !( IMG_Init( imgFlags ) & imgFlags ) ) { 
      cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
    }
    fontCache = new map<string, TTF_Font*>();
    //Initialize SDL_ttf
    if( TTF_Init() == -1 ) {
      std::cout << "Unable to init SDL_ttf: " << TTF_GetError() << std::endl;
      exit(1);
    }
  };

	~ResourceManager() {
		cout << "Unloading resources...";
		this->purge();
    TTF_Quit();
    IMG_Quit();
		cout << "Done." << endl;
	}
	
  void purge();
private:
  map<string, SDL_Texture*>* cache;
  map<string, TTF_Font*>* fontCache;
  ResourceManager(ResourceManager const&);              // Don't Implement
  void operator=(ResourceManager const&); // Don't implement
};

#endif

#include <iostream>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

using namespace std;

class ResourceManager {
public:
  SDL_Texture* getSurface(const std::string& name) {
    return this->getSurface(name.c_str());
  }
  SDL_Texture* getSurface(const char* name);



	ResourceManager() {
		cache = new map<string, SDL_Texture*>();
    int imgFlags = IMG_INIT_PNG;
    if ( !( IMG_Init( imgFlags ) & imgFlags ) ) { 
      cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
    }
  };

	~ResourceManager() {
		cout << "Unloading resources...";
		this->purge();
    IMG_Quit();
		cout << "Done." << endl;
	}
	
  void purge();
private:
  map<string, SDL_Texture*> *cache;
  ResourceManager(ResourceManager const&);              // Don't Implement
  void operator=(ResourceManager const&); // Don't implement
};

#endif

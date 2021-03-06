#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "resource.hpp"
#include "game.hpp"
#include "locator.hpp"

SDL_Texture* ResourceManager::getSurface(const char* name) {
  cout << "Trying to load " << name << "..." ;
  string key(name);
  SDL_Texture* surface;
  if(cache->find(key) == cache->end()) {
    cout << "not found! Loading";
    //Convert surface to screen format 
    SDL_Surface* loadedSurface = IMG_Load( name );
    if( NULL == loadedSurface ) { 
      cout <<  "Unable to load image " << name << " SDL Error: " << SDL_GetError() << endl;
      exit(1);
    } 
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x0, 0x0, 0x0 ) );
    surface = SDL_CreateTextureFromSurface(Locator::getRenderEngine()->getRenderer(), loadedSurface );
    if( surface == NULL ) { 
      printf( "Unable to create texture from %s! SDL Error: %s\n", name, IMG_GetError() ); 
      exit(1);
    } //Get rid of old loaded surface SDL_FreeSurface( loadedSurface );
    SDL_FreeSurface( loadedSurface );
    (*cache)[key] = surface;
  } else {
    surface = (*cache)[key];
    cout <<" found in cache " ;
  }
  cout << " " << (*cache)[key] << endl;
  return surface;
}

TTF_Font* ResourceManager::getFont(const char* name, unsigned int size) {
  TTF_Font* font;
  string key = string(name) + string("-");
  if(fontCache->find(key) == fontCache->end()) {
    font = TTF_OpenFont(key.c_str(), size);
    if(font == NULL) {
      cout << "Unable to load font " << key << endl;
      exit(1);
    }
    (*fontCache)[key] = font;
  } else {
    font = (*fontCache)[key];
  }
  return font;
}

void ResourceManager::purge() {
  map<string, SDL_Texture*>::iterator it;
  for(it = cache->begin(); it != cache->end(); ++it) {
    SDL_DestroyTexture(it->second);
  }
  map<string, TTF_Font*>::iterator itf;
  for(itf = fontCache->begin(); itf != fontCache->end(); ++itf) {
    TTF_CloseFont(itf->second);
  }
}

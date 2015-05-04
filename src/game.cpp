#include <iostream>
#include <SDL2/SDL.h>
#include "tinyxml2.h"

#include "game.hpp"
#include "timer.hpp"
#include "locator.hpp"
#include "physic_engine.hpp"
#include "util_functions.h"
#include "BrainEngine.h"

using namespace tinyxml2;


unsigned short Game::width;
unsigned short Game::height;

Game::Game(int width, int height) {
  SDL_Log("width :  %d, height : %d", width, height);
  activeActors = 0;
  Game::width = width;
  Game::height = height;
}

void Game::init() {
  // initialize SDL video
  if(!SDL_Init(SDL_INIT_EVERYTHING)) {
    cout << "Cannot work it out, " << SDL_GetError() << endl;
    exit(1);
  }
  Locator::provide( new ResourceManager() );
  Locator::provide( new RenderEngine( Game::width, Game::height ) );
 	Locator::provide( new PhysicEngine() );
  Locator::provide( new BrainEngine() );
  
  
  // setup bounds
  Locator::getPhysicEngine()->addStaticSegment(0, 0, Game::width, 0, 1., 1.); // sopra
  Locator::getPhysicEngine()->addStaticSegment(0, Game::height, Game::width, Game::height + 30, 1., 1.); // sotto
  Locator::getPhysicEngine()->addStaticSegment(0, 0, 0, Game::height, 1., 1.); // sinistra
  Locator::getPhysicEngine()->addStaticSegment(Game::width, 0, Game::width, Game::height, 1., 1.); // destra
  
  frames = 0;
  XMLDocument doc;
  const char* resourcePath = getResourcePath();
  if (doc.LoadFile(resourcePath) != tinyxml2::XML_SUCCESS ) {
    cout << "No valid resource found" << endl;
    return;
  }
  
  XMLElement* resources, *player;
  resources = doc.FirstChildElement("resources");
  if(!resources) {
    cout << "No valid resource found" << endl;
    return;
  }
  player = resources->FirstChildElement("player");
  
  while(player) {
    if(activeActors >= MAX_ACTORS) {
      cout << "Warning, your MAX_ACTORS should be raised" << endl;
      return;
    }
    actors[activeActors++].init(player);
    player = player->NextSiblingElement("player");
  }
  
  XMLElement *notifyDef = resources->FirstChildElement("notify");
  while (notifyDef) {
    ComponentId from = atoi(notifyDef->Attribute("from"));
    ComponentId to = atoi(notifyDef->Attribute("to"));
      
    GameComponent* fromComp = Actor::compMap[from];
    GameComponent* toComp = Actor::compMap[to];
    
    fromComp->addObserver(toComp);
    
    notifyDef = notifyDef->NextSiblingElement("notify");
  }
  running = true;
}

void Game::destroy() {
  cout << "closing up ... ";
  Locator::destroy();
  //Quit SDL subsystems
  SDL_Quit();
  cout << "done" << endl;
}

Game::~Game() {
  this->destroy();
}

void Game::loop() {
  timer.start();
  
  
  
  
  RenderEngine* renderEngine = Locator::getRenderEngine();
  PhysicEngine* physicEngine = Locator::getPhysicEngine();
  BrainEngine*  brainEngine  = Locator::getBrainEngine();
  
  double delta = 0;
  while( running ) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_APP_TERMINATING: {
          this->destroy();
          running = false;
          break;
        }
        case SDL_APP_LOWMEMORY: {
          Locator::getResourceManager()->purge();
          break;
        }
        case SDL_APP_WILLENTERBACKGROUND: {
          Locator::getResourceManager()->purge();
          break;
        }
        case SDL_APP_DIDENTERBACKGROUND:
          break;
        case SDL_APP_WILLENTERFOREGROUND: {
          init();
          break;
        }
        case SDL_APP_DIDENTERFOREGROUND:
          break;
        case SDL_QUIT:
          running = false;
          break;
          
          // check for keypresses
        case SDL_KEYDOWN: {
          // exit if ESCAPE is pressed
          if (event.key.keysym.sym == SDLK_ESCAPE ||
              event.key.keysym.sym == SDLK_KP_0)
            running = false;
          break;
        }
      } // end switch
    }

    if(!running) {
      return;
    }
    
    double start = timer.getTicks();
    // float avgFPS = renderEngine->getFrames() / ( start / 1000.f );
    brainEngine->update( delta );
    physicEngine->update( delta );
    renderEngine->update( delta );
    
    double end = timer.getTicks();
    delta = end - start;
    
    renderEngine->sync( delta );
  }
}

/*void appEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_APP_TERMINATING: {
          this->destroy();
          running = false;
          break;
        }
        case SDL_APP_LOWMEMORY: {
          Locator::getResourceManager()->purge();
          break;
        }
        case SDL_APP_WILLENTERBACKGROUND: {
          Locator::getResourceManager()->purge();
          break;
        }
        case SDL_APP_DIDENTERBACKGROUND:
          break;
        case SDL_APP_WILLENTERFOREGROUND: {
          init();
          break;
        }
        case SDL_APP_DIDENTERFOREGROUND:
          break;
        case SDL_QUIT:
          running = false;
          break;
          
          // check for keypresses
        case SDL_KEYDOWN: {
          // exit if ESCAPE is pressed
          if (event.key.keysym.sym == SDLK_ESCAPE ||
              event.key.keysym.sym == SDLK_KP_0)
            running = false;
          break;
        }
      } // end switch
    }
}*/
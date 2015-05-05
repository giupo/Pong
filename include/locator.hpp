#ifndef __LOCATOR_HPP__
#define __LOCATOR_HPP__

#include "resource.hpp"
#include <SDL2/SDL.h>
#include "physic_engine.hpp"
#include "RenderEngine.h"
#include "BrainEngine.h"
#include "ThreadPool.hpp"

class EventQueue;
class Game;

class Locator {
public:
  
  static Game* getGame() {
    return game_;
  }
  
  static EventQueue* getEventQueue() {
    return eventQueue_;
  }
  
  static ThreadPool* getThreadPool() {
    return threadPool_;
  }
  
  static BrainEngine* getBrainEngine() {
    return brainEngine_;
  }
  
	static ResourceManager* getResourceManager() {
		return resourceManager_;
	}

  static RenderEngine* getRenderEngine() {
    return renderEngine_;
  }
  
	static PhysicEngine* getPhysicEngine() {
		return physicEngine_;
	}
	
	static void provide(ResourceManager* manager) {
		resourceManager_ = manager;
	}

	static void provide(PhysicEngine* physicEngine) {
		physicEngine_ = physicEngine;
	}
  
  static void provide(RenderEngine* renderEngine) {
    renderEngine_ = renderEngine;
  }
  
  static void provide(BrainEngine* brainEngine) {
    brainEngine_ = brainEngine;
  }

  static void provide(ThreadPool* threadPool) {
    threadPool_ = threadPool;
  }
  
  static void provide(EventQueue* eventQueue) {
    eventQueue_ = eventQueue;
  }
  
  static void provide(Game* game) {
    game_ = game;
  }
	static void destroy() {
    delete renderEngine_;
    delete brainEngine_;
    delete physicEngine_;
    delete threadPool_;
    delete resourceManager_;
	}
	
private:
	
	static ResourceManager* resourceManager_;
	static RenderEngine* renderEngine_;
	static PhysicEngine* physicEngine_;
  static BrainEngine* brainEngine_;
  static ThreadPool* threadPool_;
  static EventQueue* eventQueue_;
  static Game* game_;
};

#endif

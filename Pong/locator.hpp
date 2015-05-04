#ifndef __LOCATOR_HPP__
#define __LOCATOR_HPP__

#include "resource.hpp"
#include <SDL2/SDL.h>
#include "physic_engine.hpp"
#include "RenderEngine.h"
#include "BrainEngine.h"

class Locator {
public:
  
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

	static void destroy() {
		delete resourceManager_;
		delete physicEngine_;
    delete renderEngine_;
	}
	
private:
	
	static ResourceManager* resourceManager_;
	static RenderEngine* renderEngine_;
	static PhysicEngine* physicEngine_;
  static BrainEngine* brainEngine_;
};

#endif

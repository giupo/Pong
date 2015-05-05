#include "locator.hpp"

#include <SDL2/SDL.h>

#include "resource.hpp"
#include "physic_engine.hpp"
#include "RenderEngine.h"
#include "BrainEngine.h"
#include "ThreadPool.hpp"

RenderEngine* Locator::renderEngine_;
ResourceManager* Locator::resourceManager_;
PhysicEngine* Locator::physicEngine_;
BrainEngine* Locator::brainEngine_;
ThreadPool* Locator::threadPool_;
EventQueue* Locator::eventQueue_;
Game* Locator::game_;
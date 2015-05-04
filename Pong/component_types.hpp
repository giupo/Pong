//
//  component_types.h
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#ifndef __Pong__component_types__
#define __Pong__component_types__

typedef enum {
  UNKNOWN_COMPONENT = 0,
  NULL_COMPONENT,
  PHYSIC_COMPONENT,
  RENDER_COMPONENT,
  INPUT_COMPONENT,
  AI_COMPONENT,
  BALL_PHYSIC_COMPONENT
} ComponentTypes;

ComponentTypes hashComponentName(const char* name);

#endif /* defined(__Pong__component_types__) */

//
//  util_functions.m
//  Pong
//
//  Created by Giuseppe Acito on 18/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
#include <string>

static inline CGSize getScreenSize() {
  CGRect screenBounds = [[UIScreen mainScreen] bounds];
  CGFloat screenScale = [[UIScreen mainScreen] scale];
  CGSize screenSize = CGSizeMake(screenBounds.size.width * screenScale,
                                 screenBounds.size.height * screenScale);
  return screenSize;
}

double getScreenWidth() {
  CGSize size = getScreenSize();
  return size.width;
}
double getScreenHeight() {
  CGSize size = getScreenSize();
  return size.height;
}

const char* getResourcePath() {
  NSString *path = [[NSBundle mainBundle] pathForResource:@"resources" ofType:@"xml"];
  NSLog(@"%@", path);
  return [path UTF8String];
}

double denormalizeX(double x) {
  return x * getScreenWidth();
}

double denormalizeY(double y) {
  return y * getScreenHeight();
}
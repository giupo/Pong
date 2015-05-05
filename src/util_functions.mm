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
#include <random>

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
  //NSLog(@"%@", path);
  return [path UTF8String];
}

double denormalizeX(double x) {
  return x * getScreenWidth();
}

double denormalizeY(double y) {
  return y * getScreenHeight();
}

double random(const double lower_bound, const double upper_bound) {
  std::random_device rand_dev;
  std::mt19937       generator(rand_dev());
  std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
  return unif(generator);
}
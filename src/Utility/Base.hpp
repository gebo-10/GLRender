#ifndef _BASE_HPP
#define _BASE_HPP
#pragma once

// #ifdef GLRENDER_CORE_SOURCE		// Build dll
// 	#define GLRENDER_CORE_API GLRENDER_SYMBOL_EXPORT
// #else							// Use dll
// 	#define GLRENDER_CORE_API GLRENDER_SYMBOL_IMPORT
// #endif
#include<stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <kazmath.h>
struct Color
{
	char r;
	char g;
	char b;
	char a;
};
using   namespace   std;

#endif
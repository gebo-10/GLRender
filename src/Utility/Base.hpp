#ifndef _BASE_H
#define _BASE_H
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
#include <GCObject.h>
struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};
enum ObjStatus
{
	OBJ_CREATED,
	OBJ_INITED,
	OBJ_DELETED,
};
typedef kmVec2 vec2;
typedef kmVec3 vec3;
typedef kmVec4 vec4;

typedef kmMat4 mat4;

using   namespace   std;

#endif
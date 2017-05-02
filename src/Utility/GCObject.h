#ifndef _GCOBJECT_H
#define _GCOBJECT_H
#pragma once

class GCObject
{
public:
	GCObject() {};
	virtual ~GCObject() {};
};

typedef std::shared_ptr< GCObject > OBJPtr;
#endif
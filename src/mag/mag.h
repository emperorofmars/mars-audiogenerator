/*
**	Author:		Martin Schwarz
**	Name:		mag.h
**	Project:	mars-audiogenerator
**	Compile:	g++
*/


#ifndef MAG
#define MAG

#include "include.h"

#include "sound.h"
#include "soundGen.h"
#include "wavWriter.h"
#include "pluginManager.h"

#ifndef _DEBUG_LEVEL
	#define _DEBUG_LEVEL 2
#endif // _DEBUG_LEVEL

namespace mag{

class mag{
public:
    mag();
    ~mag();
};

} // mag

#endif // MAG

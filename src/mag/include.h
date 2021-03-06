/*
**	Author:		Martin Schwarz
**	Name:		include.h
**	Project:	mars-audiogenerator
**	Compile:	g++
*/


#ifndef MAG_INCLUDE
#define MAG_INCLUDE

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>
#include <string.h>
#include <cmath>
#include <fstream>

#include <sndfile.h>
#include <portaudio.h>

#include "../plugin-manager/pluginManager.h"

namespace mag{

extern mplug::pluginManager *gPlugManager;

}

#ifndef _DEBUG_LEVEL
	#define _DEBUG_LEVEL 2
#endif // _DEBUG_LEVEL

#endif // MAG_INCLUDE

/*
**	Author:		Martin Schwarz
**	Name:		pluginLoader.cpp
**	Project:	mars-audiogenerator
**	Compile:	g++
*/

#include "pluginLoader.h"

namespace mag{


pluginLoader::pluginLoader(const char *path){
    mPlugin = NULL;
    mCreate = NULL;
    mDestroy = NULL;
    mName = NULL;
    if(path != NULL) load(path);
}

pluginLoader::~pluginLoader(){
    if(mPlugin == NULL){
        #if _DEBUG_LEVEL >= 1
            std::cerr << "plugin not loaded!" << std::endl;
        #endif
        return;
    }

    while(mInstances.size() > 0){
        mDestroy(mInstances[0]);
        mInstances.erase(mInstances.begin());
    }

    dlclose(mPlugin);

    if(mName != NULL) delete [] mName;

    mPlugin = NULL;
    mCreate = NULL;
    mDestroy = NULL;
    mName = NULL;
}

int pluginLoader::load(const char *path){
    if(path == NULL){
        #if _DEBUG_LEVEL >= 1
            std::cerr << "plugin path is NULL!" << std::endl;
        #endif
        return -1;
    }

    if(mPlugin != NULL){
        #if _DEBUG_LEVEL >= 1
            std::cerr << "plugin is already loaded!" << std::endl;
        #endif
        return -1;
    }

    mPlugin = dlopen(path, RTLD_LAZY);
    if(!mPlugin){
        #if _DEBUG_LEVEL >= 1
            std::cerr << "loading plugin: " << path << " failed! " << dlerror() << std::endl;
        #endif
        return -2;
    }
    dlerror();

    mCreate = (create_t *)dlsym(mPlugin, "create");
    if(!mCreate){
        #if _DEBUG_LEVEL >= 1
            std::cerr << "loading createfunction from: " << path << " failed! " << dlerror() << std::endl;
        #endif
        return -2;
    }
    dlerror();

    mDestroy = (destroy_t *)dlsym(mPlugin, "destroy");
    if(!mDestroy){
        #if _DEBUG_LEVEL >= 1
            std::cerr << "loading destroyfunction from: " << path << " failed! " << dlerror() << std::endl;
        #endif
        return -2;
    }
    dlerror();
    return 0;
}

pluginInterface *pluginLoader::create(){
    if(mPlugin == NULL){
        #if _DEBUG_LEVEL >= 1
            std::cerr << "plugin not loaded!" << std::endl;
        #endif
        return NULL;
    }
    pluginInterface *pli = mCreate();
    mInstances.push_back(pli);
    return pli;
}

int pluginLoader::destroy(pluginInterface *instance){
    if(mPlugin == NULL){
        #if _DEBUG_LEVEL >= 1
            std::cerr << "plugin not loaded!" << std::endl;
        #endif
        return -1;
    }
    for(unsigned int i = 0; i < mInstances.size(); i++){
        if(instance == mInstances[i]) mInstances.erase(mInstances.begin() + i);
    }
    mDestroy(instance);
    instance = NULL;
    return 0;
}


} // mag











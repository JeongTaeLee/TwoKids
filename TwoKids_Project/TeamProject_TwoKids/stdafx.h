#pragma once

enum SYSTEM
{
	WINSIZEX = 1280,
	WINSIZEY = 720,
	KEYMAX = 256,
};

#include <iostream>

#include <string>
#include <map>
#include <vector>
#include <list>	
#include <fstream>
#include <algorithm>
#include <io.h>

using namespace std;

#define g_device DXUTGetD3D9Device()
#define ERRMSG(ErrorText, ErrorCaption)  MessageBox(nullptr, ErrorText, ErrorCaption, MB_OK)

#ifdef DEBUG

#define DEBUG_LOGW(s) wcout << s << endl

#else

#define DEBUG_LOGW(s)

#endif

//fmod.hpp
#include "./inc/fmod.hpp"

//lib링크
#pragma comment (lib, "lib/fmodex_vc.lib")

using namespace FMOD;

//버퍼 정의
#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER EXTRACHANNELBUFFER + SOUNDBUFFER

#include "cSceneManager.h"	
#include "cTextureManager.h"
#include "cObjectManager.h"
#include "cInputManager.h"
#include "cCameraManager.h"
#include "cCollisionManager.h"
#include "cMapManager.h"
#include "cSoundManager.h"


#include "cGameObject.h"

#include "cComponent.h"
#include "cSpriteRenderer.h"
#include "cAnimater.h"
#include "cCollider2D.h"
#include "cRigidBody.h"
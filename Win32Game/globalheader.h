#pragma once

#include "framework.h"
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Resource.h"

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <cmath>

enum class LAYER_GROUP {
	DEFAULT,
	MONSTER,

	UI,
	END = 32,
};

enum class SCENE_LAYER {
	MAIN,
	PLAY,

	END,
};

enum class BRUSH_TYPE {
	HOLLOW,

	END,
};

enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,

	END,
};

enum class EVENT_TYPE {
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};

#ifndef IGNORE_RenderSYSTEM
#include "RenderSystem.h"
#endif

#ifndef IGNORE_UTILITY
#include "Utility.h"
#endif
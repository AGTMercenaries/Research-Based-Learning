#pragma once

#include "render/camera.h"
#include "loader/map_manager.h"

struct Game {
	Camera cam;
	int width, height;
	float lastX, lastY;

	MapManager map;

};

extern Game game;
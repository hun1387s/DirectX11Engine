﻿#pragma once

enum class COMPONENT_TYPE
{
	TRANSFORM,
	CAMERA,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	LIGHT2D,
	LIGHT3D,

	MESHRENDER,
	DECAL,
	LANDSCAPE,
	SKYBOX,
	PARTICLESYSTEM,
	TILEMAP,

	END,

	SCRIPT,
};

enum class ASSET_TYPE
{
	PREFAB,
	MESH,
	MESH_DATA,
	MATERIAL,
	TEXTURE,
	SOUND,
	GRAPHICS_SHADER,
	COMPUTE_SHADER,

	END,
};

enum class CB_TYPE // Constant Buffer
{
	TRNSFORM,
	MATERIAL,
	ANIMATION,
	GLOBAL,

	END,
};

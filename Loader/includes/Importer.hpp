#pragma once

#include <glad/gl.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.hpp"
#include "ProcessVAO.hpp"
#include "ProcessBones.hpp"

Model importer(const char* path);
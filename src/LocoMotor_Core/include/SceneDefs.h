#pragma once
#ifndef SCENEDEFS_H
#define SCENEDEFS_H
#include <vector>
#include <string>
#include <unordered_map>
namespace LocoMotor {
	typedef std::vector<std::pair<std::string, std::string>> ComponentMap;
	typedef std::unordered_map<std::string, ComponentMap> ObjectMap;
	typedef std::unordered_map<std::string, ObjectMap> SceneMap;
}
#endif
#pragma once

#include "Includes.hpp"
#include "Physics\Physics.hpp"

std::string ParseForSave();

BOOL              SaveConfig(CONST std::vector<nvec>&);
std::vector<nvec> LoadConfig(CONST std::string&);


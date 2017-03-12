#pragma once

#include "Includes.hpp"
#include "Physics\Physics.hpp"

BOOL              SaveConfig(CONST CHAR[], CONST std::vector<nvec>&);
std::vector<nvec> LoadConfig(CONST std::string&);


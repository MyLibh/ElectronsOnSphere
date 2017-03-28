#pragma once

#include "Includes.hpp"
#include "Physics\Physics.hpp"

BOOL              SaveConfig(CONST CHAR[], crnvector, double);
std::vector<nvec> LoadConfig(CONST std::string&);


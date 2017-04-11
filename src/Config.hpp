#pragma once

#include "Includes.hpp"
#include "Physics\Physics.hpp"

BOOL                   SaveConfig(CONST CHAR[], crnvector, double);
std::auto_ptr<nvector> LoadConfig(CONST std::string&);


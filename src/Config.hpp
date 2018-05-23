#pragma once

#include <memory>

#include "Includes.hpp"
#include "Physics\Physics.hpp"

BOOL                     SaveConfig(CONST CHAR[], crnvector, double);
std::unique_ptr<nvector> LoadConfig(CONST std::string&);


#pragma once

#include "Includes.hpp"
#include "Physics\Physics.hpp"

std::string ParseForSave();

BOOL SaveConfige(CONST std::vector<nvec>&);
BOOL LoadConfig(std::string, std::vector<nvec>&);


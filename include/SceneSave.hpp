#pragma once

#include "Entity.hpp"

class SceneSave
{
private:
    std::string saveLocation;

public:
    SceneSave(std::string &saveLocation);
};
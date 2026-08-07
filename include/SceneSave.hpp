#pragma once

#include "Entity.hpp"
#include "Camera.hpp"
#include <fstream>
#include <filesystem>

class SceneSave
{
private:
    std::string saveLocation;
    std::ofstream file;

public:
    SceneSave(std::string &saveLocation);
    ~SceneSave();

    void addEntity(Entity *entity);
    void addCamera(Camera *camera);

    std::ofstream &getFile();
};
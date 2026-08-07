#include "SceneSave.hpp"

SceneSave::SceneSave(std::string &saveLocation)
    : saveLocation(saveLocation)
{
    std::filesystem::path filePath(saveLocation);

    if (filePath.has_parent_path())
    {
        std::filesystem::create_directories(filePath.parent_path());
    }

    this->file.open(filePath);

    if (this->file.is_open())
    {
        std::cout << "Successfully created scene save file" << std::endl;
    }
    else
    {
        std::cerr << "Failed to create file: " << std::endl;
    }
}

// TODO: abstract away the entities into nodes or actually make the entity class an abstraction so that cameras, 
// characters, textures and so on can be saved like scene.addToSave(AbstractClass/Interface *object)
// that calls the actual addEntity, addCamera etc. method underneath (Liskov's substitution)

void SceneSave::addEntity(Entity *entity)
{
}
void SceneSave::addCamera(Camera *camera)
{
}

std::ofstream &SceneSave::getFile()
{
    return this->file;
}

SceneSave::~SceneSave()
{
    if (this->file.is_open())
    {
        this->file.close();
    }
}
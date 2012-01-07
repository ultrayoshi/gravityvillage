#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.hpp"
#include <vector>

#define SCENE_GAME 0

class SceneManager
{
  public:
    SceneManager();
    ~SceneManager();
    void addScene(int id, Scene *scene);
    Scene* getActive();
    void setActive(int id);
    void update(float dt);
    void render();
  private:
    int active;
    std::vector<Scene*> scenes;
};

#endif

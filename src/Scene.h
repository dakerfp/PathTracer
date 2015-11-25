#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>

#include <vector>
#include <memory>

class Scene
{
private:
	std::vector<std::unique_ptr<Object>> objects;

public:

	Scene()
	{
	}

	void add(std::unique_ptr<Object> o)
	{
		objects.push_back(std::move(o));
	}
};


#endif
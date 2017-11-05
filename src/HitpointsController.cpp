#include "HitpointsController.h"

HitpointsController::HitpointsController(const Transform & position) : transform(position)
{
}

void HitpointsController::dec()
{
	curValue--;
	renders.pop_back();
	transforms.pop_back();
}

void HitpointsController::render(const Camera & camera) const
{
	for (int i = 0; i < renders.size(); i++)
	{
		renders[i]->render(camera);
	}
}

void HitpointsController::init(int value)
{
	transforms.resize(value);
	curValue = value;
	for (int i = 0; i < value; i++)
	{
		transforms[i].setPosition(glm::vec3(transform.getPosition().x + i * 30, transform.getPosition().y, transform.getPosition().z));
		auto * render = new ObjRender(transforms[i]);

		render->loadObj("D:/projects/GraphicsV1/objects/Apple/apple.obj");
		render->loadBmp("D:/projects/GraphicsV1/objects/Apple/Maps/skin.bmp");
		render->setScale(glm::vec3(0.3f, 0.3f, 0.3f));

		renders.emplace_back((IRender*)render);
	}
	for (auto & i : renders)
	{
		auto & z = i;
	}
}

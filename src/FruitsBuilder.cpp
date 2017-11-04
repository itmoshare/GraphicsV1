#include "FruitsBuilder.h"

FruitsBuilder::FruitsBuilder(GameState::GameObjectList &gameObjects, std::vector<std::string> imagePaths) : gameObjects(gameObjects) {
	this->imagePaths = imagePaths;
}

void FruitsBuilder::spawnRandomFruit()
{
	auto x = minX + (rand() % static_cast<int>(maxX - minX + 1));
	auto i = rand() % static_cast<int>(this->imagePaths.size());
	spawnFruit(x, this->imagePaths[i]);
}

void FruitsBuilder::spawnFruit(float xPos, std::string objPath)
{
	//std::unique_ptr<GameObject> dropItem(new GameObject());
	//auto * objRender = new ObjRender(dropItem->getTransformMut());
	///*imgRender->loadImage(imagePath);
	//imgRender->fitImageSize();*/
	//objRender->loadObj(objPath);
	//dropItem->setRender(std::unique_ptr<IRender>(objRender));

	//auto size = objRender->getSize();
	//dropItem->getColliderMut().fitSize(size);

	//dropItem->getTransformMut().setPosition(glm::tvec2<float>(xPos, ySpawn));

	//this->gameObjects.push_back(std::move(dropItem));
}
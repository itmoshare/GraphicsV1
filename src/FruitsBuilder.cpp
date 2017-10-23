#include "FruitsBuilder.h"

FruitsBuilder::FruitsBuilder(GameState::GameObjectList &gameObjects, std::vector<std::string> imagePaths) : gameObjects(gameObjects) {
	this->imagePaths = imagePaths;
}

void FruitsBuilder::spawnRandomFruit()
{
	auto x = minX + (rand() % static_cast<int>(maxX - minX + 1));
	auto i = rand() % static_cast<int>(this->imagePaths.size());
	spawnFruit(x, this->imagePaths[0]);
}

void FruitsBuilder::spawnFruit(float xPos, std::string imagePath)
{
	std::unique_ptr<GameObject> dropItem(new GameObject());
	auto * imgRender = new ImageRender(dropItem->getTransformMut());
	imgRender->loadImage(imagePath);
	imgRender->fitImageSize();
	dropItem->setRender(std::unique_ptr<IRender>(imgRender));

	auto size = imgRender->getSize();
	dropItem->getColliderMut().fitSize(size);

	dropItem->getTransformMut().setPosition(glm::tvec2<float>(xPos, 20));

	this->gameObjects.push_back(std::move(dropItem));
}
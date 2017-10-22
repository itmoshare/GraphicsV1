#include "FruitsController.h"

FruitsController::FruitsController(GameState::GameObjectList &gameObjects, std::vector<std::string> imagePaths) : gameObjects(gameObjects) {
	this->imagePaths = imagePaths;
}

void FruitsController::spawnRandomFruit()
{
	auto x = minX + (rand() % static_cast<int>(maxX - minX + 1));
	auto i = rand() % static_cast<int>(this->imagePaths.size());
	spawnFruit(x, this->imagePaths[0]);
}

void FruitsController::spawnFruit(float xPos, std::string imagePath)
{
	std::unique_ptr<GameObject> dropItem(new GameObject());
	dropItem->getRenderMut().loadImage(imagePath);
	dropItem->getRenderMut().fitImageSize();
	auto size = dropItem->getRender().getSize();
	dropItem->getColliderMut().fitSize(size);

	dropItem->getTransformMut().setPosition(glm::tvec2<float>(xPos, 20));

	this->gameObjects.push_back(std::move(dropItem));
}
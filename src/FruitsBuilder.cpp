#include "FruitsBuilder.h"

FruitsBuilder::FruitsBuilder(GameState::GameObjectList &gameObjects, std::vector<FruitDescription> fruitDescriptions) : gameObjects(gameObjects) {
	this->fruitDescriptions = fruitDescriptions;
}

void FruitsBuilder::spawnRandomFruit()
{
	auto x = minX + (rand() % static_cast<int>(maxX - minX + 1));
	auto i = rand() % static_cast<int>(this->fruitDescriptions.size());
	spawnFruit(x, this->fruitDescriptions[i]);
}

void FruitsBuilder::spawnFruit(float xPos, FruitDescription fruitDescription)
{
	std::unique_ptr<GameObject> dropItem(new GameObject());
	auto * objRender = new ObjRender(dropItem->getTransformMut());
	objRender->loadObj(fruitDescription.modelPath);
	objRender->loadBmp(fruitDescription.texturePath);
	objRender->setScale(fruitDescription.scale);
	dropItem->setRender(std::unique_ptr<IRender>(objRender));

	auto size = objRender->getSize();
	dropItem->getColliderMut().fitSize(size);

	dropItem->getTransformMut().setPosition(glm::tvec2<float>(xPos, ySpawn));

	this->gameObjects.push_back(std::move(dropItem));
}
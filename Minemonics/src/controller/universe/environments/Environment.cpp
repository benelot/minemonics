//# corresponding headers
#include <controller/universe/environments/Environment.hpp>

//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//## view headers
#include <view/universe/environments/EnvironmentGraphics.hpp>

//## utils headers

Environment::Environment() :
	mEnvironmentType(UNKNOWN_ENVIRONMENT_TYPE), mEnvironmentGraphics(NULL), mEnvironmentModel(
		NULL) {
}

Environment::~Environment() {

	delete mEnvironmentGraphics;
	mEnvironmentGraphics = NULL;

	delete mEnvironmentModel;
	mEnvironmentModel = NULL;
}

void Environment::initialize(const EnvironmentType environmentType) {
	mEnvironmentType = environmentType;
}

bool Environment::isInWorld() const {
	return (mEnvironmentGraphics->isInWorld() == mEnvironmentModel->isInWorld());
}

void Environment::addToPhysicsWorld() {
	if (!mEnvironmentModel->isInWorld()) {
		mEnvironmentModel->addToWorld();
	}
}

void Environment::addToWorld() {
	if (!mEnvironmentModel->isInWorld()) {
		mEnvironmentModel->addToWorld();
	}

	if (!mEnvironmentGraphics->isInWorld()) {
		mEnvironmentGraphics->addToWorld();
	}
}

void Environment::removeFromWorld() {
	if (mEnvironmentModel->isInWorld()) {
		mEnvironmentModel->removeFromWorld();
	}

	if (mEnvironmentGraphics->isInWorld()) {
		mEnvironmentGraphics->removeFromWorld();
	}
}

void Environment::update(double timeSinceLastTick) {
	//TODO: Make terrain paging with bullet physics
//	std::vector<Ogre::Terrain*> terrains = getEnvironmentO3D()->getAllDefinedTerrains();
//	Ogre::TerrainIterator tit = getEnvironmentO3D()->getTerrainGroup()->getTerrainIterator();
////	Ogre::TerrainGroup * pGroup =
////			((Ogre::TerrainPagedWorldSection *) getEnvironmentO3D()->getTerrainPagedWorldSection())->getTerrainGroup();
////	long x, y;
////	pGroup->unpackIndex(page->getID(), &x, &y);
//	Ogre::Terrain * pTerrain = pGroup->getTerrain(x, y);
//	float * data = pTerrain->getHeightData();
//	Ogre::Vector3 tpos = pTerrain->getPosition();
//	btVector3 pos(tpos.x, tpos.y, tpos.z);
//
//	float * pDataConvert = new float[pTerrain->getSize() * pTerrain->getSize()];
//	for (int i = 0; i < pTerrain->getSize(); i++)
//		memcpy(pDataConvert + pTerrain->getSize() * i,
//				data + pTerrain->getSize() * (pTerrain->getSize() - i - 1),
//				sizeof(float) * (pTerrain->getSize()));
//
//	mEnvironmentModel->putTerrainData(pTerrain->getSize(), pTerrain->getSize(),
//			pDataConvert, pTerrain->getMinHeight(), pTerrain->getMaxHeight(),
//			pos, pTerrain->getWorldSize() / (pTerrain->getSize() - 1));
//
//	delete[] pDataConvert;
}


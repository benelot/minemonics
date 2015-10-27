//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/FSPhenomeModel.hpp>

#include <list>
#include <map>

//## controller headers
//## model headers
#include <BulletDynamics/Featherstone/btMultiBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h>
#include <BulletDynamics/Featherstone/btMultiBodyJointLimitConstraint.h>
#include <BulletDynamics/Featherstone/btMultiBodyLink.h>
#include <LinearMath/btAlignedObjectArray.h>
#include <LinearMath/btQuadWord.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/FSEmbryogenesis.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/PhenotypeGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/FSServoMotor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger FSPhenomeModel::mBoostLogger; /*<! initialize the boost logger*/
FSPhenomeModel::_Init FSPhenomeModel::_initializer;
FSPhenomeModel::FSPhenomeModel() :
	mMultiBody(NULL), mWorld(NULL) {
}

FSPhenomeModel::FSPhenomeModel(CreatureModel* const creatureModel) :
	PhenomeModel(creatureModel), mMultiBody(NULL), mWorld(NULL) {

	//set the dynamics world for the phenome model
#ifndef EXCLUDE_FROM_TEST
	mWorld =
		(btMultiBodyDynamicsWorld*) mCreatureModel->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld();
#endif
	mControllers.clear();
}

FSPhenomeModel::FSPhenomeModel(const FSPhenomeModel& phenomeModel) {
	mInWorld = phenomeModel.mInWorld;
	mCreatureModel = phenomeModel.mCreatureModel;
	mDeveloped = phenomeModel.mDeveloped;
	mHasInterpenetrations = phenomeModel.mHasInterpenetrations;
	mMultiBody = phenomeModel.mMultiBody;
	mWorld = phenomeModel.mWorld;
	for (std::vector<Controller*>::const_iterator cit =
		phenomeModel.mControllers.begin();
		cit != phenomeModel.mControllers.end(); cit++) {
		mControllers.push_back((*cit)->clone());
	}

	for (std::vector<ComponentModel*>::const_iterator coit =
		phenomeModel.mComponentModels.begin();
		coit != phenomeModel.mComponentModels.end(); coit++) {
		ComponentModel* componentModel = (*coit)->clone();
		mComponentModels.push_back(componentModel);
		switch (componentModel->getComponentType()) {
		case ComponentModel::LimbComponent:
			mLimbModels.push_back((LimbModel*) componentModel);
			break;
		case ComponentModel::JointComponent:
			mJointModels.push_back((JointModel*) componentModel);
			break;

		}
	}
}

FSPhenomeModel::~FSPhenomeModel() {
	delete mMultiBody;
	mMultiBody = NULL;

	mWorld = NULL;

	while (!mLimitConstraints.empty()) {
		delete mLimitConstraints.back();
		mLimitConstraints.pop_back();
	}
}

void FSPhenomeModel::initialize() {

	performEmbryogenesis(); /**!< Perform embryogenesis to build a body plan*/

	//initialize the limb models if it did not already happen in embryogenesis
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		((FSLimbModel*) (*lit))->setWorld(getWorld());
		(*lit)->initialize();
	}

	//initialize the joint models if it did not already happen in embryogenesis
	for (std::vector<JointModel*>::iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		(*jit)->initialize();
	}

	generateBody(); /**!< Build the body from the body plan */

	addJointConstraints(); /**!< Add the joint constraints */

}

void FSPhenomeModel::update(const double timeSinceLastTick) {
	//update all controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		(*cit)->perform(timeSinceLastTick);
	}

	// Update all limb models
	mHasInterpenetrations = false;
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {

		//detect interpenetrations
		if ((*lit)->getInterpenetrationDepth() < 0 && !mHasInterpenetrations) {
			mHasInterpenetrations = true;
			break;
		}
		(*lit)->setInterpenetrationDepth(0);
	}

}

void FSPhenomeModel::addToWorld() {
	if (!isInWorld()) {
		if (mMultiBody != NULL) {
			getWorld()->addMultiBody(mMultiBody);
		}
	}
	PhenomeModel::addToWorld();
}

void FSPhenomeModel::removeFromWorld() {
	if (isInWorld()) {
		if (mMultiBody != NULL) {
			getWorld()->removeMultiBody(mMultiBody);
		}
	}
	PhenomeModel::removeFromWorld();
}

void FSPhenomeModel::calm() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->calm();
	}
}

int FSPhenomeModel::performEmbryogenesis() {
	int totalSegmentCounter = 0;
	if (!mDeveloped) {
		cleanup();
		mBodyGenerated = false;
		std::list<PhenotypeGenerator*> generatorList;

		// get the first gene from the genome
		Gene* gene =
			mCreatureModel->getGenotype().getGenes()[mCreatureModel->getGenotype().getRootIndex()];

		//create a phenotype generator and initialize it with the starting point of the creation of the creature
		PhenotypeGenerator* rootGenerator = new PhenotypeGenerator();
		std::map<int, int> repList;
		rootGenerator->initialize(repList, mCreatureModel->getInitialPosition(),
			Ogre::Quaternion().IDENTITY, NULL, NULL, 1);
		rootGenerator->setGene(gene);
		rootGenerator->setRoot2LeafPath(0);
		generatorList.push_back(rootGenerator);

		while (!generatorList.empty()) { // this loop creates the creature up to the point at which we reach the correct root-to-leaf path length

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Phenome generator qty:" << generatorList.size();

			PhenotypeGenerator* generator = generatorList.front();
			generatorList.pop_front();

			FSEmbryogenesis::transcribeGene(generatorList, totalSegmentCounter,
				this, generator);

			delete generator; // delete the generator of this gene
		}

		mDeveloped = true;
	} else {
		mComponentModels.clear();
		for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
			it != mLimbModels.end(); it++) {
			mComponentModels.push_back((*it));
		}

		for (std::vector<JointModel*>::const_iterator it = mJointModels.begin();
			it != mJointModels.end(); it++) {
			mComponentModels.push_back((*it));
		}
	}
	return totalSegmentCounter;
}

void FSPhenomeModel::generateBody() {
	bool isFixedBase = false;
	bool isMultiDof = true;
	bool setDamping = true;
	bool gyro = true;
	bool canSleep = true;

	if (mBodyGenerated) {
		return;
	}

	if (mJointModels.size() != 0) {
		bool selfCollision = true; /**!< The collision is handled on a per-limb basis*/

		int linkQty = 0;
		for (int i = 0; i < mJointModels.size(); i++) {
			switch (mJointModels[i]->getType()) {
			case JointPhysics::HINGE_JOINT:
				linkQty++;
				break;
			case JointPhysics::SPHERICAL_JOINT:
				linkQty += 3;
				break;
			}
		}
		mMultiBody = new btMultiBody(linkQty,
			btScalar(mLimbModels[0]->getMass()), mLimbModels[0]->getInertia(),
			isFixedBase, canSleep, isMultiDof);

		mMultiBody->setBasePos(
			OgreBulletUtils::convert(mLimbModels[0]->getPosition()));
		mMultiBody->setWorldToBaseRot(
			OgreBulletUtils::convert(mLimbModels[0]->getOrientation()));

		btScalar linkLength = MorphologyConfiguration::LINK_LENGTH;

		linkQty = 0;
		for (int i = 0; i < mJointModels.size(); i++) {
			switch (mJointModels[i]->getType()) {
			case JointPhysics::HINGE_JOINT:
				mMultiBody->setupRevolute(
					((long) mJointModels[i]->getChildIndex()) - 1,
					btScalar(mLimbModels[i + 1]->getMass()),
					mLimbModels[i + 1]->getInertia(),
					((long) mJointModels[i]->getParentIndex()) - 1,
					mJointModels[i]->getParentComToPivot().getRotation().normalized()
						* mJointModels[i]->getPivotToChildCom().getRotation().normalized(),
					mJointModels[i]->getJointPitchAxis().normalized(),
					mJointModels[i]->getParentComToPivot().getOrigin()
						* linkLength,
					-mJointModels[i]->getPivotToChildCom().getOrigin()
						* linkLength, true);
				break;
			case JointPhysics::SPHERICAL_JOINT:
				mMultiBody->setupSpherical(
					((long) mJointModels[i]->getChildIndex()) - 1,
					btScalar(mLimbModels[i + 1]->getMass()),
					mLimbModels[i + 1]->getInertia(),
					((long) mJointModels[i]->getParentIndex()) - 1,
					mJointModels[i]->getParentComToPivot().getRotation().normalized()
						* mJointModels[i]->getPivotToChildCom().getRotation().normalized(),
					mJointModels[i]->getParentComToPivot().getOrigin()
						* linkLength,
					-mJointModels[i]->getPivotToChildCom().getOrigin()
						* linkLength, true);
				break;
			default:
				break;
			}

			for (std::vector<Motor*>::iterator mit =
				mJointModels[i]->getMotors().begin();
				mit != mJointModels[i]->getMotors().end(); mit++) {
				((FSServoMotor*) (*mit))->instantiate(mMultiBody,
					mJointModels[i]->getIndex());
			}
		}

		mMultiBody->finalizeMultiDof();

		mMultiBody->setCanSleep(canSleep);
		mMultiBody->setHasSelfCollision(selfCollision);
		mMultiBody->setUseGyroTerm(gyro);

		if (!setDamping) {
			mMultiBody->setLinearDamping(0.f);
			mMultiBody->setAngularDamping(0.f);
		} else {
			mMultiBody->setLinearDamping(0.1f);
			mMultiBody->setAngularDamping(0.9f);
		}

		btAlignedObjectArray<btQuaternion> worldtoLocal;
		worldtoLocal.resize(mMultiBody->getNumLinks() + 1);

		btAlignedObjectArray<btVector3> localOrigin;
		localOrigin.resize(mMultiBody->getNumLinks() + 1);

		worldtoLocal[0] = mMultiBody->getWorldToBaseRot();
		localOrigin[0] = mMultiBody->getBasePos();
		for (int i = 0; i < mMultiBody->getNumLinks(); ++i) {
			const int parent = mMultiBody->getParent(i);
			worldtoLocal[i + 1] = mMultiBody->getParentToLocalRot(i)
				* worldtoLocal[parent + 1];
			localOrigin[i + 1] = localOrigin[parent + 1]
				+ (quatRotate(worldtoLocal[i + 1].inverse(),
					mMultiBody->getRVector(i)));
		}

		{
			btVector3 origin = localOrigin[0];

			btQuaternion orientation(-worldtoLocal[0].x(), -worldtoLocal[0].y(),
				-worldtoLocal[0].z(), worldtoLocal[0].w());

			((FSLimbBt*) mLimbModels[0]->getLimbPhysics())->generateLink(
				mMultiBody, mLimbModels[0], origin, orientation, -1);
			mMultiBody->setBaseCollider(
				((FSLimbBt*) mLimbModels[0]->getLimbPhysics())->getLink());
		}

		for (int i = 0; i < mMultiBody->getNumLinks(); ++i) {

			btVector3 origin = localOrigin[i + 1];

			btQuaternion orientation(-worldtoLocal[i + 1].x(),
				-worldtoLocal[i + 1].y(), -worldtoLocal[i + 1].z(),
				worldtoLocal[i + 1].w());
			((FSLimbBt*) mLimbModels[i + 1]->getLimbPhysics())->generateLink(
				mMultiBody, mLimbModels[i + 1], origin, orientation, i);

			mMultiBody->getLink(i).m_collider =
				((FSLimbBt*) mLimbModels[i + 1]->getLimbPhysics())->getLink();
		}
	}
	mBodyGenerated = true;
}

void FSPhenomeModel::addJointConstraints() {
	for(std::vector<btMultiBodyConstraint*>::iterator lit = mLimitConstraints.begin(); lit != mLimitConstraints.end();){
		delete *lit;
		lit = mLimitConstraints.erase(lit);
	}

	for (int i = 0; i < mJointModels.size(); i++) {
		//TODO: Limit joints that way, the joint limit constraint does not yet support the limiting of the spherical joint
		// Link joint limits
		btMultiBodyConstraint* limitCons = new btMultiBodyJointLimitConstraint(
			mMultiBody, i,
			btScalar(
				mJointModels[i]->getLowerLimits()[JointPhysics::RDOF_PITCH]),
			btScalar(
				mJointModels[i]->getUpperLimits()[JointPhysics::RDOF_PITCH]));
		// The default value (100) behaves like a lock on -1.6
//		limitCons->setMaxAppliedImpulse(40);
		mLimitConstraints.push_back(limitCons);
	}

}

void FSPhenomeModel::reset(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	//TODO: Reset position of the FSCreature
	//mMultiBody->setBasePos(OgreBulletUtils::convert(position));
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reset(position);
	}
}

void FSPhenomeModel::cleanup() {
	for (std::vector<ComponentModel*>::iterator cit = mComponentModels.begin();
		cit != mComponentModels.end();) {
		delete *cit;
		cit = mComponentModels.erase(cit);
	}
	mLimbModels.clear();
	mJointModels.clear();
	delete mMultiBody;
	mMultiBody = NULL;
}

void FSPhenomeModel::reposition(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reposition(position);

	}
}

bool FSPhenomeModel::equals(const FSPhenomeModel& phenomeModel) const {
	if (mInWorld != phenomeModel.mInWorld) {
		return false;
	}

	if (mDeveloped != phenomeModel.mDeveloped) {
		return false;
	}

	/**The vector of limb models.*/
	if (mLimbModels.size() != phenomeModel.mLimbModels.size()) {
		return false;
	}
	std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
	std::vector<LimbModel*>::const_iterator it2 =
		phenomeModel.mLimbModels.begin();
	for (; it != mLimbModels.end(), it2 != phenomeModel.mLimbModels.end();
		it++, it2++) {
		if (!(*it)->equals(**(it2))) {
			return false;
		}
	}

	/**The vector of joint models.*/
	if (mJointModels.size() != phenomeModel.mJointModels.size()) {
		return false;
	}
	std::vector<JointModel*>::const_iterator it3 = mJointModels.begin();
	std::vector<JointModel*>::const_iterator it4 =
		phenomeModel.mJointModels.begin();
	for (; it3 != mJointModels.end(), it4 != phenomeModel.mJointModels.end();
		it3++, it4++) {
		if (!(*it3)->equals(**(it4))) {
			return false;
		}
	}

	/**The vector of controllers.*/
	if (mControllers.size() != phenomeModel.mControllers.size()) {
		return false;
	}
	std::vector<Controller*>::const_iterator it5 = mControllers.begin();
	std::vector<Controller*>::const_iterator it6 =
		phenomeModel.mControllers.begin();
	for (; it5 != mControllers.end(), it6 != phenomeModel.mControllers.end();
		it5++, it6++) {
		if (!(*it5)->equals(**(it6))) {
			return false;
		}
	}
	return true;
}

PhenomeModel* FSPhenomeModel::clone() {
	return new FSPhenomeModel(*this);
}

btMultiBodyDynamicsWorld* FSPhenomeModel::getWorld() {
	if (!mWorld) {
#ifndef EXCLUDE_FROM_TEST
		mWorld =
			(btMultiBodyDynamicsWorld*) mCreatureModel->getWorld();
#endif
	}
	return mWorld;
}

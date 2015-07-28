//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>

//# forward declarations
//# system headers
#include <list>
#include <map>

//## controller headers
//## model headers
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

//## view headers
#include <OgreColourValue.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

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
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/PhenotypeGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/Euler.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger PhenomeModel::mBoostLogger; /*<! initialize the boost logger*/
PhenomeModel::_Init PhenomeModel::_initializer;
PhenomeModel::PhenomeModel() :
		mCreatureModel(NULL), mInWorld(false), mDeveloped(false) {
	mControllers.clear();
}

PhenomeModel::PhenomeModel(const PhenomeModel& phenomeModel) {
	mInWorld = phenomeModel.mInWorld;
	mCreatureModel = phenomeModel.mCreatureModel;
	mDeveloped = phenomeModel.mDeveloped;

	std::vector<Controller*>::const_iterator cit =
			phenomeModel.mControllers.begin();
	for (; cit != phenomeModel.mControllers.end(); cit++) {
		mControllers.push_back((*cit)->clone());
	}

	std::vector<ComponentModel*>::const_iterator coit =
			phenomeModel.mComponentModels.begin();
	for (; coit != phenomeModel.mComponentModels.end(); coit++) {
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

PhenomeModel::~PhenomeModel() {
	mControllers.clear();
}

void PhenomeModel::initialize(CreatureModel* const creatureModel) {
	mCreatureModel = creatureModel;
}

void PhenomeModel::update(const double timeSinceLastTick) {
	//update all controllers
	//TODO: Hacks to make it run, make nicer
	// let the controller perform
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
			cit != mControllers.end(); cit++) {
		(*cit)->perform(timeSinceLastTick);
		(*cit)->getOutputValue();
	}

//
//		std::vector<JointModel*>::iterator jit = mJointModels.begin();
//		for (; jit != mJointModels.end(); jit++) {
//			(*jit)->
//		}

//	// test for strains
//	std::vector<JointModel*>::iterator jit = mJointModels.begin();
//	for (; jit != mJointModels.end(); jit++) {
//		(*jit)->isStrained();
//	}

}

void PhenomeModel::performEmbryogenesis(CreatureModel* const creatureModel) {
	if (!mDeveloped) {
		cleanup();
		std::list<PhenotypeGenerator*> generatorList;
		int totalSegmentCounter = 0;

		// get the first gene from the genome
		Gene* gene = creatureModel->getGenotype().getGenes().front();

		//create a phenotype generator and initialize it with the starting point of the creation of the creature
		PhenotypeGenerator* rootGenerator = new PhenotypeGenerator();
		std::map<int, int> repList;
		rootGenerator->initialize(repList, creatureModel->getInitialPosition(),
				Ogre::Quaternion().IDENTITY, NULL, NULL, 1);
		rootGenerator->setGene(gene);
		rootGenerator->setRoot2LeafPath(0);
		generatorList.push_back(rootGenerator);

		// this loop creates the creature up to the point at which we reach the correct root-to-leaf path length
		while (!generatorList.empty()) {

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Phenome generator qty:" << generatorList.size();

			PhenotypeGenerator* generator = generatorList.front();
			generatorList.pop_front();

			//		Embryogenesis::transcribeGene(generator);

			// what is the next gene type
			switch (generator->getGene()->getType()) {
				case Gene::MorphoGene: {

					// if the current root to leaf path is equal to the maximal segments depth, break
					if (generator->getRoot2LeafPath()
							== creatureModel->getGenotype().getSegmentsDepthLimit()) {
						break;
					}

					//if the total segment counter reached the total segment quantity, break
					if (totalSegmentCounter
							== creatureModel->getGenotype().getTotalSegmentQtyLimit()) {
						break;
					}

					totalSegmentCounter++;

					// get the morphogene and start creating the limb and its joint to its parent
					Morphogene* morphogene = ((Morphogene*) generator->getGene());

					// joint position in reference frame A
					Ogre::Vector3 localJointOA(0, 0, 0);

					// joint position in reference frame B
					Ogre::Vector3 localJointOB(0, 0, 0);

					// if there exists a parent component, then we calculate the position of the new limb according to the parent component
					if (generator->getParentComponentModel() != NULL) {

						// get parent limb A
						LimbPhysics* limbA =
						((LimbModel*) generator->getParentComponentModel())->getLimbPhysics();

						//get the limb A'a center of mass
						Ogre::Vector3 limbACOM =
						((LimbModel*) generator->getParentComponentModel())->getPosition();

						//get anchor direction of limb A in reference frame of A
						Ogre::Vector3 localAnchorDirOA;

						if (generator->isMirrored()) {
							localAnchorDirOA =
							(-((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(), -((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(), -((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());
						} else if (generator->isFlipped()) {
							localAnchorDirOA =
							(((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());
							//	get direction vector of object
							Ogre::Vector3 n(1, 0, 0);
							n =
							((LimbModel*) generator->getParentComponentModel())->getOrientation()
							* n;

							//reflect on the direction vector
							localAnchorDirOA = -localAnchorDirOA
							- 2 * ((-localAnchorDirOA).dotProduct(n)) * n;
						} else {
							localAnchorDirOA =
							(((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());
						}

						//get surface point of limb A in reference frame of A
						Ogre::Vector3 localAnchorOA(limbA->getLocalIntersection(
										/*origin of limb A*/
										OgreBulletUtils::convert(limbACOM),
										/*direction of anchor of limb A*/
										OgreBulletUtils::convert(localAnchorDirOA)));

						// joint direction of joint part of A
						Ogre::Euler eulerA(
								((MorphogeneBranch*) generator->getGeneBranch())->getJointYaw(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointPitch(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointRoll());

						//get local joint rotation point in reference frame A
						localJointOA = localAnchorOA
						+ eulerA * localAnchorDirOA.normalisedCopy()
						* MorphologyConfiguration::JOINT_LENGTH;

						//get anchor direction of limb B
						Ogre::Vector3 localAnchorDirOB(
								morphogene->getJointAnchorX(),
								morphogene->getJointAnchorY(),
								morphogene->getJointAnchorZ());

						// get local joint rotation point in the local reference frame of B
						Ogre::Euler eulerB(morphogene->getJointYaw(),
								morphogene->getJointPitch(),
								morphogene->getJointRoll());

						//get local surface anchor point of B in reference frame A
						Ogre::Vector3 localAnchorOBinA(
								localJointOA
								- eulerB * localAnchorDirOB.normalisedCopy()
								* MorphologyConfiguration::JOINT_LENGTH);

						// find the joint anchor position of the limb by positioning the limb at an arbitrary position to cast a ray
						LimbBt* limbBBt = new LimbBt();

						limbBBt->initialize(mCreatureModel->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
								NULL, morphogene->getPrimitiveType(),
								OgreBulletUtils::convert(generator->getPosition()),
								btQuaternion(morphogene->getOrientationX(),
										morphogene->getOrientationY(),
										morphogene->getOrientationZ(),
										morphogene->getOrientationW()), btVector3(),
								btQuaternion(),
								/*size*/
								btVector3(
										generator->getCurrentShrinkageFactor()
										* morphogene->getX(),
										generator->getCurrentShrinkageFactor()
										* morphogene->getY(),
										generator->getCurrentShrinkageFactor()
										* morphogene->getZ()),
								/*mass*/
								btScalar(
										generator->getCurrentShrinkageFactor()
										* morphogene->getX()
										* generator->getCurrentShrinkageFactor()
										* morphogene->getY()
										* generator->getCurrentShrinkageFactor()
										* morphogene->getZ()),
								morphogene->getRestitution(),
								morphogene->getFriction());
						limbBBt->addToWorld();

						//get the surface point of limb B in the local reference frame of B
						Ogre::Vector3 localAnchorOB(
								OgreBulletUtils::convert(
										limbBBt->getLocalIntersection(
												/*origin of limb B*/
												OgreBulletUtils::convert(
														generator->getPosition()),
												/*direction of anchor of limb B*/
												OgreBulletUtils::convert(
														localAnchorDirOB))));

						limbBBt->removeFromWorld();

						delete limbBBt;
						limbBBt = NULL;

						// global center of mass of limb B
						Ogre::Vector3 limbBCOM(
								limbACOM + localAnchorOBinA - localAnchorOB);
						// set global center of mass of limb B as the new generation point

						generator->setPosition(limbBCOM);
						generator->setOrientation(
								Ogre::Quaternion(morphogene->getOrientationW(),
										morphogene->getOrientationX(),
										morphogene->getOrientationY(),
										morphogene->getOrientationZ()));

						localJointOB = localAnchorOB
						+ eulerB * localAnchorDirOB.normalisedCopy()
						* MorphologyConfiguration::JOINT_LENGTH;

//				// draw line from limb A along test ray (RED LINE)
//				//TODO: Debug lines
//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbACOM,
//						limbACOM + 10000.0f * localAnchorDirOA,
//						Ogre::ColourValue(1, 0, 0));
//
//				// draw line from limb B along test ray (RED LINE)
//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbBCOM,
//						limbBCOM + 10000.0f * localAnchorDirOB,
//						Ogre::ColourValue(1, 0, 0));

//				// draw line from limb A to surface anchor point of A (GREEN LINE)
//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbACOM,
//						limbACOM + localAnchorOA, Ogre::ColourValue(0, 1, 0));
//
//				// draw line from anchor point of A to joint rotation point (BLUE LINE)
//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(
//						limbACOM + localAnchorOA, limbACOM + localJointOA,
//						Ogre::ColourValue(0, 0, 1));
//
//				// draw line from joint rotation point to surface anchor point of B (BLUE LINE)
//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(
//						limbACOM + localJointOA, limbACOM + localAnchorOBinA,
//						Ogre::ColourValue(0, 0, 1));
//
//				// draw line from limb B to anchor point of B (GREEN LINE)
//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbBCOM,
//						limbBCOM + localAnchorOB, Ogre::ColourValue(0, 1, 0));
//
//				// draw line from limb A to limb B (WHITE LINE)
//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbBCOM,
//						limbACOM, Ogre::ColourValue(1, 1, 1));
					}

					//build the limb out of the morphogene
					LimbModel* limbB = new LimbModel();
					mLimbModels.push_back(limbB);
					mComponentModels.push_back(limbB);

					limbB->initialize(mCreatureModel->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(), creatureModel,
							morphogene->getPrimitiveType(),
							generator->getPosition(), generator->getOrientation(),
							Ogre::Vector3(
									generator->getPosition()
									- creatureModel->getPosition()),
							Ogre::Quaternion(generator->getOrientation()),
							/*size*/
							Ogre::Vector3(
									generator->getCurrentShrinkageFactor()
									* morphogene->getX(),
									generator->getCurrentShrinkageFactor()
									* morphogene->getY(),
									generator->getCurrentShrinkageFactor()
									* morphogene->getZ()),
							/*mass*/
							generator->getCurrentShrinkageFactor()
							* morphogene->getX()
							* generator->getCurrentShrinkageFactor()
							* morphogene->getY()
							* generator->getCurrentShrinkageFactor()
							* morphogene->getZ(),
							morphogene->getRestitution(), morphogene->getFriction(),
							Ogre::ColourValue(morphogene->getColorR(),
									morphogene->getColorB(),
									morphogene->getColorG()),
							mComponentModels.size() - 1);

					if (generator->getParentComponentModel() != NULL) {

						// transformation from the limb A and limb B center of mass to the joint in the respective reference frames
						btTransform localA, localB;
						localA.setIdentity();
						localB.setIdentity();

						MorphogeneBranch* morphogeneBranch =
						((MorphogeneBranch*) generator->getGeneBranch());

						// define the position and direction of the joint in the reference frame of A
						localA.setOrigin(OgreBulletUtils::convert(localJointOA));
						localA.getBasis().setEulerZYX(
								morphogeneBranch->getJointRoll(),
								morphogeneBranch->getJointYaw(),
								morphogeneBranch->getJointPitch());

						// define the position and direction of the joint in the reference frame of B
						localB.setOrigin(OgreBulletUtils::convert(localJointOB));
						localB.getBasis().setEulerZYX(morphogene->getJointRoll(),
								morphogene->getJointYaw(),
								morphogene->getJointPitch());

						//create the joint from the two limbs using limb A, limb B and their joint definitions in the respective reference frames
						JointModel* joint = new JointModel();

						// add the joint to the phenotype joints
						mJointModels.push_back(joint);
						mComponentModels.push_back(joint);

						joint->initialize(mCreatureModel->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
								/*limbA*/
								((LimbBt*) ((LimbModel*) generator->getParentComponentModel())->getLimbPhysics())->getRigidBody(),
								((LimbBt*) limbB->getLimbPhysics())->getRigidBody(),
								localA, localB,
								((LimbModel*) generator->getParentComponentModel())->getOwnIndex(),
								limbB->getOwnIndex(), mComponentModels.size() - 1);

						//initialize rotational limit motors
						joint->initializeRotationalLimitMotors(
								Ogre::Vector3(
										morphogeneBranch->getJointMaxPitchForce(),
										morphogeneBranch->getJointMaxYawForce(),
										morphogeneBranch->getJointMaxRollForce()),
								Ogre::Vector3(
										morphogeneBranch->getJointMaxPitchForce(),
										morphogeneBranch->getJointMaxYawForce(),
										morphogeneBranch->getJointMaxRollForce()));

						//TODO: Quick controller hack
						for (std::vector<Motor*>::const_iterator motorIterator =
								joint->getMotors().begin(); motorIterator != joint->getMotors().end();
								motorIterator++) {
							SineController* controller = new SineController();
							controller->initialize(0.5, 1, 0, 0);
							controller->addControlOutput((*motorIterator));
							mControllers.push_back(controller);
						}

						//set the angular limits of the joint
						joint->setAngularLimits(
								Ogre::Vector3(
										morphogeneBranch->getJointPitchMinAngle(),
										morphogeneBranch->getJointYawMinAngle(),
										morphogeneBranch->getJointRollMinAngle()),
								Ogre::Vector3(
										morphogeneBranch->getJointPitchMaxAngle(),
										morphogeneBranch->getJointYawMaxAngle(),
										morphogeneBranch->getJointRollMaxAngle()));

						//set the angular stiffness of the joint
						joint->setAngularStiffness(
								morphogeneBranch->getJointPitchStiffness(),
								morphogeneBranch->getJointYawStiffness(),
								morphogeneBranch->getJointRollStiffness());

						//set the angular spring damping coefficients of the joint
						joint->setAngularDamping(
								morphogeneBranch->getSpringPitchDampingCoefficient(),
								morphogeneBranch->getSpringYawDampingCoefficient(),
								morphogeneBranch->getSpringRollDampingCoefficient());

						//set if the angular motor is enabled
						joint->enableAngularMotor(
								morphogeneBranch->isJointPitchMotorEnabled(),
								morphogeneBranch->isJointYawMotorEnabled(),
								morphogeneBranch->isJointRollMotorEnabled());
					}

					//iterate over all morphogene branches
					for (std::vector<MorphogeneBranch*>::iterator branchIt =
							morphogene->getGeneBranches().begin();
							branchIt != morphogene->getGeneBranches().end();
							branchIt++) {

						// only add new generator if the branch is active
						if ((*branchIt)->isActive()) {
							// get the branch gene type defined by the branch
							Morphogene* offspring =
							(Morphogene*) creatureModel->getGenotype().getGenes()[(*branchIt)->getBranchGeneType()];

							// create the new generator
							PhenotypeGenerator* generatorFromBranch =
							new PhenotypeGenerator();
							generatorFromBranch->initialize(
									generator->getRepetitionList(),
									generator->getPosition(),
									generator->getOrientation(), limbB,
									(*branchIt.base()),
									morphogene->getSegmentShrinkFactor()
									* generator->getCurrentShrinkageFactor());

							//If repetition limit not exceeded (if it does not find the key OR if the repetition limit of the key is not exceeded)
							if (generatorFromBranch->getRepetitionList().find(
											(*branchIt)->getBranchGeneType())
									== generatorFromBranch->getRepetitionList().end()
									|| generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
									<= offspring->getRepetitionLimit()) {

								//add another of this offspring type
								generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
								generatorFromBranch->setGene(offspring);
							} else {

								//add the offspring's follower because the repetition limit of the offspring is exceeded
								generatorFromBranch->setGene(
										creatureModel->getGenotype().getGenes()[offspring->getFollowUpGene()]);
							}

							//set new root to leaf path length
							generatorFromBranch->setRoot2LeafPath(
									generator->getRoot2LeafPath() + 1);

							//add generator to the list
							generatorList.push_back(generatorFromBranch);

							if ((*branchIt)->isFlipped()) {
								// create the new generator
								PhenotypeGenerator* flippedGeneratorFromBranch =
								new PhenotypeGenerator();
								flippedGeneratorFromBranch->initialize(
										generator->getRepetitionList(),
										generator->getPosition(),
										generator->getOrientation(), limbB,
										(*branchIt.base()),
										morphogene->getSegmentShrinkFactor()
										* generator->getCurrentShrinkageFactor(),
										true/*Flipped*/, false);

								//If repetition limit not exceeded (if it does not find the key OR if the repetition limit of the key is not exceeded)
								if (flippedGeneratorFromBranch->getRepetitionList().find(
												(*branchIt)->getBranchGeneType())
										== flippedGeneratorFromBranch->getRepetitionList().end()
										|| flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
										<= offspring->getRepetitionLimit()) {

									//add another of this offspring type
									flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
									flippedGeneratorFromBranch->setGene(offspring);
								} else {

									//add the offspring's follower because the repetition limit of the offspring is exceeded
									flippedGeneratorFromBranch->setGene(
											creatureModel->getGenotype().getGenes()[offspring->getFollowUpGene()]);
								}

								//set new root to leaf path length
								flippedGeneratorFromBranch->setRoot2LeafPath(
										generator->getRoot2LeafPath() + 1);

								//add generator to the list
								generatorList.push_back(flippedGeneratorFromBranch);
							}

							if ((*branchIt)->isMirrored()) {
								// create the new generator
								PhenotypeGenerator* mirroredGeneratorFromBranch =
								new PhenotypeGenerator();
								mirroredGeneratorFromBranch->initialize(
										generator->getRepetitionList(),
										generator->getPosition(),
										generator->getOrientation(), limbB,
										(*branchIt.base()),
										morphogene->getSegmentShrinkFactor()
										* generator->getCurrentShrinkageFactor(),
										false, true/*Mirrored*/);

								//If repetition limit not exceeded (if it does not find the key OR if the repetition limit of the key is not exceeded)
								if (mirroredGeneratorFromBranch->getRepetitionList().find(
												(*branchIt)->getBranchGeneType())
										== mirroredGeneratorFromBranch->getRepetitionList().end()
										|| mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
										<= offspring->getRepetitionLimit()) {

									//add another of this offspring type
									mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
									mirroredGeneratorFromBranch->setGene(offspring);
								} else {

									//add the offspring's follower because the repetition limit of the offspring is exceeded
									mirroredGeneratorFromBranch->setGene(
											creatureModel->getGenotype().getGenes()[offspring->getFollowUpGene()]);
								}

								//set new root to leaf path length
								mirroredGeneratorFromBranch->setRoot2LeafPath(
										generator->getRoot2LeafPath() + 1);

								//add generator to the list
								generatorList.push_back(
										mirroredGeneratorFromBranch);
							}
						}
					}
					break;
				}
				default:
				break;
			}
			// delete the generator of this gene
			delete generator;
		}

		mDeveloped = true;
	}
}

void PhenomeModel::reset(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
			it != mLimbModels.end(); it++) {
		(*it)->reset(position);
	}
}

void PhenomeModel::cleanup() {
	for (std::vector<ComponentModel*>::iterator cit = mComponentModels.begin();
			cit != mComponentModels.end();) {
		delete *cit;
		cit = mComponentModels.erase(cit);
	}
	mLimbModels.clear();
	mJointModels.clear();
}

void PhenomeModel::reposition(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
			it != mLimbModels.end(); it++) {
		(*it)->reposition(position);

	}
}

bool PhenomeModel::equals(const PhenomeModel& phenomeModel) const {
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
	if(mJointModels.size() != phenomeModel.mJointModels.size()){
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
	if(mControllers.size() != phenomeModel.mControllers.size()){
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

PhenomeModel* PhenomeModel::clone() {
	return new PhenomeModel(*this);
}

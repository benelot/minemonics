//# corresponding header
#include <utils/Debugger.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/Population.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>

//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger Debugger::mBoostLogger; /*<! initialize the boost logger*/
Debugger::_Init Debugger::_initializer;
Debugger::Debugger() {

}

Debugger::~Debugger() {
}

/**
 * Debug method to see the child nodes of a node.
 * @param node
 * @return
 */
bool Debugger::detectChildren(Ogre::SceneNode* node) {
	int i = 0;
	Ogre::SceneNode::ChildNodeIterator m = node->getChildIterator();
	while (m.hasMoreElements()) {
		i++;
		m.getNext();
	}

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "\nRoot children: " << i << "\n";

	return i;
}

void Debugger::writeJuries(Population* population,
	bool shortNotationEnabled) {
	std::string juriesString;
	for (std::vector<Creature*>::iterator cit =
		population->getCreatures().begin();
		cit != population->getCreatures().end(); cit++) {
		if (shortNotationEnabled) {
			juriesString.append(
				boost::lexical_cast<std::string>(
					(*cit)->getCreatureModel()->getJuries().size()));
		} else {
			juriesString.append((*cit)->getCreatureModel()->getFirstName());
			juriesString.append(": Number of juries: ");
			juriesString.append(
				boost::lexical_cast<std::string>(
					(*cit)->getCreatureModel()->getJuries().size()));
		}
	}
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< juriesString;

	if (shortNotationEnabled) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "";
	} else {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Creatures size: " << population->getCreatures().size();
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Creature models size: "
		<< population->getPopulationModel()->getCreatureModels().size();
	}
}

bool Debugger::isNaN(double d) {
	// Only NaN is not itself
	return d != d;
}

bool Debugger::isNaN(Ogre::Vector3 v) {
	return isNaN(OgreBulletUtils::convert(v));
}

bool Debugger::isNaN(Ogre::Quaternion q) {
	return isNaN(OgreBulletUtils::convert(q));
}

bool Debugger::isNaN(btVector3 v) {
	return isNaN(v.w()) || isNaN(v.x()) || isNaN(v.y()) || isNaN(v.z());
}

bool Debugger::isNaN(btQuaternion q) {
	return isNaN(q.w()) || isNaN(q.x()) || isNaN(q.y()) || isNaN(q.z());
}

bool Debugger::isNaN(btTransform t) {
	return isNaN(t.getOrigin()) || isNaN(t.getRotation());
}

bool Debugger::isInf(double d) {
	// Only Inf does pass this
	return (d/0.0f == d);
}

bool Debugger::isInf(Ogre::Vector3 v) {
	return isInf(OgreBulletUtils::convert(v));
}

bool Debugger::isInf(Ogre::Quaternion q) {
	return isInf(OgreBulletUtils::convert(q));
}

bool Debugger::isInf(btVector3 v) {
	return isInf(v.w()) || isInf(v.x()) || isInf(v.y()) || isInf(v.z());
}

bool Debugger::isInf(btQuaternion q) {
	return isInf(q.w()) || isInf(q.x()) || isInf(q.y()) || isInf(q.z());
}

bool Debugger::isInf(btTransform t) {
	return isInf(t.getOrigin()) || isInf(t.getRotation());
}

bool Debugger::isFinite(double d) {
	return !(isInf(d) && isNaN(d));
}

bool Debugger::isFinite(Ogre::Vector3 v) {
	return !(isInf(OgreBulletUtils::convert(v)) && isNaN(OgreBulletUtils::convert(v)));
}

bool Debugger::isFinite(Ogre::Quaternion q) {
	return !(isInf(OgreBulletUtils::convert(q)) && isNaN(OgreBulletUtils::convert(q)));
}

bool Debugger::isFinite(btVector3 v) {
	return !(isInf(v) && isNaN(v));
}

bool Debugger::isFinite(btQuaternion q) {
	return !(isInf(q)&& isNaN(q));
}

bool Debugger::isFinite(btTransform t) {
	return !(isInf(t) && isNaN(t));
}


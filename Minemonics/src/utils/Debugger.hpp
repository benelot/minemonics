#ifndef UTILS_DEBUGGER_HPP_
#define UTILS_DEBUGGER_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
class Population;
class btTransform;
class btVector3;
class btQuaternion;
class btTransform;

//# system headers
#include <vector>
#include <iostream>

//## controller headers
//## model headers
#include <OgreIteratorWrapper.h>
#include <OgreSceneNode.h>
#include <boost/lexical_cast.hpp>


//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/StringFormatter.hpp>
#include <utils/logging/Logger.hpp>

/**
 * @brief		The debugger collects debug methods to be used in different contexts do quickly get debug information.
 * @details		Details
 * @date		2015-07-22
 * @author		Benjamin Ellenberger
 */
class Debugger {
public:
	Debugger();
	virtual ~Debugger();

	/**
	 * Debug method for an error causing the vectors to have wrong sizes via the iterators.
	 * @param vector Vector to be tested
	 * @param numberOfRuns
	 * @param identifier
	 * @param additionalCounter
	 * @param showNothingFound
	 * @return
	 */
	template<typename T>
	static bool detectVectorSizeError(std::string strid, std::vector<T> vector,
		int numberOfRuns, int identifier, int additionalCounter,
		bool showNothingFound = true) {
		bool nothingFound = true;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		for (int j = 0; j < numberOfRuns; j++) {
			int i = 0;
			for (typename std::vector<T>::const_iterator cit = vector.begin();
				cit != vector.end() && i <= vector.size(); cit++) {
				i++;
			}
			if (i != vector.size()) {
				nothingFound = false;
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Block " << identifier << "::..."
				<< additionalCounter << "/" << j << "\n" << strid
				<< "vector size check...." << "\nsize: " << vector.size()
				<< "\t" << "size2: >" << i;
				throw std::runtime_error(
					StringFormatter() << "Block " << identifier << "::..."
						<< additionalCounter << "/" << j << strid
						<< "vector size check...." << "\nsize: "
						<< vector.size() << "\t" << "size2: >" << i
						>> StringFormatter::to_str);
				return true;
			}
		}

		if (showNothingFound && nothingFound) {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Block " << identifier << "::..." << additionalCounter;
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "\n" << strid << "vector size check....";
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "\nNo errors found\n\n";
			return false;
		}
		return false;

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}

	/**
	 * Debug method to see the child nodes of a node.
	 * @param node
	 * @return
	 */
	static bool detectChildren(Ogre::SceneNode* node);

	static void writeJuries(Population* population, bool shortNotationEnabled);

	static bool isNaN(double d);

	static bool isNaN(Ogre::Vector3 v);

	static bool isNaN(Ogre::Quaternion q);

	static bool isNaN(btVector3 v);

	static bool isNaN(btQuaternion q);

	static bool isNaN(btTransform t);

	static bool isInf(double d);

	static bool isInf(Ogre::Vector3 v);

	static bool isInf(Ogre::Quaternion q);

	static bool isInf(btVector3 v);

	static bool isInf(btQuaternion q);

	static bool isInf(btTransform t);

	static bool isFinite(double d);

	static bool isFinite(Ogre::Vector3 v);

	static bool isFinite(Ogre::Quaternion q);

	static bool isFinite(btVector3 v);

	static bool isFinite(btQuaternion q);

	static bool isFinite(btTransform t);

private:
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string
				> ("Debugger"));
		}
	}_initializer;
};
#endif /* UTILS_DEBUGGER_HPP_ */

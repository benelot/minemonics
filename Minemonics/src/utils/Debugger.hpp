#ifndef UTILS_DEBUGGER_HPP_
#define UTILS_DEBUGGER_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <vector>
#include <iostream>

//## controller headers
//## model headers
#include <OgreIteratorWrapper.h>
#include <OgreSceneNode.h>

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
#include <utils/StringFormatter.hpp>

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
				std::cout << "Block " << identifier << "::..."
					<< additionalCounter << "/" << j << "\n" << strid
					<< "vector size check...." << "\nsize: " << vector.size()
					<< "\t" << "size2: >" << i << std::endl;
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
			std::cout << "Block " << identifier << "::..." << additionalCounter;
			std::cout << "\n" << strid << "vector size check....";
			std::cout << "\nNo errors found\n\n";
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
	static bool detectChildren(Ogre::SceneNode* node) {
		int i = 0;
		Ogre::SceneNode::ChildNodeIterator m = node->getChildIterator();
		while (m.hasMoreElements()) {
			i++;
			m.getNext();
		}

		std::cout << "\nRoot children: " << i << "\n";

		return i;
	}

	static void writeJuries(Population* population, bool shortNotationEnabled) {
		for (std::vector<Creature*>::iterator cit =
			population->getCreatures().begin();
			cit != population->getCreatures().end(); cit++) {
			if (shortNotationEnabled) {
				std::cout << (*cit)->getCreatureModel()->getJuries().size();
			} else {
				std::cout << (*cit)->getCreatureModel()->getFirstName()
					<< ": Number of juries: "
					<< (*cit)->getCreatureModel()->getJuries().size()
					<< std::endl;
			}
		}

		if (shortNotationEnabled) {
			std::cout << std::endl;
		} else {
			std::cout << "Creatures size: " << population->getCreatures().size()
				<< std::endl;
			std::cout << "Creature models size: "
				<< population->getPopulationModel()->getCreatureModels().size()
				<< std::endl;
		}

	}
};

#endif /* UTILS_DEBUGGER_HPP_ */

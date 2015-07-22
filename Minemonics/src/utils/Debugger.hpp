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
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers

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
	 * Debug method for an error causing the creature vectors to have wrong sizes via the iterators.
	 * @param populationModel
	 * @param numberOfRuns
	 * @param identifier
	 * @param additionalCounter
	 * @param showNothingFound
	 * @return
	 */
	static bool detectError(PopulationModel* populationModel, int numberOfRuns,
			int identifier, int additionalCounter,
			bool showNothingFound = true) {
		bool nothingFound = true;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		for (int j = 0; j < numberOfRuns; j++) {
			int i = 0;
			for (std::vector<CreatureModel*>::const_iterator cit =
					populationModel->getCreatureModels().begin();
					cit != populationModel->getCreatureModels().end()
							&& i <= populationModel->getCreatureModels().size();
					cit++) {
				i++;
			}
			if (i != populationModel->getCreatureModels().size()) {
				nothingFound = false;
				std::cout << "Block " << identifier << "::..."
						<< additionalCounter << "/" << j;
				std::cout << "CreatureModel vector size check....";
				std::cout << "\nsize: "
						<< populationModel->getCreatureModels().size() << "\t";
				std::cout << "size2: >" << i << std::endl;
				return true;
			}
		}

		if (showNothingFound && nothingFound) {
			std::cout << "Block " << identifier << "::..." << additionalCounter;
			std::cout << "\nCreatureModel vector size check....";
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
};

#endif /* UTILS_DEBUGGER_HPP_ */

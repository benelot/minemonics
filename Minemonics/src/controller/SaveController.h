/*
 * SaveController.h
 *
 *  Created on: Mar 3, 2015
 *      Author: leviathan
 */

#ifndef SAVECONTROLLER_H_
#define SAVECONTROLLER_H_

//# corresponding header

//# forward declarations

//# system headers
//## controller headers

//## model headers

//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers
#include "model/evolution/population/creature/Creature.h"
//## view headers

//## utils headers

class SaveController {
public:
	virtual ~SaveController();
	SaveController();

	void saveCreature(const Creature &creature, const char* filename) {
		// make an archive from the creature
		std::ofstream ofs(filename);
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(creature);
	}

	void restoreCreature(Creature &creature, const char* filename) {
		// open the archive
		std::ifstream ifs(filename);
		assert(ifs.good());
		boost::archive::xml_iarchive ia(ifs);

		// restore the creature from the archive
		ia >> BOOST_SERIALIZATION_NVP(creature);
	}
};

#endif /* SAVECONTROLLER_H_ */

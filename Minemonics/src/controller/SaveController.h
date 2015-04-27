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
#include <fstream>

//## controller headers
//## model headers
// include headers that implement a archive in xml format
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/base_object.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
template <class T> class SaveController {
public:
	SaveController(){

	}
	virtual ~SaveController(){

	}

	void save(const T & object,const char* filename){
		// make an archive from the object
		std::ofstream ofs(filename);
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(object);
	}

	void restore(T &object, const char* filename){
		// open the archive
		std::ifstream ifs(filename);
		assert(ifs.good());
		boost::archive::xml_iarchive ia(ifs);

		// restore the object from the archive
		ia >> BOOST_SERIALIZATION_NVP(object);
	}
};

#endif /* SAVECONTROLLER_H_ */

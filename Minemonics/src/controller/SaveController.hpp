#ifndef CONTROLLER_SAVECONTROLLER_H_
#define CONTROLLER_SAVECONTROLLER_H_

//# corresponding header
//# forward declarations
//# system headers
#include <fstream>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>
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
#include <utils/logging/Logger.hpp>

/**
 * @brief		The template to serialize objects with boost.
 * @details		Details
 * @date		2015-03-03
 * @author		Benjamin Ellenberger
 */
template<class T> class SaveController {
public:
	SaveController() {
		mBoostLogger.add_attribute("ClassName",
			boost::log::attributes::constant<std::string>("SaveController"));
	}
	virtual ~SaveController() {

	}

	void save(const T & object, const char* filename) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Saving "
		<< filename << "...";
		// make an archive from the object
		std::ofstream ofs(filename);
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(object);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Saved "
		<< filename << ".";
	}

	void restore(T &object, const char* filename) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Restoring "
		<< filename << "...";
		// open the archive
		std::ifstream ifs(filename);
		assert(ifs.good());
		boost::archive::xml_iarchive ia(ifs);

		// restore the object from the archive
		ia >> BOOST_SERIALIZATION_NVP(object);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Restored "
		<< filename << ".";
	}

private:
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;
};

template<typename T>
BoostLogger SaveController<T>::mBoostLogger; /*<! initialize the boost logger*/

#endif /* SAVECONTROLLER_H_ */

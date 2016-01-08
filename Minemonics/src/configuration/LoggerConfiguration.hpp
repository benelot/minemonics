#ifndef CONFIGURATION_LOGGERCONFIGURATION_HPP_
#define CONFIGURATION_LOGGERCONFIGURATION_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The configuration of the Logger.
 * @details		Details
 * @date		2015-07-13
 * @author		Benjamin Ellenberger
 */
class LoggerConfiguration {
public:
	static const boost::log::trivial::severity_level trace =
			boost::log::trivial::trace;
	static const boost::log::trivial::severity_level debug =
			boost::log::trivial::debug;
	static const boost::log::trivial::severity_level info =
			boost::log::trivial::info;
	static const boost::log::trivial::severity_level warning =
			boost::log::trivial::warning;
	static const boost::log::trivial::severity_level error =
			boost::log::trivial::error;
	static const boost::log::trivial::severity_level fatal =
			boost::log::trivial::fatal;

	static const boost::log::trivial::severity_level LOGGING_LEVEL = info;

	static const std::string loggedClasses;

	static const std::string TOP_FOLDER;

	static const int LOG_DATA_QTY;

	static const bool LOG_SPECIAL;
};

#endif /* CONFIGURATION_LOGGERCONFIGURATION_HPP_ */

#ifndef UTILS_LOGGING_LOGGER_H_
#define UTILS_LOGGING_LOGGER_H_

//# corresponding header
//# forward declarations
//# system headers
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

typedef boost::log::sources::severity_logger<boost::log::trivial::severity_level> BoostLogger;

/**
 * @brief		The logger class helps to handle a boost logger.
 * The logger levels are in this order: trace, debug, info, warning, error, fatal
 * @details		Details
 * @date		2015-02-14
 * @author		Benjamin Ellenberger
 */
class Logger {
public:
	static void init(std::string fileName,boost::log::trivial::severity_level severity);
	static void initTermSink();

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
};

#endif /* UTILS_LOGGING_LOGGER_H_ */

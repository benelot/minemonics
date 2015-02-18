/*
 * Logger.h
 *
 *  Created on: Feb 14, 2015
 *      Author: leviathan
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

typedef boost::log::sources::severity_logger<boost::log::trivial::severity_level> BoostLogger;

class Logger {
public:
	Logger();
	~Logger();
	static void init(std::string fileName);
	static void initTermSink();
	//static void setClass(BoostLogger logger,std::string className);
	//static void log(boost::log::trivial::severity_level severityLevel,std::string message);


	static const boost::log::trivial::severity_level trace = boost::log::trivial::trace;
	static const boost::log::trivial::severity_level debug = boost::log::trivial::debug;
	static const boost::log::trivial::severity_level info = boost::log::trivial::info;
	static const boost::log::trivial::severity_level warning = boost::log::trivial::warning;
	static const boost::log::trivial::severity_level error = boost::log::trivial::error;
	static const boost::log::trivial::severity_level fatal = boost::log::trivial::fatal;
};

#endif /* LOGGER_H_ */

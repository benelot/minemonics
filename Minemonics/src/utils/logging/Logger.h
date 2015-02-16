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
	virtual ~Logger();
	static void init(std::string fileName);
	static void initTermSink();
};

#endif /* LOGGER_H_ */

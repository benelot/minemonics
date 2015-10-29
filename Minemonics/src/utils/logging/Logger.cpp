//# corresponding header
#include <utils/logging/Logger.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/log/core.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/value_ref.hpp>
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/regex.hpp>
#include <boost/log/expressions/predicates/matches.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>

// Supporting headers
#include <boost/log/support/regex.hpp>
#include <boost/log/support/xpressive.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/LoggerConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

Logger::Logger() {

}

Logger::~Logger() {

}

void Logger::init(std::string fileName,
	boost::log::trivial::severity_level severity) {
	namespace logging = boost::log;
	namespace src = boost::log::sources;
	namespace sinks = boost::log::sinks;
	namespace expr = boost::log::expressions;
	namespace keywords = boost::log::keywords;
	namespace attrs = boost::log::attributes;

	// Set up our sink and formatting
	logging::add_file_log(keywords::file_name = fileName,
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0,
			0, 0),
		keywords::format = (expr::stream
			<< expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
				"%Y-%m-%d %H:%M:%S") << ": ["
			<< expr::attr<std::string>("ClassName") << "] <"
			<< logging::trivial::severity << "> " << expr::smessage));

	logging::add_common_attributes();

	logging::core::get()->set_filter(
		logging::trivial::severity >= severity
			&& (expr::has_attr("ClassName")
	&& expr::matches(expr::attr< std::string >("ClassName"), boost::regex(LoggerConfiguration::loggedClasses))));
}

void Logger::initTermSink() {
	namespace logging = boost::log;
	namespace src = boost::log::sources;
	namespace sinks = boost::log::sinks;
	namespace expr = boost::log::expressions;
	namespace keywords = boost::log::keywords;
	typedef logging::sinks::synchronous_sink<
		logging::sinks::text_ostream_backend> text_sink;

	boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
	sink->locked_backend()->add_stream(
		boost::shared_ptr<std::ostream>(&std::cout, logging::empty_deleter()));

	sink->locked_backend()->auto_flush(true);

	sink->set_formatter(
		logging::expressions::stream << logging::expressions::message);

	logging::core::get()->add_sink(sink);
	logging::add_common_attributes();
}


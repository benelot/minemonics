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
#include <boost/log/sinks/text_multifile_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/value_ref.hpp>
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/regex.hpp>
#include <boost/log/expressions/predicates/matches.hpp>
#include <boost/preprocessor/seq/enum.hpp>

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

using boost::shared_ptr;

void Logger::init(std::string fileName,
	boost::log::trivial::severity_level severity) {
	initFileSink(fileName, severity);
	initTermSink(severity);
	initSpecialLoggers();
}

void Logger::initFileSink(std::string fileName,
	boost::log::trivial::severity_level severity) {

	namespace logging = boost::log;
	namespace src = boost::log::sources;
	namespace sinks = boost::log::sinks;
	namespace expr = boost::log::expressions;
	namespace keywords = boost::log::keywords;
	namespace attrs = boost::log::attributes;

	boost::shared_ptr<logging::core> core = logging::core::get();

	// Set up our sink and formatting
	// Create a text file sink
	typedef sinks::synchronous_sink<sinks::text_file_backend> file_sink;
	boost::shared_ptr<file_sink> sink(new file_sink(keywords::file_name =
		fileName));

	sink->set_formatter(
		expr::format("%1%: [%2%] <%3%> %4%")
			% expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
				"%Y-%m-%d %H:%M:%S") % expr::attr<std::string>("ClassName")
			% logging::trivial::severity % expr::smessage);

	// set a filter to only log information coming from specified classes
	sink->set_filter(
		logging::trivial::severity >= severity && expr::has_attr("ClassName")
//			&& expr::matches(expr::attr<std::string>("ClassName"),
//				boost::regex(LoggerConfiguration::loggedClasses))
			);

	core->add_sink(sink);
}

void Logger::initTermSink(boost::log::trivial::severity_level severity) {
	namespace logging = boost::log;
	namespace src = boost::log::sources;
	namespace sinks = boost::log::sinks;
	namespace expr = boost::log::expressions;
	namespace keywords = boost::log::keywords;

	//setup a synchronous shared sink
	typedef logging::sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
	boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
	sink->locked_backend()->add_stream(
		boost::shared_ptr<std::ostream>(&std::cout, logging::empty_deleter()));
	sink->locked_backend()->auto_flush(true);

	sink->set_filter(
		logging::trivial::severity >= severity && !expr::has_attr("LoggerName")
			&& (expr::has_attr("ClassName")
				&& expr::matches(expr::attr<std::string>("ClassName"),
					boost::regex(LoggerConfiguration::loggedClasses))));

	sink->set_formatter(
		expr::format("%1%: [%2%] <%3%> %4%")
			% expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
				"%Y-%m-%d %H:%M:%S") % expr::attr<std::string>("ClassName")
			% logging::trivial::severity % expr::smessage);

	logging::core::get()->add_sink(sink);
	logging::add_common_attributes();
}

void Logger::initSpecialLoggers() {
	namespace logging = boost::log;
	namespace src = boost::log::sources;
	namespace sinks = boost::log::sinks;
	namespace expr = boost::log::expressions;
	namespace keywords = boost::log::keywords;

	// Create a text file sink
	typedef sinks::synchronous_sink<sinks::text_multifile_backend> file_sink;
	shared_ptr<file_sink> sink(new file_sink);

	// Set up the file naming pattern
	// Set up how the file names will be generated
	sink->locked_backend()->set_file_name_composer(
		sinks::file::as_file_name_composer(
			expr::stream << "logs/log" << expr::attr<std::string>("LoggerName")
				<< ".log"));

	// Set the formatter
	sink->set_formatter(expr::stream << expr::smessage);
	sink->set_filter(expr::has_attr("LoggerName"));

	logging::core::get()->add_sink(sink);
}


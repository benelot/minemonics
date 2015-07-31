/*
 * StringFormatter.hpp
 *
 *  Created on: Jul 31, 2015
 *      Author: leviathan
 */

#ifndef UTILS_STRINGFORMATTER_HPP_
#define UTILS_STRINGFORMATTER_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <sstream>
#include <string>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The string formatter helps to quickly put together std::strings via the << operator.
 * @details		Details
 * @date		2015-07-31
 * @author		Benjamin Ellenberger
 */
class StringFormatter
{
public:
    StringFormatter();
    ~StringFormatter();

    template <typename Type>
    StringFormatter & operator << (const Type & value)
    {
        stream_ << value;
        return *this;
    }

    std::string str() const         { return stream_.str(); }
    operator std::string () const   { return stream_.str(); }

    enum ConvertToString
    {
        to_str
    };
    std::string operator >> (ConvertToString) { return stream_.str(); }

private:
    std::stringstream stream_;

    StringFormatter(const StringFormatter &);
    StringFormatter & operator = (StringFormatter &);
};

#endif /* UTILS_STRINGFORMATTER_HPP_ */

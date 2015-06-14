#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include <string>
#include <vector>

namespace utility
{

/** \brief Configuration file
 *
 *  Used to parse pairs of "string = string"
 *  Additional functions may parse the second string to numbers or other strings, separated by commas
 */


class Configuration
{
public:

    // initialization of a configuration
    Configuration(std::string filename);
    // find one variable
    std::string find_string(std::string searched);
    // find some variables
    std::vector<std::string> find_strings(std::string searched);

private:

    // vector of pairs to hold the config
    std::vector<std::pair<std::string,std::string>>config;

};

}//end of utility namespace

#endif // CONFIGURATION_H_INCLUDED

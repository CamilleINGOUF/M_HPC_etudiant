#ifndef UTILS_HPP_
#define UTILS_HPP_

//////////////////////////////////////////////////////////////////////
// chrono
//////////////////////////////////////////////////////////////////////

#include <chrono>

using timePoint_t = std::chrono::time_point<std::chrono::system_clock>;

auto now = std::chrono::system_clock::now;

double duration(const timePoint_t & tp0, const timePoint_t & tp1)
{
    std::chrono::duration<double> nbSeconds = tp1 - tp0;
    return nbSeconds.count();
}

//////////////////////////////////////////////////////////////////////
// filesystem
//////////////////////////////////////////////////////////////////////

#include <boost/filesystem.hpp>

void getBasenameAndExtension(const char * filename, 
        std::string & basename, std::string & extension)
{
    boost::filesystem::path path(filename);
    basename = path.stem().string();
    extension = path.extension().string();
}

#endif


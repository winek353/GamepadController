#pragma once
#include <fstream>

class Logger
{
public:
    Logger()
    {
        debugStream.open("debug.txt");
    }

    static Logger& getLogger()
    {
        static Logger theOnlyLogger;
        return theOnlyLogger;
    }

    std::ostream& getDebugStream()
    {
        return debugStream;
    }

    ~Logger()
    {
        debugStream.close();
    }

private:
    std::ofstream debugStream;
};


#define DEBUG int ___debug___ = 1; while(true) if(___debug___--==0){Logger::getLogger().getDebugStream() << std::endl;break;} else Logger::getLogger().getDebugStream() << __FILE__ << ":" << __LINE__ << " "

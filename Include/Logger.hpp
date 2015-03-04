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


#define DEBUG_ENABLED 1
#define DEBUG if(DEBUG_ENABLED) for(int ___debug___ = 1;___debug___>=0;___debug___--) if(___debug___==0){Logger::getLogger().getDebugStream() << std::endl;} else Logger::getLogger().getDebugStream() << __FILE__ << ":" << __LINE__ << " "

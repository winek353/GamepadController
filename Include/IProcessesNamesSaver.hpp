#pragma once
#include <string>

class IProcessesNamesSaver
{
public:
    virtual void addProcessName(const std::string&) = 0;
    virtual void saveProcesses() = 0;
};

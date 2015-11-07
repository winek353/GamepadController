#pragma once
#include "IProcessesNamesSaver.hpp"
#include <set>

class ProcessesNamesSaver : public IProcessesNamesSaver
{
public:
    void addProcessName(const std::string&) override;
    void saveProcesses() override;
private:
    std::set<std::string> processesNames;
};


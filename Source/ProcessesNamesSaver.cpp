#include "ProcessesNamesSaver.hpp"
#include <fstream>
#include <iostream>

void ProcessesNamesSaver::addProcessName(const std::string& processName)
{
	processesNames.insert(processName);
}

void ProcessesNamesSaver::saveProcesses()
{
    std::ofstream file("/home/winiarz/temp/GamepadControllerProcessesNames.txt");

	for(const auto& processName : processesNames)
	{
        file << processName << std::endl;
	}

    file.close();

    std::cout << "processes names saved!" << std::endl;
}


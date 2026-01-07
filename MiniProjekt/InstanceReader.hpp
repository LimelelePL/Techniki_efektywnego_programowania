#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "VrpInstance.hpp"
#include "Errors/Result.h"
#include "Errors/Error.h"

class InstanceReader {
public:
	InstanceReader(std::string  dirName, std::string  fileName);

	[[nodiscard]] Result<VrpInstance, Error> readInstance() const;

private:
	std::string directory;
	std::string filename;
	std::string fullFilePath;

	static Result<void, Error> processFile(std::ifstream& fileStream, VrpInstance& instance);

	static Result<void, Error> loadNodeCoordinates(std::ifstream& fileStream, VrpInstance& instance);
	static Result<void, Error> loadNodeDemands(std::ifstream& fileStream, VrpInstance& instance);
	static Result<void, Error> loadDepotInformation(std::ifstream& fileStream, VrpInstance& instance);
	static Result<void, Error> loadDistanceMatrix(std::ifstream& fileStream, VrpInstance& instance);

	static std::string trim(const std::string& s);
};

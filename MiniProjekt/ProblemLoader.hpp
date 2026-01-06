#pragma once

#include "ProblemData.hpp"
#include <string>

#include "Errors/Error.h"
#include "Errors/Result.h"

using namespace std;

namespace LcVRPContest {
	class ProblemLoader {
	public:
		ProblemLoader(const string& folder_name, const string& instance_name);

		Result<ProblemData, Error> LoadProblem();

	private:
		string folder_name_;
		string instance_name_;
		string base_path_;

		Result<void, Error> ParseLcVrpFile(const string& file_path, ProblemData& problem_data);
		void ParseEdgeWeightSection(ifstream& file, ProblemData& problem_data);
		void ParseNodeCoordSection(ifstream& file, ProblemData& problem_data);
		void ParseDemandSection(ifstream& file, ProblemData& problem_data);
		void ParseDepotSection(ifstream& file, ProblemData& problem_data);
	};
}

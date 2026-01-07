#include "InstanceReader.hpp"

#include <sstream>
#include <stdexcept>
#include <cmath>
#include <utility>

InstanceReader::InstanceReader(std::string  dirName, std::string  fileName)
    : directory(std::move(dirName)), filename(std::move(fileName)) {
    fullFilePath = "data/lcvrp/" + directory + "/" + filename + ".lcvrp";
}

Result<VrpInstance, Error> InstanceReader::readInstance() const {
    VrpInstance instance;
    std::ifstream file(fullFilePath);

    if (!file.is_open()) {
        return Result<VrpInstance, Error>::fail(
            new Error("FILE_NOT_FOUND: " + fullFilePath)
        );
    }

    auto parseRes = processFile(file, instance);
    if (!parseRes.isSuccess()) {
        return Result<VrpInstance, Error>::fail(parseRes.getErrors());
    }

    if (instance.getDistanceType() == "EUC_2D") {
        instance.generateDistanceTable();
    }

    return Result<VrpInstance, Error>::ok(instance);
}

Result<void, Error> InstanceReader::processFile(
    std::ifstream& file,
    VrpInstance& instance
) {
    std::string line;

    try {
        while (std::getline(file, line)) {
            line = trim(line);
            if (line.empty()) continue;

            // ---------- HEADERS ----------
            if (line.starts_with("NAME")) {
                instance.setInstanceName(trim(line.substr(line.find(':') + 1)));
            }
            else if (line.starts_with("DIMENSION")) {
                instance.initialize(
                    std::stoi(trim(line.substr(line.find(':') + 1))),
                    0, 0, 1
                );
            }
            else if (line.starts_with("CAPACITY")) {
                instance.initialize(
                    instance.getTotalNodes(),
                    std::stoi(trim(line.substr(line.find(':') + 1))),
                    instance.getFleetSize(),
                    instance.getDepotNode()
                );
            }
            else if (line.starts_with("NUM_GROUPS")) {
                instance.initialize(
                    instance.getTotalNodes(),
                    instance.getCapacityLimit(),
                    std::stoi(trim(line.substr(line.find(':') + 1))),
                    instance.getDepotNode()
                );
            }
            else if (line.starts_with("DISTANCE")) {
                instance.setMaxDistance(
                    std::stod(trim(line.substr(line.find(':') + 1)))
                );
            }
            else if (line.starts_with("EDGE_WEIGHT_TYPE")) {
                instance.setDistanceType(
                    trim(line.substr(line.find(':') + 1))
                );
            }
            else if (line.starts_with("PERMUTATION")) {
                std::vector<int> perm;
                std::istringstream iss(line.substr(line.find(':') + 1));
                int x;
                while (iss >> x) perm.push_back(x);
                instance.assignVisitOrder(perm);
            }

            // ---------- SECTIONS ----------
            else if (line.contains("NODE_COORD_SECTION")) {
                auto r = loadNodeCoordinates(file, instance);
                if (!r.isSuccess()) return r;
            }
            else if (line.contains("DEMAND_SECTION")) {
                auto r = loadNodeDemands(file, instance);
                if (!r.isSuccess()) return r;
            }
            else if (line.contains("DEPOT_SECTION")) {
                auto r = loadDepotInformation(file, instance);
                if (!r.isSuccess()) return r;
            }
            else if (line.contains("EDGE_WEIGHT_SECTION")) {
                auto r = loadDistanceMatrix(file, instance);
                if (!r.isSuccess()) return r;
            }
            else if (line.contains("EOF")) {
                break;
            }
        }
    }
    catch (const std::exception& e) {
        return Result<void, Error>::fail(
            new Error(std::string("PARSING_EXCEPTION: ") + e.what())
        );
    }

    return Result<void, Error>::ok();
}

Result<void, Error> InstanceReader::loadNodeCoordinates(
    std::ifstream& file,
    VrpInstance& instance
) {
    const int n = instance.getTotalNodes();
    if (n <= 0)
        return Result<void, Error>::fail(new Error("NODE_COORD_WITHOUT_DIMENSION"));

    std::vector<Coordinate> coords(n);

    for (int i = 0; i < n; ++i) {
        int id;
        double x, y;
        if (!(file >> id >> x >> y))
            return Result<void, Error>::fail(new Error("NODE_COORD_SECTION_TRUNCATED"));
        if (id < 1 || id > n)
            return Result<void, Error>::fail(new Error("NODE_ID_OUT_OF_RANGE"));
        coords[id - 1] = Coordinate(x, y);
    }

    instance.assignCoordinates(coords);
    return Result<void, Error>::ok();
}

Result<void, Error> InstanceReader::loadNodeDemands(
    std::ifstream& file,
    VrpInstance& instance
) {
    const int n = instance.getTotalNodes();
    std::vector<int> demands(n, 0);

    for (int i = 0; i < n; ++i) {
        int id, d;
        if (!(file >> id >> d))
            return Result<void, Error>::fail(new Error("DEMAND_SECTION_TRUNCATED"));
        if (id < 1 || id > n)
            return Result<void, Error>::fail(new Error("DEMAND_NODE_ID_OUT_OF_RANGE"));
        demands[id - 1] = d;
    }

    instance.assignDemands(demands);
    return Result<void, Error>::ok();
}

Result<void, Error> InstanceReader::loadDepotInformation(
    std::ifstream& file,
    VrpInstance& instance
) {
    int depot, term;
    if (!(file >> depot))
        return Result<void, Error>::fail(new Error("DEPOT_SECTION_TRUNCATED"));

    instance.initialize(
        instance.getTotalNodes(),
        instance.getCapacityLimit(),
        instance.getFleetSize(),
        depot
    );

    file >> term; // -1
    return Result<void, Error>::ok();
}

Result<void, Error> InstanceReader::loadDistanceMatrix(
    std::ifstream& file,
    VrpInstance& instance
) {
    const int n = instance.getTotalNodes();
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n, 0.0));

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            double v;
            if (!(file >> v))
                return Result<void, Error>::fail(new Error("EDGE_WEIGHT_SECTION_TRUNCATED"));
            matrix[i][j] = v;
            matrix[j][i] = v;
        }
    }

    instance.assignDistanceTable(matrix);
    return Result<void, Error>::ok();
}

std::string InstanceReader::trim(const std::string& s) {
    const auto start = s.find_first_not_of(" \t\r\n");
    const auto end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos || end == std::string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

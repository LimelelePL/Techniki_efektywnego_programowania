#include "VrpInstance.hpp"
#include <cmath>
#include <algorithm>

Coordinate::Coordinate() : xPos(0.0), yPos(0.0) {}
Coordinate::Coordinate(double x, double y) : xPos(x), yPos(y) {}

VrpInstance::VrpInstance()
    : totalNodes(0), capacityLimit(0), fleetSize(0),
      depotNode(1), maxDistance(0.0), hasDistLimit(false) {}

void VrpInstance::initialize(int nodes, int cap, int fleet, int depot) {
    totalNodes = nodes;
    capacityLimit = cap;
    fleetSize = fleet;
    depotNode = depot;
    coordinates.resize(nodes);
    demands.resize(nodes, 0);
}


double VrpInstance::computeEuclidean(const Coordinate& a, const Coordinate& b) {
    double dx = a.xPos - b.xPos;
    double dy = a.yPos - b.yPos;
    return std::sqrt(dx * dx + dy * dy);
}

double VrpInstance::calculateDistance(int i, int j) const {
    if (i < 0 || j < 0 || i >= totalNodes || j >= totalNodes) return -1.0;
    if (i == j) return 0.0;

    if (distanceType == "EXPLICIT") {
        return distanceTable[i][j];
    }
    return computeEuclidean(coordinates[i], coordinates[j]);
}

void VrpInstance::generateDistanceTable() {
    if (distanceType != "EUC_2D") return;

    distanceTable.assign(totalNodes, std::vector<double>(totalNodes, 0.0));
    for (int i = 0; i < totalNodes; i++)
        for (int j = i + 1; j < totalNodes; j++) {
            double d = computeEuclidean(coordinates[i], coordinates[j]);
            distanceTable[i][j] = d;
            distanceTable[j][i] = d;
        }
}

void VrpInstance::setInstanceName(const std::string& name) { instanceName = name; }
void VrpInstance::setDistanceType(const std::string& type) { distanceType = type; }
void VrpInstance::setMaxDistance(double dist) { maxDistance = dist; hasDistLimit = true; }

void VrpInstance::assignCoordinates(const std::vector<Coordinate>& c) { coordinates = c; }
void VrpInstance::assignDemands(const std::vector<int>& d) { demands = d; }
void VrpInstance::assignVisitOrder(const std::vector<int>& o) { visitOrder = o; }
void VrpInstance::assignDistanceTable(const std::vector<std::vector<double>>& t) { distanceTable = t; }

std::string VrpInstance::getInstanceName() const { return instanceName; }
int VrpInstance::getTotalNodes() const { return totalNodes; }
int VrpInstance::getCapacityLimit() const { return capacityLimit; }
int VrpInstance::getFleetSize() const { return fleetSize; }
int VrpInstance::getDepotNode() const { return depotNode; }
int VrpInstance::getCustomerCount() const { return totalNodes > 0 ? totalNodes - 1 : 0; }

double VrpInstance::getMaxDistance() const { return maxDistance; }
bool VrpInstance::hasDistanceLimit() const { return hasDistLimit; }

std::string VrpInstance::getDistanceType() const { return distanceType; }

const std::vector<Coordinate>& VrpInstance::getCoordinates() const { return coordinates; }
const std::vector<int>& VrpInstance::getDemands() const { return demands; }
const std::vector<int>& VrpInstance::getVisitOrder() const { return visitOrder; }
const std::vector<std::vector<double>>& VrpInstance::getDistanceTable() const { return distanceTable; }
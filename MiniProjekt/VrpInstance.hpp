#pragma once

#include <vector>
#include <string>

struct Coordinate {
    double xPos;
    double yPos;

    Coordinate();
    Coordinate(double x, double y);
};

class VrpInstance {
public:
    VrpInstance();

    void initialize(int totalNodes, int maxLoad, int vehicleFleet, int depotNode);

    void setInstanceName(const std::string& name);
    void setDistanceType(const std::string& type);
    void setMaxDistance(double dist);

    void assignCoordinates(const std::vector<Coordinate>& coords);
    void assignDemands(const std::vector<int>& dems);
    void assignVisitOrder(const std::vector<int>& order);
    void assignDistanceTable(const std::vector<std::vector<double>>& table);

    [[nodiscard]] std::string getInstanceName() const;
    [[nodiscard]] int getTotalNodes() const;
    [[nodiscard]] int getCapacityLimit() const;
    [[nodiscard]] int getFleetSize() const;
    [[nodiscard]] int getDepotNode() const;
    [[nodiscard]] int getCustomerCount() const;

    [[nodiscard]] double getMaxDistance() const;
    [[nodiscard]] bool hasDistanceLimit() const;

    [[nodiscard]] std::string getDistanceType() const;

    [[nodiscard]] const std::vector<Coordinate>& getCoordinates() const;
    [[nodiscard]] const std::vector<int>& getDemands() const;
    [[nodiscard]] const std::vector<int>& getVisitOrder() const;
    [[nodiscard]] const std::vector<std::vector<double>>& getDistanceTable() const;

    [[nodiscard]] double calculateDistance(int node1, int node2) const;
    void generateDistanceTable();

private:
    static double computeEuclidean(const Coordinate& c1, const Coordinate& c2) ;

    std::string instanceName;
    std::string distanceType;

    int totalNodes;
    int capacityLimit;
    int fleetSize;
    int depotNode;

    double maxDistance;
    bool hasDistLimit;

    std::vector<Coordinate> coordinates;
    std::vector<int> demands;
    std::vector<int> visitOrder;
    std::vector<std::vector<double>> distanceTable;
};

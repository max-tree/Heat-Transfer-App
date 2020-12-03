#include "HeatTransferNode.h"
#include "gtest/gtest.h"
#include "math.h"

double calculate_distance_between_two_nodes(HeatTransferNode node1, HeatTransferNode node2)
{
    double distance{0.0};
    distance = sqrt(pow(node1.xCoordinate-node2.xCoordinate,2) + pow(node1.yCoordinate-node2.yCoordinate,2));
    return distance;
}

TEST(CalculateDistanceBetweenTwoNodes, WhenNodesAreIdentical_ExpectDistanceOfZero)
{
    HeatTransferNode node1;
    HeatTransferNode node2;
    double expectedResult{0.0};
    double result{0.0};
    double tolerance{0.001};

    node1.xCoordinate = 1.0;
    node1.yCoordinate = 1.0;
    node2.xCoordinate = 1.0;
    node2.yCoordinate = 1.0;

    result = calculate_distance_between_two_nodes(node1, node2);

    EXPECT_NEAR(expectedResult, result, tolerance);
}

TEST(CalculateDistanceBetweenTwoNodes, WhenNodesHaveDifferentCoordinates_ExpectCorrectDistance)
{
    HeatTransferNode node1;
    HeatTransferNode node2;
    double expectedResult{2.0};
    double result{0.0};
    double tolerance{0.001};

    node1.xCoordinate = 1.0;
    node1.yCoordinate = 1.0;
    node2.xCoordinate = 1.0;
    node2.yCoordinate = -1.0;

    result = calculate_distance_between_two_nodes(node1, node2);

    EXPECT_NEAR(expectedResult, result, tolerance);
}

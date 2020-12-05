#include "HeatTransferNode.h"
#include "gtest/gtest.h"

TEST(CalculateDistanceBetweenTwoNodes, WhenNodesAreIdentical_ExpectDistanceOfZero)
{
    HeatTransferNode* node1 = new HeatTransferNode;
    HeatTransferNode* node2 = new HeatTransferNode;
    double expectedResult{0.0};
    double result{0.0};
    double tolerance{0.001};

    node1->xCoordinate = 1.0;
    node1->yCoordinate = 1.0;
    node2->xCoordinate = 1.0;
    node2->yCoordinate = 1.0;

    result = calculate_distance_between_two_nodes(node1, node2);

    EXPECT_NEAR(expectedResult, result, tolerance);
}

TEST(CalculateDistanceBetweenTwoNodes, WhenNodesHaveDifferentCoordinates_ExpectCorrectDistance)
{
    HeatTransferNode* node1 = new HeatTransferNode;
    HeatTransferNode* node2 = new HeatTransferNode;
    double expectedResult{2.0};
    double result{0.0};
    double tolerance{0.001};

    node1->xCoordinate = 1.0;
    node1->yCoordinate = 1.0;
    node2->xCoordinate = 1.0;
    node2->yCoordinate = -1.0;

    result = calculate_distance_between_two_nodes(node1, node2);

    EXPECT_NEAR(expectedResult, result, tolerance);
}

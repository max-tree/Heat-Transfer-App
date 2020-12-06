#include "gtest/gtest.h"
#include "HeatTransferNode.h"
#include "HeatTransferWorld.h"
#include <iostream>

void set_xCoordinate_of_each_node(HeatTransferWorld &HTW, std::array <double, 5> xCoordinateOfEachNode, int numberOfNodes)
{
    for(int index{0};index<numberOfNodes;index++)
    {
        HTW.nodeStorage[index]->xCoordinate = xCoordinateOfEachNode[index];
    }
}

void set_yCoordinate_of_each_node(HeatTransferWorld &HTW, std::array <double, 5> distancesBetweenNodes, int numberOfNodes)
{
    for(int index{0};index<numberOfNodes;index++)
    {
        HTW.nodeStorage[index]->yCoordinate = distancesBetweenNodes[index];
    }
}

void test_neighbor_results(HeatTransferWorld HTW, std::array <int,4> expectedResult)
{
    EXPECT_EQ(HTW.nodeStorage[0]->conditionAboveNode,expectedResult[0]);
    EXPECT_EQ(HTW.nodeStorage[0]->conditionBelowNode,expectedResult[1]);
    EXPECT_EQ(HTW.nodeStorage[0]->conditionToTheLeftOfTheNode,expectedResult[2]);
    EXPECT_EQ(HTW.nodeStorage[0]->conditionToTheRightOfTheNode,expectedResult[3]);
}

TEST(IdentifyNeighborNodes, WhenNodeStorageVectorHasASizeOfZero_ExpectFalseNodeToPreventVectorFromCausingAnError)
{
    HeatTransferWorld HTW;
    std::array <int,4> expectedResult{NOT_INITIALIZED,NOT_INITIALIZED,NOT_INITIALIZED,NOT_INITIALIZED};
    int nodeIndex{0};
    HTW.numberOfNodes = 5;

    HTW.identify_neighbor_nodes(nodeIndex, HTW.numberOfNodes);

    test_neighbor_results(HTW, expectedResult);

    delete_all_heat_transfer_nodes(HTW,HTW.numberOfNodes);
}



TEST(IdentifyNeighborNodes, WhenNodeHasOneNeighborOnTheLeft_ExpectCorrectNeighbor)
{
    HeatTransferWorld HTW;
    HTW.set_deltaX_and_deltaY(1.0);
    HTW.numberOfNodes = 5;
    std::array <double,5> xCoordinateOfEachNode{0.0,-1.0,0.0,0.0,0.0};
    std::array <double,5> yCoordinateOfEachNode{0.0,0.0,0.0,0.0,0.0};
    std::array <int,4> expectedResult{NOT_INITIALIZED,NOT_INITIALIZED,NEIGHBOR_NODE,NOT_INITIALIZED};
    int nodeIndex{0};

    create_new_heat_transfer_nodes(HTW, HTW.numberOfNodes);
    set_xCoordinate_of_each_node(HTW, xCoordinateOfEachNode, HTW.numberOfNodes);
    set_yCoordinate_of_each_node(HTW, yCoordinateOfEachNode, HTW.numberOfNodes);

    HTW.identify_neighbor_nodes(nodeIndex, HTW.numberOfNodes);

    test_neighbor_results(HTW, expectedResult);

    delete_all_heat_transfer_nodes(HTW,HTW.numberOfNodes);
}

TEST(IdentifyNeighborNodes, WhenNodeHasThreeNeighbors_ExpectThreeCorrectNeighbors)
{
    HeatTransferWorld HTW;
    HTW.set_deltaX_and_deltaY(1.0);
    HTW.numberOfNodes = 5;
    std::array <double,5> xCoordinateOfEachNode{0.0,1.0,0.0,5.0,0.0};
    std::array <double,5> yCoordinateOfEachNode{0.0,0.0,1.0,0.0,-1.0};
    std::array <int,4> expectedResult{NEIGHBOR_NODE,NEIGHBOR_NODE,NOT_INITIALIZED,NEIGHBOR_NODE};
    int nodeIndex{0};

    create_new_heat_transfer_nodes(HTW, HTW.numberOfNodes);
    set_xCoordinate_of_each_node(HTW, xCoordinateOfEachNode, HTW.numberOfNodes);
    set_yCoordinate_of_each_node(HTW, yCoordinateOfEachNode, HTW.numberOfNodes);

    HTW.identify_neighbor_nodes(nodeIndex, HTW.numberOfNodes);

    test_neighbor_results(HTW, expectedResult);

    delete_all_heat_transfer_nodes(HTW,HTW.numberOfNodes);
}

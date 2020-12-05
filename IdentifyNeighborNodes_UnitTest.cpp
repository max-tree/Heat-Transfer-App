#include "gtest/gtest.h"
#include "HeatTransferNode.h"
#include "HeatTransferWorld.h"
#include <iostream>

//bool is_a_neighbor_on_top(HeatTransferNode* node1, HeatTransferNode* node2)
//{

//}

void create_new_heat_transfer_nodes(HeatTransferWorld HTW, int numberOfNodes)
{
    for(int index=0;index<numberOfNodes;index++)
    {
        HeatTransferNode* newNode = new HeatTransferNode;
        newNode->nodeIdNum = index;
        HTW.nodeStorage.push_back(newNode);
    }
}

void set_xCoordinates_of_nodes(HeatTransferWorld HTW, std::array <double, 5> distancesBetweenNodes, int numberOfNodes)
{
    for(int index{0};index<numberOfNodes;index++)
    {
        HTW.nodeStorage[index]->xCoordinate = distancesBetweenNodes[index];
    }
}


void HeatTransferWorld::identify_neighbor_nodes(int nodeIndex, int numberOfNodes)
{
    double placeholder{0.0};
    if(nodeStorage.size() == 0)
    {
        for(int index=0;index<numberOfNodes;index++)
        {
            HeatTransferNode* falseNode = new HeatTransferNode;
            nodeStorage.push_back(falseNode);
        }
        return;
    }

    for(int index{0};index<numberOfNodes;index++)
    {
       placeholder = calculate_distance_between_two_nodes(nodeStorage[nodeIndex],nodeStorage[index]);
       if(placeholder == get_deltaX())
       {
            nodeStorage[index]->conditionAboveNode = NEIGHBOR_NODE;
//           if(is_a_neighbor_on_top(nodeStorage[nodeIndex],nodeStorage[index]))
       }
       else{}
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
    int numberOfNodes{5};

    HTW.identify_neighbor_nodes(nodeIndex, numberOfNodes);
    test_neighbor_results(HTW, expectedResult);
    delete_all_heat_transfer_nodes(HTW,numberOfNodes);
}



TEST(IdentifyNeighborNodes, WhenNodeHasOneNeighbor_ExpectCorrectNeighbor)
{
    HeatTransferWorld HTW;
    HTW.set_deltaX_and_deltaY(1.0);
    int numberOfNodes{5};
    std::array <double,5> xCoordinateOfEachNode{0.0,1.0,0.0,0.0,0.0};

    create_new_heat_transfer_nodes(HTW, numberOfNodes);
    set_xCoordinates_of_nodes(HTW, xCoordinateOfEachNode, numberOfNodes);

    std::array <int,4> expectedResult{NEIGHBOR_NODE,NOT_INITIALIZED,NOT_INITIALIZED,NOT_INITIALIZED};
    int nodeIndex{0};
    HTW.identify_neighbor_nodes(nodeIndex, numberOfNodes);
    test_neighbor_results(HTW, expectedResult);
    delete_all_heat_transfer_nodes(HTW,numberOfNodes);
}

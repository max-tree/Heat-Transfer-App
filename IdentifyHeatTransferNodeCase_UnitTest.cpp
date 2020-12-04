#include "gtest/gtest.h"
#include "HeatTransferNode.h"
#include "HeatTransferWorld.h"

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasNotBeenInitialized_ExpectNoChangeInCaseIdNum)//question for Dr. McBride: Should I put in methods of spitting out error messages? Or should I just have the function not do any changes?
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{NOT_INITIALIZED};

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeIsInterior_ExpectCorrectCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_INTERIOR_NODE};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = NEIGHBOR_NODE;
    node->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasConvectionPlaneSurfaceOnTop_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_PLANE_SURFACE_WITH_CONVECTION_ON_TOP};

    node->conditionAboveNode = CONVECTION;
    node->conditionBelowNode = NEIGHBOR_NODE;
    node->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasConvectionPlaneSurfaceOnBottom_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_PLANE_SURFACE_WITH_CONVECTION_ON_BOTTOM};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = CONVECTION;
    node->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAnInternalCornerWithConvectionOnBottomRight_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_INTERNAL_CORNER_WITH_CONVECTION_ON_BOTTOM_RIGHT};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = NEIGHBOR_NODE;
    node->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;
    node->specialConditionInternalCornerBottomRight = CONVECTION;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAdiabaticPlaneSurfaceOnTheRight_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_ADIABATIC_PLANE_SURFACE_ON_THE_RIGHT};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = NEIGHBOR_NODE;
    node->conditionToTheRightOfTheNode = ADIABAT;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAdiabaticPlaneSurfaceOnTheLeft_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = NEIGHBOR_NODE;
    node->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
    node->conditionToTheLeftOfTheNode = ADIABAT;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAdiabaticPlaneSurfaceOnTheBottom_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_ADIABATIC_PLANE_SURFACE_ON_THE_BOTTOM};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = ADIABAT;
    node->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAdiabatOnTheBottomAndTheLeft_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_ADIABAT_ON_LEFT_AND_BOTTOM};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = ADIABAT;
    node->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
    node->conditionToTheLeftOfTheNode = ADIABAT;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAdiabatOnTheBottomAndConvectionOnTheRight_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_ADIABAT_ON_BOTTOM_AND_CONVECTION_ON_RIGHT};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = ADIABAT;
    node->conditionToTheRightOfTheNode = CONVECTION;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAdiabatOnTheRightAndConvectionOnTheBottom_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_BOTTOM};

    node->conditionAboveNode = NEIGHBOR_NODE;
    node->conditionBelowNode = CONVECTION;
    node->conditionToTheRightOfTheNode = ADIABAT;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAdiabatOnTheRightAndConvectionOnTheTop_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_TOP};

    node->conditionAboveNode = CONVECTION;
    node->conditionBelowNode = NEIGHBOR_NODE;
    node->conditionToTheRightOfTheNode = ADIABAT;
    node->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

TEST(IdentifyHeatTransferNodeCase, WhenNodeHasAdiabatOnTheLeftAndConvectionOnTheTop_ExpectCorrectChangeInCaseIdNum)
{
    HeatTransferNode* node = new HeatTransferNode;
    int expectedResult{CASE_ADIABAT_ON_LEFT_AND_CONVECTION_ON_TOP};

    node->conditionAboveNode = CONVECTION;
    node->conditionBelowNode = NEIGHBOR_NODE;
    node->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
    node->conditionToTheLeftOfTheNode = ADIABAT;

    identify_heat_transfer_node_case_id(node);
    EXPECT_EQ(expectedResult, node->nodeCaseIdNum);

    delete node;
}

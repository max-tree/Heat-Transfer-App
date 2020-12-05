#include "HeatTransferWorld.h"
#include "HeatTransferNode.h"

void HeatTransferWorld::get_node_equation(int nodeCaseIdNum)
{
    std::array <double,6> coefficients{0.0,0.0,0.0,0.0,0.0,0.0};
    switch (nodeCaseIdNum)
    {
    case CASE_INTERIOR_NODE:
        coefficients = {-4.0,1.0,1.0,1.0,1.0,0.0};
        set_coefficients(coefficients);
        break;
    case CASE_PLANE_SURFACE_WITH_CONVECTION_ON_TOP:
        coefficients = {-(2*h*deltaX)/k - 4.0,0.0,2.0,1.0,1.0,-(2.0*h*deltaX*freeStreamTemp)/k};
        set_coefficients(coefficients);
        break;
    case CASE_PLANE_SURFACE_WITH_CONVECTION_ON_BOTTOM:
        coefficients = {-(2.0*h*deltaX)/k - 4.0,2.0,0.0,1.0,1.0,-(2*h*deltaX*freeStreamTemp)/k};
        set_coefficients(coefficients);
        break;
    case CASE_INTERNAL_CORNER_WITH_CONVECTION_ON_BOTTOM_RIGHT:
        coefficients = {-(2.0*h*deltaX)/k - 6.0,2.0,1.0,2.0,1.0,-(2*h*deltaX*freeStreamTemp)/k};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABATIC_PLANE_SURFACE_ON_THE_RIGHT:
        coefficients = {-4.0,1.0,1.0,2.0,0.0,0.0};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT:
        coefficients = {-4.0,1.0,1.0,0.0,2.0,0.0};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABATIC_PLANE_SURFACE_ON_THE_BOTTOM:
        coefficients = {-4.0,2.0,0.0,1.0,1.0,0.0};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABAT_ON_LEFT_AND_BOTTOM:
        coefficients = {-2.0,1.0,0.0,0.0,1.0,0.0};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABAT_ON_BOTTOM_AND_CONVECTION_ON_RIGHT:
        coefficients = {-2.0-h*deltaX/k,1.0,0.0,1.0,0.0,-h*deltaX*freeStreamTemp/k};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_BOTTOM:
        coefficients = {-2.0-h*deltaX/k,1.0,0.0,1.0,0.0,-h*deltaX*freeStreamTemp/k};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_TOP:
        coefficients = {-2.0-h*deltaX/k,0.0,1.0,1.0,0.0,-h*deltaX*freeStreamTemp/k};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABAT_ON_LEFT_AND_CONVECTION_ON_TOP:
        coefficients = {-2.0-h*deltaX/k,0.0,1.0,0.0,1.0,-h*deltaX*freeStreamTemp/k};
        set_coefficients(coefficients);
        break;
    default:
        return;
    }
}

void delete_all_heat_transfer_nodes(HeatTransferWorld &HTW, int numberOfNodes)
{
    for(int index=0;index<numberOfNodes;index++)
    {
        delete HTW.nodeStorage[index];
    }
}

void create_new_heat_transfer_nodes(HeatTransferWorld &HTW, int numberOfNodes)
{
    for(int index{0};index<numberOfNodes;index++)
    {
        HeatTransferNode* newNode = new HeatTransferNode;
        newNode->nodeIdNum = index;
        HTW.nodeStorage.push_back(newNode);
    }
}

bool is_a_neighbor_on_top(HeatTransferNode* node1, HeatTransferNode* node2)
{
    if(node2->yCoordinate - node1->yCoordinate == 1)
        return true;
    else
        return false;
}

bool is_a_neighbor_on_bottom(HeatTransferNode* node1, HeatTransferNode* node2)
{
    if(node1->yCoordinate - node2->yCoordinate == 1)
        return true;
    else
        return false;
}

bool is_a_neighbor_on_the_right(HeatTransferNode* node1, HeatTransferNode* node2)
{
    if(node2->xCoordinate - node1->xCoordinate == 1)
        return true;
    else
        return false;
}

bool is_a_neighbor_on_the_left(HeatTransferNode* node1, HeatTransferNode* node2)
{
    if(node1->xCoordinate - node2->xCoordinate == 1)
        return true;
    else
        return false;
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
           if(is_a_neighbor_on_top(nodeStorage[nodeIndex],nodeStorage[index]))
               nodeStorage[nodeIndex]->conditionAboveNode = NEIGHBOR_NODE;
           else if(is_a_neighbor_on_bottom(nodeStorage[nodeIndex],nodeStorage[index]))
               nodeStorage[nodeIndex]->conditionBelowNode = NEIGHBOR_NODE;
           else if(is_a_neighbor_on_the_right(nodeStorage[nodeIndex],nodeStorage[index]))
               nodeStorage[nodeIndex]->conditionToTheRightOfTheNode = NEIGHBOR_NODE;
           else if(is_a_neighbor_on_the_left(nodeStorage[nodeIndex],nodeStorage[index]))
               nodeStorage[nodeIndex]->conditionToTheLeftOfTheNode = NEIGHBOR_NODE;
           else{}
       }
       else{}
    }
}

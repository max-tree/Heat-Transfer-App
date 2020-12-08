#include "HeatTransferWorld.h"
#include "HeatTransferNode.h"

HeatTransferWorld::~HeatTransferWorld()
{
    for(int index=0;index<numberOfNodes;index++)
    {
        delete nodeStorage[index];
    }
}

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
        coefficients = {-(2*hTop*deltaX)/k - 4.0,0.0,2.0,1.0,1.0,-(2.0*hTop*deltaX*freeStreamTemp)/k};
        set_coefficients(coefficients);
        break;
    case CASE_PLANE_SURFACE_WITH_CONVECTION_ON_BOTTOM:
        coefficients = {-(2.0*hBottom*deltaX)/k - 4.0,2.0,0.0,1.0,1.0,-(2*hBottom*deltaX*freeStreamTemp)/k};
        set_coefficients(coefficients);
        break;
    case CASE_INTERNAL_CORNER_WITH_CONVECTION_ON_BOTTOM_RIGHT:
        coefficients = {-(2.0*hBottom*deltaX)/k - 6.0,2.0,1.0,2.0,1.0,-(2*hBottom*deltaX*freeStreamTemp)/k};
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
        coefficients = {-2.0-hBottom*deltaX/k,1.0,0.0,1.0,0.0,-hBottom*deltaX*freeStreamTemp/k};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_BOTTOM:
        coefficients = {-2.0-hBottom*deltaX/k,1.0,0.0,1.0,0.0,-hBottom*deltaX*freeStreamTemp/k};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_TOP:
        coefficients = {-2.0-hTop*deltaX/k,0.0,1.0,1.0,0.0,-hTop*deltaX*freeStreamTemp/k};
        set_coefficients(coefficients);
        break;
    case CASE_ADIABAT_ON_LEFT_AND_CONVECTION_ON_TOP:
        coefficients = {-2.0-hTop*deltaX/k,0.0,1.0,0.0,1.0,-hTop*deltaX*freeStreamTemp/k};
        set_coefficients(coefficients);
        break;
    default:
        return;
    }
}

void HeatTransferWorld::create_new_heat_transfer_nodes(int numberOfPoints, vtkSmartPointer<vtkPoints> points)
{
    for(int index=0;index<numberOfPoints;index++)
    {
        double pt[3];
        HeatTransferNode* newNode = new HeatTransferNode;
        newNode->nodeIdNum = index;
        points->GetPoint(index,pt);

        set_x_and_y_coordinates(newNode, pt[0], pt[1]);
        nodeXCoordinates.push_back(pt[0]);
        nodeYCoordinates.push_back(pt[1]);

        nodeStorage.push_back(newNode);
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

void HeatTransferWorld::identities_specific_to_the_turbine_blade_mesh(int index)
{
    if(nodeStorage[index]->conditionAboveNode !=1)
    {
        nodeStorage[index]->conditionAboveNode = CONVECTION;
    }
    if(nodeStorage[index]->conditionBelowNode != 1 && index <18)
    {
        nodeStorage[index]->conditionBelowNode = CONVECTION;
    }
    else
    {
        nodeStorage[index]->conditionBelowNode = ADIABAT;
    }
    if(nodeStorage[index]->conditionToTheLeftOfTheNode !=1)
    {
        nodeStorage[index]->conditionToTheLeftOfTheNode = ADIABAT;
    }
    if(nodeStorage[index]->conditionToTheRightOfTheNode != 1 && index != 20)
    {
        nodeStorage[index]->conditionToTheRightOfTheNode = ADIABAT;
    }
    else
    {
        nodeStorage[index]->conditionToTheRightOfTheNode = CONVECTION;
    }
}

void HeatTransferWorld::identify_all_node_neighbors()
{
    for(int index{0};index<nodeStorage.size();index++)
    {
        identify_neighbor_nodes(index, nodeStorage.size());
        identities_specific_to_the_turbine_blade_mesh(index);
    }
}

#include "HeatTransferNode.h"

bool is_an_interior_node(HeatTransferNode* node)
{
    if(node->conditionAboveNode == NEIGHBOR_NODE &&
            node->conditionBelowNode == NEIGHBOR_NODE &&
            node->conditionToTheRightOfTheNode == NEIGHBOR_NODE &&
            node->conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_an_adiabatic_plane_surface_on_the_left(HeatTransferNode* node)
{
    if(node->conditionAboveNode == NEIGHBOR_NODE &&
            node->conditionBelowNode == NEIGHBOR_NODE &&
            node->conditionToTheRightOfTheNode == NEIGHBOR_NODE &&
            node->conditionToTheLeftOfTheNode == ADIABAT)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_an_adiabatic_plane_surface_on_the_right(HeatTransferNode* node)
{
    if(node->conditionAboveNode == NEIGHBOR_NODE &&
            node->conditionBelowNode == NEIGHBOR_NODE &&
            node->conditionToTheRightOfTheNode == ADIABAT &&
            node->conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_a_plane_surface_with_convection_on_the_bottom(HeatTransferNode* node)
{
    if(node->conditionAboveNode == NEIGHBOR_NODE &&
            node->conditionBelowNode == CONVECTION &&
            node->conditionToTheRightOfTheNode == NEIGHBOR_NODE &&
            node->conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_an_adiabat_on_the_right_and_convection_on_the_bottom(HeatTransferNode* node)
{
    if(node->conditionAboveNode == NEIGHBOR_NODE &&
            node->conditionBelowNode == CONVECTION &&
            node->conditionToTheRightOfTheNode == ADIABAT &&
            node->conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_an_adiabatic_plane_surface_on_the_bottom(HeatTransferNode* node)
{
    if(node->conditionAboveNode == NEIGHBOR_NODE &&
            node->conditionBelowNode == ADIABAT &&
            node->conditionToTheRightOfTheNode == NEIGHBOR_NODE &&
            node->conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_an_adiabat_on_the_bottom_and_convection_on_the_right(HeatTransferNode* node)
{
    if(node->conditionAboveNode == NEIGHBOR_NODE &&
            node->conditionBelowNode == ADIABAT &&
            node->conditionToTheRightOfTheNode == CONVECTION &&
            node->conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_an_adiabat_on_the_left_and_bottom(HeatTransferNode* node)
{
    if(node->conditionAboveNode == NEIGHBOR_NODE &&
            node->conditionBelowNode == ADIABAT &&
            node->conditionToTheRightOfTheNode == NEIGHBOR_NODE &&
            node->conditionToTheLeftOfTheNode == ADIABAT)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_an_adiabat_on_the_left_and_convection_on_top(HeatTransferNode* node)
{
    if(node->conditionAboveNode == CONVECTION &&
            node->conditionBelowNode == NEIGHBOR_NODE &&
            node->conditionToTheRightOfTheNode == NEIGHBOR_NODE &&
            node->conditionToTheLeftOfTheNode == ADIABAT)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_an_adiabat_on_the_right_and_convection_on_the_top(HeatTransferNode* node)
{
    if(node->conditionAboveNode == CONVECTION &&
            node->conditionBelowNode == NEIGHBOR_NODE &&
            node->conditionToTheRightOfTheNode == ADIABAT &&
            node->conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void identify_heat_transfer_node_case_id(HeatTransferNode* node)
{
    if(node->specialConditionInternalCornerBottomRight != NOT_INITIALIZED)
        node->nodeCaseIdNum = CASE_INTERNAL_CORNER_WITH_CONVECTION_ON_BOTTOM_RIGHT;

    else if(is_an_interior_node(node))
        node->nodeCaseIdNum = CASE_INTERIOR_NODE;

    else if (has_an_adiabatic_plane_surface_on_the_left(node))
        node->nodeCaseIdNum = CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT;

    else if (has_an_adiabatic_plane_surface_on_the_right(node))
        node->nodeCaseIdNum = CASE_ADIABATIC_PLANE_SURFACE_ON_THE_RIGHT;

    else if (has_a_plane_surface_with_convection_on_the_bottom(node))
        node->nodeCaseIdNum = CASE_PLANE_SURFACE_WITH_CONVECTION_ON_BOTTOM;

    else if(has_an_adiabat_on_the_right_and_convection_on_the_bottom(node))
        node->nodeCaseIdNum = CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_BOTTOM;

    else if (has_an_adiabatic_plane_surface_on_the_bottom(node))
        node->nodeCaseIdNum = CASE_ADIABATIC_PLANE_SURFACE_ON_THE_BOTTOM;
    else if (has_an_adiabat_on_the_bottom_and_convection_on_the_right(node))
        node->nodeCaseIdNum = CASE_ADIABAT_ON_BOTTOM_AND_CONVECTION_ON_RIGHT;

    else if (has_an_adiabat_on_the_left_and_bottom(node))
        node->nodeCaseIdNum = CASE_ADIABAT_ON_LEFT_AND_BOTTOM;

    else if (has_an_adiabat_on_the_left_and_convection_on_top(node))
        node->nodeCaseIdNum = CASE_ADIABAT_ON_LEFT_AND_CONVECTION_ON_TOP;

    else if (has_an_adiabat_on_the_right_and_convection_on_the_top(node))
        node->nodeCaseIdNum = CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_TOP;
}

void set_x_and_y_coordinates(HeatTransferNode* node, double xCoordinate, double yCoordinate)
{
    node->xCoordinate = xCoordinate;
    node->yCoordinate = yCoordinate;
}

double calculate_distance_between_two_nodes(HeatTransferNode* node1, HeatTransferNode* node2)
{
    double distance{0.0};
    distance = sqrt(pow(node1->xCoordinate-node2->xCoordinate,2) + pow(node1->yCoordinate-node2->yCoordinate,2));
    return distance;
}

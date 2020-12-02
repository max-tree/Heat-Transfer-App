#include "HeatTransferNode.h"

void identify_heat_transfer_node_case_id(HeatTransferNode &node)
{
    if(node.specialConditionInternalCornerBottomRight == NOT_INITIALIZED)
    {


        if(node.conditionAboveNode == NEIGHBOR_NODE)
        {
            if(node.conditionBelowNode == NEIGHBOR_NODE)
            {
                if(node.conditionToTheRightOfTheNode == NEIGHBOR_NODE)
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_INTERIOR_NODE;
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {
                        node.nodeCaseIdNum = CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT;
                    }
                }
                else if (node.conditionToTheRightOfTheNode == CONVECTION)
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_INTERIOR_NODE;
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {
                        node.nodeCaseIdNum = CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT;
                    }
                }
                else
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_ADIABATIC_PLANE_SURFACE_ON_THE_RIGHT;
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {
                        node.nodeCaseIdNum = CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT;
                    }
                }
            }
            else if(node.conditionBelowNode == CONVECTION)
            {
                if(node.conditionToTheRightOfTheNode == NEIGHBOR_NODE)
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_PLANE_SURFACE_WITH_CONVECTION_ON_BOTTOM;
                    }
                }
                else if (node.conditionToTheRightOfTheNode == CONVECTION)
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {

                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {

                    }
                }
                else
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_BOTTOM;
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {
                    }
                }
            }
            else
            {
                if(node.conditionToTheRightOfTheNode == NEIGHBOR_NODE)
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_ADIABATIC_PLANE_SURFACE_ON_THE_BOTTOM;
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {
                        node.nodeCaseIdNum = CASE_ADIABAT_ON_LEFT_AND_BOTTOM;
                    }
                }
                else if (node.conditionToTheRightOfTheNode == CONVECTION)
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_ADIABAT_ON_BOTTOM_AND_CONVECTION_ON_RIGHT;
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {

                    }
                }
                else
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {
                    }
                }
            }
        }
        else if(node.conditionAboveNode == CONVECTION)
        {
            if(node.conditionBelowNode == NEIGHBOR_NODE)
            {
                if(node.conditionToTheRightOfTheNode == NEIGHBOR_NODE)
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_PLANE_SURFACE_WITH_CONVECTION_ON_TOP;
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {
                        node.nodeCaseIdNum = CASE_ADIABAT_ON_LEFT_AND_CONVECTION_ON_TOP;
                    }
                }
                else if (node.conditionToTheRightOfTheNode == CONVECTION)
                {

                }
                else
                {
                    if(node.conditionToTheLeftOfTheNode == NEIGHBOR_NODE)
                    {
                        node.nodeCaseIdNum = CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_TOP;
                    }
                    else if(node.conditionToTheLeftOfTheNode == CONVECTION)
                    {

                    }
                    else
                    {

                    }
                }
            }
        }
        else
        {

        }
    }
    else{
        node.nodeCaseIdNum = CASE_INTERNAL_CORNER_WITH_CONVECTION_ON_BOTTOM_RIGHT;
    }
}

#ifndef NODEINFO_H
#define NODEINFO_H

#include "HeatTransferWorld.h"

#define NOT_INITIALIZED -1
#define NEIGHBOR_NODE 1
#define ADIABAT 2
#define CONVECTION 3

struct HeatTransferNode
{
//    HeatTransferNode* node{nullptr};

    int nodeIdNum{NOT_INITIALIZED};
    int nodeCaseIdNum{NOT_INITIALIZED};

    int conditionAboveNode{NOT_INITIALIZED};
    int conditionBelowNode{NOT_INITIALIZED};
    int conditionToTheRightOfTheNode{NOT_INITIALIZED};
    int conditionToTheLeftOfTheNode{NOT_INITIALIZED};

    int specialConditionInternalCornerBottomRight{NOT_INITIALIZED};

    double xCoordinate{0.0};
    double yCoordinate{0.0};
};

void identify_heat_transfer_node_case_id(HeatTransferNode* node);//might need the & to save changes.
void set_x_and_y_coordinates(HeatTransferNode* node, double xCoordinate, double yCoordinate);
double calculate_distance_between_two_nodes(HeatTransferNode* node1, HeatTransferNode* node2);

bool is_an_interior_node(HeatTransferNode* node);
bool has_an_adiabatic_plane_surface_on_the_left(HeatTransferNode* node);
bool has_an_adiabatic_plane_surface_on_the_right(HeatTransferNode* node);
bool has_a_plane_surface_with_convection_on_the_bottom(HeatTransferNode* node);
bool has_an_adiabat_on_the_right_and_convection_on_the_bottom(HeatTransferNode* node);
bool has_an_adiabatic_plane_surface_on_the_bottom(HeatTransferNode* node);
bool has_an_adiabat_on_the_bottom_and_convection_on_the_right(HeatTransferNode* node);
bool has_an_adiabat_on_the_left_and_bottom(HeatTransferNode* node);
bool has_an_adiabat_on_the_left_and_convection_on_top(HeatTransferNode* node);
bool has_an_adiabat_on_the_right_and_convection_on_the_top(HeatTransferNode* node);
bool has_a_plane_surface_with_convection_on_the_top(HeatTransferNode* node);

#endif // NODEINFO_H

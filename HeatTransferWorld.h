#ifndef HEATTRANSFERWORLD_H
#define HEATTRANSFERWORLD_H

#include "HeatTransferNode.h"
#include <vector>
#include <iostream>
#include <array>

#define NODE_ABOVE 0
#define NODE_TO_THE_LEFT 1
#define NODE_TO_THE_RIGHT 2
#define NODE_BELOW 3
#define NODE_INNER 4
#define NODE_CONVECTION 5

#define CASE_INTERIOR_NODE 0
#define CASE_PLANE_SURFACE_WITH_CONVECTION_ON_TOP 1
#define CASE_PLANE_SURFACE_WITH_CONVECTION_ON_BOTTOM 2
#define CASE_INTERNAL_CORNER_WITH_CONVECTION_ON_BOTTOM_RIGHT 3
#define CASE_ADIABATIC_PLANE_SURFACE_ON_THE_RIGHT 4
#define CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT 5
#define CASE_ADIABATIC_PLANE_SURFACE_ON_THE_BOTTOM 6
#define CASE_ADIABAT_ON_LEFT_AND_BOTTOM 7
#define CASE_ADIABAT_ON_BOTTOM_AND_CONVECTION_ON_RIGHT 8
#define CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_BOTTOM 9
#define CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_TOP 10
#define CASE_ADIABAT_ON_LEFT_AND_CONVECTION_ON_TOP 11

class HeatTransferWorld
{
public:
    HeatTransferWorld(){}
    ~HeatTransferWorld(){}
    std::array <double,6> get_node_equation_coefficients();
    std::vector <HeatTransferNode*> nodeStorage;
    void get_node_equation(int nodeCaseIdNum);
    void set_convection_coefficient(double hNew);
    double get_convection_coefficient();
    double get_deltaX();
    double get_deltaY();
    double get_thermal_conductivity();
    void set_thermal_conductivity(double kNew);
    double get_free_stream_temperature();
    void set_free_stream_temperature(double freeStreamTempNew);
    void set_deltaX_and_deltaY(double newDeltaX);

private:
    std::array <double,6> nodeEquationCoefficients{0.0,0.0,0.0,0.0,0.0,0.0};
    double h{0.0};
    double deltaX{1.0};
    double deltaY{deltaX};
    double k{0.0};
    double freeStreamTemp{0.0};
};

#endif // HEATTRANSFERWORLD_H

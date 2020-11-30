#ifndef HEATTRANSFERWORLD_H
#define HEATTRANSFERWORLD_H
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

class HeatTransferWorld
{
public:
    HeatTransferWorld(){}
    ~HeatTransferWorld(){}
    std::array <double,6> get_node_equation_coefficients();
    void get_node_equation(int nodeIndexNum);
    void set_convection_coefficient(double hNew);
    double get_convection_coefficient();
    double get_deltaX();
    double get_deltaY();
    double get_thermal_conductivity();
    void set_thermal_conductivity(double kNew);
    double get_free_stream_temperature();
    void set_free_stream_temperature(double freeStreamTempNew);
private:
    std::array <double,6> nodeValues{0.0,0.0,0.0,0.0,0.0,0.0};
    double h{0.0};
    double deltaX{1.0};
    double deltaY{deltaX};
    double k{0.0};
    double freeStreamTemp{0.0};
};

#endif // HEATTRANSFERWORLD_H

#include "HeatTransferWorld.h"

std::array <double,6> HeatTransferWorld::get_node_equation_coefficients()
{
    return nodeValues;
}

void HeatTransferWorld::set_convection_coefficient(double hNew)
{
    h = hNew;
}

double HeatTransferWorld::get_convection_coefficient()
{
    return h;
}

double HeatTransferWorld::get_deltaX()
{
    return deltaX;
}
double HeatTransferWorld::get_deltaY()
{
    return deltaY;
}

double HeatTransferWorld::get_thermal_conductivity()
{
    return k;
}
void HeatTransferWorld::set_thermal_conductivity(double kNew)
{
    k = kNew;
}

double HeatTransferWorld::get_free_stream_temperature()
{
    return freeStreamTemp;
}
void HeatTransferWorld::set_free_stream_temperature(double freeStreamTempNew)
{
    freeStreamTemp = freeStreamTempNew;
}


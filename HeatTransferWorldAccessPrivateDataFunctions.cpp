#include "HeatTransferWorld.h"
#include "HeatTransferNode.h"

std::array <double,6> HeatTransferWorld::get_node_equation_coefficients()
{
    return nodeEquationCoefficients;
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

void HeatTransferWorld::set_coefficients(std::array <double,6> coefficients)
{
    nodeEquationCoefficients[NODE_INNER] = coefficients[0];
    nodeEquationCoefficients[NODE_ABOVE] = coefficients[1];
    nodeEquationCoefficients[NODE_BELOW] = coefficients[2];
    nodeEquationCoefficients[NODE_TO_THE_LEFT] = coefficients[3];
    nodeEquationCoefficients[NODE_TO_THE_RIGHT] = coefficients[4];
    nodeEquationCoefficients[NODE_CONVECTION] = coefficients[5];
}

void HeatTransferWorld::set_deltaX_and_deltaY(double newDeltaX)
{
    deltaX = newDeltaX;
    deltaY = deltaX;
}

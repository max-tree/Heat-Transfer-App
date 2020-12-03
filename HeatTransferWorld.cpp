#include "HeatTransferWorld.h"

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

void HeatTransferWorld::get_node_equation(int nodeCaseIdNum)
{
    switch (nodeCaseIdNum)
    {
    case CASE_INTERIOR_NODE:
        nodeEquationCoefficients[NODE_INNER] = -4.0;
        nodeEquationCoefficients[NODE_ABOVE] = 1.0;
        nodeEquationCoefficients[NODE_BELOW] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 1.0;
        nodeEquationCoefficients[NODE_CONVECTION] = 0.0;
        break;
    case CASE_PLANE_SURFACE_WITH_CONVECTION_ON_TOP:
        nodeEquationCoefficients[NODE_INNER] = -(2*h*deltaX)/k - 4.0;
        nodeEquationCoefficients[NODE_ABOVE] = 0.0;
        nodeEquationCoefficients[NODE_BELOW] = 2.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 1.0;
        nodeEquationCoefficients[NODE_CONVECTION] = -(2.0*h*deltaX*freeStreamTemp)/k;
        break;
    case CASE_PLANE_SURFACE_WITH_CONVECTION_ON_BOTTOM:
        nodeEquationCoefficients[NODE_INNER] = -(2.0*h*deltaX)/k - 4.0;
        nodeEquationCoefficients[NODE_ABOVE] = 2.0;
        nodeEquationCoefficients[NODE_BELOW] = 0.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 1.0;
        nodeEquationCoefficients[NODE_CONVECTION] = -(2*h*deltaX*freeStreamTemp)/k;
        break;
    case CASE_INTERNAL_CORNER_WITH_CONVECTION_ON_BOTTOM_RIGHT:
        nodeEquationCoefficients[NODE_INNER] = -(2.0*h*deltaX)/k - 6.0;
        nodeEquationCoefficients[NODE_ABOVE] = 2.0;
        nodeEquationCoefficients[NODE_BELOW] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 2.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 1.0;
        nodeEquationCoefficients[NODE_CONVECTION] = -(2*h*deltaX*freeStreamTemp)/k;
        break;
    case CASE_ADIABATIC_PLANE_SURFACE_ON_THE_RIGHT:
        nodeEquationCoefficients[NODE_INNER] = -4.0;
        nodeEquationCoefficients[NODE_ABOVE] = 1.0;
        nodeEquationCoefficients[NODE_BELOW] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 2.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 0.0;
        nodeEquationCoefficients[NODE_CONVECTION] = 0.0;
        break;
    case CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT:
        nodeEquationCoefficients[NODE_INNER] = -4.0;
        nodeEquationCoefficients[NODE_ABOVE] = 1.0;
        nodeEquationCoefficients[NODE_BELOW] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 0.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 2.0;
        nodeEquationCoefficients[NODE_CONVECTION] = 0.0;
        break;
    case CASE_ADIABATIC_PLANE_SURFACE_ON_THE_BOTTOM:
        nodeEquationCoefficients[NODE_INNER] = -4.0;
        nodeEquationCoefficients[NODE_ABOVE] = 2.0;
        nodeEquationCoefficients[NODE_BELOW] = 0.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 1.0;
        nodeEquationCoefficients[NODE_CONVECTION] = 0.0;
        break;
    case CASE_ADIABAT_ON_LEFT_AND_BOTTOM:
        nodeEquationCoefficients[NODE_INNER] = -2.0;
        nodeEquationCoefficients[NODE_ABOVE] = 1.0;
        nodeEquationCoefficients[NODE_BELOW] = 0.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 0.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 1.0;
        nodeEquationCoefficients[NODE_CONVECTION] = 0.0;
        break;
    case CASE_ADIABAT_ON_BOTTOM_AND_CONVECTION_ON_RIGHT:
        nodeEquationCoefficients[NODE_INNER] = -2.0-h*deltaX/k;
        nodeEquationCoefficients[NODE_ABOVE] = 1.0;
        nodeEquationCoefficients[NODE_BELOW] = 0.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 0.0;
        nodeEquationCoefficients[NODE_CONVECTION] = -h*deltaX*freeStreamTemp/k;
        break;
    case CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_BOTTOM:
        nodeEquationCoefficients[NODE_INNER] = -2.0-h*deltaX/k;
        nodeEquationCoefficients[NODE_ABOVE] = 1.0;
        nodeEquationCoefficients[NODE_BELOW] = 0.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 0.0;
        nodeEquationCoefficients[NODE_CONVECTION] = -h*deltaX*freeStreamTemp/k;
        break;
    case CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_TOP:
        nodeEquationCoefficients[NODE_INNER] = -2.0-h*deltaX/k;
        nodeEquationCoefficients[NODE_ABOVE] = 0.0;
        nodeEquationCoefficients[NODE_BELOW] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 0.0;
        nodeEquationCoefficients[NODE_CONVECTION] = -h*deltaX*freeStreamTemp/k;
        break;
    case CASE_ADIABAT_ON_LEFT_AND_CONVECTION_ON_TOP:
        nodeEquationCoefficients[NODE_INNER] = -2.0-h*deltaX/k;
        nodeEquationCoefficients[NODE_ABOVE] = 0.0;
        nodeEquationCoefficients[NODE_BELOW] = 1.0;
        nodeEquationCoefficients[NODE_TO_THE_LEFT] = 0.0;
        nodeEquationCoefficients[NODE_TO_THE_RIGHT] = 1.0;
        nodeEquationCoefficients[NODE_CONVECTION] = -h*deltaX*freeStreamTemp/k;
        break;
    default:
        std::cout << '\n' << "ERROR" << '\n';
    }
}

void HeatTransferWorld::set_deltaX_and_deltaY(double newDeltaX)
{
    deltaX = newDeltaX;
    deltaY = deltaX;
}



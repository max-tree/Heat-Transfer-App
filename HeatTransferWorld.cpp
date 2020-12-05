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

void HeatTransferWorld::set_coefficients(std::array <double,6> coefficients)
{
    nodeEquationCoefficients[NODE_INNER] = coefficients[0];
    nodeEquationCoefficients[NODE_ABOVE] = coefficients[1];
    nodeEquationCoefficients[NODE_BELOW] = coefficients[2];
    nodeEquationCoefficients[NODE_TO_THE_LEFT] = coefficients[3];
    nodeEquationCoefficients[NODE_TO_THE_RIGHT] = coefficients[4];
    nodeEquationCoefficients[NODE_CONVECTION] = coefficients[5];
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

void HeatTransferWorld::set_deltaX_and_deltaY(double newDeltaX)
{
    deltaX = newDeltaX;
    deltaY = deltaX;
}



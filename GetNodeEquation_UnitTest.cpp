#include "HeatTransferWorld.h"
#include "gtest/gtest.h"

void test_all_nodes(std::array <double,6> expectedResult, std::array <double,6> result)
{
    double tolerance{0.001};

    EXPECT_NEAR(expectedResult[NODE_ABOVE],result[NODE_ABOVE], tolerance);
    EXPECT_NEAR(expectedResult[NODE_TO_THE_LEFT],result[NODE_TO_THE_LEFT], tolerance);
    EXPECT_NEAR(expectedResult[NODE_TO_THE_RIGHT],result[NODE_TO_THE_RIGHT], tolerance);
    EXPECT_NEAR(expectedResult[NODE_BELOW],result[NODE_BELOW], tolerance);
    EXPECT_NEAR(expectedResult[NODE_INNER],result[NODE_INNER], tolerance);
    EXPECT_NEAR(expectedResult[NODE_CONVECTION],result[NODE_CONVECTION], tolerance);
}

void set_trivial_heat_transfer_values(HeatTransferWorld& HTW)
{
    HTW.set_top_convection_coefficient(1.0);
    HTW.set_bottom_convection_coefficient(1.0);
    HTW.set_thermal_conductivity(1.0);
    HTW.set_free_stream_temperature(1.0);
}

TEST(GetNodeEquation, WhenNodeIsAnInteriorNode_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -4.0;
    expectedResult[NODE_ABOVE] = 1.0;
    expectedResult[NODE_BELOW] = 1.0;
    expectedResult[NODE_TO_THE_LEFT] = 1.0;
    expectedResult[NODE_TO_THE_RIGHT] = 1.0;
    expectedResult[NODE_CONVECTION] = 0.0;

    HTW.get_node_equation(CASE_INTERIOR_NODE);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeAtAPlaneSurfaceWithConvectionOnTheTop_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -6.0;
    expectedResult[NODE_ABOVE] = 0.0;
    expectedResult[NODE_BELOW] = 2.0;
    expectedResult[NODE_TO_THE_LEFT] = 1.0;
    expectedResult[NODE_TO_THE_RIGHT] = 1.0;
    expectedResult[NODE_CONVECTION] = -2.0;

    HTW.get_node_equation(CASE_PLANE_SURFACE_WITH_CONVECTION_ON_TOP);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeAtAPlaneSurfaceWithConvectionOnTheBottom_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -6.0;
    expectedResult[NODE_ABOVE] = 2.0;
    expectedResult[NODE_BELOW] = 0.0;
    expectedResult[NODE_TO_THE_LEFT] = 1.0;
    expectedResult[NODE_TO_THE_RIGHT] = 1.0;
    expectedResult[NODE_CONVECTION] = -2.0;

    HTW.get_node_equation(CASE_PLANE_SURFACE_WITH_CONVECTION_ON_BOTTOM);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeAtAnInternalCornerWithConvectionOnTheBottomRight_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -8.0;
    expectedResult[NODE_ABOVE] = 2.0;
    expectedResult[NODE_BELOW] = 1.0;
    expectedResult[NODE_TO_THE_LEFT] = 2.0;
    expectedResult[NODE_TO_THE_RIGHT] = 1.0;
    expectedResult[NODE_CONVECTION] = -2.0;

    HTW.get_node_equation(CASE_INTERNAL_CORNER_WITH_CONVECTION_ON_BOTTOM_RIGHT);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeAtAnAdiabatOnTheRight_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -4.0;
    expectedResult[NODE_ABOVE] = 1.0;
    expectedResult[NODE_BELOW] = 1.0;
    expectedResult[NODE_TO_THE_LEFT] = 2.0;
    expectedResult[NODE_TO_THE_RIGHT] = 0.0;
    expectedResult[NODE_CONVECTION] = 0.0;

    HTW.get_node_equation(CASE_ADIABATIC_PLANE_SURFACE_ON_THE_RIGHT);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeAtAnAdiabatOnTheLeft_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -4.0;
    expectedResult[NODE_ABOVE] = 1.0;
    expectedResult[NODE_BELOW] = 1.0;
    expectedResult[NODE_TO_THE_LEFT] = 0.0;
    expectedResult[NODE_TO_THE_RIGHT] = 2.0;
    expectedResult[NODE_CONVECTION] = 0.0;

    HTW.get_node_equation(CASE_ADIABATIC_PLANE_SURFACE_ON_THE_LEFT);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeAtAnAdiabatOnTheBottom_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -4.0;
    expectedResult[NODE_ABOVE] = 2.0;
    expectedResult[NODE_BELOW] = 0.0;
    expectedResult[NODE_TO_THE_LEFT] = 1.0;
    expectedResult[NODE_TO_THE_RIGHT] = 1.0;
    expectedResult[NODE_CONVECTION] = 0.0;

    HTW.get_node_equation(CASE_ADIABATIC_PLANE_SURFACE_ON_THE_BOTTOM);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeWithAnAdiabatOnTheLeftAndTheBottom_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -2.0;
    expectedResult[NODE_ABOVE] = 1.0;
    expectedResult[NODE_BELOW] = 0.0;
    expectedResult[NODE_TO_THE_LEFT] = 0.0;
    expectedResult[NODE_TO_THE_RIGHT] = 1.0;
    expectedResult[NODE_CONVECTION] = 0.0;

    HTW.get_node_equation(CASE_ADIABAT_ON_LEFT_AND_BOTTOM);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeWithAnAdiabatOnTheBottomAndConvectionToTheRight_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -3.0;
    expectedResult[NODE_ABOVE] = 1.0;
    expectedResult[NODE_BELOW] = 0.0;
    expectedResult[NODE_TO_THE_LEFT] = 1.0;
    expectedResult[NODE_TO_THE_RIGHT] = 0.0;
    expectedResult[NODE_CONVECTION] = -1.0;

    HTW.get_node_equation(CASE_ADIABAT_ON_BOTTOM_AND_CONVECTION_ON_RIGHT);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeWithAnAdiabatOnTheRightAndConvectionOnTheBottom_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -3.0;
    expectedResult[NODE_ABOVE] = 1.0;
    expectedResult[NODE_BELOW] = 0.0;
    expectedResult[NODE_TO_THE_LEFT] = 1.0;
    expectedResult[NODE_TO_THE_RIGHT] = 0.0;
    expectedResult[NODE_CONVECTION] = -1.0;

    HTW.get_node_equation(CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_BOTTOM);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeWithAnAdiabatOnTheRightAndConvectionOnTheTop_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -3.0;
    expectedResult[NODE_ABOVE] = 0.0;
    expectedResult[NODE_BELOW] = 1.0;
    expectedResult[NODE_TO_THE_LEFT] = 1.0;
    expectedResult[NODE_TO_THE_RIGHT] = 0.0;
    expectedResult[NODE_CONVECTION] = -1.0;

    HTW.get_node_equation(CASE_ADIABAT_ON_RIGHT_AND_CONVECTION_ON_TOP);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

TEST(GetNodeEquation, WhenNodeIsANodeWithAnAdiabatOnTheLeftAndConvectionOnTheTop_ExpectCorrectCoefficients)
{
    std::array <double,6> result{0.0,0.0,0.0,0.0,0.0,0.0};
    HeatTransferWorld HTW;

    set_trivial_heat_transfer_values(HTW);

    std::array <double,6> expectedResult{0.0,0.0,0.0,0.0,0.0,0.0};
    expectedResult[NODE_INNER] = -3.0;
    expectedResult[NODE_ABOVE] = 0.0;
    expectedResult[NODE_BELOW] = 1.0;
    expectedResult[NODE_TO_THE_LEFT] = 0.0;
    expectedResult[NODE_TO_THE_RIGHT] = 1.0;
    expectedResult[NODE_CONVECTION] = -1.0;

    HTW.get_node_equation(CASE_ADIABAT_ON_LEFT_AND_CONVECTION_ON_TOP);
    result = HTW.get_node_equation_coefficients();

    test_all_nodes(expectedResult, result);
}

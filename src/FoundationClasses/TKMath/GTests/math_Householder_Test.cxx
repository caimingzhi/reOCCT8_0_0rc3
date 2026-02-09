

#include <math_Householder.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>
#include <Standard_OutOfRange.hpp>
#include <Precision.hpp>

namespace
{

  TEST(MathHouseholderTest, ExactlyDeterminedSystem)
  {

    math_Matrix aA(1, 3, 1, 3);
    aA(1, 1) = 1.0;
    aA(1, 2) = 2.0;
    aA(1, 3) = 3.0;
    aA(2, 1) = 4.0;
    aA(2, 2) = 5.0;
    aA(2, 3) = 6.0;
    aA(3, 1) = 7.0;
    aA(3, 2) = 8.0;
    aA(3, 3) = 10.0;

    math_Vector aB(1, 3);
    aB(1) = 14.0;
    aB(2) = 32.0;
    aB(3) = 55.0;

    math_Householder aHouseholder(aA, aB);
    EXPECT_TRUE(aHouseholder.IsDone()) << "Householder should succeed for well-conditioned system";

    math_Vector aSol(1, 3);
    aHouseholder.Value(aSol, 1);

    math_Vector aVerify(1, 3);
    for (int i = 1; i <= 3; i++)
    {
      aVerify(i) = 0.0;
      for (int j = 1; j <= 3; j++)
      {
        aVerify(i) += aA(i, j) * aSol(j);
      }
    }

    EXPECT_NEAR(aVerify(1), aB(1), 1.0e-10) << "Solution verification A*x=b (1)";
    EXPECT_NEAR(aVerify(2), aB(2), 1.0e-10) << "Solution verification A*x=b (2)";
    EXPECT_NEAR(aVerify(3), aB(3), 1.0e-10) << "Solution verification A*x=b (3)";
  }

  TEST(MathHouseholderTest, OverdeterminedSystem)
  {

    math_Matrix aA(1, 4, 1, 2);
    aA(1, 1) = 1.0;
    aA(1, 2) = 1.0;
    aA(2, 1) = 1.0;
    aA(2, 2) = 2.0;
    aA(3, 1) = 2.0;
    aA(3, 2) = 1.0;
    aA(4, 1) = 1.0;
    aA(4, 2) = 3.0;

    math_Vector aB(1, 4);
    aB(1) = 2.0;
    aB(2) = 3.0;
    aB(3) = 3.0;
    aB(4) = 4.0;

    math_Householder aHouseholder(aA, aB);
    EXPECT_TRUE(aHouseholder.IsDone()) << "Householder should succeed for overdetermined system";

    math_Vector aSol(1, 2);
    aHouseholder.Value(aSol, 1);

    EXPECT_NEAR(aSol(1), 1.0, 1.0e-6) << "Least squares solution X(1)";
    EXPECT_NEAR(aSol(2), 1.0, 1.0e-6) << "Least squares solution X(2)";
  }

  TEST(MathHouseholderTest, MultipleRightHandSides)
  {

    math_Matrix aA(1, 3, 1, 2);
    aA(1, 1) = 1.0;
    aA(1, 2) = 0.0;
    aA(2, 1) = 0.0;
    aA(2, 2) = 1.0;
    aA(3, 1) = 1.0;
    aA(3, 2) = 1.0;

    math_Matrix aB(1, 3, 1, 2);
    aB(1, 1) = 1.0;
    aB(1, 2) = 2.0;
    aB(2, 1) = 3.0;
    aB(2, 2) = 4.0;
    aB(3, 1) = 4.0;
    aB(3, 2) = 6.0;

    math_Householder aHouseholder(aA, aB);
    EXPECT_TRUE(aHouseholder.IsDone()) << "Householder should succeed for multiple RHS";

    math_Vector aSol1(1, 2);
    aHouseholder.Value(aSol1, 1);

    math_Vector aSol2(1, 2);
    aHouseholder.Value(aSol2, 2);

    EXPECT_NEAR(aSol1(1), 1.0, 1.0e-6) << "First solution X(1)";
    EXPECT_NEAR(aSol1(2), 3.0, 1.0e-6) << "First solution X(2)";

    EXPECT_NEAR(aSol2(1), 2.0, 1.0e-6) << "Second solution X(1)";
    EXPECT_NEAR(aSol2(2), 4.0, 1.0e-6) << "Second solution X(2)";
  }

  TEST(MathHouseholderTest, NearSingularMatrix)
  {

    math_Matrix aA(1, 3, 1, 3);
    aA(1, 1) = 1.0;
    aA(1, 2) = 2.0;
    aA(1, 3) = 3.0;
    aA(2, 1) = 2.0;
    aA(2, 2) = 4.0;
    aA(2, 3) = 6.0 + 1.0e-15;
    aA(3, 1) = 3.0;
    aA(3, 2) = 6.0;
    aA(3, 3) = 9.0 + 2.0e-15;

    math_Vector aB(1, 3);
    aB(1) = 1.0;
    aB(2) = 2.0;
    aB(3) = 3.0;

    math_Householder aHouseholder(aA, aB);

    EXPECT_FALSE(aHouseholder.IsDone()) << "Should fail for near-singular matrix with default EPS";
  }

  TEST(MathHouseholderTest, CustomEpsilon)
  {

    math_Matrix aA(1, 2, 1, 2);
    aA(1, 1) = 1.0e-3;
    aA(1, 2) = 1.0;
    aA(2, 1) = 2.0e-3;
    aA(2, 2) = 2.0;

    math_Vector aB(1, 2);
    aB(1) = 1.0;
    aB(2) = 2.0;

    math_Householder aHouseholder1(aA, aB);
    EXPECT_TRUE(aHouseholder1.IsDone()) << "Should succeed with default EPS";

    math_Householder aHouseholder2(aA, aB, 1.0e-2);
    EXPECT_FALSE(aHouseholder2.IsDone()) << "Should fail with very restrictive EPS";
  }

  TEST(MathHouseholderTest, IdentityMatrix)
  {

    math_Matrix aA(1, 3, 1, 3);
    aA(1, 1) = 1.0;
    aA(1, 2) = 0.0;
    aA(1, 3) = 0.0;
    aA(2, 1) = 0.0;
    aA(2, 2) = 1.0;
    aA(2, 3) = 0.0;
    aA(3, 1) = 0.0;
    aA(3, 2) = 0.0;
    aA(3, 3) = 1.0;

    math_Vector aB(1, 3);
    aB(1) = 5.0;
    aB(2) = 7.0;
    aB(3) = 9.0;

    math_Householder aHouseholder(aA, aB);
    EXPECT_TRUE(aHouseholder.IsDone()) << "Householder should succeed for identity matrix";

    math_Vector aSol(1, 3);
    aHouseholder.Value(aSol, 1);

    EXPECT_NEAR(aSol(1), 5.0, Precision::Confusion()) << "Identity matrix solution X(1)";
    EXPECT_NEAR(aSol(2), 7.0, Precision::Confusion()) << "Identity matrix solution X(2)";
    EXPECT_NEAR(aSol(3), 9.0, Precision::Confusion()) << "Identity matrix solution X(3)";
  }

  TEST(MathHouseholderTest, DimensionCompatibility)
  {

    math_Matrix aA(1, 3, 1, 2);
    aA(1, 1) = 1.0;
    aA(1, 2) = 2.0;
    aA(2, 1) = 3.0;
    aA(2, 2) = 4.0;
    aA(3, 1) = 5.0;
    aA(3, 2) = 6.0;

    math_Vector aB_correct(1, 3);
    aB_correct(1) = 1.0;
    aB_correct(2) = 2.0;
    aB_correct(3) = 3.0;

    math_Householder aHouseholder1(aA, aB_correct);
    EXPECT_TRUE(aHouseholder1.IsDone()) << "Should work with correct B vector size";

    math_Matrix aB_matrix_correct(1, 3, 1, 2);
    aB_matrix_correct(1, 1) = 1.0;
    aB_matrix_correct(1, 2) = 4.0;
    aB_matrix_correct(2, 1) = 2.0;
    aB_matrix_correct(2, 2) = 5.0;
    aB_matrix_correct(3, 1) = 3.0;
    aB_matrix_correct(3, 2) = 6.0;

    math_Householder aHouseholder2(aA, aB_matrix_correct);
    EXPECT_TRUE(aHouseholder2.IsDone()) << "Should work with correct B matrix size";
  }

  TEST(MathHouseholderTest, NearZeroMatrixState)
  {

    math_Matrix aA(1, 2, 1, 2);
    aA(1, 1) = 1.0e-25;
    aA(1, 2) = 0.0;
    aA(2, 1) = 0.0;
    aA(2, 2) = 1.0e-25;

    math_Vector aB(1, 2);
    aB(1) = 1.0;
    aB(2) = 2.0;

    math_Householder aHouseholder(aA, aB, 1.0e-10);
    EXPECT_FALSE(aHouseholder.IsDone()) << "Should fail for nearly zero matrix";
  }

  TEST(MathHouseholderTest, ValidIndexRange)
  {

    math_Matrix aA(1, 2, 1, 2);
    aA(1, 1) = 1.0;
    aA(1, 2) = 0.0;
    aA(2, 1) = 0.0;
    aA(2, 2) = 1.0;

    math_Matrix aB(1, 2, 1, 2);
    aB(1, 1) = 1.0;
    aB(1, 2) = 2.0;
    aB(2, 1) = 3.0;
    aB(2, 2) = 4.0;

    math_Householder aHouseholder(aA, aB);
    EXPECT_TRUE(aHouseholder.IsDone());

    math_Vector aSol(1, 2);

    aHouseholder.Value(aSol, 1);
    EXPECT_EQ(aSol.Length(), 2) << "Solution vector should have correct size";

    aHouseholder.Value(aSol, 2);
    EXPECT_EQ(aSol.Length(), 2) << "Solution vector should have correct size";

    EXPECT_EQ(aB.ColNumber(), 2) << "Matrix should have 2 columns available";
  }

  TEST(MathHouseholderTest, RegressionTest)
  {

    math_Matrix aA(1, 3, 1, 2);
    aA(1, 1) = 2.0;
    aA(1, 2) = 1.0;
    aA(2, 1) = 1.0;
    aA(2, 2) = 1.0;
    aA(3, 1) = 1.0;
    aA(3, 2) = 2.0;

    math_Vector aB(1, 3);
    aB(1) = 5.0;
    aB(2) = 3.0;
    aB(3) = 4.0;

    math_Householder aHouseholder(aA, aB);
    EXPECT_TRUE(aHouseholder.IsDone()) << "Regression test should succeed";

    math_Vector aSol(1, 2);
    aHouseholder.Value(aSol, 1);

    EXPECT_NEAR(aSol(1), 2.0, 1.0e-10) << "Regression solution X(1)";
    EXPECT_NEAR(aSol(2), 1.0, 1.0e-10) << "Regression solution X(2)";
  }

} // namespace

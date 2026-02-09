

#include <GeomFill_CorrectedFrenet.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <BRepAdaptor_CompCurve.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <GC_MakeSegment.hpp>
#include <ShapeExtend_WireData.hpp>
#include <TopoDS_Edge.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>

#include <gtest/gtest.h>

TEST(GeomFill_CorrectedFrenet, EndlessLoopPrevention)
{
  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0.0, 0.0, 0.0);
  aPoles(2) = gp_Pnt(1.0, 0.0, 0.0);
  aPoles(3) = gp_Pnt(1.0, 1.0, 0.0);
  aPoles(4) = gp_Pnt(0.0, 1.0, 0.0);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  occ::handle<Geom_BSplineCurve> aCurve    = new Geom_BSplineCurve(aPoles, aKnots, aMults, 3);
  occ::handle<GeomAdaptor_Curve> anAdaptor = new GeomAdaptor_Curve(aCurve);

  GeomFill_CorrectedFrenet aCorrectedFrenet(false);
  aCorrectedFrenet.SetCurve(anAdaptor);

  double aParam1 = 0.0;
  double aParam2 = 1.0;

  gp_Vec aTangent1, aNormal1, aBinormal1;
  gp_Vec aTangent2, aNormal2, aBinormal2;

  EXPECT_NO_THROW({
    aCorrectedFrenet.D0(aParam1, aTangent1, aNormal1, aBinormal1);
    aCorrectedFrenet.D0(aParam2, aTangent2, aNormal2, aBinormal2);
  });

  EXPECT_GT(aTangent1.Magnitude(), 1e-10);
  EXPECT_GT(aNormal1.Magnitude(), 1e-10);
  EXPECT_GT(aBinormal1.Magnitude(), 1e-10);

  EXPECT_GT(aTangent2.Magnitude(), 1e-10);
  EXPECT_GT(aNormal2.Magnitude(), 1e-10);
  EXPECT_GT(aBinormal2.Magnitude(), 1e-10);
}

TEST(GeomFill_CorrectedFrenet, SmallStepHandling)
{
  NCollection_Array1<gp_Pnt> aPoles(1, 2);
  aPoles(1) = gp_Pnt(0.0, 0.0, 0.0);
  aPoles(2) = gp_Pnt(1e-10, 0.0, 0.0);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 2;
  aMults(2) = 2;

  occ::handle<Geom_BSplineCurve> aCurve    = new Geom_BSplineCurve(aPoles, aKnots, aMults, 1);
  occ::handle<GeomAdaptor_Curve> anAdaptor = new GeomAdaptor_Curve(aCurve);

  GeomFill_CorrectedFrenet aCorrectedFrenet(false);
  aCorrectedFrenet.SetCurve(anAdaptor);

  gp_Vec aTangent, aNormal, aBinormal;

  EXPECT_NO_THROW({ aCorrectedFrenet.D0(0.5, aTangent, aNormal, aBinormal); });
}

TEST(GeomFill_CorrectedFrenet, ParameterProgressionGuarantee)
{
  NCollection_Array1<gp_Pnt> aPoles(1, 3);
  aPoles(1) = gp_Pnt(0.0, 0.0, 0.0);
  aPoles(2) = gp_Pnt(0.5, 0.5, 0.0);
  aPoles(3) = gp_Pnt(1.0, 0.0, 0.0);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 3;
  aMults(2) = 3;

  occ::handle<Geom_BSplineCurve> aCurve    = new Geom_BSplineCurve(aPoles, aKnots, aMults, 2);
  occ::handle<GeomAdaptor_Curve> anAdaptor = new GeomAdaptor_Curve(aCurve);

  GeomFill_CorrectedFrenet aCorrectedFrenet(false);
  aCorrectedFrenet.SetCurve(anAdaptor);

  for (double aParam = 0.1; aParam <= 0.9; aParam += 0.1)
  {
    gp_Vec aTangent, aNormal, aBinormal;

    EXPECT_NO_THROW({ aCorrectedFrenet.D0(aParam, aTangent, aNormal, aBinormal); });

    EXPECT_GT(aTangent.Magnitude(), 1e-12);
    EXPECT_GT(aNormal.Magnitude(), 1e-12);
    EXPECT_GT(aBinormal.Magnitude(), 1e-12);
  }
}

TEST(GeomFill_CorrectedFrenet, ActualReproducerCase)
{
  NCollection_Array1<gp_Pnt> aPoints(1, 4);
  aPoints(1) = gp_Pnt(-1, -1, 0);
  aPoints(2) = gp_Pnt(0, -2, 0);
  aPoints(3) = gp_Pnt(0, -2, -1);
  aPoints(4) = gp_Pnt(0, -1, -1);

  ShapeExtend_WireData anExtend;
  for (int i = 2; i <= aPoints.Length(); i++)
  {
    occ::handle<Geom_Curve> aCurve = GC_MakeSegment(aPoints(i - 1), aPoints(i)).Value();
    TopoDS_Edge             anEdge = BRepBuilderAPI_MakeEdge(aCurve).Edge();
    anExtend.Add(anEdge);
  }

  BRepAdaptor_CompCurve anAdaptor(anExtend.WireAPIMake());

  GeomFill_CorrectedFrenet aCorrectedFrenet(false);

  EXPECT_NO_THROW({ aCorrectedFrenet.SetCurve(anAdaptor.ShallowCopy()); });

  gp_Vec aTangent, aNormal, aBinormal;

  EXPECT_NO_THROW({ aCorrectedFrenet.D0(0.0, aTangent, aNormal, aBinormal); });

  EXPECT_NO_THROW({ aCorrectedFrenet.D0(0.5, aTangent, aNormal, aBinormal); });

  EXPECT_NO_THROW({ aCorrectedFrenet.D0(1.0, aTangent, aNormal, aBinormal); });
}

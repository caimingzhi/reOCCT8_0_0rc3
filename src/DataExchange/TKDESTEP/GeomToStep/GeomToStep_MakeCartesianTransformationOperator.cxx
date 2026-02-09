

#include <GeomToStep_MakeCartesianTransformationOperator.hpp>

#include <GeomToStep_MakeCartesianPoint.hpp>
#include <GeomToStep_MakeDirection.hpp>
#include <gp_Trsf.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>

GeomToStep_MakeCartesianTransformationOperator::GeomToStep_MakeCartesianTransformationOperator(
  const gp_Trsf&          theTrsf,
  const StepData_Factors& theLocalFactors)
{
  gp_Trsf anInvTrsf = theTrsf;
  anInvTrsf.Invert();
  double aScale   = anInvTrsf.ScaleFactor();
  gp_Mat anInvMat = anInvTrsf.HVectorialPart();

  gp_Mat aMat         = theTrsf.HVectorialPart();
  gp_XYZ aTranslation = anInvTrsf.TranslationPart().Multiplied(aMat);
  aTranslation.Reverse();

  GeomToStep_MakeCartesianPoint aMkPoint(aTranslation, theLocalFactors.LengthFactor());
  GeomToStep_MakeDirection      aMkDir1(anInvMat.Row(1));
  GeomToStep_MakeDirection      aMkDir2(anInvMat.Row(2));
  GeomToStep_MakeDirection      aMkDir3(anInvMat.Row(3));

  myTrsfOp = new StepGeom_CartesianTransformationOperator3d();
  myTrsfOp->SetName(new TCollection_HAsciiString(""));
  myTrsfOp->SetAxis1(aMkDir1.Value());
  myTrsfOp->SetAxis2(aMkDir2.Value());
  myTrsfOp->SetAxis3(aMkDir3.Value());
  myTrsfOp->SetLocalOrigin(aMkPoint.Value());
  myTrsfOp->SetScale(aScale);

  done = true;
}

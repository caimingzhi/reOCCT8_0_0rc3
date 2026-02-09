

#include <RWMesh_CoordinateSystemConverter.hpp>

#include <gp_Quaternion.hpp>

RWMesh_CoordinateSystemConverter::RWMesh_CoordinateSystemConverter()
    : myInputLengthUnit(-1.0),
      myOutputLengthUnit(-1.0),
      myHasInputAx3(false),
      myHasOutputAx3(false),

      myUnitFactor(1),
      myHasScale(false),
      myIsEmpty(true)
{
}

void RWMesh_CoordinateSystemConverter::Init(const gp_Ax3& theInputSystem,
                                            double        theInputLengthUnit,
                                            const gp_Ax3& theOutputSystem,
                                            double        theOutputLengthUnit)
{
  myInputLengthUnit  = theInputLengthUnit;
  myOutputLengthUnit = theOutputLengthUnit;
  myInputAx3         = theInputSystem;
  myOutputAx3        = theOutputSystem;
  if (theInputLengthUnit > 0.0 && theOutputLengthUnit > 0.0)
  {
    myUnitFactor = theInputLengthUnit / theOutputLengthUnit;
    myHasScale   = std::abs(myUnitFactor - 1.0) > gp::Resolution();
  }
  else
  {
    myUnitFactor = 1.0;
    myHasScale   = false;
  }

  gp_Trsf aTrsf;
  if (myHasInputAx3 && myHasOutputAx3)
  {
    aTrsf.SetTransformation(theOutputSystem, theInputSystem);
    if (aTrsf.TranslationPart().IsEqual(gp_XYZ(0.0, 0.0, 0.0), gp::Resolution())
        && aTrsf.GetRotation().IsEqual(gp_Quaternion()))
    {
      aTrsf = gp_Trsf();
    }
  }

  myTrsf    = aTrsf;
  myTrsfInv = aTrsf.Inverted();
  myTrsf.GetMat4(myNormTrsf);
  myIsEmpty = !myHasScale && myTrsf.Form() == gp_Identity;
}

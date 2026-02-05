#include <HLRAlgo_PolyShellData.hpp>

#include <HLRAlgo_BiPoint.hpp>
#include <NCollection_List.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HLRAlgo_PolyShellData, Standard_Transient)

//=================================================================================================

HLRAlgo_PolyShellData::HLRAlgo_PolyShellData(const int nbFace)
    : myPolyg(1, nbFace)
{
}

//=================================================================================================

void HLRAlgo_PolyShellData::UpdateGlobalMinMax(Bnd_Box& theBox)
{
  for (NCollection_List<HLRAlgo_BiPoint>::Iterator it(mySegList); it.More(); it.Next())
  {
    const HLRAlgo_BiPoint::PointsT& aPoints = it.Value().Points();
    theBox.Update(aPoints.PntP1.X(), aPoints.PntP1.Y(), aPoints.PntP1.Z());
    theBox.Update(aPoints.PntP2.X(), aPoints.PntP2.Y(), aPoints.PntP2.Z());
  }
  for (int i = myPolyg.Lower(); i <= myPolyg.Upper(); i++)
  {
    const occ::handle<HLRAlgo_PolyData>& aPd = myPolyg.ChangeValue(i);
    aPd->UpdateGlobalMinMax(theBox);
  }
}

//=================================================================================================

void HLRAlgo_PolyShellData::UpdateHiding(const int nbHiding)
{
  if (nbHiding > 0)
  {
    myHPolHi.Resize(1, nbHiding, false);
  }
  else
  {
    NCollection_Array1<occ::handle<HLRAlgo_PolyData>> anEmpty;
    myHPolHi.Move(anEmpty);
  }
}

#include <BRepMesh_ConeRangeSplitter.hpp>

#include <GCPnts_TangentialDeflection.hpp>
#include <IMeshTools_Parameters.hpp>

std::pair<double, double> BRepMesh_ConeRangeSplitter::GetSplitSteps(
  const IMeshTools_Parameters& theParameters,
  std::pair<int, int>&         theStepsNb) const
{
  const std::pair<double, double>& aRangeU = GetRangeU();
  const std::pair<double, double>& aRangeV = GetRangeV();

  gp_Cone aCone   = GetDFace()->GetSurface()->Cone();
  double  aRefR   = aCone.RefRadius();
  double  aSAng   = aCone.SemiAngle();
  double  aRadius = std::max(std::abs(aRefR + aRangeV.first * std::sin(aSAng)),
                            std::abs(aRefR + aRangeV.second * std::sin(aSAng)));

  double Dv, Du = GCPnts_TangentialDeflection::ArcAngularStep(aRadius,
                                                              GetDFace()->GetDeflection(),
                                                              theParameters.Angle,
                                                              theParameters.MinSize);

  const double aDiffU = aRangeU.second - aRangeU.first;
  const double aDiffV = aRangeV.second - aRangeV.first;
  const double aScale = (Du * aRadius);
  const double aRatio = std::max(1., std::log(aDiffV / aScale));
  const int    nbU    = (int)(aDiffU / Du);
  const int    nbV    = (int)(aDiffV / aScale / aRatio);

  Du = aDiffU / (nbU + 1);
  Dv = aDiffV / (nbV + static_cast<int>(aRatio));

  theStepsNb.first  = nbU;
  theStepsNb.second = nbV;
  return std::make_pair(Du, Dv);
}

Handle(IMeshData::ListOfPnt2d) BRepMesh_ConeRangeSplitter::GenerateSurfaceNodes(
  const IMeshTools_Parameters& theParameters) const
{
  const std::pair<double, double>& aRangeU = GetRangeU();
  const std::pair<double, double>& aRangeV = GetRangeV();

  std::pair<int, int>       aStepsNb;
  std::pair<double, double> aSteps = GetSplitSteps(theParameters, aStepsNb);

  const occ::handle<NCollection_IncAllocator> aTmpAlloc =
    new NCollection_IncAllocator(IMeshData::MEMORY_BLOCK_SIZE_HUGE);
  Handle(IMeshData::ListOfPnt2d) aNodes = new IMeshData::ListOfPnt2d(aTmpAlloc);

  const double aPasMaxV = aRangeV.second - aSteps.second * 0.5;
  const double aPasMaxU = aRangeU.second - aSteps.first * 0.5;
  for (double aPasV = aRangeV.first + aSteps.second; aPasV < aPasMaxV; aPasV += aSteps.second)
  {
    for (double aPasU = aRangeU.first + aSteps.first; aPasU < aPasMaxU; aPasU += aSteps.first)
    {
      aNodes->Append(gp_Pnt2d(aPasU, aPasV));
    }
  }

  return aNodes;
}

#include <BRepMesh_SphereRangeSplitter.hpp>
#include <GCPnts_TangentialDeflection.hpp>

//=================================================================================================

Handle(IMeshData::ListOfPnt2d) BRepMesh_SphereRangeSplitter::GenerateSurfaceNodes(
  const IMeshTools_Parameters& theParameters) const
{
  // Calculate parameters for iteration in V direction
  double aStep =
    0.7
    * GCPnts_TangentialDeflection::ArcAngularStep(GetDFace()->GetSurface()->Sphere().Radius(),
                                                  GetDFace()->GetDeflection(),
                                                  theParameters.Angle,
                                                  theParameters.MinSize);

  const std::pair<double, double>* aRange[2] = {&GetRangeV(), &GetRangeU()};

  std::pair<double, double> aStepAndOffset[2];
  computeStep(*aRange[0], aStep, aStepAndOffset[0]);
  computeStep(*aRange[1], aStep, aStepAndOffset[1]);

  const occ::handle<NCollection_IncAllocator> aTmpAlloc =
    new NCollection_IncAllocator(IMeshData::MEMORY_BLOCK_SIZE_HUGE);
  Handle(IMeshData::ListOfPnt2d) aNodes = new IMeshData::ListOfPnt2d(aTmpAlloc);

  const double aHalfDu = aStepAndOffset[1].first * 0.5;
  bool         Shift   = false;
  double       aPasV   = aRange[0]->first + aStepAndOffset[0].first;
  for (; aPasV < aStepAndOffset[0].second; aPasV += aStepAndOffset[0].first)
  {
    Shift              = !Shift;
    const double d     = (Shift) ? aHalfDu : 0.;
    double       aPasU = aRange[1]->first + d;
    for (; aPasU < aStepAndOffset[1].second; aPasU += aStepAndOffset[1].first)
    {
      aNodes->Append(gp_Pnt2d(aPasU, aPasV));
    }
  }

  return aNodes;
}

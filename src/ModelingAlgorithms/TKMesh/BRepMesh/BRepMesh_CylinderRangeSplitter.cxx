#include <BRepMesh_CylinderRangeSplitter.hpp>

#include <GCPnts_TangentialDeflection.hpp>
#include <IMeshTools_Parameters.hpp>

void BRepMesh_CylinderRangeSplitter::Reset(const IMeshData::IFaceHandle& theDFace,
                                           const IMeshTools_Parameters&  theParameters)
{
  BRepMesh_DefaultRangeSplitter::Reset(theDFace, theParameters);

  const double aRadius = GetDFace()->GetSurface()->Cylinder().Radius();
  myDu                 = GCPnts_TangentialDeflection::ArcAngularStep(aRadius,
                                                     GetDFace()->GetDeflection(),
                                                     theParameters.Angle,
                                                     theParameters.MinSize);
}

Handle(IMeshData::ListOfPnt2d) BRepMesh_CylinderRangeSplitter::GenerateSurfaceNodes(
  const IMeshTools_Parameters&) const
{
  const std::pair<double, double>& aRangeU = GetRangeU();
  const std::pair<double, double>& aRangeV = GetRangeV();

  const double aRadius = GetDFace()->GetSurface()->Cylinder().Radius();

  int          nbU     = 0;
  int          nbV     = 0;
  const double su      = aRangeU.second - aRangeU.first;
  const double sv      = aRangeV.second - aRangeV.first;
  const double aArcLen = su * aRadius;
  if (aArcLen > GetDFace()->GetDeflection())
  {

    nbU = (int)(su / myDu);
  }

  const double Du = su / (nbU + 1);
  const double Dv = sv / (nbV + 1);

  const occ::handle<NCollection_IncAllocator> aTmpAlloc =
    new NCollection_IncAllocator(IMeshData::MEMORY_BLOCK_SIZE_HUGE);
  Handle(IMeshData::ListOfPnt2d) aNodes = new IMeshData::ListOfPnt2d(aTmpAlloc);

  const double aPasMaxV = aRangeV.second - Dv * 0.5;
  const double aPasMaxU = aRangeU.second - Du * 0.5;
  for (double aPasV = aRangeV.first + Dv; aPasV < aPasMaxV; aPasV += Dv)
  {
    for (double aPasU = aRangeU.first + Du; aPasU < aPasMaxU; aPasU += Du)
    {
      aNodes->Append(gp_Pnt2d(aPasU, aPasV));
    }
  }

  return aNodes;
}

void BRepMesh_CylinderRangeSplitter::computeDelta(const double, const double theLengthV)
{
  const std::pair<double, double>& aRangeV = GetRangeV();
  myDelta.first  = myDu / std::max(theLengthV, aRangeV.second - aRangeV.first);
  myDelta.second = 1.;
}

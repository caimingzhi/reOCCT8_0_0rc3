#include <BRep_Tool.hpp>
#include <HLRBRep_EdgeData.hpp>
#include <TopoDS_Edge.hpp>

//=================================================================================================

void HLRBRep_EdgeData::Set(const bool         Rg1L,
                           const bool         RgNL,
                           const TopoDS_Edge& EG,
                           const int          V1,
                           const int          V2,
                           const bool         Out1,
                           const bool         Out2,
                           const bool         Cut1,
                           const bool         Cut2,
                           const double       Start,
                           const float        TolStart,
                           const double       End,
                           const float        TolEnd)
{
  Rg1Line(Rg1L);
  RgNLine(RgNL);
  Used(false);
  ChangeGeometry().Curve(EG);
  myTolerance = (float)(BRep_Tool::Tolerance(EG));
  VSta(V1);
  VEnd(V2);
  OutLVSta(Out1);
  OutLVEnd(Out2);
  CutAtSta(Cut1);
  CutAtEnd(Cut2);
  Status().Initialize(Start,
                      (float)(ChangeGeometry().Curve().Resolution((double)TolStart)),
                      End,
                      (float)(ChangeGeometry().Curve().Resolution((double)TolEnd)));
}

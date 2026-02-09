#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRAlgo_Intersection.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
class HLRBRep_Data;
class gp_Dir;
class HLRAlgo_Interference;

class HLRBRep_EdgeInterferenceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_EdgeInterferenceTool(const occ::handle<HLRBRep_Data>& DS);

  Standard_EXPORT void LoadEdge();

  void InitVertices();

  bool MoreVertices() const;

  void NextVertex();

  const HLRAlgo_Intersection& CurrentVertex() const;

  TopAbs_Orientation CurrentOrientation() const;

  double CurrentParameter() const;

  bool IsPeriodic() const;

  Standard_EXPORT void EdgeGeometry(const double Param,
                                    gp_Dir&      Tgt,
                                    gp_Dir&      Nrm,
                                    double&      Curv) const;

  double ParameterOfInterference(const HLRAlgo_Interference& I) const;

  Standard_EXPORT bool SameInterferences(const HLRAlgo_Interference& I1,
                                         const HLRAlgo_Interference& I2) const;

  Standard_EXPORT bool SameVertexAndInterference(const HLRAlgo_Interference& I) const;

  Standard_EXPORT void InterferenceBoundaryGeometry(const HLRAlgo_Interference& I,
                                                    gp_Dir&                     Tang,
                                                    gp_Dir&                     Norm,
                                                    double&                     Curv) const;

private:
  occ::handle<HLRBRep_Data> myDS;
  HLRAlgo_Intersection      inter[2];
  int                       cur;
};

#include <HLRAlgo_Interference.hpp>

inline void HLRBRep_EdgeInterferenceTool::InitVertices()
{
  cur = 0;
}

inline bool HLRBRep_EdgeInterferenceTool::MoreVertices() const
{
  return cur < 2;
}

inline void HLRBRep_EdgeInterferenceTool::NextVertex()
{
  cur++;
}

inline const HLRAlgo_Intersection& HLRBRep_EdgeInterferenceTool::CurrentVertex() const
{
  return inter[cur];
}

inline TopAbs_Orientation HLRBRep_EdgeInterferenceTool::CurrentOrientation() const
{
  if (cur == 0)
    return TopAbs_FORWARD;
  else
    return TopAbs_REVERSED;
}

inline double HLRBRep_EdgeInterferenceTool::CurrentParameter() const
{
  return inter[cur].Parameter();
}

inline bool HLRBRep_EdgeInterferenceTool::IsPeriodic() const
{
  return false;
}

inline double HLRBRep_EdgeInterferenceTool::ParameterOfInterference(
  const HLRAlgo_Interference& I) const
{
  return I.Intersection().Parameter();
}

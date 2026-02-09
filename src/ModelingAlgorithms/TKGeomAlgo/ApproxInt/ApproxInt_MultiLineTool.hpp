#include TheMultiLine_hxx

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

#include <Approx_Status.hpp>

inline int ApproxInt_MultiLineTool::NbP2d(const TheMultiLine& ML)
{
  return (ML.NbP2d());
}

inline int ApproxInt_MultiLineTool::NbP3d(const TheMultiLine& ML)
{
  return (ML.NbP3d());
}

inline int ApproxInt_MultiLineTool::FirstPoint(const TheMultiLine& ML)
{
  return (ML.FirstPoint());
}

inline int ApproxInt_MultiLineTool::LastPoint(const TheMultiLine& ML)
{
  return (ML.LastPoint());
}

inline void ApproxInt_MultiLineTool::Value(const TheMultiLine&         ML,
                                           const int                   Index,
                                           NCollection_Array1<gp_Pnt>& TabPnt)
{
  ML.Value(Index, TabPnt);
}

inline void ApproxInt_MultiLineTool::Value(const TheMultiLine&           ML,
                                           const int                     Index,
                                           NCollection_Array1<gp_Pnt2d>& TabPnt2d)
{
  ML.Value(Index, TabPnt2d);
}

inline void ApproxInt_MultiLineTool::Value(const TheMultiLine&           ML,
                                           const int                     Index,
                                           NCollection_Array1<gp_Pnt>&   TabPnt,
                                           NCollection_Array1<gp_Pnt2d>& TabPnt2d)
{
  ML.Value(Index, TabPnt, TabPnt2d);
}

inline bool ApproxInt_MultiLineTool::Tangency(const TheMultiLine&         ML,
                                              const int                   Index,
                                              NCollection_Array1<gp_Vec>& TabVec)
{
  return (ML.Tangency(Index, TabVec));
}

inline bool ApproxInt_MultiLineTool::Tangency(const TheMultiLine&           ML,
                                              const int                     Index,
                                              NCollection_Array1<gp_Vec2d>& TabVec2d)
{
  return (ML.Tangency(Index, TabVec2d));
}

inline bool ApproxInt_MultiLineTool::Tangency(const TheMultiLine&           ML,
                                              const int                     Index,
                                              NCollection_Array1<gp_Vec>&   TabVec,
                                              NCollection_Array1<gp_Vec2d>& TabVec2d)
{
  return (ML.Tangency(Index, TabVec, TabVec2d));
}

inline bool ApproxInt_MultiLineTool::Curvature(const TheMultiLine&,
                                               const int,
                                               NCollection_Array1<gp_Vec>&)
{
  return false;
}

inline bool ApproxInt_MultiLineTool::Curvature(const TheMultiLine&,
                                               const int,
                                               NCollection_Array1<gp_Vec2d>&)
{
  return false;
}

inline bool ApproxInt_MultiLineTool::Curvature(const TheMultiLine&,
                                               const int,
                                               NCollection_Array1<gp_Vec>&,
                                               NCollection_Array1<gp_Vec2d>&)
{
  return false;
}

inline Approx_Status ApproxInt_MultiLineTool::WhatStatus(const TheMultiLine& ML,
                                                         const int,
                                                         const int)
{

  return (ML.WhatStatus());
}

inline TheMultiLine ApproxInt_MultiLineTool::MakeMLBetween(const TheMultiLine& ML,
                                                           const int           I1,
                                                           const int           I2,
                                                           const int           NbPMin)
{

  return (ML.MakeMLBetween(I1, I2, NbPMin));
}

inline bool ApproxInt_MultiLineTool::MakeMLOneMorePoint(const TheMultiLine& ML,
                                                        const int           I1,
                                                        const int           I2,
                                                        const int           indbad,
                                                        TheMultiLine&       OtherLine)
{
  return (ML.MakeMLOneMorePoint(I1, I2, indbad, OtherLine));
}

inline void ApproxInt_MultiLineTool::Dump(const TheMultiLine& ML)
{
  ML.Dump();
}

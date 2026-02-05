#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt2d.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>

class TopOpeBRepTool_mkTondgE
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_mkTondgE();

  Standard_EXPORT bool Initialize(const TopoDS_Edge& dgE,
                                  const TopoDS_Face& F,
                                  const gp_Pnt2d&    uvi,
                                  const TopoDS_Face& Fi);

  Standard_EXPORT bool SetclE(const TopoDS_Edge& clE);

  Standard_EXPORT bool IsT2d() const;

  Standard_EXPORT bool SetRest(const double pari, const TopoDS_Edge& Ei);

  Standard_EXPORT int GetAllRest(NCollection_List<TopoDS_Shape>& lEi);

  Standard_EXPORT bool MkTonE(int& mkT, double& par1, double& par2);

  Standard_EXPORT bool MkTonE(const TopoDS_Edge& Ei, int& mkT, double& par1, double& par2);

private:
  TopoDS_Edge                                                        mydgE;
  TopoDS_Face                                                        myF;
  TopoDS_Edge                                                        myclE;
  gp_Dir                                                             mydirINcle;
  TopoDS_Face                                                        myFi;
  gp_Pnt2d                                                           myuvi;
  bool                                                               isT2d;
  NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher> myEpari;
  bool                                                               hasRest;
  gp_Dir                                                             myngf;
  gp_Dir                                                             myngfi;
};

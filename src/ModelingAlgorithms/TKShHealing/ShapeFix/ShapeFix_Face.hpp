#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeFix_Root.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>
#include <Bnd_Box2d.hpp>
#include <ShapeExtend_Status.hpp>
class ShapeAnalysis_Surface;
class ShapeFix_Wire;
class Geom_Surface;
class ShapeExtend_BasicMsgRegistrator;
class TopoDS_Wire;
class ShapeExtend_WireData;
class TopoDS_Vertex;

#ifdef Status
  #undef Status
#endif

class ShapeFix_Face : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_Face();

  Standard_EXPORT ShapeFix_Face(const TopoDS_Face& face);

  Standard_EXPORT virtual void ClearModes();

  Standard_EXPORT void Init(const TopoDS_Face& face);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& surf,
                            const double                     preci,
                            const bool                       fwd = true);

  Standard_EXPORT void Init(const occ::handle<ShapeAnalysis_Surface>& surf,
                            const double                              preci,
                            const bool                                fwd = true);

  Standard_EXPORT void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg) override;

  Standard_EXPORT void SetPrecision(const double preci) override;

  Standard_EXPORT void SetMinTolerance(const double mintol) override;

  Standard_EXPORT void SetMaxTolerance(const double maxtol) override;

  int& FixWireMode();

  int& FixOrientationMode();

  int& FixAddNaturalBoundMode();

  int& FixMissingSeamMode();

  int& FixSmallAreaWireMode();

  int& RemoveSmallAreaFaceMode();

  int& FixIntersectingWiresMode();

  int& FixLoopWiresMode();

  int& FixSplitFaceMode();

  int& AutoCorrectPrecisionMode();

  int& FixPeriodicDegeneratedMode();

  TopoDS_Face Face() const;

  TopoDS_Shape Result() const;

  Standard_EXPORT void Add(const TopoDS_Wire& wire);

  Standard_EXPORT bool Perform();

  Standard_EXPORT bool FixOrientation();

  Standard_EXPORT bool FixOrientation(
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      MapWires);

  Standard_EXPORT bool FixAddNaturalBound();

  Standard_EXPORT bool FixMissingSeam();

  Standard_EXPORT bool FixSmallAreaWire(const bool theIsRemoveSmallFace);

  Standard_EXPORT bool FixLoopWire(NCollection_Sequence<TopoDS_Shape>& aResWires);

  Standard_EXPORT bool FixIntersectingWires();

  Standard_EXPORT bool FixWiresTwoCoincEdges();

  Standard_EXPORT bool FixSplitFace(const NCollection_DataMap<TopoDS_Shape,
                                                              NCollection_List<TopoDS_Shape>,
                                                              TopTools_ShapeMapHasher>& MapWires);

  Standard_EXPORT bool FixPeriodicDegenerated();

  bool Status(const ShapeExtend_Status status) const;

  occ::handle<ShapeFix_Wire> FixWireTool();

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Face, ShapeFix_Root)

protected:
  occ::handle<ShapeAnalysis_Surface> mySurf;
  TopoDS_Face                        myFace;
  TopoDS_Shape                       myResult;
  occ::handle<ShapeFix_Wire>         myFixWire;
  bool                               myFwd;
  int                                myStatus;

private:
  bool isNeedAddNaturalBound(const NCollection_Sequence<TopoDS_Shape>& theOrientedWires);

  Standard_EXPORT bool SplitEdge(
    const occ::handle<ShapeExtend_WireData>&                               sewd,
    const int                                                              num,
    const double                                                           param,
    const TopoDS_Vertex&                                                   vert,
    const double                                                           preci,
    NCollection_DataMap<TopoDS_Shape, Bnd_Box2d, TopTools_ShapeMapHasher>& boxes);

  Standard_EXPORT bool SplitEdge(
    const occ::handle<ShapeExtend_WireData>&                               sewd,
    const int                                                              num,
    const double                                                           param1,
    const double                                                           param2,
    const TopoDS_Vertex&                                                   vert,
    const double                                                           preci,
    NCollection_DataMap<TopoDS_Shape, Bnd_Box2d, TopTools_ShapeMapHasher>& boxes);

  int myFixWireMode;
  int myFixOrientationMode;
  int myFixAddNaturalBoundMode;
  int myFixMissingSeamMode;
  int myFixSmallAreaWireMode;
  int myRemoveSmallAreaFaceMode;
  int myFixLoopWiresMode;
  int myFixIntersectingWiresMode;
  int myFixSplitFaceMode;
  int myAutoCorrectPrecisionMode;
  int myFixPeriodicDegenerated;
};

#include <ShapeExtend.hpp>

inline int& ShapeFix_Face::FixWireMode()
{
  return myFixWireMode;
}

inline int& ShapeFix_Face::FixOrientationMode()
{
  return myFixOrientationMode;
}

inline int& ShapeFix_Face::FixAddNaturalBoundMode()
{
  return myFixAddNaturalBoundMode;
}

inline int& ShapeFix_Face::FixMissingSeamMode()
{
  return myFixMissingSeamMode;
}

inline int& ShapeFix_Face::FixSmallAreaWireMode()
{
  return myFixSmallAreaWireMode;
}

inline int& ShapeFix_Face::RemoveSmallAreaFaceMode()
{
  return myRemoveSmallAreaFaceMode;
}

inline int& ShapeFix_Face::FixIntersectingWiresMode()
{
  return myFixIntersectingWiresMode;
}

inline int& ShapeFix_Face::FixLoopWiresMode()
{
  return myFixLoopWiresMode;
}

inline int& ShapeFix_Face::FixSplitFaceMode()
{
  return myFixSplitFaceMode;
}

inline int& ShapeFix_Face::AutoCorrectPrecisionMode()
{
  return myAutoCorrectPrecisionMode;
}

inline int& ShapeFix_Face::FixPeriodicDegeneratedMode()
{
  return myFixPeriodicDegenerated;
}

inline TopoDS_Face ShapeFix_Face::Face() const
{
  return myFace;
}

inline TopoDS_Shape ShapeFix_Face::Result() const
{
  return myResult;
}

inline bool ShapeFix_Face::Status(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatus, status);
}

inline occ::handle<ShapeFix_Wire> ShapeFix_Face::FixWireTool()
{
  return myFixWire;
}

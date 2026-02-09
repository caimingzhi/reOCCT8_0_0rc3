#pragma once

#include <DBRep_Edge.hpp>
#include <NCollection_List.hpp>
#include <DBRep_Face.hpp>
#include <DBRep_HideData.hpp>
#include <Draw_Color.hpp>
#include <Draw_Drawable3D.hpp>
#include <Draw_Interpretor.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_OStream.hpp>
#include <TopoDS_Shape.hpp>

class Draw_Display;
class Poly_Triangulation;
class gp_Trsf;

class DBRep_DrawableShape : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(DBRep_DrawableShape, Draw_Drawable3D)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DBRep_DrawableShape(const TopoDS_Shape& C,
                                      const Draw_Color&   FreeCol,
                                      const Draw_Color&   ConnCol,
                                      const Draw_Color&   EdgeCol,
                                      const Draw_Color&   IsosCol,
                                      const double        size,
                                      const int           nbisos,
                                      const int           discret);

  Standard_EXPORT void ChangeNbIsos(const int NbIsos);

  Standard_EXPORT int NbIsos() const;

  Standard_EXPORT void ChangeDiscret(const int Discret);

  Standard_EXPORT int Discret() const;

  Standard_EXPORT TopoDS_Shape Shape() const;

  Standard_EXPORT void DisplayOrientation(const bool D);

  Standard_EXPORT void DisplayTriangulation(const bool D);

  Standard_EXPORT void DisplayPolygons(const bool D);

  Standard_EXPORT void DisplayHLR(const bool   withHLR,
                                  const bool   withRg1,
                                  const bool   withRgN,
                                  const bool   withHid,
                                  const double ang);

  Standard_EXPORT bool DisplayTriangulation() const;

  Standard_EXPORT bool DisplayPolygons() const;

  Standard_EXPORT void GetDisplayHLR(bool&   withHLR,
                                     bool&   withRg1,
                                     bool&   withRgN,
                                     bool&   withHid,
                                     double& ang) const;

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT void DisplayHiddenLines(Draw_Display& dis);

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Save(Standard_OStream& theStream) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  Standard_EXPORT static void LastPick(TopoDS_Shape& S, double& u, double& v);

public:
  Standard_EXPORT static bool addMeshNormals(
    NCollection_Vector<std::pair<gp_Pnt, gp_Pnt>>& theNormals,
    const TopoDS_Face&                             theFace,
    const double                                   theLength);

  Standard_EXPORT static void addMeshNormals(
    NCollection_DataMap<TopoDS_Face, NCollection_Vector<std::pair<gp_Pnt, gp_Pnt>>>& theNormals,
    const TopoDS_Shape&                                                              theShape,
    const double                                                                     theLength);

  Standard_EXPORT static bool addSurfaceNormals(
    NCollection_Vector<std::pair<gp_Pnt, gp_Pnt>>& theNormals,
    const TopoDS_Face&                             theFace,
    const double                                   theLength,
    const int                                      theNbAlongU,
    const int                                      theNbAlongV);

  Standard_EXPORT static void addSurfaceNormals(
    NCollection_DataMap<TopoDS_Face, NCollection_Vector<std::pair<gp_Pnt, gp_Pnt>>>& theNormals,
    const TopoDS_Shape&                                                              theShape,
    const double                                                                     theLength,
    const int                                                                        theNbAlongU,
    const int                                                                        theNbAlongV);

private:
  void display(const occ::handle<Poly_Triangulation>& T,
               const gp_Trsf&                         tr,
               Draw_Display&                          dis) const;

  void updateDisplayData() const;

private:
  TopoDS_Shape myShape;

  mutable NCollection_List<occ::handle<DBRep_Edge>> myEdges;
  mutable NCollection_List<occ::handle<DBRep_Face>> myFaces;
  NCollection_List<DBRep_HideData>                  myHidData;

  double     mySize;
  int        myDiscret;
  Draw_Color myFreeCol;
  Draw_Color myConnCol;
  Draw_Color myEdgeCol;
  Draw_Color myIsosCol;
  int        myNbIsos;
  bool       myDispOr;
  bool       mytriangulations;
  bool       mypolygons;
  bool       myHLR;
  bool       myRg1;
  bool       myRgN;
  bool       myHid;
  double     myAng;
};

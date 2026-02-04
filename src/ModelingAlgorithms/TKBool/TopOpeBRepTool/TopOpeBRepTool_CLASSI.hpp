#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <Bnd_Box2d.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopOpeBRepTool_face.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class Bnd_Box2d;
class TopOpeBRepTool_face;

class TopOpeBRepTool_CLASSI
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_CLASSI();

  Standard_EXPORT void Init2d(const TopoDS_Face& Fref);

  Standard_EXPORT bool HasInit2d() const;

  Standard_EXPORT bool Add2d(const TopoDS_Shape& S);

  Standard_EXPORT bool GetBox2d(const TopoDS_Shape& S, Bnd_Box2d& Box2d);

  Standard_EXPORT int ClassiBnd2d(const TopoDS_Shape& S1,
                                  const TopoDS_Shape& S2,
                                  const double        tol,
                                  const bool          checklarge);

  Standard_EXPORT int Classip2d(const TopoDS_Shape& S1,
                                const TopoDS_Shape& S2,
                                const int           stabnd2d12);

  Standard_EXPORT bool Getface(const TopoDS_Shape& S, TopOpeBRepTool_face& fa) const;

  Standard_EXPORT bool Classilist(
    const NCollection_List<TopoDS_Shape>& lS,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      mapgreasma);

private:
  TopoDS_Face                                                                     myFref;
  NCollection_IndexedDataMap<TopoDS_Shape, Bnd_Box2d>                             mymapsbox2d;
  NCollection_DataMap<TopoDS_Shape, TopOpeBRepTool_face, TopTools_ShapeMapHasher> mymapsface;
};


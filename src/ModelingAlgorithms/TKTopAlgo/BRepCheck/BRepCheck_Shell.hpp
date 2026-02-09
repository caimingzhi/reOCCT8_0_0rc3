#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <BRepCheck_Result.hpp>
class TopoDS_Shell;
class TopoDS_Shape;

class BRepCheck_Shell : public BRepCheck_Result
{

public:
  Standard_EXPORT BRepCheck_Shell(const TopoDS_Shell& S);

  Standard_EXPORT void InContext(const TopoDS_Shape& ContextShape) override;

  Standard_EXPORT void Minimum() override;

  Standard_EXPORT void Blind() override;

  Standard_EXPORT BRepCheck_Status Closed(const bool Update = false);

  Standard_EXPORT BRepCheck_Status Orientation(const bool Update = false);

  Standard_EXPORT void SetUnorientable();

  Standard_EXPORT bool IsUnorientable() const;

  Standard_EXPORT int NbConnectedSet(NCollection_List<TopoDS_Shape>& theSets);

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Shell, BRepCheck_Result)

private:
  int              myNbori;
  bool             myCdone;
  BRepCheck_Status myCstat;
  bool             myOdone;
  BRepCheck_Status myOstat;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myMapEF;
};

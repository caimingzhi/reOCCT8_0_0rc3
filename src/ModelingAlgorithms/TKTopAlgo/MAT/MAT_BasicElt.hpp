#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class MAT_Arc;

class MAT_BasicElt : public Standard_Transient
{

public:
  Standard_EXPORT MAT_BasicElt(const int anInteger);

  Standard_EXPORT occ::handle<MAT_Arc> StartArc() const;

  Standard_EXPORT occ::handle<MAT_Arc> EndArc() const;

  Standard_EXPORT int Index() const;

  Standard_EXPORT int GeomIndex() const;

  Standard_EXPORT void SetStartArc(const occ::handle<MAT_Arc>& anArc);

  Standard_EXPORT void SetEndArc(const occ::handle<MAT_Arc>& anArc);

  Standard_EXPORT void SetIndex(const int anInteger);

  Standard_EXPORT void SetGeomIndex(const int anInteger);

  DEFINE_STANDARD_RTTIEXT(MAT_BasicElt, Standard_Transient)

private:
  void* startLeftArc;
  void* endLeftArc;
  int   index;
  int   geomIndex;
};

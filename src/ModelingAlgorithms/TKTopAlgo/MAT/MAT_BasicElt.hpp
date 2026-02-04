#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class MAT_Arc;

//! A BasicELt is associated to each elementary
//! constituent of the figure.
class MAT_BasicElt : public Standard_Transient
{

public:
  //! Constructor, <anInteger> is the <index> of <me>.
  Standard_EXPORT MAT_BasicElt(const int anInteger);

  //! Return <startArcLeft> or <startArcRight> corresponding
  //! to <aSide>.
  Standard_EXPORT occ::handle<MAT_Arc> StartArc() const;

  //! Return <endArcLeft> or <endArcRight> corresponding
  //! to <aSide>.
  Standard_EXPORT occ::handle<MAT_Arc> EndArc() const;

  //! Return the <index> of <me> in Graph.TheBasicElts.
  Standard_EXPORT int Index() const;

  //! Return the <GeomIndex> of <me>.
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


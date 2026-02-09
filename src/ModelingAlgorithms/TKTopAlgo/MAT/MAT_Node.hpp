#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
#include <MAT_Arc.hpp>
#include <NCollection_Sequence.hpp>
#include <MAT_BasicElt.hpp>
class MAT_Arc;

class MAT_Node : public Standard_Transient
{

public:
  Standard_EXPORT MAT_Node(const int                   GeomIndex,
                           const occ::handle<MAT_Arc>& LinkedArc,
                           const double                Distance);

  Standard_EXPORT int GeomIndex() const;

  Standard_EXPORT int Index() const;

  Standard_EXPORT void LinkedArcs(NCollection_Sequence<occ::handle<MAT_Arc>>& S) const;

  Standard_EXPORT void NearElts(NCollection_Sequence<occ::handle<MAT_BasicElt>>& S) const;

  Standard_EXPORT double Distance() const;

  Standard_EXPORT bool PendingNode() const;

  Standard_EXPORT bool OnBasicElt() const;

  Standard_EXPORT bool Infinite() const;

  Standard_EXPORT void SetIndex(const int anIndex);

  Standard_EXPORT void SetLinkedArc(const occ::handle<MAT_Arc>& anArc);

  DEFINE_STANDARD_RTTIEXT(MAT_Node, Standard_Transient)

private:
  int    nodeIndex;
  int    geomIndex;
  void*  aLinkedArc;
  double distance;
};

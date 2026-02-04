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

//! Node of Graph.
class MAT_Node : public Standard_Transient
{

public:
  Standard_EXPORT MAT_Node(const int                   GeomIndex,
                           const occ::handle<MAT_Arc>& LinkedArc,
                           const double                Distance);

  //! Returns the index associated of the geometric
  //! representation of <me>.
  Standard_EXPORT int GeomIndex() const;

  //! Returns the index associated of the node
  Standard_EXPORT int Index() const;

  //! Returns in <S> the Arcs linked to <me>.
  Standard_EXPORT void LinkedArcs(NCollection_Sequence<occ::handle<MAT_Arc>>& S) const;

  //! Returns in <S> the BasicElts equidistant
  //! to <me>.
  Standard_EXPORT void NearElts(NCollection_Sequence<occ::handle<MAT_BasicElt>>& S) const;

  Standard_EXPORT double Distance() const;

  //! Returns True if <me> is a pending Node.
  //! (ie : the number of Arc Linked = 1)
  Standard_EXPORT bool PendingNode() const;

  //! Returns True if <me> belongs to the figure.
  Standard_EXPORT bool OnBasicElt() const;

  //! Returns True if the distance of <me> is Infinite
  Standard_EXPORT bool Infinite() const;

  //! Set the index associated of the node
  Standard_EXPORT void SetIndex(const int anIndex);

  Standard_EXPORT void SetLinkedArc(const occ::handle<MAT_Arc>& anArc);

  DEFINE_STANDARD_RTTIEXT(MAT_Node, Standard_Transient)

private:
  int    nodeIndex;
  int    geomIndex;
  void*  aLinkedArc;
  double distance;
};


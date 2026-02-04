#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <MAT_Arc.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <MAT_Side.hpp>
class MAT_BasicElt;
class MAT_Arc;
class MAT_Node;

//! Definition of Zone of Proximity of a BasicElt :
//! ----------------------------------------------
//! A Zone of proximity is the set of the points which are
//! more near from the BasicElt than any other.
class MAT_Zone : public Standard_Transient
{

public:
  Standard_EXPORT MAT_Zone();

  //! Compute the frontier of the Zone of proximity.
  Standard_EXPORT MAT_Zone(const occ::handle<MAT_BasicElt>& aBasicElt);

  //! Compute the frontier of the Zone of proximity.
  Standard_EXPORT void Perform(const occ::handle<MAT_BasicElt>& aBasicElt);

  //! Return the number Of Arcs On the frontier of <me>.
  Standard_EXPORT int NumberOfArcs() const;

  //! Return the Arc number <Index> on the frontier.
  //! of <me>.
  Standard_EXPORT occ::handle<MAT_Arc> ArcOnFrontier(const int Index) const;

  //! Return TRUE if <me> is not empty .
  Standard_EXPORT bool NoEmptyZone() const;

  //! Return TRUE if <me> is Limited.
  Standard_EXPORT bool Limited() const;

  DEFINE_STANDARD_RTTIEXT(MAT_Zone, Standard_Transient)

private:
  Standard_EXPORT occ::handle<MAT_Node> NodeForTurn(const occ::handle<MAT_Arc>&      anArc,
                                                    const occ::handle<MAT_BasicElt>& aBasicElt,
                                                    const MAT_Side                   aSide) const;

  NCollection_Sequence<occ::handle<MAT_Arc>> frontier;
  bool                                       limited;
};


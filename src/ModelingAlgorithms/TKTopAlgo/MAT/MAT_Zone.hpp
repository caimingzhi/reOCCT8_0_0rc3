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

class MAT_Zone : public Standard_Transient
{

public:
  Standard_EXPORT MAT_Zone();

  Standard_EXPORT MAT_Zone(const occ::handle<MAT_BasicElt>& aBasicElt);

  Standard_EXPORT void Perform(const occ::handle<MAT_BasicElt>& aBasicElt);

  Standard_EXPORT int NumberOfArcs() const;

  Standard_EXPORT occ::handle<MAT_Arc> ArcOnFrontier(const int Index) const;

  Standard_EXPORT bool NoEmptyZone() const;

  Standard_EXPORT bool Limited() const;

  DEFINE_STANDARD_RTTIEXT(MAT_Zone, Standard_Transient)

private:
  Standard_EXPORT occ::handle<MAT_Node> NodeForTurn(const occ::handle<MAT_Arc>&      anArc,
                                                    const occ::handle<MAT_BasicElt>& aBasicElt,
                                                    const MAT_Side                   aSide) const;

  NCollection_Sequence<occ::handle<MAT_Arc>> frontier;
  bool                                       limited;
};

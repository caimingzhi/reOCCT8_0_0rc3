#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;

//! This Selection returns the pcurves which lie on a face
//! In two modes : global (i.e. a CompositeCurve is not explored)
//! or basic (all the basic curves are listed)
class IGESSelect_SelectPCurves : public IFSelect_SelectExplore
{

public:
  //! Creates a SelectPCurves
  //! basic True  : lists all the components of pcurves
  //! basic False : lists the uppest level definitions
  //! (i.e. stops at CompositeCurve)
  Standard_EXPORT IGESSelect_SelectPCurves(const bool basic);

  //! Explores an entity, to take its contained PCurves
  //! An independent curve is IGNORED : only faces are explored
  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium : "Basic PCurves" or
  //! "Global PCurves"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectPCurves, IFSelect_SelectExplore)

private:
  bool thebasic;
};


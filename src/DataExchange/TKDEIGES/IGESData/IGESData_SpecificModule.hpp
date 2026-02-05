#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

//! This class defines some Services which are specifically
//! attached to IGES Entities : Dump
class IGESData_SpecificModule : public Standard_Transient
{

public:
  //! Specific Dump for each type of IGES Entity : it concerns only
  //! own parameters, the general data (Directory Part, Lists) are
  //! taken into account by the IGESDumper
  //! See class IGESDumper for the rules to follow for <own> and
  //! <attached> level
  Standard_EXPORT virtual void OwnDump(const int                               CN,
                                       const occ::handle<IGESData_IGESEntity>& ent,
                                       const IGESData_IGESDumper&              dumper,
                                       Standard_OStream&                       S,
                                       const int                               own) const = 0;

  //! Specific Automatic Correction on own Parameters of an Entity.
  //! It works by setting in accordance redundant data, if there are
  //! when there is no ambiguity (else, it does nothing).
  //! Remark that classic Corrections on Directory Entry (to set
  //! void data) are taken into account alsewhere.
  //!
  //! For instance, many "Associativity Entities" have a Number of
  //! Properties which must have a fixed value.
  //! Or, a ConicalArc has its Form Number which records the kind of
  //! Conic, also determined from its coefficients
  //! But, a CircularArc of which Distances (Center-Start) and
  //! (Center-End) are not equal cannot be corrected ...
  //!
  //! Returns True if something has been corrected in <ent>
  //! By default, does nothing. If at least one of the Types
  //! processed by a sub-class of SpecificModule has a Correct
  //! procedure attached, this method can be redefined
  Standard_EXPORT virtual bool OwnCorrect(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& ent) const;

  DEFINE_STANDARD_RTTIEXT(IGESData_SpecificModule, Standard_Transient)
};

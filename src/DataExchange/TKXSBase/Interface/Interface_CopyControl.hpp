#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

//! This deferred class describes the services required by
//! CopyTool to work. They are very simple and correspond
//! basically to the management of an indexed map.
//! But they can be provided by various classes which can
//! control a Transfer. Each Starting Entity have at most
//! one Result (Mapping one-one)
class Interface_CopyControl : public Standard_Transient
{

public:
  //! Clears List of Copy Results. Gets Ready to begin another Copy
  //! Process.
  Standard_EXPORT virtual void Clear() = 0;

  //! Bind a Result to a Starting Entity identified by its Number
  Standard_EXPORT virtual void Bind(const occ::handle<Standard_Transient>& ent,
                                    const occ::handle<Standard_Transient>& res) = 0;

  //! Searches for the Result bound to a Startingf Entity identified
  //! by its Number.
  //! If Found, returns True and fills <res>
  //! Else, returns False and nullifies <res>
  Standard_EXPORT virtual bool Search(const occ::handle<Standard_Transient>& ent,
                                      occ::handle<Standard_Transient>&       res) const = 0;

  DEFINE_STANDARD_RTTIEXT(Interface_CopyControl, Standard_Transient)
};


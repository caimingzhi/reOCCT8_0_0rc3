#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Interface_Graph;
class Interface_Check;
class Interface_InterfaceModel;

//! General description of Interface Protocols. A Protocol defines
//! a set of Entity types. This class provides also the notion of
//! Active Protocol, as a working context, defined once then
//! exploited by various Tools and Libraries.
//!
//! It also gives control of type definitions. By default, types
//! are provided by CDL, but specific implementations, or topics
//! like multi-typing, may involve another way
class Interface_Protocol : public Standard_Transient
{

public:
  //! Returns the Active Protocol, if defined (else, returns a
  //! Null Handle, which means "no defined active protocol")
  Standard_EXPORT static occ::handle<Interface_Protocol> Active();

  //! Sets a given Protocol to be the Active one (for the users of
  //! Active, see just above). Applies to every sub-type of Protocol
  Standard_EXPORT static void SetActive(const occ::handle<Interface_Protocol>& aprotocol);

  //! Erases the Active Protocol (hence it becomes undefined)
  Standard_EXPORT static void ClearActive();

  //! Returns count of Protocol used as Resources (level one)
  Standard_EXPORT virtual int NbResources() const = 0;

  //! Returns a Resource, given its rank (between 1 and NbResources)
  Standard_EXPORT virtual occ::handle<Interface_Protocol> Resource(const int num) const = 0;

  //! Returns a unique positive CaseNumber for each Recognized
  //! Object. By default, recognition is based on Type(1)
  //! By default, calls the following one which is deferred.
  Standard_EXPORT virtual int CaseNumber(const occ::handle<Standard_Transient>& obj) const;

  //! Returns True if type of <obj> is that defined from CDL
  //! This is the default but it may change according implementation
  Standard_EXPORT virtual bool IsDynamicType(const occ::handle<Standard_Transient>& obj) const;

  //! Returns the count of DISTINCT types under which an entity may
  //! be processed. Each one is candidate to be recognized by
  //! TypeNumber, <obj> is then processed according it
  //! By default, returns 1 (the DynamicType)
  Standard_EXPORT virtual int NbTypes(const occ::handle<Standard_Transient>& obj) const;

  //! Returns a type under which <obj> can be recognized and
  //! processed, according its rank in its definition list (see
  //! NbTypes).
  //! By default, returns DynamicType
  Standard_EXPORT occ::handle<Standard_Type> Type(const occ::handle<Standard_Transient>& obj,
                                                  const int nt = 1) const;

  //! Returns a unique positive CaseNumber for each Recognized Type,
  //! Returns Zero for "<type> not recognized"
  Standard_EXPORT virtual int TypeNumber(const occ::handle<Standard_Type>& atype) const = 0;

  //! Evaluates a Global Check for a model (with its Graph)
  //! Returns True when done, False if data in model do not apply
  //!
  //! Very specific of each norm, i.e. of each protocol : the
  //! uppest level Protocol assumes it, it can call GlobalCheck of
  //! its resources only if it is necessary
  //!
  //! Default does nothing, can be redefined
  Standard_EXPORT virtual bool GlobalCheck(const Interface_Graph&        G,
                                           occ::handle<Interface_Check>& ach) const;

  //! Creates an empty Model of the considered Norm
  Standard_EXPORT virtual occ::handle<Interface_InterfaceModel> NewModel() const = 0;

  //! Returns True if <model> is a Model of the considered Norm
  Standard_EXPORT virtual bool IsSuitableModel(
    const occ::handle<Interface_InterfaceModel>& model) const = 0;

  //! Creates a new Unknown Entity for the considered Norm
  Standard_EXPORT virtual occ::handle<Standard_Transient> UnknownEntity() const = 0;

  //! Returns True if <ent> is an Unknown Entity for the Norm, i.e.
  //! same Type as them created by method UnknownEntity
  //! (for an Entity out of the Norm, answer can be unpredictable)
  Standard_EXPORT virtual bool IsUnknownEntity(
    const occ::handle<Standard_Transient>& ent) const = 0;

  DEFINE_STANDARD_RTTIEXT(Interface_Protocol, Standard_Transient)
};

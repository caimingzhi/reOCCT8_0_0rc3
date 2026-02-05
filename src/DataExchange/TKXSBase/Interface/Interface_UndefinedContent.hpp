#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Interface_EntityList.hpp>
#include <Standard_Transient.hpp>
#include <Interface_ParamType.hpp>
class TCollection_HAsciiString;
class Interface_CopyTool;

//! Defines resources for an "Undefined Entity" : such an Entity
//! is used to describe an Entity which complies with the Norm,
//! but of an Unknown Type : hence it is kept under a literal
//! form (avoiding to loose data). UndefinedContent offers a way
//! to store a list of Parameters, as literals or references to
//! other Entities
//!
//! Each Interface must provide one "UndefinedEntity", which must
//! have same basic description as all its types of entities :
//! the best way would be double inheritance : on the Entity Root
//! of the Norm and on an general "UndefinedEntity"
//!
//! While it is not possible to do so, the UndefinedEntity of each
//! Interface can define its own UndefinedEntity by INCLUDING
//! (in a field) this UndefinedContent
//!
//! Hence, for that UndefinedEntity, define a Constructor which
//! creates this UndefinedContent, plus access methods to it
//! (or to its data, calling methods defined here).
//!
//! Finally, the Protocols of each norm have to Create and
//! Recognize Unknown Entities of this norm
class Interface_UndefinedContent : public Standard_Transient
{

public:
  //! Defines an empty UndefinedContent
  Standard_EXPORT Interface_UndefinedContent();

  //! Gives count of recorded parameters
  Standard_EXPORT int NbParams() const;

  //! Gives count of Literal Parameters
  Standard_EXPORT int NbLiterals() const;

  //! Returns data of a Parameter : its type, and the entity if it
  //! designates en entity ("ent") or its literal value else ("str")
  //! Returned value (Boolean) : True if it is an Entity, False else
  Standard_EXPORT bool ParamData(const int                              num,
                                 Interface_ParamType&                   ptype,
                                 occ::handle<Standard_Transient>&       ent,
                                 occ::handle<TCollection_HAsciiString>& val) const;

  //! Returns the ParamType of a Param, given its rank
  //! Error if num is not between 1 and NbParams
  Standard_EXPORT Interface_ParamType ParamType(const int num) const;

  //! Returns True if a Parameter is recorded as an entity
  //! Error if num is not between 1 and NbParams
  Standard_EXPORT bool IsParamEntity(const int num) const;

  //! Returns Entity corresponding to a Param, given its rank
  Standard_EXPORT occ::handle<Standard_Transient> ParamEntity(const int num) const;

  //! Returns literal value of a Parameter, given its rank
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ParamValue(const int num) const;

  //! Manages reservation for parameters (internal use)
  //! (nb : total count of parameters, nblit : count of literals)
  Standard_EXPORT void Reservate(const int nb, const int nblit);

  //! Adds a literal Parameter to the list
  Standard_EXPORT void AddLiteral(const Interface_ParamType                    ptype,
                                  const occ::handle<TCollection_HAsciiString>& val);

  //! Adds a Parameter which references an Entity
  Standard_EXPORT void AddEntity(const Interface_ParamType              ptype,
                                 const occ::handle<Standard_Transient>& ent);

  //! Removes a Parameter given its rank
  Standard_EXPORT void RemoveParam(const int num);

  //! Sets a new value for the Parameter <num>, to a literal value
  //! (if it referenced formerly an Entity, this Entity is removed)
  Standard_EXPORT void SetLiteral(const int                                    num,
                                  const Interface_ParamType                    ptype,
                                  const occ::handle<TCollection_HAsciiString>& val);

  //! Sets a new value for the Parameter <num>, to reference an
  //! Entity. To simply change the Entity, see the variant below
  Standard_EXPORT void SetEntity(const int                              num,
                                 const Interface_ParamType              ptype,
                                 const occ::handle<Standard_Transient>& ent);

  //! Changes the Entity referenced by the Parameter <num>
  //! (with same ParamType)
  Standard_EXPORT void SetEntity(const int num, const occ::handle<Standard_Transient>& ent);

  //! Returns globally the list of param entities. Note that it can
  //! be used as shared entity list for the UndefinedEntity
  Standard_EXPORT Interface_EntityList EntityList() const;

  //! Copies contents of undefined entities; deigned to be called by
  //! GetFromAnother method from Undefined entity of each Interface
  //! (the basic operation is the same regardless the norm)
  Standard_EXPORT void GetFromAnother(const occ::handle<Interface_UndefinedContent>& other,
                                      Interface_CopyTool&                            TC);

  DEFINE_STANDARD_RTTIEXT(Interface_UndefinedContent, Standard_Transient)

private:
  int                                                                     thenbparams;
  int                                                                     thenbstr;
  occ::handle<NCollection_HArray1<int>>                                   theparams;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> thevalues;
  Interface_EntityList                                                    theentities;
};

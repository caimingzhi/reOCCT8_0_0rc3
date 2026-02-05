#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <Interface_ParamType.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class IGESData_IGESEntity;
class TCollection_HAsciiString;
class IGESData_IGESWriter;

//! This class allows to create IGES Entities in a literal form :
//! their definition is free, but they are not recognized as
//! instances of specific classes.
//!
//! This is a way to define test files without having to create
//! and fill specific classes of Entities, or creating an IGES
//! File ex nihilo, with respect for all format constraints
//! (such a way is very difficult to run and to master).
//!
//! This class has the same content as an UndefinedEntity, only
//! it gives way to act on its content
class IGESData_FreeFormatEntity : public IGESData_UndefinedEntity
{

public:
  //! Creates a completely empty FreeFormatEntity
  Standard_EXPORT IGESData_FreeFormatEntity();

  //! Sets Type Number to a new Value, and Form Number to Zero
  Standard_EXPORT void SetTypeNumber(const int typenum);

  //! Sets Form Number to a new Value (to called after SetTypeNumber)
  Standard_EXPORT void SetFormNumber(const int formnum);

  //! Gives count of recorded parameters
  Standard_EXPORT int NbParams() const;

  //! Returns data of a Parameter : its type, and the entity if it
  //! designates en entity ("ent") or its literal value else ("str")
  //! Returned value (Boolean) : True if it is an Entity, False else
  Standard_EXPORT bool ParamData(const int                              num,
                                 Interface_ParamType&                   ptype,
                                 occ::handle<IGESData_IGESEntity>&      ent,
                                 occ::handle<TCollection_HAsciiString>& val) const;

  //! Returns the ParamType of a Param, given its rank
  //! Error if num is not between 1 and NbParams
  Standard_EXPORT Interface_ParamType ParamType(const int num) const;

  //! Returns True if a Parameter is recorded as an entity
  //! Error if num is not between 1 and NbParams
  Standard_EXPORT bool IsParamEntity(const int num) const;

  //! Returns Entity corresponding to a Param, given its rank
  //! Error if out of range or if Param num does not designate
  //! an Entity
  Standard_EXPORT occ::handle<IGESData_IGESEntity> ParamEntity(const int num) const;

  //! Returns True if <num> is noted as for a "Negative Pointer"
  //! (see AddEntity for details). Senseful only if IsParamEntity
  //! answers True for <num>, else returns False.
  Standard_EXPORT bool IsNegativePointer(const int num) const;

  //! Returns literal value of a Parameter, given its rank
  //! Error if num is out of range, or if Parameter is not literal
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ParamValue(const int num) const;

  //! Returns the complete list of Ramks of Parameters which have
  //! been noted as Negative Pointers
  //! Warning : It is returned as a Null Handle if none was noted
  Standard_EXPORT occ::handle<NCollection_HSequence<int>> NegativePointers() const;

  //! Adds a literal Parameter to the list (as such)
  Standard_EXPORT void AddLiteral(const Interface_ParamType                    ptype,
                                  const occ::handle<TCollection_HAsciiString>& val);

  //! Adds a literal Parameter to the list (builds an HAsciiString)
  Standard_EXPORT void AddLiteral(const Interface_ParamType ptype, const char* val);

  //! Adds a Parameter which references an Entity. If the Entity is
  //! Null, the added parameter will define a "Null Pointer" (0)
  //! If <negative> is given True, this will command Sending to File
  //! (see IGESWriter) to produce a "Negative Pointer"
  //! (Default is False)
  Standard_EXPORT void AddEntity(const Interface_ParamType               ptype,
                                 const occ::handle<IGESData_IGESEntity>& ent,
                                 const bool                              negative = false);

  //! Adds a set of Entities, given as a HArray1OfIGESEntity
  //! Causes creation of : an Integer Parameter which gives count
  //! of Entities, then the list of Entities of the Array
  //! Error if an Entity is not an IGESEntity
  //! All these Entities will be interpreted as "Positive Pointers"
  //! by IGESWriter
  Standard_EXPORT void AddEntities(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& ents);

  //! Adds a list of Ranks of Parameters to be noted as Negative
  //! Pointers (this will be taken into account for Parameters
  //! which are Entities)
  Standard_EXPORT void AddNegativePointers(const occ::handle<NCollection_HSequence<int>>& list);

  //! Clears all information about Negative Pointers, hence every
  //! Entity kind Parameter will be sent normally, as Positive
  Standard_EXPORT void ClearNegativePointers();

  //! WriteOwnParams is redefined for FreeFormatEntity to take
  //! into account the supplementary information "Negative Pointer"
  Standard_EXPORT void WriteOwnParams(IGESData_IGESWriter& IW) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_FreeFormatEntity, IGESData_UndefinedEntity)

private:
  occ::handle<NCollection_HSequence<int>> thenegptrs;
};

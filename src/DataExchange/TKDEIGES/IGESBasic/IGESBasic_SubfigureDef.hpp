#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class TCollection_HAsciiString;
class Standard_Transient;

//! defines SubfigureDef, Type <308> Form <0>
//! in package IGESBasic
//! This Entity permits a single definition of a detail to
//! be utilized in multiple instances in the creation of
//! the whole picture
class IGESBasic_SubfigureDef : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_SubfigureDef();

  //! This method is used to set the fields of the class
  //! SubfigureDef
  //! - aDepth           : It indicates the amount of nesting
  //! - aName            : the subfigure name
  //! - allAssocEntities : the associated entities
  Standard_EXPORT void Init(
    const int                                                                 aDepth,
    const occ::handle<TCollection_HAsciiString>&                              aName,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allAssocEntities);

  //! returns depth of the Subfigure
  //! if theDepth = 0 - No reference to any subfigure instance.
  Standard_EXPORT int Depth() const;

  //! returns the name of Subfigure
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! returns number of entities. Is greater than or equal to zero.
  Standard_EXPORT int NbEntities() const;

  //! returns the specific entity as indicated by Index
  //! raises exception if Index <= 0 or Index > NbEntities()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> AssociatedEntity(const int Index) const;

  //! returns the specific entity as indicated by Index
  //! raises exception if Index <= 0 or Index > NbEntities()
  Standard_EXPORT occ::handle<Standard_Transient> Value(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_SubfigureDef, IGESData_IGESEntity)

private:
  int                                                                theDepth;
  occ::handle<TCollection_HAsciiString>                              theName;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theAssocEntities;
};

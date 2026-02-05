#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! Selects Entities which have a given name.
//! Consider Property Name if present, else Short Label, but
//! not the Subscript Number
//! First version : keeps exact name
//! Later : regular expression
class IGESSelect_SelectName : public IFSelect_SelectExtract
{

public:
  //! Creates an empty SelectName : every entity is considered
  //! good (no filter active)
  Standard_EXPORT IGESSelect_SelectName();

  //! Returns True if Name of Entity complies with Name Filter
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Sets a Name as a criterium : IGES Entities which have this name
  //! are kept (without regular expression, there should be at most
  //! one). <name> can be regarded as a Text Parameter
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& name);

  //! Returns the Name used as Filter
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Returns the Selection criterium : "IGES Entity, Name : <name>"
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectName, IFSelect_SelectExtract)

private:
  occ::handle<TCollection_HAsciiString> thename;
};

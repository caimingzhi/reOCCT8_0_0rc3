#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! This selection looks at Blank Status of IGES Entities
//! Direct  selection keeps Visible Entities (Blank = 0),
//! Reverse selection keeps Blanked Entities (Blank = 1)
class IGESSelect_SelectVisibleStatus : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectVisibleStatus
  Standard_EXPORT IGESSelect_SelectVisibleStatus();

  //! Returns True if <ent> is an IGES Entity with Blank Status = 0
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns the Selection criterium : "IGES Entity, Status Visible"
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectVisibleStatus, IFSelect_SelectExtract)
};

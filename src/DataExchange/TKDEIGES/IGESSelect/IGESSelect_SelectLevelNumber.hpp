#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class IFSelect_IntParam;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IGESSelect_SelectLevelNumber : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT IGESSelect_SelectLevelNumber();

  Standard_EXPORT void SetLevelNumber(const occ::handle<IFSelect_IntParam>& levnum);

  Standard_EXPORT occ::handle<IFSelect_IntParam> LevelNumber() const;

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectLevelNumber, IFSelect_SelectExtract)

private:
  occ::handle<IFSelect_IntParam> thelevnum;
};

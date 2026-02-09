#pragma once

#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class Standard_Transient;
class Interface_InterfaceModel;

class IFSelect_SelectFlag : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT IFSelect_SelectFlag(const char* flagname);

  Standard_EXPORT const char* FlagName() const;

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectFlag, IFSelect_SelectExtract)

private:
  TCollection_AsciiString thename;
};

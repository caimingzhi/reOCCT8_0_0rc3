#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IFSelect_SelectRoots : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT IFSelect_SelectRoots();

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectRoots, IFSelect_SelectExtract)

protected:
  Standard_EXPORT bool HasUniqueResult() const override;
};

#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_SelectExtract.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IFSelect_SelectSent : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT IFSelect_SelectSent(const int sentcount = 1, const bool atleast = true);

  Standard_EXPORT int SentCount() const;

  Standard_EXPORT bool AtLeast() const;

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectSent, IFSelect_SelectExtract)

private:
  int  thecnt;
  bool thelst;
};

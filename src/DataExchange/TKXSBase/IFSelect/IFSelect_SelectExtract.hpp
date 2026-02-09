#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
#include <Standard_Integer.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IFSelect_SelectExtract : public IFSelect_SelectDeduct
{

public:
  Standard_EXPORT bool IsDirect() const;

  Standard_EXPORT void SetDirect(const bool direct);

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT virtual bool Sort(const int                                    rank,
                                    const occ::handle<Standard_Transient>&       ent,
                                    const occ::handle<Interface_InterfaceModel>& model) const = 0;

  Standard_EXPORT virtual bool SortInGraph(const int                              rank,
                                           const occ::handle<Standard_Transient>& ent,
                                           const Interface_Graph&                 G) const;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  Standard_EXPORT virtual TCollection_AsciiString ExtractLabel() const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectExtract, IFSelect_SelectDeduct)

protected:
  Standard_EXPORT IFSelect_SelectExtract();

private:
  bool thesort;
};

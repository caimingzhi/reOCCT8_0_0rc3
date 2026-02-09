#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
class IGESSelect_ViewSorter;
class TCollection_AsciiString;
class Interface_Graph;
class IFGraph_SubPartsIterator;
class Interface_EntityIterator;

class IGESSelect_DispPerDrawing : public IFSelect_Dispatch
{

public:
  Standard_EXPORT IGESSelect_DispPerDrawing();

  Standard_EXPORT TCollection_AsciiString Label() const override;

  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  Standard_EXPORT bool CanHaveRemainder() const override;

  Standard_EXPORT Interface_EntityIterator Remainder(const Interface_Graph& G) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_DispPerDrawing, IFSelect_Dispatch)

private:
  occ::handle<IGESSelect_ViewSorter> thesorter;
};

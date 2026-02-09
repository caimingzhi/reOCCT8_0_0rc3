#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
#include <Standard_Integer.hpp>
class IFSelect_IntParam;
class TCollection_AsciiString;
class Interface_Graph;
class IFGraph_SubPartsIterator;

class IFSelect_DispPerCount : public IFSelect_Dispatch
{

public:
  Standard_EXPORT IFSelect_DispPerCount();

  Standard_EXPORT occ::handle<IFSelect_IntParam> Count() const;

  Standard_EXPORT void SetCount(const occ::handle<IFSelect_IntParam>& count);

  Standard_EXPORT int CountValue() const;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  Standard_EXPORT bool LimitedMax(const int nbent, int& max) const override;

  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_DispPerCount, IFSelect_Dispatch)

private:
  occ::handle<IFSelect_IntParam> thecount;
};

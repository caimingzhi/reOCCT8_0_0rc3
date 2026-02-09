#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
#include <Standard_Integer.hpp>
class IFSelect_SignCounter;
class TCollection_AsciiString;
class Interface_Graph;
class IFGraph_SubPartsIterator;

class IFSelect_DispPerSignature : public IFSelect_Dispatch
{

public:
  Standard_EXPORT IFSelect_DispPerSignature();

  Standard_EXPORT occ::handle<IFSelect_SignCounter> SignCounter() const;

  Standard_EXPORT void SetSignCounter(const occ::handle<IFSelect_SignCounter>& sign);

  Standard_EXPORT const char* SignName() const;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  Standard_EXPORT bool LimitedMax(const int nbent, int& max) const override;

  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_DispPerSignature, IFSelect_Dispatch)

private:
  occ::handle<IFSelect_SignCounter> thesign;
};

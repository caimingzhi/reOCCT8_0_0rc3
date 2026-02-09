#pragma once

#include <Standard.hpp>

#include <IFSelect_SignatureList.hpp>
class MoniTool_SignText;
class Interface_CheckIterator;
class Interface_InterfaceModel;

class IFSelect_CheckCounter : public IFSelect_SignatureList
{

public:
  Standard_EXPORT IFSelect_CheckCounter(const bool withlist = false);

  Standard_EXPORT void SetSignature(const occ::handle<MoniTool_SignText>& sign);

  Standard_EXPORT occ::handle<MoniTool_SignText> Signature() const;

  Standard_EXPORT void Analyse(const Interface_CheckIterator&               list,
                               const occ::handle<Interface_InterfaceModel>& model,
                               const bool                                   original  = false,
                               const bool                                   failsonly = false);

  DEFINE_STANDARD_RTTIEXT(IFSelect_CheckCounter, IFSelect_SignatureList)

private:
  occ::handle<MoniTool_SignText> thesign;
};

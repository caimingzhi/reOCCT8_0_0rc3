#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Signature.hpp>
class XSControl_TransferReader;
class Transfer_TransientProcess;
class Standard_Transient;
class Interface_InterfaceModel;

class XSControl_SignTransferStatus : public IFSelect_Signature
{

public:
  Standard_EXPORT XSControl_SignTransferStatus();

  Standard_EXPORT XSControl_SignTransferStatus(const occ::handle<XSControl_TransferReader>& TR);

  Standard_EXPORT void SetReader(const occ::handle<XSControl_TransferReader>& TR);

  Standard_EXPORT void SetMap(const occ::handle<Transfer_TransientProcess>& TP);

  Standard_EXPORT occ::handle<Transfer_TransientProcess> Map() const;

  Standard_EXPORT occ::handle<XSControl_TransferReader> Reader() const;

  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(XSControl_SignTransferStatus, IFSelect_Signature)

private:
  occ::handle<XSControl_TransferReader>  theTR;
  occ::handle<Transfer_TransientProcess> theTP;
};

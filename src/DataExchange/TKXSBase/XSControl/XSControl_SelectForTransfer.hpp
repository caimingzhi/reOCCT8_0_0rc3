#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class XSControl_TransferReader;
class Transfer_ActorOfTransientProcess;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class XSControl_SelectForTransfer : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT XSControl_SelectForTransfer();

  Standard_EXPORT XSControl_SelectForTransfer(const occ::handle<XSControl_TransferReader>& TR);

  Standard_EXPORT void SetReader(const occ::handle<XSControl_TransferReader>& TR);

  Standard_EXPORT void SetActor(const occ::handle<Transfer_ActorOfTransientProcess>& act);

  Standard_EXPORT occ::handle<Transfer_ActorOfTransientProcess> Actor() const;

  Standard_EXPORT occ::handle<XSControl_TransferReader> Reader() const;

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(XSControl_SelectForTransfer, IFSelect_SelectExtract)

private:
  occ::handle<XSControl_TransferReader>         theTR;
  occ::handle<Transfer_ActorOfTransientProcess> theAC;
};

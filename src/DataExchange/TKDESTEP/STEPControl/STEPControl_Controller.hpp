#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XSControl_Controller.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Integer.hpp>
class Interface_InterfaceModel;
class XSControl_WorkSession;
class TopoDS_Shape;
class Transfer_FinderProcess;

class STEPControl_Controller : public XSControl_Controller
{

public:
  Standard_EXPORT STEPControl_Controller();

  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewModel() const override;

  Standard_EXPORT occ::handle<Transfer_ActorOfTransientProcess> ActorRead(
    const occ::handle<Interface_InterfaceModel>& theModel) const override;

  Standard_EXPORT void Customise(occ::handle<XSControl_WorkSession>& WS) override;

  Standard_EXPORT IFSelect_ReturnStatus TransferWriteShape(
    const TopoDS_Shape&                          shape,
    const occ::handle<Transfer_FinderProcess>&   FP,
    const occ::handle<Interface_InterfaceModel>& model,
    const int                                    modetrans = 0,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const override;

  Standard_EXPORT static bool Init();

  DEFINE_STANDARD_RTTIEXT(STEPControl_Controller, XSControl_Controller)
};

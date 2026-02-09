#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XSControl_Controller.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Integer.hpp>
class Interface_InterfaceModel;
class Transfer_ActorOfTransientProcess;
class TopoDS_Shape;
class Transfer_FinderProcess;
class XSControl_WorkSession;

class IGESControl_Controller : public XSControl_Controller
{

public:
  Standard_EXPORT IGESControl_Controller(const bool modefnes = false);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewModel() const override;

  Standard_EXPORT occ::handle<Transfer_ActorOfTransientProcess> ActorRead(
    const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT IFSelect_ReturnStatus TransferWriteShape(
    const TopoDS_Shape&                          shape,
    const occ::handle<Transfer_FinderProcess>&   FP,
    const occ::handle<Interface_InterfaceModel>& model,
    const int                                    modetrans = 0,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const override;

  Standard_EXPORT static bool Init();

  Standard_EXPORT void Customise(occ::handle<XSControl_WorkSession>& WS) override;

  DEFINE_STANDARD_RTTIEXT(IGESControl_Controller, XSControl_Controller)

private:
  bool themode;
};

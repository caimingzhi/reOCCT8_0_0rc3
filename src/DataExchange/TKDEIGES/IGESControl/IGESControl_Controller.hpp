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

//! Controller for IGES-5.1
class IGESControl_Controller : public XSControl_Controller
{

public:
  //! Initializes the use of IGES Norm (the first time) and returns
  //! a Controller for IGES-5.1
  //! If <modefnes> is True, sets it to internal FNES format
  Standard_EXPORT IGESControl_Controller(const bool modefnes = false);

  //! Creates a new empty Model ready to receive data of the Norm.
  //! It is taken from IGES Template Model
  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewModel() const override;

  //! Returns the Actor for Read attached to the pair (norm,appli)
  //! It is an Actor from IGESToBRep, adapted from an IGESModel :
  //! Unit, tolerances
  Standard_EXPORT occ::handle<Transfer_ActorOfTransientProcess> ActorRead(
    const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Takes one Shape and transfers it to the InterfaceModel
  //! (already created by NewModel for instance)
  //! <modetrans> is to be interpreted by each kind of XstepAdaptor
  //! Returns a status : 0 OK  1 No result  2 Fail  -1 bad modeshape
  //! -2 bad model (requires an IGESModel)
  //! modeshape : 0 group of face (version < 5.1)
  //! 1  BREP-version 5.1 of IGES
  Standard_EXPORT IFSelect_ReturnStatus TransferWriteShape(
    const TopoDS_Shape&                          shape,
    const occ::handle<Transfer_FinderProcess>&   FP,
    const occ::handle<Interface_InterfaceModel>& model,
    const int                                    modetrans = 0,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const override;

  //! Standard Initialisation. It creates a Controller for IGES and
  //! records it to various names, available to select it later
  //! Returns True when done, False if could not be done
  //! Also, it creates and records an Adaptor for FNES
  Standard_EXPORT static bool Init();

  Standard_EXPORT void Customise(occ::handle<XSControl_WorkSession>& WS) override;

  DEFINE_STANDARD_RTTIEXT(IGESControl_Controller, XSControl_Controller)

private:
  bool themode;
};

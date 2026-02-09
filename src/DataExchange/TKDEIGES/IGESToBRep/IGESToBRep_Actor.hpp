#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Transfer_ActorOfTransientProcess.hpp>
#include <Message_ProgressRange.hpp>

struct DE_ShapeFixParameters;
class Interface_InterfaceModel;
class Standard_Transient;
class Transfer_Binder;
class Transfer_TransientProcess;

class IGESToBRep_Actor : public Transfer_ActorOfTransientProcess
{
public:
  Standard_EXPORT IGESToBRep_Actor();

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT void SetContinuity(const int continuity = 0);

  Standard_EXPORT int GetContinuity() const;

  Standard_EXPORT bool Recognize(const occ::handle<Standard_Transient>& start) override;

  Standard_EXPORT occ::handle<Transfer_Binder> Transfer(
    const occ::handle<Standard_Transient>&        start,
    const occ::handle<Transfer_TransientProcess>& TP,
    const Message_ProgressRange&                  theProgress = Message_ProgressRange()) override;

  Standard_EXPORT double UsedTolerance() const;

  DEFINE_STANDARD_RTTIEXT(IGESToBRep_Actor, Transfer_ActorOfTransientProcess)

private:
  occ::handle<Interface_InterfaceModel> themodel;
  int                                   thecontinuity;
  double                                theeps;
};

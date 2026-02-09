#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Vector.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <NCollection_DataMap.hpp>
#include <Message_ProgressRange.hpp>

class IFSelect_WorkLibrary;
class Interface_Protocol;
class Transfer_ActorOfTransientProcess;
class Transfer_ActorOfFinderProcess;
class XSControl_WorkSession;
class Interface_InterfaceModel;
class Transfer_FinderProcess;
class TopoDS_Shape;

class XSControl_Controller : public Standard_Transient
{
public:
  Standard_EXPORT void SetNames(const char* theLongName, const char* theShortName);

  void AutoRecord() const
  {
    Record(Name(true));
    Record(Name(false));
  }

  Standard_EXPORT void Record(const char* name) const;

  Standard_EXPORT static occ::handle<XSControl_Controller> Recorded(const char* name);

  const char* Name(const bool rsc = false) const
  {
    return (rsc ? myShortName.ToCString() : myLongName.ToCString());
  }

  const occ::handle<Interface_Protocol>& Protocol() const { return myAdaptorProtocol; }

  const occ::handle<IFSelect_WorkLibrary>& WorkLibrary() const { return myAdaptorLibrary; }

  Standard_EXPORT virtual occ::handle<Interface_InterfaceModel> NewModel() const = 0;

  Standard_EXPORT virtual occ::handle<Transfer_ActorOfTransientProcess> ActorRead(
    const occ::handle<Interface_InterfaceModel>& model) const;

  Standard_EXPORT virtual occ::handle<Transfer_ActorOfFinderProcess> ActorWrite() const;

  Standard_EXPORT void SetModeWrite(const int modemin, const int modemax, const bool shape = true);

  Standard_EXPORT void SetModeWriteHelp(const int   modetrans,
                                        const char* help,
                                        const bool  shape = true);

  Standard_EXPORT bool ModeWriteBounds(int& modemin, int& modemax, const bool shape = true) const;

  Standard_EXPORT bool IsModeWrite(const int modetrans, const bool shape = true) const;

  Standard_EXPORT const char* ModeWriteHelp(const int modetrans, const bool shape = true) const;

  Standard_EXPORT virtual bool RecognizeWriteTransient(const occ::handle<Standard_Transient>& obj,
                                                       const int modetrans = 0) const;

  Standard_EXPORT virtual IFSelect_ReturnStatus TransferWriteTransient(
    const occ::handle<Standard_Transient>&       obj,
    const occ::handle<Transfer_FinderProcess>&   FP,
    const occ::handle<Interface_InterfaceModel>& model,
    const int                                    modetrans   = 0,
    const Message_ProgressRange&                 theProgress = Message_ProgressRange()) const;

  Standard_EXPORT virtual bool RecognizeWriteShape(const TopoDS_Shape& shape,
                                                   const int           modetrans = 0) const;

  Standard_EXPORT virtual IFSelect_ReturnStatus TransferWriteShape(
    const TopoDS_Shape&                          shape,
    const occ::handle<Transfer_FinderProcess>&   FP,
    const occ::handle<Interface_InterfaceModel>& model,
    const int                                    modetrans   = 0,
    const Message_ProgressRange&                 theProgress = Message_ProgressRange()) const;

  Standard_EXPORT void AddSessionItem(const occ::handle<Standard_Transient>& theItem,
                                      const char*                            theName,
                                      const bool                             toApply = false);

  Standard_EXPORT occ::handle<Standard_Transient> SessionItem(const char* theName) const;

  Standard_EXPORT virtual void Customise(occ::handle<XSControl_WorkSession>& WS);

  const NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>&
    AdaptorSession() const
  {
    return myAdaptorSession;
  }

  DEFINE_STANDARD_RTTIEXT(XSControl_Controller, Standard_Transient)

protected:
  Standard_EXPORT XSControl_Controller(const char* theLongName, const char* theShortName);

  Standard_EXPORT void TraceStatic(const char* theName, const int theUse);

  TCollection_AsciiString           myShortName;
  TCollection_AsciiString           myLongName;
  occ::handle<IFSelect_WorkLibrary> myAdaptorLibrary;
  occ::handle<Interface_Protocol>   myAdaptorProtocol;

  occ::handle<Transfer_ActorOfTransientProcess>                                 myAdaptorRead;
  occ::handle<Transfer_ActorOfFinderProcess>                                    myAdaptorWrite;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> myAdaptorSession;

private:
  NCollection_Sequence<occ::handle<Standard_Transient>>                   myAdaptorApplied;
  NCollection_Vector<occ::handle<Standard_Transient>>                     myParams;
  NCollection_Vector<int>                                                 myParamUses;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> myModeWriteShapeN;
};

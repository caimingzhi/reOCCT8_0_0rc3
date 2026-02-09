

#include <Interface_InterfaceError.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_ReadWriteModule.hpp>
#include <StepData_UndefinedEntity.hpp>
#include <StepSelect_StepType.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepSelect_StepType, IFSelect_Signature)

StepSelect_StepType::StepSelect_StepType()
    : IFSelect_Signature("Step Type")
{
}

void StepSelect_StepType::SetProtocol(const occ::handle<Interface_Protocol>& proto)
{
  DeclareAndCast(StepData_Protocol, newproto, proto);
  if (newproto.IsNull())
    throw Interface_InterfaceError("StepSelect_StepType");
  theproto = newproto;
  thelib.Clear();
  thelib.AddProtocol(theproto);
  thename.Clear();
  thename.AssignCat("Step Type (Schema ");
  thename.AssignCat(theproto->SchemaName(nullptr));
  thename.AssignCat(")");
}

const char* StepSelect_StepType::Value(const occ::handle<Standard_Transient>&       ent,
                                       const occ::handle<Interface_InterfaceModel>& model) const
{
  std::lock_guard<std::mutex> aLock(myMutex);

  occ::handle<StepData_ReadWriteModule> aModule;
  int                                   aCN;
  if (!thelib.Select(ent, aModule, aCN))
  {

    theLastValue = "..NOT FROM SCHEMA ";
    theLastValue += theproto->SchemaName(model);
    theLastValue += "..";
    return theLastValue.ToCString();
  }

  if (!aModule->IsComplex(aCN))
    return aModule->StepType(aCN).data();

  NCollection_Sequence<TCollection_AsciiString> aList;
  if (aModule->ComplexType(aCN, aList))
  {
    int aNb = aList.Length();
    if (aNb == 0)
    {
      theLastValue = "(..COMPLEX TYPE..)";
    }
    else
    {
      theLastValue = "(";
      for (int i = 1; i <= aNb; i++)
      {
        if (i > 1)
          theLastValue += ",";
        theLastValue += aList.Value(i);
      }
      theLastValue += ")";
    }
    return theLastValue.ToCString();
  }

  DeclareAndCast(StepData_UndefinedEntity, anUnd, ent);
  if (anUnd.IsNull())
  {
    theLastValue.Clear();
    return theLastValue.ToCString();
  }

  if (!anUnd->IsComplex())
    return anUnd->StepType();

  theLastValue = "(";
  bool isFirst = true;
  while (!anUnd.IsNull())
  {
    if (!isFirst)
      theLastValue += ",";
    theLastValue += anUnd->StepType();
    anUnd   = anUnd->Next();
    isFirst = false;
  }
  theLastValue += ")";

  return theLastValue.ToCString();
}

#include <Standard_DomainError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_ImmutableObject.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_AttributeDelta.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_DefaultDeltaOnModification.hpp>
#include <TDF_DefaultDeltaOnRemoval.hpp>
#include <TDF_DeltaOnAddition.hpp>
#include <TDF_DeltaOnForget.hpp>
#include <TDF_DeltaOnModification.hpp>
#include <TDF_DeltaOnRemoval.hpp>
#include <TDF_DeltaOnResume.hpp>
#include <TDF_IDFilter.hpp>
#include <TDF_Label.hpp>
#include <TDF_LabelNode.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_Attribute, Standard_Transient)

#define TDF_DATA_COMMIT_OPTIMIZED

//=================================================================================================

TDF_Attribute::TDF_Attribute()
    : myLabelNode(nullptr),
      myTransaction(0),
      mySavedTransaction(0),
      myFlags(1)

{
}

//=================================================================================================

const TDF_Label TDF_Attribute::Label() const
{
  return TDF_Label(myLabelNode);
}

//=================================================================================================

bool TDF_Attribute::FindAttribute(const Standard_GUID&        anID,
                                  occ::handle<TDF_Attribute>& anAttribute) const
{
  return Label().FindAttribute(anID, anAttribute);
}

//=================================================================================================

bool TDF_Attribute::IsAttribute(const Standard_GUID& anID) const
{
  return Label().IsAttribute(anID);
}

//=================================================================================================

void TDF_Attribute::AddAttribute(const occ::handle<TDF_Attribute>& otherAttribute) const
{
  Label().AddAttribute(otherAttribute);
}

//=================================================================================================

bool TDF_Attribute::ForgetAttribute(const Standard_GUID& anID) const
{
  return Label().ForgetAttribute(anID);
}

//=================================================================================================

void TDF_Attribute::ForgetAllAttributes(const bool clearChildren) const
{
  Label().ForgetAllAttributes(clearChildren);
}

//=================================================================================================

void TDF_Attribute::Forget(const int aTransaction)
{
  mySavedTransaction = myTransaction;
  myTransaction      = aTransaction;
  myFlags            = (myFlags | TDF_AttributeForgottenMsk);
#ifdef TDF_DATA_COMMIT_OPTIMIZED
  if (myLabelNode)
    myLabelNode->AttributesModified(true);
#endif
  Validate(false);
}

//=================================================================================================

void TDF_Attribute::Resume()
{
  myTransaction      = mySavedTransaction;
  mySavedTransaction = -1; // To say "just resumed"!
  myFlags            = (myFlags & ~TDF_AttributeForgottenMsk);
  Validate(true);
}

//=================================================================================================

int TDF_Attribute::UntilTransaction() const
{
  if (IsForgotten())
    return myTransaction;
  else if (IsBackuped())
    return myNext->myTransaction - 1;
  else if (IsValid())
    return myLabelNode->Data()->Transaction();
  throw Standard_DomainError("The attribute structure is wrong.");
}

//=================================================================================================

void TDF_Attribute::AfterAddition() {}

//=================================================================================================

void TDF_Attribute::BeforeRemoval() {}

//=================================================================================================

void TDF_Attribute::BeforeForget() {}

//=================================================================================================

void TDF_Attribute::AfterResume() {}

//=======================================================================
// function : BeforeUndo
// purpose  : Before application of a TDF_Delta.
//=======================================================================

bool TDF_Attribute::BeforeUndo(const occ::handle<TDF_AttributeDelta>& /*anAttDelta*/,
                               const bool /*forceIt*/)
{
  return true;
}

//=======================================================================
// function : AfterUndo
// purpose  : After application of a TDF_Delta.
//=======================================================================

bool TDF_Attribute::AfterUndo(const occ::handle<TDF_AttributeDelta>& /*anAttDelta*/,
                              const bool /*forceIt*/)
{
  return true;
}

//=================================================================================================

bool TDF_Attribute::AfterRetrieval(const bool /*forceIt*/)
{
  return true;
}

//=================================================================================================

void TDF_Attribute::BeforeCommitTransaction() {}

//=======================================================================
// function : Backup
// purpose  : Backups the attribute.
//=======================================================================

void TDF_Attribute::Backup()
{
  // The attribute must be valid and attached to a label.
  if (IsValid() && (myLabelNode != nullptr))
  {
    occ::handle<TDF_Data> aData = myLabelNode->Data();

    // check that modification is allowed
    if (!aData->IsModificationAllowed())
    {
      TCollection_AsciiString aMess;
      aMess = "Attribute \"";
      aMess += DynamicType()->Name();
      aMess += "\" is changed outside transaction";
      throw Standard_ImmutableObject(aMess.ToCString());
    }

    const int currentTransaction = aData->Transaction();
    if (myTransaction < currentTransaction)
    { //"!=" is less secure.
      occ::handle<TDF_Attribute> backup = BackupCopy();
#ifdef TDF_DATA_COMMIT_OPTIMIZED
      myLabelNode->AttributesModified(true);
#endif
      backup->myLabelNode   = myLabelNode;
      backup->myNext        = this; // Back reference;
      backup->myBackup      = myBackup;
      backup->myTransaction = myTransaction;
      backup->Backup(true);

      myBackup      = backup;
      myTransaction = currentTransaction;
    }
  }
}

//=======================================================================
// function : BackupCopy
// purpose  : Standard implementation of BackupCopy.
//=======================================================================

occ::handle<TDF_Attribute> TDF_Attribute::BackupCopy() const
{
  occ::handle<TDF_Attribute> copy = NewEmpty();
  copy->Restore(this);
  return copy;
}

//=================================================================================================

void TDF_Attribute::RemoveBackup()
{
#ifdef OCCT_DEBUG
  if (myBackup.IsNull())
    throw Standard_DomainError("Impossible to remove a nonexistent backup.");
#endif
  myBackup->BeforeRemoval();
  myBackup->myLabelNode = nullptr; // Absolutely necessary!
  myBackup->myNext.Nullify();      // Absolutely necessary!
  myBackup = myBackup->myBackup;
  if (!myBackup.IsNull())
    myBackup->myNext = this; // New back reference.
}

//=======================================================================
// function : References
// purpose  : Adds the referenced attributes or labels.
//=======================================================================

void TDF_Attribute::References(const occ::handle<TDF_DataSet>& /*aDataSet*/) const {}

//=================================================================================================

occ::handle<TDF_DeltaOnAddition> TDF_Attribute::DeltaOnAddition() const
{
  return new TDF_DeltaOnAddition(this);
}

//=================================================================================================

occ::handle<TDF_DeltaOnForget> TDF_Attribute::DeltaOnForget() const
{
  return new TDF_DeltaOnForget(this);
}

//=================================================================================================

occ::handle<TDF_DeltaOnResume> TDF_Attribute::DeltaOnResume() const
{
  return new TDF_DeltaOnResume(this);
}

//=================================================================================================

occ::handle<TDF_DeltaOnModification> TDF_Attribute::DeltaOnModification(
  const occ::handle<TDF_Attribute>& anOldAttribute) const
{
  return new TDF_DefaultDeltaOnModification(anOldAttribute);
}

//=================================================================================================

void TDF_Attribute::DeltaOnModification(const occ::handle<TDF_DeltaOnModification>& aDelta)
{
  Backup();
  Restore(aDelta->Attribute());
}

//=================================================================================================

occ::handle<TDF_DeltaOnRemoval> TDF_Attribute::DeltaOnRemoval() const
{
  return new TDF_DefaultDeltaOnRemoval(this);
} // myBackup

//=======================================================================
// function : Dump
// purpose  : This method is equivalent to operator <<
//=======================================================================

Standard_OStream& TDF_Attribute::Dump(Standard_OStream& anOS) const
{
  anOS << "\t" << DynamicType()->Name() << "\tTrans. " << myTransaction << ";";
  if (IsValid())
    anOS << " Valid";
  if (IsBackuped())
    anOS << " Backuped";
  if (IsForgotten())
    anOS << " Forgotten";
  char                toto[45];
  Standard_PCharacter pStr;
  //
  pStr = toto;
  ID().ToCString(pStr);
  anOS << ";\tID = " << toto << std::endl;
  return anOS;
}

//=================================================================================================

void TDF_Attribute::ExtendedDump(Standard_OStream& anOS,
                                 const TDF_IDFilter& /*aFilter*/,
                                 NCollection_IndexedMap<occ::handle<TDF_Attribute>>& /*aMap*/) const
{
  Dump(anOS);
}

//=================================================================================================

void TDF_Attribute::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  TCollection_AsciiString aLabel;
  TDF_Tool::Entry(Label(), aLabel);
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, aLabel)

  OCCT_DUMP_FIELD_VALUE_GUID(theOStream, ID())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Transaction())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsValid())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsNew())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsBackuped())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsForgotten())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFlags)
}

#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Interface_SignType.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

//! Signature provides the basic service used by the classes
//! SelectSignature and Counter (i.e. Name, Value), which is :
//! - for an entity in a model, give a characteristic string, its
//! signature
//! This string has not to be unique in the model, but gives a
//! value for such or such important feature.
//! Examples : Dynamic Type; Category; etc
class IFSelect_Signature : public Interface_SignType
{

public:
  //! Sets the information data to tell "integer cases" with
  //! possible min and max values
  //! To be called when creating
  Standard_EXPORT void SetIntCase(const bool hasmin,
                                  const int  valmin,
                                  const bool hasmax,
                                  const int  valmax);

  //! Tells if this Signature gives integer values
  //! and returns values from SetIntCase if True
  Standard_EXPORT bool IsIntCase(bool& hasmin, int& valmin, bool& hasmax, int& valmax) const;

  //! Adds a possible case
  //! To be called when creating, IF the list of possible cases for
  //! Value is known when starting
  //! For instance, for CDL types, rather do not fill this,
  //! but for a specific enumeration (such as a status), can be used
  Standard_EXPORT void AddCase(const char* acase);

  //! Returns the predefined list of possible cases, filled by AddCase
  //! Null Handle if no predefined list (hence, to be counted)
  //! Useful to filter on really possible vase, for instance, or
  //! for a help
  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> CaseList() const;

  //! Returns an identification of the Signature (a word), given at
  //! initialization time
  //! Returns the Signature for a Transient object. It is specific
  //! of each sub-class of Signature. For a Null Handle, it should
  //! provide ""
  //! It can work with the model which contains the entity
  Standard_EXPORT const char* Name() const override;

  //! The label of a Signature uses its name as follow :
  //! "Signature : <name>"
  Standard_EXPORT TCollection_AsciiString Label() const;

  //! Tells if the value for <ent> in <model> matches a text, with
  //! a criterium <exact>.
  //! The default definition calls MatchValue
  //! Can be redefined
  Standard_EXPORT virtual bool Matches(const occ::handle<Standard_Transient>&       ent,
                                       const occ::handle<Interface_InterfaceModel>& model,
                                       const TCollection_AsciiString&               text,
                                       const bool                                   exact) const;

  //! Default procedure to tell if a value <val> matches a text
  //! with a criterium <exact>. <exact> = True requires equality,
  //! else only contained (no reg-exp)
  Standard_EXPORT static bool MatchValue(const char*                    val,
                                         const TCollection_AsciiString& text,
                                         const bool                     exact);

  //! This procedure converts an Integer to a CString
  //! It is a convenient way when the value of a signature has the
  //! form of a simple integer value
  //! The value is to be used immediately (one buffer only, no copy)
  Standard_EXPORT static const char* IntValue(const int val);

  DEFINE_STANDARD_RTTIEXT(IFSelect_Signature, Interface_SignType)

protected:
  //! Initializes a Signature with its name
  Standard_EXPORT IFSelect_Signature(const char* name);

  TCollection_AsciiString thename;

private:
  int                                                         thecasi[3];
  occ::handle<NCollection_HSequence<TCollection_AsciiString>> thecasl;
};

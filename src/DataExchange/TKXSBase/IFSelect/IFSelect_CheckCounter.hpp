#pragma once


#include <Standard.hpp>

#include <IFSelect_SignatureList.hpp>
class MoniTool_SignText;
class Interface_CheckIterator;
class Interface_InterfaceModel;

//! A CheckCounter allows to see a CheckList (i.e. CheckIterator)
//! not per entity, its messages, but per message, the entities
//! attached (count and list). Because many messages can be
//! repeated if they are due to systematic errors
class IFSelect_CheckCounter : public IFSelect_SignatureList
{

public:
  //! Creates a CheckCounter, empty ready to work
  Standard_EXPORT IFSelect_CheckCounter(const bool withlist = false);

  //! Sets a specific signature
  //! Else, the current SignType (in the model) is used
  Standard_EXPORT void SetSignature(const occ::handle<MoniTool_SignText>& sign);

  //! Returns the Signature;
  Standard_EXPORT occ::handle<MoniTool_SignText> Signature() const;

  //! Analyses a CheckIterator according a Model (which detains the
  //! entities for which the CheckIterator has messages), i.e.
  //! counts messages for entities
  //! If <original> is True, does not consider final messages but
  //! those before interpretation (such as inserting variables :
  //! integers, reals, strings)
  //! If <failsonly> is True, only Fails are considered
  //! Remark : global messages are recorded with a Null entity
  Standard_EXPORT void Analyse(const Interface_CheckIterator&               list,
                               const occ::handle<Interface_InterfaceModel>& model,
                               const bool                                   original  = false,
                               const bool                                   failsonly = false);

  DEFINE_STANDARD_RTTIEXT(IFSelect_CheckCounter, IFSelect_SignatureList)

private:
  occ::handle<MoniTool_SignText> thesign;
};


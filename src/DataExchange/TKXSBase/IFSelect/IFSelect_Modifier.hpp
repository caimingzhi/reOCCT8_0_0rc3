#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_GeneralModifier.hpp>
class IFSelect_ContextModif;
class Interface_InterfaceModel;
class Interface_Protocol;
class Interface_CopyTool;

//! This class gives a frame for Actions which can work globally
//! on a File once completely defined (i.e. afterwards)
//!
//! Remark : if no Selection is set as criterium, the Modifier is
//! set to work and should consider all the content of the Model
//! produced.
class IFSelect_Modifier : public IFSelect_GeneralModifier
{

public:
  //! This deferred method defines the action specific to each class
  //! of Modifier. It is called by a ModelCopier, once the Model
  //! generated and filled. ModelCopier has already checked the
  //! criteria (Dispatch, Model Rank, Selection) before calling it.
  //!
  //! <ctx> detains information about original data and selection.
  //! The result of copying, on which modifications are to be done,
  //! is <target>.
  //! <TC> allows to run additional copies as required
  //!
  //! In case of Error, use methods CCheck from the ContextModif
  //! to acknowledge an entity Check or a Global Check with messages
  Standard_EXPORT virtual void Perform(IFSelect_ContextModif&                       ctx,
                                       const occ::handle<Interface_InterfaceModel>& target,
                                       const occ::handle<Interface_Protocol>&       protocol,
                                       Interface_CopyTool&                          TC) const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_Modifier, IFSelect_GeneralModifier)

protected:
  //! Calls inherited Initialize, transmits to it the information
  //! <maychangegraph>
  Standard_EXPORT IFSelect_Modifier(const bool maychangegraph);
};

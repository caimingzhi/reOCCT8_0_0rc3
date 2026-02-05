#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class XSControl_TransferReader;
class Transfer_ActorOfTransientProcess;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! This selection selects the entities which are recognised for
//! transfer by an Actor for Read : current one or another one.
//!
//! An Actor is an operator which runs transfers from interface
//! entities to objects for Imagine. It has a method to recognize
//! the entities it can process (by default, it recognises all,
//! this method can be redefined).
//!
//! A TransferReader brings an Actor, according to the currently
//! selected norm and transfer conditions.
//!
//! This selection considers, either the current Actor (brought by
//! the TransferReader, updated as required), or a precise one.
class XSControl_SelectForTransfer : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectForTransfer, non initialised
  //! it sorts nothing, unless an Actor has been defined
  Standard_EXPORT XSControl_SelectForTransfer();

  //! Creates a SelectForTransfer, which will work with the
  //! currently defined Actor brought by the TransferReader
  Standard_EXPORT XSControl_SelectForTransfer(const occ::handle<XSControl_TransferReader>& TR);

  //! Sets a TransferReader to sort entities : it brings the Actor,
  //! which may change, while the TransferReader does not
  Standard_EXPORT void SetReader(const occ::handle<XSControl_TransferReader>& TR);

  //! Sets a precise actor to sort entities
  //! This definition oversedes the creation with a TransferReader
  Standard_EXPORT void SetActor(const occ::handle<Transfer_ActorOfTransientProcess>& act);

  //! Returns the Actor used as precised one.
  //! Returns a Null Handle for a creation from a TransferReader
  //! without any further setting
  Standard_EXPORT occ::handle<Transfer_ActorOfTransientProcess> Actor() const;

  //! Returns the Reader (if created with a Reader)
  //! Returns a Null Handle if not created with a Reader
  Standard_EXPORT occ::handle<XSControl_TransferReader> Reader() const;

  //! Returns True for an Entity which is recognized by the Actor,
  //! either the precised one, or the one defined by TransferReader
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns a text defining the criterium : "Recognized for Transfer [(current actor)]"
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(XSControl_SelectForTransfer, IFSelect_SelectExtract)

private:
  occ::handle<XSControl_TransferReader>         theTR;
  occ::handle<Transfer_ActorOfTransientProcess> theAC;
};

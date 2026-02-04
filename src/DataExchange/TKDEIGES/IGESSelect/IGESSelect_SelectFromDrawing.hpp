#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! This selection gets in all the model, the entities which are
//! attached to the drawing(s) given as input. This includes :
//! - Drawing Frame (Annotations directky referenced by Drawings)
//! - Entities attached to the single Views referenced by Drawings
class IGESSelect_SelectFromDrawing : public IFSelect_SelectDeduct
{

public:
  //! Creates a SelectFromDrawing
  Standard_EXPORT IGESSelect_SelectFromDrawing();

  //! Selects the Entities which are attached to the Drawing(s)
  //! present in the Input
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns the label, with is "Entities attached to Drawing"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectFromDrawing, IFSelect_SelectDeduct)
};


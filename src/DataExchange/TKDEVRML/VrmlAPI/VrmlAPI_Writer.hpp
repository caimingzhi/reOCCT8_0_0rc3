// Created on: 2000-06-20
// Created by: Sergey MOZOKHIN
// Copyright (c) 2000-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _VrmlAPI_Writer_HeaderFile
#define _VrmlAPI_Writer_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
// Created on: 2000-05-30
// Created by: Sergey MOZOKHIN
// Copyright (c) 2000-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _VrmlAPI_RepresentationOfShape_HeaderFile
#define _VrmlAPI_RepresentationOfShape_HeaderFile

//! Identifies the representation of the shape written
//! to a VRML file. The available options are :
//! -      VrmlAPI_ShadedRepresentation :
//! the shape is translated with a shaded representation.
//! -      VrmlAPI_WireFrameRepresentation :
//! the shape is translated with a wireframe representation.
//! -      VrmlAPI_BothRepresentation : the shape is translated
//! to VRML format with both representations : shaded and
//! wireframe. This is the default option.
enum VrmlAPI_RepresentationOfShape
{
  VrmlAPI_ShadedRepresentation,
  VrmlAPI_WireFrameRepresentation,
  VrmlAPI_BothRepresentation
};

#endif // _VrmlAPI_RepresentationOfShape_HeaderFile

#include <Quantity_Color.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

class VrmlConverter_Drawer;
class VrmlConverter_Projector;
class Vrml_Material;
class TopoDS_Shape;
class TDocStd_Document;

//! Creates and writes VRML files from Open
//! CASCADE shapes. A VRML file can be written to
//! an existing VRML file or to a new one.
class VrmlAPI_Writer
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a writer object with default parameters.
  Standard_EXPORT VrmlAPI_Writer();

  //! Resets all parameters (representation, deflection)
  //! to their default values..
  Standard_EXPORT void ResetToDefaults();

  //! Returns drawer object
  Standard_EXPORT occ::handle<VrmlConverter_Drawer> Drawer() const;

  //! Sets the deflection aDef of
  //! the mesh algorithm which is used to compute the shaded
  //! representation of the translated shape. The default
  //! value is -1. When the deflection value is less than
  //! 0, the deflection is calculated from the relative
  //! size of the shaped.
  Standard_EXPORT void SetDeflection(const double aDef);

  //! Sets the representation of the
  //! shape aRep which is written to the VRML file. The three options are :
  //! -      shaded
  //! -      wireframe
  //! -      both shaded and wireframe (default)
  //! defined through the VrmlAPI_RepresentationOfShape enumeration.
  Standard_EXPORT void SetRepresentation(const VrmlAPI_RepresentationOfShape aRep);

  //! Set transparency to given material
  Standard_EXPORT void SetTransparencyToMaterial(occ::handle<Vrml_Material>& aMaterial,
                                                 const double                aTransparency);

  Standard_EXPORT void SetShininessToMaterial(occ::handle<Vrml_Material>& aMaterial,
                                              const double                aShininess);

  Standard_EXPORT void SetAmbientColorToMaterial(
    occ::handle<Vrml_Material>&                             aMaterial,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& Color);

  Standard_EXPORT void SetDiffuseColorToMaterial(
    occ::handle<Vrml_Material>&                             aMaterial,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& Color);

  Standard_EXPORT void SetSpecularColorToMaterial(
    occ::handle<Vrml_Material>&                             aMaterial,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& Color);

  Standard_EXPORT void SetEmissiveColorToMaterial(
    occ::handle<Vrml_Material>&                             aMaterial,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& Color);

  //! Returns the representation of the shape which is
  //! written to the VRML file. Types of representation are set through the
  //! VrmlAPI_RepresentationOfShape enumeration.
  Standard_EXPORT VrmlAPI_RepresentationOfShape GetRepresentation() const;

  Standard_EXPORT occ::handle<Vrml_Material> GetFrontMaterial() const;

  Standard_EXPORT occ::handle<Vrml_Material> GetPointsMaterial() const;

  Standard_EXPORT occ::handle<Vrml_Material> GetUisoMaterial() const;

  Standard_EXPORT occ::handle<Vrml_Material> GetVisoMaterial() const;

  Standard_EXPORT occ::handle<Vrml_Material> GetLineMaterial() const;

  Standard_EXPORT occ::handle<Vrml_Material> GetWireMaterial() const;

  Standard_EXPORT occ::handle<Vrml_Material> GetFreeBoundsMaterial() const;

  Standard_EXPORT occ::handle<Vrml_Material> GetUnfreeBoundsMaterial() const;

  //! Converts the shape aShape to
  //! VRML format of the passed version and writes it to the file identified by aFile.
  Standard_EXPORT bool Write(const TopoDS_Shape& aShape,
                             const char*         aFile,
                             const int           aVersion = 2) const;

  //! Converts the document to VRML format of the passed version
  //! and writes it to the file identified by aFile.
  Standard_EXPORT bool WriteDoc(const occ::handle<TDocStd_Document>& theDoc,
                                const char*                          theFile,
                                const double                         theScale) const;

  //! Converts the shape aShape to
  //! VRML format of the passed version and writes it to the given stream.
  Standard_EXPORT bool Write(const TopoDS_Shape& aShape,
                             Standard_OStream&   theOStream,
                             const int           aVersion = 2) const;

  //! Converts the document to VRML format of the passed version
  //! and writes it to the given stream.
  Standard_EXPORT bool WriteDoc(const occ::handle<TDocStd_Document>& theDoc,
                                Standard_OStream&                    theOStream,
                                const double                         theScale) const;

protected:
  //! Converts the shape aShape to VRML format of version 1.0 and writes it
  //! to the given stream using default parameters.
  Standard_EXPORT bool write_v1(const TopoDS_Shape& aShape, Standard_OStream& theOStream) const;

  //! Converts the shape aShape to VRML format of version 2.0 and writes it
  //! to the given stream using default parameters.
  Standard_EXPORT bool write_v2(const TopoDS_Shape& aShape, Standard_OStream& theOStream) const;

private:
  VrmlAPI_RepresentationOfShape        myRepresentation;
  occ::handle<VrmlConverter_Drawer>    myDrawer;
  double                               myDeflection;
  occ::handle<VrmlConverter_Projector> myPerespectiveCamera;
  occ::handle<VrmlConverter_Projector> myOrthographicCamera;
  double                               myTransparency;
  double                               myShininess;
  occ::handle<Vrml_Material>           myFrontMaterial;
  occ::handle<Vrml_Material>           myPointsMaterial;
  occ::handle<Vrml_Material>           myUisoMaterial;
  occ::handle<Vrml_Material>           myVisoMaterial;
  occ::handle<Vrml_Material>           myLineMaterial;
  occ::handle<Vrml_Material>           myWireMaterial;
  occ::handle<Vrml_Material>           myFreeBoundsMaterial;
  occ::handle<Vrml_Material>           myUnfreeBoundsMaterial;
  double                               DX;
  double                               DY;
  double                               DZ;
  double                               XUp;
  double                               YUp;
  double                               ZUp;
  double                               Focus;
};

#endif // _VrmlAPI_Writer_HeaderFile

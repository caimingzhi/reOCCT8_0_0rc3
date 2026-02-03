// Created on: 2014-08-13
// Created by: Maxim GLIBIN
// Copyright (c) 2014 OPEN CASCADE SAS
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

#ifndef _AIS_PointCloud_HeaderFile
#define _AIS_PointCloud_HeaderFile
// Created on: 1996-12-11
// Created by: Robert COUBLANC
// Copyright (c) 1996-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

#ifndef _AIS_HeaderFile
#define _AIS_HeaderFile

#include <Prs3d_Presentation.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

//! Application Interactive Services provide the means to create links between an application GUI
//! viewer and the packages which are used to manage selection and presentation. The tools AIS
//! defined in order to do this include different sorts of entities: both the selectable viewable
//! objects themselves and the context and attribute managers to define their selection and display.
//! To orient the user as he works in a modeling environment, views and selections must be
//! comprehensible. There must be several different sorts of selectable and viewable object defined.
//! These must also be interactive, that is, connecting graphic representation and the underlying
//! reference geometry. These entities are called Interactive Objects, and are divided into four
//! types:
//! -   the Datum
//! -   the Relation
//! -   the Object
//! -   None.
//! The Datum groups together the construction elements such as lines, circles, points, trihedra,
//! plane trihedra, planes and axes. The Relation is made up of constraints on one or more
//! interactive shapes and the corresponding reference geometry. For example, you might want to
//! constrain two edges in a parallel relation. This constraint is considered as an object in its
//! own right, and is shown as a sensitive primitive. This takes the graphic form of a perpendicular
//! arrow marked with the || symbol and lying between the two edges. The Object type includes
//! topological shapes, and connections between shapes. None, in order not to eliminate the object,
//! tells the application to look further until it finds an object definition in its generation
//! which is accepted. Inside these categories, you have the possibility of an additional
//! characterization by means of a signature. The signature provides an index to the further
//! characterization. By default, the Interactive Object has a None type and a signature of 0
//! (equivalent to None.) If you want to give a particular type and signature to your interactive
//! object, you must redefine the two virtual methods: Type and Signature. In the C++ inheritance
//! structure of the package, each class representing a specific Interactive Object inherits
//! AIS_InteractiveObject. Among these inheriting classes, PrsDim_Relation functions as the abstract
//! mother class for tinheriting classes defining display of specific relational constraints and
//! types of dimension. Some of these include:
//! -   display of constraints based on relations of symmetry, tangency, parallelism and
//! concentricity
//! -   display of dimensions for angles, offsets, diameters, radii and chamfers.
//! No viewer can show everything at once with any coherence or clarity.
//! Views must be managed carefully both sequentially and at any given instant.
//! Another function of the view is that of a context to carry out design in.
//! The design changes are applied to the objects in the view and then extended to the underlying
//! reference geometry by a solver. To make sense of this complicated visual data, several display
//! and selection tools are required. To facilitate management, each object and each construction
//! element has a selection priority. There are also means to modify the default priority. To define
//! an environment of dynamic detection, you can use standard filter classes or create your own. A
//! filter questions the owner of the sensitive primitive to determine if it has the desired
//! qualities. If it answers positively, it is kept. If not, it is rejected. The standard filters
//! supplied in AIS include:
//! - AIS_AttributeFilter
//! - AIS_SignatureFilter
//! - AIS_TypeFilter.
//! A set of functions allows you to choose the interactive objects which you want to act on, the
//! selection modes which you want to activate. An interactive object can have a certain number of
//! graphic attributes which are specific to it, such as visualization mode, color, and material. By
//! the same token, the interactive context has a set of graphic attributes, the Drawer which is
//! valid by default for the objects it controls. When an interactive object is visualized, the
//! required graphic attributes are first taken from the object's own Drawer if one exists, or from
//! the context drawer for the others.
class AIS
{
public:
  DEFINE_STANDARD_ALLOC
};

#endif // _AIS_HeaderFile

#include <AIS_InteractiveObject.hpp>
#include <Bnd_Box.hpp>
#include <Graphic3d_ArrayOfPoints.hpp>
#include <Quantity_Color.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>

class TColStd_HPackedMapOfInteger;

//! Interactive object for set of points.
//! The presentation supports two display modes:
//! - Points.
//! - Bounding box for highlighting.
//! Presentation provides selection by bounding box.
//! Selection and consequently highlighting can disabled by
//! setting default selection mode to -1. There will be no way
//! to select object from interactive view. Any calls to
//! AIS_InteractiveContext::AddOrRemoveSelected should be also prohibited,
//! to avoid programmatic highlighting (workaround is setting non-supported
//! hilight mode, e.g. 100);
class AIS_PointCloud : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_PointCloud, AIS_InteractiveObject)
public:
  //! Display modes supported by this Point Cloud object
  enum DisplayMode
  {
    DM_Points = 0, //!< display as normal points, default presentation
    DM_BndBox = 2  //!< display as bounding box,  default for highlighting
  };

  //! Selection modes supported by this Point Cloud object
  enum SelectionMode
  {
    SM_Points         = 0, //!< detected by points
    SM_SubsetOfPoints = 1, //!< detect point(s) within Point Cloud rather than object as whole
    SM_BndBox         = 2, //!< detected by bounding box
  };

public:
  //! Constructor.
  Standard_EXPORT AIS_PointCloud();

  //! Sets the points from array of points.
  //! Method will not copy the input data - array will be stored as handle.
  //! @param[in] thePoints  the array of points
  Standard_EXPORT virtual void SetPoints(const occ::handle<Graphic3d_ArrayOfPoints>& thePoints);

  //! Sets the points with optional colors.
  //! The input data will be copied into internal buffer.
  //! The input arrays should have equal length, otherwise
  //! the presentation will not be computed and displayed.
  //! @param[in] theCoords   the array of coordinates
  //! @param[in] theColors   optional array of colors
  //! @param[in] theNormals  optional array of normals
  Standard_EXPORT virtual void SetPoints(
    const occ::handle<NCollection_HArray1<gp_Pnt>>&         theCoords,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& theColors  = nullptr,
    const occ::handle<NCollection_HArray1<gp_Dir>>&         theNormals = nullptr);

public:
  //! Get the points array.
  //! Method might be overridden to fill in points array dynamically from application data
  //! structures.
  //! @return the array of points
  Standard_EXPORT virtual const occ::handle<Graphic3d_ArrayOfPoints> GetPoints() const;

  //! Get bounding box for presentation.
  Standard_EXPORT virtual Bnd_Box GetBoundingBox() const;

public:
  //! Setup custom color. Affects presentation only when no per-point color attribute has been
  //! assigned.
  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  //! Restore default color.
  Standard_EXPORT void UnsetColor() override;

  //! Setup custom material. Affects presentation only when normals are defined.
  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& theMat) override;

  //! Restore default material.
  Standard_EXPORT void UnsetMaterial() override;

protected:
  //! Prepare presentation for this object.
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  //! Prepare selection for this object.
  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

private:
  occ::handle<Graphic3d_ArrayOfPoints> myPoints; //!< points array for presentation
  Bnd_Box                              myBndBox; //!< bounding box for presentation
};

//! Custom owner for highlighting selected points.
class AIS_PointCloudOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(AIS_PointCloudOwner, SelectMgr_EntityOwner)
public:
  //! Main constructor.
  Standard_EXPORT AIS_PointCloudOwner(const occ::handle<AIS_PointCloud>& theOrigin);

  //! Destructor.
  Standard_EXPORT ~AIS_PointCloudOwner() override;

  //! Return selected points.
  //! WARNING! Indexation starts with 0 (shifted by -1 comparing to
  //! Graphic3d_ArrayOfPoints::Vertice()).
  const occ::handle<TColStd_HPackedMapOfInteger>& SelectedPoints() const { return mySelPoints; }

  //! Return last detected points.
  //! WARNING! Indexation starts with 0 (shifted by -1 comparing to
  //! Graphic3d_ArrayOfPoints::Vertice()).
  const occ::handle<TColStd_HPackedMapOfInteger>& DetectedPoints() const { return myDetPoints; }

  //! Always update dynamic highlighting.
  Standard_EXPORT bool IsForcedHilight() const override;

  //! Handle dynamic highlighting.
  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  //! Removes highlighting.
  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                 const int                                      theMode) override;

  //! Clears presentation.
  Standard_EXPORT void Clear(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                             const int                                      theMode) override;

protected:
  occ::handle<TColStd_HPackedMapOfInteger> myDetPoints; //!< last detected points
  occ::handle<TColStd_HPackedMapOfInteger> mySelPoints; //!< selected points
};

#endif // _AIS_PointCloud_HeaderFile

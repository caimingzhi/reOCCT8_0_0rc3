#pragma once

#include <Bnd_OBB.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Root.hpp>

//! Tool for computing bounding box presentation.
class Prs3d_BndBox : public Prs3d_Root
{
public:
  //! Computes presentation of a bounding box.
  //! @param[in] thePresentation  the presentation.
  //! @param[in] theBndBox  the bounding box.
  //! @param[in] theDrawer  the drawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const Bnd_Box&                         theBndBox,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer);

  //! Computes presentation of a bounding box.
  //! @param[in] thePresentation  the presentation.
  //! @param[in] theBndBox  the bounding box.
  //! @param[in] theDrawer  the drawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const Bnd_OBB&                         theBndBox,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer);

public:
  //! Create primitive array with line segments for displaying a box.
  //! @param[in] theBox  the box to add
  static occ::handle<Graphic3d_ArrayOfSegments> FillSegments(const Bnd_OBB& theBox)
  {
    if (theBox.IsVoid())
    {
      return occ::handle<Graphic3d_ArrayOfSegments>();
    }

    occ::handle<Graphic3d_ArrayOfSegments> aSegs = new Graphic3d_ArrayOfSegments(8, 12 * 2);
    FillSegments(aSegs, theBox);
    return aSegs;
  }

  //! Create primitive array with line segments for displaying a box.
  //! @param[in] theBox  the box to add
  static occ::handle<Graphic3d_ArrayOfSegments> FillSegments(const Bnd_Box& theBox)
  {
    if (theBox.IsVoid())
    {
      return occ::handle<Graphic3d_ArrayOfSegments>();
    }

    occ::handle<Graphic3d_ArrayOfSegments> aSegs = new Graphic3d_ArrayOfSegments(8, 12 * 2);
    FillSegments(aSegs, theBox);
    return aSegs;
  }

  //! Create primitive array with line segments for displaying a box.
  //! @param[in][out] theSegments   primitive array to be filled;
  //!                               should be at least 8 nodes and 24 edges in size
  //! @param[in] theBox  the box to add
  static void FillSegments(const occ::handle<Graphic3d_ArrayOfSegments>& theSegments,
                           const Bnd_OBB&                                theBox)
  {
    if (!theBox.IsVoid())
    {
      gp_Pnt aXYZ[8];
      theBox.GetVertex(aXYZ);
      fillSegments(theSegments, aXYZ);
    }
  }

  //! Create primitive array with line segments for displaying a box.
  //! @param[in][out] theSegments   primitive array to be filled;
  //!                               should be at least 8 nodes and 24 edges in size
  //! @param[in] theBox  the box to add
  static void FillSegments(const occ::handle<Graphic3d_ArrayOfSegments>& theSegments,
                           const Bnd_Box&                                theBox)
  {
    if (!theBox.IsVoid())
    {
      const gp_Pnt aMin    = theBox.CornerMin();
      const gp_Pnt aMax    = theBox.CornerMax();
      const gp_Pnt aXYZ[8] = {
        gp_Pnt(aMin.X(), aMin.Y(), aMin.Z()),
        gp_Pnt(aMax.X(), aMin.Y(), aMin.Z()),
        gp_Pnt(aMin.X(), aMax.Y(), aMin.Z()),
        gp_Pnt(aMax.X(), aMax.Y(), aMin.Z()),
        gp_Pnt(aMin.X(), aMin.Y(), aMax.Z()),
        gp_Pnt(aMax.X(), aMin.Y(), aMax.Z()),
        gp_Pnt(aMin.X(), aMax.Y(), aMax.Z()),
        gp_Pnt(aMax.X(), aMax.Y(), aMax.Z()),
      };
      fillSegments(theSegments, aXYZ);
    }
  }

public:
  //! Create primitive array with line segments for displaying a box.
  //! @param[in][out] theSegments   primitive array to be filled;
  //!                               should be at least 8 nodes and 24 edges in size
  //! @param[in] theBox  the box to add
  static void fillSegments(const occ::handle<Graphic3d_ArrayOfSegments>& theSegments,
                           const gp_Pnt*                                 theBox)
  {
    const int aFrom = theSegments->VertexNumber();
    for (int aVertIter = 0; aVertIter < 8; ++aVertIter)
    {
      theSegments->AddVertex(theBox[aVertIter]);
    }

    theSegments->AddEdges(aFrom + 1, aFrom + 2);
    theSegments->AddEdges(aFrom + 3, aFrom + 4);
    theSegments->AddEdges(aFrom + 5, aFrom + 6);
    theSegments->AddEdges(aFrom + 7, aFrom + 8);
    //
    theSegments->AddEdges(aFrom + 1, aFrom + 3);
    theSegments->AddEdges(aFrom + 2, aFrom + 4);
    theSegments->AddEdges(aFrom + 5, aFrom + 7);
    theSegments->AddEdges(aFrom + 6, aFrom + 8);
    //
    theSegments->AddEdges(aFrom + 1, aFrom + 5);
    theSegments->AddEdges(aFrom + 2, aFrom + 6);
    theSegments->AddEdges(aFrom + 3, aFrom + 7);
    theSegments->AddEdges(aFrom + 4, aFrom + 8);
  }
};

#pragma once

#include <IMeshTools_CurveTessellator.hpp>

#include <IMeshData_Types.hpp>
#include <IMeshData_Edge.hpp>
#include <IMeshData_Face.hpp>
#include <TopoDS.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Extrema_LocateExtPC.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <Adaptor3d_CurveOnSurface.hpp>
#include <Geom2dAdaptor_Curve.hpp>

class gp_Pnt;
class TopoDS_Edge;
class TopoDS_Face;

//! Auxiliary class provides correct parameters
//! on curve regarding SameParameter flag.
template <class ParametersCollection>
class BRepMesh_EdgeParameterProvider : public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor. Initializes empty provider.
  BRepMesh_EdgeParameterProvider()
      : myIsSameParam(false),
        myFirstParam(0.0),
        myOldFirstParam(0.0),
        myScale(0.0),
        myCurParam(0.0),
        myFoundParam(0.0)
  {
  }

  //! Constructor.
  //! @param theEdge edge which parameters should be processed.
  //! @param theFace face the parametric values are defined for.
  //! @param theParameters parameters corresponded to discretization points.
  BRepMesh_EdgeParameterProvider(const IMeshData::IEdgeHandle& theEdge,
                                 const TopAbs_Orientation      theOrientation,
                                 const IMeshData::IFaceHandle& theFace,
                                 const ParametersCollection&   theParameters)
  {
    Init(theEdge, theOrientation, theFace, theParameters);
  }

  //! Initialized provider by the given data.
  void Init(const IMeshData::IEdgeHandle& theEdge,
            const TopAbs_Orientation      theOrientation,
            const IMeshData::IFaceHandle& theFace,
            const ParametersCollection&   theParameters)
  {
    myParameters  = theParameters;
    myIsSameParam = theEdge->GetSameParam();
    myScale       = 1.;

    // Extract actual parametric values
    const TopoDS_Edge aEdge = TopoDS::Edge(theEdge->GetEdge().Oriented(theOrientation));

    myCurveAdaptor.Initialize(aEdge, theFace->GetFace());
    if (myIsSameParam)
    {
      return;
    }

    myFirstParam            = myCurveAdaptor.FirstParameter();
    const double aLastParam = myCurveAdaptor.LastParameter();

    myFoundParam = myCurParam = myFirstParam;

    // Extract parameters stored in polygon
    myOldFirstParam            = myParameters->Value(myParameters->Lower());
    const double aOldLastParam = myParameters->Value(myParameters->Upper());

    // Calculate scale factor between actual and stored parameters
    if ((myOldFirstParam != myFirstParam || aOldLastParam != aLastParam)
        && myOldFirstParam != aOldLastParam)
    {
      myScale = (aLastParam - myFirstParam) / (aOldLastParam - myOldFirstParam);
    }

    myProjector.Initialize(myCurveAdaptor,
                           myCurveAdaptor.FirstParameter(),
                           myCurveAdaptor.LastParameter(),
                           Precision::PConfusion());
  }

  //! Returns parameter according to SameParameter flag of the edge.
  //! If SameParameter is TRUE returns value from parameters w/o changes,
  //! elsewhere scales initial parameter and tries to determine resulting
  //! value using projection of the corresponded 3D point on PCurve.
  double Parameter(const int theIndex, const gp_Pnt& thePoint3d) const
  {
    if (myIsSameParam)
    {
      return myParameters->Value(theIndex);
    }

    // Use scaled
    const double aParam = myParameters->Value(theIndex);

    const double aPrevParam = myCurParam;
    myCurParam              = myFirstParam + myScale * (aParam - myOldFirstParam);

    const double aPrevFoundParam = myFoundParam;
    myFoundParam += (myCurParam - aPrevParam);

    myProjector.Perform(thePoint3d, myFoundParam);
    if (myProjector.IsDone())
    {
      const double aFoundParam = myProjector.Point().Parameter();
      if ((aPrevFoundParam < myFoundParam && aPrevFoundParam < aFoundParam)
          || (aPrevFoundParam > myFoundParam && aPrevFoundParam > aFoundParam))
      {
        // Rude protection against case when amplified parameter goes before
        // previous one due to period or other reason occurred in projector.
        // Using parameter returned by projector as is can produce self-intersections.
        myFoundParam = aFoundParam;
      }
    }

    return myFoundParam;
  }

  //! Returns pcurve used to compute parameters.
  const occ::handle<Adaptor2d_Curve2d>& GetPCurve() const
  {
    return myCurveAdaptor.CurveOnSurface().GetCurve();
  }

private:
  ParametersCollection myParameters;

  bool   myIsSameParam;
  double myFirstParam;

  double myOldFirstParam;
  double myScale;

  mutable double myCurParam;
  mutable double myFoundParam;

  BRepAdaptor_Curve myCurveAdaptor;

  mutable Extrema_LocateExtPC myProjector;
};

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <TopLoc_Location.hpp>

//! Auxiliary class implements functionality retrieving tessellated
//! representation of an edge stored in polygon.
class BRepMesh_EdgeTessellationExtractor : public IMeshTools_CurveTessellator
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_EdgeTessellationExtractor(const IMeshData::IEdgeHandle& theEdge,
                                                     const IMeshData::IFaceHandle& theFace);

  //! Destructor.
  Standard_EXPORT ~BRepMesh_EdgeTessellationExtractor() override;

  //! Returns number of tessellation points.
  Standard_EXPORT int PointsNb() const override;

  //! Returns parameters of solution with the given index.
  //! @param theIndex index of tessellation point.
  //! @param theParameter parameters on PCurve corresponded to the solution.
  //! @param thePoint tessellation point.
  //! @return True in case of valid result, false elewhere.
  Standard_EXPORT bool Value(const int theIndex,
                             gp_Pnt&   thePoint,
                             double&   theParameter) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_EdgeTessellationExtractor, IMeshTools_CurveTessellator)

private:
  BRepMesh_EdgeParameterProvider<occ::handle<NCollection_HArray1<double>>> myProvider;
  const Poly_Triangulation*                                                myTriangulation;
  const NCollection_Array1<int>*                                           myIndices;
  TopLoc_Location                                                          myLoc;
};

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

template <class ParametersCollection>
class BRepMesh_EdgeParameterProvider : public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC

  BRepMesh_EdgeParameterProvider()
      : myIsSameParam(false),
        myFirstParam(0.0),
        myOldFirstParam(0.0),
        myScale(0.0),
        myCurParam(0.0),
        myFoundParam(0.0)
  {
  }

  BRepMesh_EdgeParameterProvider(const IMeshData::IEdgeHandle& theEdge,
                                 const TopAbs_Orientation      theOrientation,
                                 const IMeshData::IFaceHandle& theFace,
                                 const ParametersCollection&   theParameters)
  {
    Init(theEdge, theOrientation, theFace, theParameters);
  }

  void Init(const IMeshData::IEdgeHandle& theEdge,
            const TopAbs_Orientation      theOrientation,
            const IMeshData::IFaceHandle& theFace,
            const ParametersCollection&   theParameters)
  {
    myParameters  = theParameters;
    myIsSameParam = theEdge->GetSameParam();
    myScale       = 1.;

    const TopoDS_Edge aEdge = TopoDS::Edge(theEdge->GetEdge().Oriented(theOrientation));

    myCurveAdaptor.Initialize(aEdge, theFace->GetFace());
    if (myIsSameParam)
    {
      return;
    }

    myFirstParam            = myCurveAdaptor.FirstParameter();
    const double aLastParam = myCurveAdaptor.LastParameter();

    myFoundParam = myCurParam = myFirstParam;

    myOldFirstParam            = myParameters->Value(myParameters->Lower());
    const double aOldLastParam = myParameters->Value(myParameters->Upper());

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

  double Parameter(const int theIndex, const gp_Pnt& thePoint3d) const
  {
    if (myIsSameParam)
    {
      return myParameters->Value(theIndex);
    }

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

        myFoundParam = aFoundParam;
      }
    }

    return myFoundParam;
  }

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

class BRepMesh_EdgeTessellationExtractor : public IMeshTools_CurveTessellator
{
public:
  Standard_EXPORT BRepMesh_EdgeTessellationExtractor(const IMeshData::IEdgeHandle& theEdge,
                                                     const IMeshData::IFaceHandle& theFace);

  Standard_EXPORT ~BRepMesh_EdgeTessellationExtractor() override;

  Standard_EXPORT int PointsNb() const override;

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

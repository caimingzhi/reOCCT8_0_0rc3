#pragma once

#include <NCollection_Handle.hpp>
#include <NCollection_Array1.hpp>

template <typename T>
class math_VectorBase;
using math_Vector = math_VectorBase<double>;

class BRepGProp_Gauss
{

  struct Inertia
  {

    double Mass;

    double Ix;
    double Iy;
    double Iz;

    double Ixx;
    double Iyy;
    double Izz;
    double Ixy;
    double Ixz;
    double Iyz;

    Inertia();

    void Reset();
  };

  typedef NCollection_Handle<NCollection_Array1<Inertia>> InertiaArray;
  typedef double (*BRepGProp_GaussFunc)(const double, const double);

public:
  typedef enum
  {
    Vinert = 0,
    Sinert
  } BRepGProp_GaussType;

  Standard_EXPORT explicit BRepGProp_Gauss(const BRepGProp_GaussType theType);

  Standard_EXPORT void Compute(const BRepGProp_Face& theSurface,
                               const gp_Pnt&         theLocation,
                               const double          theCoeff[],
                               const bool            theIsByPoint,
                               double&               theOutMass,
                               gp_Pnt&               theOutGravityCenter,
                               gp_Mat&               theOutInertia);

  Standard_EXPORT void Compute(const BRepGProp_Face& theSurface,
                               const gp_Pnt&         theLocation,
                               double&               theOutMass,
                               gp_Pnt&               theOutGravityCenter,
                               gp_Mat&               theOutInertia);

  Standard_EXPORT void Compute(BRepGProp_Face&   theSurface,
                               BRepGProp_Domain& theDomain,
                               const gp_Pnt&     theLocation,
                               const double      theCoeff[],
                               const bool        theIsByPoint,
                               double&           theOutMass,
                               gp_Pnt&           theOutGravityCenter,
                               gp_Mat&           theOutInertia);

  Standard_EXPORT void Compute(BRepGProp_Face&   theSurface,
                               BRepGProp_Domain& theDomain,
                               const gp_Pnt&     theLocation,
                               double&           theOutMass,
                               gp_Pnt&           theOutGravityCenter,
                               gp_Mat&           theOutInertia);

  Standard_EXPORT double Compute(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const gp_Pnt&     theLocation,
                                 const double      theEps,
                                 const double      theCoeff[],
                                 const bool        theByPoint,
                                 double&           theOutMass,
                                 gp_Pnt&           theOutGravityCenter,
                                 gp_Mat&           theOutInertia);

  Standard_EXPORT double Compute(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const gp_Pnt&     theLocation,
                                 const double      theEps,
                                 double&           theOutMass,
                                 gp_Pnt&           theOutGravityCenter,
                                 gp_Mat&           theOutInertia);

private:
  BRepGProp_Gauss(BRepGProp_Gauss const&)            = delete;
  BRepGProp_Gauss& operator=(BRepGProp_Gauss const&) = delete;

  void computeVInertiaOfElementaryPart(const gp_Pnt&             thePoint,
                                       const gp_Vec&             theNormal,
                                       const gp_Pnt&             theLocation,
                                       const double              theWeight,
                                       const double              theCoeff[],
                                       const bool                theIsByPoint,
                                       BRepGProp_Gauss::Inertia& theOutInertia);

  void computeSInertiaOfElementaryPart(const gp_Pnt&             thePoint,
                                       const gp_Vec&             theNormal,
                                       const gp_Pnt&             theLocation,
                                       const double              theWeight,
                                       BRepGProp_Gauss::Inertia& theOutInertia);

  void checkBounds(const double theU1, const double theU2, const double theV1, const double theV2);

  void addAndRestoreInertia(const BRepGProp_Gauss::Inertia& theInInertia,
                            BRepGProp_Gauss::Inertia&       theOutInertia);

  void multAndRestoreInertia(const double theValue, BRepGProp_Gauss::Inertia& theInertia);

  void convert(const BRepGProp_Gauss::Inertia& theInertia,
               gp_Pnt&                         theOutGravityCenter,
               gp_Mat&                         theOutMatrixOfInertia,
               double&                         theOutMass);

  void convert(const BRepGProp_Gauss::Inertia& theInertia,
               const double                    theCoeff[],
               const bool                      theIsByPoint,
               gp_Pnt&                         theOutGravityCenter,
               gp_Mat&                         theOutMatrixOfInertia,
               double&                         theOutMass);

  static int MaxSubs(const int theN, const int theCoeff = 32);

  static void Init(NCollection_Handle<math_Vector>& theOutVec,
                   const double                     theValue,
                   const int                        theFirst = 0,
                   const int                        theLast  = 0);

  static void InitMass(const double  theValue,
                       const int     theFirst,
                       const int     theLast,
                       InertiaArray& theArray);

  static int FillIntervalBounds(const double                      theA,
                                const double                      theB,
                                const NCollection_Array1<double>& theKnots,
                                const int                         theNumSubs,
                                InertiaArray&                     theInerts,
                                NCollection_Handle<math_Vector>&  theParam1,
                                NCollection_Handle<math_Vector>&  theParam2,
                                NCollection_Handle<math_Vector>&  theError,
                                NCollection_Handle<math_Vector>&  theCommonError);

private:
  BRepGProp_GaussType myType;
  BRepGProp_GaussFunc add;
  BRepGProp_GaussFunc mult;
};

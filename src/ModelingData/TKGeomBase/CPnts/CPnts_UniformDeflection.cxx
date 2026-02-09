

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Curve.hpp>
#include <CPnts_UniformDeflection.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <StdFail_NotDone.hpp>

static inline void D03d(void* const C, const double U, gp_Pnt& P)
{
  ((Adaptor3d_Curve*)C)->D0(U, P);
}

static void D02d(void* const C, const double U, gp_Pnt& PP)
{
  gp_Pnt2d P;
  ((Adaptor2d_Curve2d*)C)->D0(U, P);
  PP.SetCoord(P.X(), P.Y(), 0.);
}

static inline void D23d(void* const C, const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2)
{
  ((Adaptor3d_Curve*)C)->D2(U, P, V1, V2);
}

static void D22d(void* const C, const double U, gp_Pnt& PP, gp_Vec& VV1, gp_Vec& VV2)
{
  gp_Pnt2d P;
  gp_Vec2d V1, V2;
  ((Adaptor2d_Curve2d*)C)->D2(U, P, V1, V2);
  PP.SetCoord(P.X(), P.Y(), 0.);
  VV1.SetCoord(V1.X(), V1.Y(), 0.);
  VV2.SetCoord(V2.X(), V2.Y(), 0.);
}

void CPnts_UniformDeflection::Perform()
{
  gp_Pnt P, P1, P2;
  gp_Vec V1, V2, VV;
  double Un1;
  double NormD1, NormD2;

  myIPoint   = -1;
  myNbPoints = -1;

  const double anEspilon = Epsilon(myFirstParam);

  while ((myNbPoints < 2) && (!myFinish))
  {
    ++myNbPoints;
    myParams[myNbPoints] = myFirstParam;

    if (my3d)
    {
      D23d(myCurve, myFirstParam, myPoints[myNbPoints], V1, V2);
    }
    else
    {
      D22d(myCurve, myFirstParam, myPoints[myNbPoints], V1, V2);
    }
    P      = myPoints[myNbPoints];
    NormD1 = V1.Magnitude();
    if (NormD1 < myTolCur || V2.Magnitude() < myTolCur)
    {

      myDu = std::min(myDwmax, 1.5 * myDu);
    }
    else
    {
      NormD2 = V2.CrossMagnitude(V1);
      if (NormD2 / NormD1 < myDeflection)
      {

        myDu = std::min(myDwmax, 1.5 * myDu);
      }
      else
      {
        myDu = std::sqrt(8. * myDeflection * NormD1 / NormD2);
        myDu = std::min(std::max(myDu, myTolCur), myDwmax);
      }
    }

    if (myControl)
    {
      myDu = std::min(myDu, myLastParam - myFirstParam);
      if (my3d)
      {
        D03d(myCurve, myFirstParam + myDu, P);
        D03d(myCurve, myFirstParam + (myDu / 2.0), P1);
      }
      else
      {
        D02d(myCurve, myFirstParam + myDu, P);
        D02d(myCurve, myFirstParam + (myDu / 2.0), P1);
      }
      V1     = gp_Vec(myPoints[myNbPoints], P);
      NormD1 = V1.Magnitude();
      if (NormD1 >= myDeflection)
      {
        V2     = gp_Vec(myPoints[myNbPoints], P1);
        NormD2 = V2.CrossMagnitude(V1) / NormD1;

        if (NormD2 > myDeflection / 5.0)
        {
          NormD2 = std::max(NormD2, 1.1 * myDeflection);
          myDu   = myDu * std::sqrt(myDeflection / NormD2);
          myDu   = std::min(std::max(myDu, myTolCur), myDwmax);
        }
      }
    }
    myFirstParam += myDu;
    myFinish = myLastParam - myFirstParam < myTolCur || std::abs(myDu) < myTolCur ||

               myDu < anEspilon;
  }
  if (myFinish)
  {

    if (myControl && (myNbPoints == 1))
    {
      Un1 = myParams[0];
      if (myLastParam - Un1 < 0.33 * (myLastParam - myFirstParam))
      {
        myFirstParam = (myLastParam + Un1) / 2.0;
        myParams[0]  = myFirstParam;
        myParams[1]  = myLastParam;
        if (my3d)
        {
          D03d(myCurve, myParams[0], myPoints[0]);
          D03d(myCurve, myParams[1], myPoints[1]);
        }
        else
        {
          D02d(myCurve, myParams[0], myPoints[0]);
          D02d(myCurve, myParams[1], myPoints[1]);
        }
      }
      else
      {
        if (my3d)
        {
          D23d(myCurve, myLastParam, P1, V1, V2);
        }
        else
        {
          D22d(myCurve, myLastParam, P1, V1, V2);
        }
        P      = myPoints[0];
        VV     = gp_Vec(P1, P);
        NormD1 = VV.Magnitude();
        if (NormD1 < myDeflection)
        {
          myParams[1] = myLastParam;
          myPoints[1] = P1;
        }
        else
        {
          myFirstParam = (myLastParam * (myParams[1] - Un1) + Un1 * myDu) / (myFirstParam - Un1);
          if (my3d)
          {
            D03d(myCurve, myFirstParam, P2);
          }
          else
          {
            D02d(myCurve, myFirstParam, P2);
          }
          if ((VV.CrossMagnitude(gp_Vec(P2, P)) / NormD1 < myDeflection)
              && (Un1 >= myLastParam - myDwmax))
          {

            myParams[1] = myLastParam;
            myPoints[1] = P1;
          }
          else
          {
            myParams[1] = myFirstParam;
            myPoints[1] = P2;
            myParams[2] = myLastParam;
            myPoints[2] = P1;
            ++myNbPoints;
          }
        }
      }
    }
    else
    {
      ++myNbPoints;
      if (myNbPoints >= 3)
      {
        myNbPoints = 2;
      }
      myParams[myNbPoints] = myLastParam;
      if (my3d)
      {
        D03d(myCurve, myLastParam, myPoints[myNbPoints]);
      }
      else
      {
        D02d(myCurve, myLastParam, myPoints[myNbPoints]);
      }
    }
  }
}

CPnts_UniformDeflection::CPnts_UniformDeflection()
    : myDone(false),
      my3d(false),
      myFinish(false),
      myTolCur(0.0),
      myControl(false),
      myIPoint(0),
      myNbPoints(0),
      myDwmax(0.0),
      myDeflection(0.0),
      myFirstParam(0.0),
      myLastParam(0.0),
      myDu(0.0)
{
  memset(myParams, 0, sizeof(myParams));
}

CPnts_UniformDeflection::CPnts_UniformDeflection(const Adaptor3d_Curve& C,
                                                 const double           Deflection,
                                                 const double           Resolution,
                                                 const bool             WithControl)
{
  Initialize(C, Deflection, Resolution, WithControl);
}

CPnts_UniformDeflection::CPnts_UniformDeflection(const Adaptor2d_Curve2d& C,
                                                 const double             Deflection,
                                                 const double             Resolution,
                                                 const bool               WithControl)
{
  Initialize(C, Deflection, Resolution, WithControl);
}

void CPnts_UniformDeflection::Initialize(const Adaptor3d_Curve& C,
                                         const double           Deflection,
                                         const double           Resolution,
                                         const bool             WithControl)
{
  Initialize(C, Deflection, C.FirstParameter(), C.LastParameter(), Resolution, WithControl);
}

void CPnts_UniformDeflection::Initialize(const Adaptor2d_Curve2d& C,
                                         const double             Deflection,
                                         const double             Resolution,
                                         const bool               WithControl)
{
  Initialize(C, Deflection, C.FirstParameter(), C.LastParameter(), Resolution, WithControl);
}

CPnts_UniformDeflection ::CPnts_UniformDeflection(const Adaptor3d_Curve& C,
                                                  const double           Deflection,
                                                  const double           U1,
                                                  const double           U2,
                                                  const double           Resolution,
                                                  const bool             WithControl)
{
  Initialize(C, Deflection, U1, U2, Resolution, WithControl);
}

CPnts_UniformDeflection ::CPnts_UniformDeflection(const Adaptor2d_Curve2d& C,
                                                  const double             Deflection,
                                                  const double             U1,
                                                  const double             U2,
                                                  const double             Resolution,
                                                  const bool               WithControl)
{
  Initialize(C, Deflection, U1, U2, Resolution, WithControl);
}

void CPnts_UniformDeflection::Initialize(const Adaptor3d_Curve& C,
                                         const double           Deflection,
                                         const double           U1,
                                         const double           U2,
                                         const double           Resolution,
                                         const bool             WithControl)
{
  if (U1 > U2)
  {
    myFirstParam = U2;
    myLastParam  = U1;
  }
  else
  {
    myFirstParam = U1;
    myLastParam  = U2;
  }
  my3d         = true;
  myDwmax      = myLastParam - myFirstParam;
  myDu         = myDwmax / 2.;
  myDone       = true;
  myCurve      = (void*)&C;
  myFinish     = false;
  myTolCur     = Resolution;
  myDeflection = Deflection;
  myControl    = WithControl;
  Perform();
}

void CPnts_UniformDeflection::Initialize(const Adaptor2d_Curve2d& C,
                                         const double             Deflection,
                                         const double             U1,
                                         const double             U2,
                                         const double             Resolution,
                                         const bool               WithControl)
{
  if (U1 > U2)
  {
    myFirstParam = U2;
    myLastParam  = U1;
  }
  else
  {
    myFirstParam = U1;
    myLastParam  = U2;
  }
  my3d         = false;
  myDwmax      = myLastParam - myFirstParam;
  myDu         = myDwmax / 2.;
  myDone       = true;
  myCurve      = (void*)&C;
  myFinish     = false;
  myTolCur     = Resolution;
  myDeflection = Deflection;
  myControl    = WithControl;
  Perform();
}

bool CPnts_UniformDeflection::More()
{
  if (!myDone)
  {
    return false;
  }
  else if (myIPoint == myNbPoints)
  {
    if (myFinish)
    {
      return false;
    }
    else
    {
      Perform();
      return myDone;
    }
  }
  else
  {
    return myIPoint < myNbPoints;
  }
}

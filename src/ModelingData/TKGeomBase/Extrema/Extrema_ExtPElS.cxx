

#include <ElSLib.hpp>
#include <Extrema_ExtPElS.hpp>
#include <Extrema_POnSurf.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

static const double ExtPElS_MyEps = Epsilon(2. * M_PI);

Extrema_ExtPElS::Extrema_ExtPElS()
{
  myDone  = false;
  myNbExt = 0;
  for (int i = 0; i < 4; i++)
  {
    mySqDist[i] = RealLast();
  }
}

Extrema_ExtPElS::Extrema_ExtPElS(const gp_Pnt& P, const gp_Cylinder& S, const double Tol)
{

  Perform(P, S, Tol);
}

void Extrema_ExtPElS::Perform(const gp_Pnt& P, const gp_Cylinder& S, const double Tol)
{
  myDone  = false;
  myNbExt = 0;

  gp_Ax3 Pos = S.Position();
  gp_Pnt O   = Pos.Location();
  gp_Vec OZ(Pos.Direction());
  double V  = gp_Vec(O, P).Dot(OZ);
  gp_Pnt Pp = P.Translated(OZ.Multiplied(-V));

  gp_Vec OPp(O, Pp);
  if (OPp.Magnitude() < Tol)
  {
    return;
  }
  gp_Vec myZ = Pos.XDirection() ^ Pos.YDirection();
  double U1  = gp_Vec(Pos.XDirection()).AngleWithRef(OPp, myZ);
  if (U1 > -ExtPElS_MyEps && U1 < ExtPElS_MyEps)
  {
    U1 = 0.;
  }
  double U2 = U1 + M_PI;
  if (U1 < 0.)
  {
    U1 += 2. * M_PI;
  }

  gp_Pnt Ps;
  Ps          = ElSLib::Value(U1, V, S);
  mySqDist[0] = Ps.SquareDistance(P);
  myPoint[0]  = Extrema_POnSurf(U1, V, Ps);
  Ps          = ElSLib::Value(U2, V, S);
  mySqDist[1] = Ps.SquareDistance(P);
  myPoint[1]  = Extrema_POnSurf(U2, V, Ps);

  myNbExt = 2;
  myDone  = true;
}

Extrema_ExtPElS::Extrema_ExtPElS(const gp_Pnt& P, const gp_Cone& S, const double Tol)
{
  Perform(P, S, Tol);
}

void Extrema_ExtPElS::Perform(const gp_Pnt& P, const gp_Cone& S, const double Tol)
{
  myDone  = false;
  myNbExt = 0;

  gp_Pnt M   = S.Apex();
  gp_Ax3 Pos = S.Position();
  gp_Pnt O   = Pos.Location();
  double A   = S.SemiAngle();
  gp_Vec OZ(Pos.Direction());
  gp_Vec myZ = Pos.XDirection() ^ Pos.YDirection();
  gp_Vec MP(M, P);

  double L2 = MP.SquareMagnitude();
  double Vm = -(S.RefRadius() / std::sin(A));

  if (L2 < Tol * Tol)
  {
    mySqDist[0] = L2;
    myPoint[0]  = Extrema_POnSurf(0., Vm, M);
    myNbExt     = 1;
    myDone      = true;
    return;
  }
  gp_Vec DirZ;
  if (M.SquareDistance(O) < Tol * Tol)
  {
    DirZ = (A < 0 ? -OZ : OZ);
  }
  else
    DirZ = gp_Vec(M, O);

  double Zp = gp_Vec(O, P).Dot(OZ);

  gp_Pnt Pp = P.Translated(OZ.Multiplied(-Zp));
  gp_Vec OPp(O, Pp);
  if (OPp.SquareMagnitude() < Tol * Tol)
    return;
  double U1, V1, U2, V2;
  bool   Same = DirZ.Dot(MP) >= 0.0;
  U1          = gp_Vec(Pos.XDirection()).AngleWithRef(OPp, myZ);
  if (U1 > -ExtPElS_MyEps && U1 < ExtPElS_MyEps)
  {
    U1 = 0.;
  }
  if (!Same)
  {
    U1 += M_PI;
  }
  U2 = U1 + M_PI;
  if (U1 < 0.)
  {
    U1 += 2. * M_PI;
  }
  if (U2 > 2. * M_PI)
  {
    U2 -= 2. * M_PI;
  }
  double B = MP.Angle(DirZ);
  A        = std::abs(A);
  double L = sqrt(L2);
  if (!Same)
  {
    B  = M_PI - B;
    V1 = -L * cos(B - A);
    V2 = -L * cos(B + A);
  }
  else
  {
    V1 = L * cos(B - A);
    V2 = L * cos(B + A);
  }
  double Sense = OZ.Dot(gp_Dir(DirZ));
  V1 *= Sense;
  V2 *= Sense;
  V1 += Vm;
  V2 += Vm;

  gp_Pnt Ps;
  Ps          = ElSLib::Value(U1, V1, S);
  mySqDist[0] = Ps.SquareDistance(P);
  myPoint[0]  = Extrema_POnSurf(U1, V1, Ps);
  Ps          = ElSLib::Value(U2, V2, S);
  mySqDist[1] = Ps.SquareDistance(P);
  myPoint[1]  = Extrema_POnSurf(U2, V2, Ps);

  myNbExt = 2;
  myDone  = true;
}

Extrema_ExtPElS::Extrema_ExtPElS(const gp_Pnt& P, const gp_Sphere& S, const double Tol)
{
  Perform(P, S, Tol);
}

void Extrema_ExtPElS::Perform(const gp_Pnt& P, const gp_Sphere& S, const double Tol)
{
  myDone  = false;
  myNbExt = 0;

  gp_Ax3 Pos = S.Position();
  gp_Vec OP(Pos.Location(), P);

  if (OP.SquareMagnitude() < Tol * Tol)
  {
    return;
  }

  gp_Pnt O = Pos.Location();
  gp_Vec OZ(Pos.Direction());
  double Zp = OP.Dot(OZ);
  gp_Pnt Pp = P.Translated(OZ.Multiplied(-Zp));

  gp_Vec OPp(O, Pp);
  double U1, U2, V;
  if (OPp.SquareMagnitude() < Tol * Tol)
  {
    U1 = 0.;
    U2 = 0.;
    if (Zp < 0.)
    {
      V = -M_PI / 2.;
    }
    else
    {
      V = M_PI / 2.;
    }
  }
  else
  {
    gp_Vec myZ = Pos.XDirection() ^ Pos.YDirection();
    U1         = gp_Vec(Pos.XDirection()).AngleWithRef(OPp, myZ);
    if (U1 > -ExtPElS_MyEps && U1 < ExtPElS_MyEps)
    {
      U1 = 0.;
    }
    U2 = U1 + M_PI;
    if (U1 < 0.)
    {
      U1 += 2. * M_PI;
    }
    V = OP.Angle(OPp);
    if (Zp < 0.)
    {
      V = -V;
    }
  }

  gp_Pnt Ps;
  Ps          = ElSLib::Value(U1, V, S);
  mySqDist[0] = Ps.SquareDistance(P);
  myPoint[0]  = Extrema_POnSurf(U1, V, Ps);
  Ps          = ElSLib::Value(U2, -V, S);
  mySqDist[1] = Ps.SquareDistance(P);
  myPoint[1]  = Extrema_POnSurf(U2, -V, Ps);

  myNbExt = 2;
  myDone  = true;
}

Extrema_ExtPElS::Extrema_ExtPElS(const gp_Pnt& P, const gp_Torus& S, const double Tol)
{
  Perform(P, S, Tol);
}

void Extrema_ExtPElS::Perform(const gp_Pnt& P, const gp_Torus& S, const double Tol)
{
  const double tol2 = Tol * Tol;
  myDone            = false;
  myNbExt           = 0;

  gp_Ax3 Pos = S.Position();
  gp_Pnt O   = Pos.Location();
  gp_Vec OZ(Pos.Direction());
  gp_Pnt Pp = P.Translated(OZ.Multiplied(-(gp_Vec(O, P).Dot(Pos.Direction()))));

  gp_Vec OPp(O, Pp);
  double R2 = OPp.SquareMagnitude();
  if (R2 < tol2)
  {
    return;
  }

  gp_Vec myZ = Pos.XDirection() ^ Pos.YDirection();
  double U1  = gp_Vec(Pos.XDirection()).AngleWithRef(OPp, myZ);
  if (U1 > -ExtPElS_MyEps && U1 < ExtPElS_MyEps)
  {
    U1 = 0.;
  }
  double U2 = U1 + M_PI;
  if (U1 < 0.)
  {
    U1 += 2. * M_PI;
  }
  double R   = sqrt(R2);
  gp_Vec OO1 = OPp.Divided(R).Multiplied(S.MajorRadius());
  gp_Vec OO2 = OO1.Multiplied(-1.);
  gp_Pnt O1  = O.Translated(OO1);
  gp_Pnt O2  = O.Translated(OO2);

  if (O1.SquareDistance(P) < tol2)
  {
    return;
  }
  if (O2.SquareDistance(P) < tol2)
  {
    return;
  }

  double V1 = OPp.AngleWithRef(gp_Vec(O1, P), OPp.Crossed(OZ));
  if (V1 > -ExtPElS_MyEps && V1 < ExtPElS_MyEps)
  {
    V1 = 0.;
  }
  OPp.Reverse();
  double V2 = OPp.AngleWithRef(gp_Vec(P, O2), OPp.Crossed(OZ));
  if (V2 > -ExtPElS_MyEps && V2 < ExtPElS_MyEps)
  {
    V2 = 0.;
  }

  if (V1 < 0.)
  {
    V1 += 2. * M_PI;
  }
  if (V2 < 0.)
  {
    V2 += 2. * M_PI;
  }

  gp_Pnt Ps;
  Ps          = ElSLib::Value(U1, V1, S);
  mySqDist[0] = Ps.SquareDistance(P);
  myPoint[0]  = Extrema_POnSurf(U1, V1, Ps);

  Ps          = ElSLib::Value(U1, V1 + M_PI, S);
  mySqDist[1] = Ps.SquareDistance(P);
  myPoint[1]  = Extrema_POnSurf(U1, V1 + M_PI, Ps);

  Ps          = ElSLib::Value(U2, V2, S);
  mySqDist[2] = Ps.SquareDistance(P);
  myPoint[2]  = Extrema_POnSurf(U2, V2, Ps);

  Ps          = ElSLib::Value(U2, V2 + M_PI, S);
  mySqDist[3] = Ps.SquareDistance(P);
  myPoint[3]  = Extrema_POnSurf(U2, V2 + M_PI, Ps);

  myNbExt = 4;
  myDone  = true;
}

Extrema_ExtPElS::Extrema_ExtPElS(const gp_Pnt& P, const gp_Pln& S, const double Tol)
{
  Perform(P, S, Tol);
}

void Extrema_ExtPElS::Perform(const gp_Pnt& P,
                              const gp_Pln& S,

                              const double)
{
  myDone  = false;
  myNbExt = 0;

  gp_Pnt O = S.Location();
  gp_Vec OZ(S.Axis().Direction());
  double U, V = gp_Vec(O, P).Dot(OZ);
  gp_Pnt Pp = P.Translated(OZ.Multiplied(-V));

  ElSLib::Parameters(S, P, U, V);
  mySqDist[0] = Pp.SquareDistance(P);
  myPoint[0]  = Extrema_POnSurf(U, V, Pp);
  myNbExt     = 1;
  myDone      = true;
}

bool Extrema_ExtPElS::IsDone() const
{
  return myDone;
}

int Extrema_ExtPElS::NbExt() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myNbExt;
}

double Extrema_ExtPElS::SquareDistance(const int N) const
{
  if ((N < 1) || (N > NbExt()))
  {
    throw Standard_OutOfRange();
  }
  return mySqDist[N - 1];
}

const Extrema_POnSurf& Extrema_ExtPElS::Point(const int N) const
{
  if ((N < 1) || (N > NbExt()))
  {
    throw Standard_OutOfRange();
  }
  return myPoint[N - 1];
}

#include <Adaptor3d_Curve.hpp>
#include <Blend_Point.hpp>
#include <BlendFunc.hpp>
#include <BlendFunc_EvolRad.hpp>
#include <CSLib.hpp>
#include <ElCLib.hpp>
#include <GeomFill.hpp>
#include <gp_Circ.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <Law_Function.hpp>
#include <math_Gauss.hpp>
#include <math_Matrix.hpp>
#include <math_SVD.hpp>
#include <Precision.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NotImplemented.hpp>
#include <NCollection_Sequence.hpp>

#define Eps 1.e-15

static void FusionneIntervalles(const NCollection_Array1<double>& I1,
                                const NCollection_Array1<double>& I2,
                                NCollection_Sequence<double>&     Seq)
{
  int    ind1 = 1, ind2 = 1;
  double Epspar = Precision::PConfusion() * 0.99;

  double v1, v2;

  while ((ind1 <= I1.Upper()) && (ind2 <= I2.Upper()))
  {
    v1 = I1(ind1);
    v2 = I2(ind2);
    if (std::abs(v1 - v2) <= Epspar)
    {

      Seq.Append((v1 + v2) / 2);
      ind1++;
      ind2++;
    }
    else if (v1 < v2)
    {

      Seq.Append(v1);
      ind1++;
    }
    else
    {

      Seq.Append(v2);
      ind2++;
    }
  }

  if (ind1 > I1.Upper())
  {

    for (; ind2 <= I2.Upper(); ind2++)
    {
      Seq.Append(I2(ind2));
    }
  }

  if (ind2 > I2.Upper())
  {

    for (; ind1 <= I1.Upper(); ind1++)
    {
      Seq.Append(I1(ind1));
    }
  }
}

BlendFunc_EvolRad::BlendFunc_EvolRad(const occ::handle<Adaptor3d_Surface>& S1,
                                     const occ::handle<Adaptor3d_Surface>& S2,
                                     const occ::handle<Adaptor3d_Curve>&   C,
                                     const occ::handle<Law_Function>&      Law)
    : surf1(S1),
      surf2(S2),
      curv(C),
      tcurv(C),
      istangent(true),
      xval(1, 4),
      E(1, 4),
      DEDX(1, 4, 1, 4),
      DEDT(1, 4),
      D2EDX2(4, 4, 4),
      D2EDXDT(1, 4, 1, 4),
      D2EDT2(1, 4),
      minang(RealLast()),
      maxang(RealFirst()),
      lengthmin(RealLast()),
      lengthmax(RealFirst()),
      distmin(RealLast()),
      mySShape(BlendFunc_Rational)
{
  fevol = Law;
  tevol = Law;

  tval = -9.876e100;
  xval.Init(-9.876e100);
  myXOrder = -1;
  myTOrder = -1;
}

int BlendFunc_EvolRad::NbEquations() const
{
  return 4;
}

void BlendFunc_EvolRad::Set(const int Choix)
{
  choix = Choix;
  switch (choix)
  {
    case 1:
    case 2:
    {
      sg1 = -1.;
      sg2 = -1.;
    }
    break;
    case 3:
    case 4:
    {
      sg1 = 1.;
      sg2 = -1.;
    }
    break;
    case 5:
    case 6:
    {
      sg1 = 1.;
      sg2 = 1.;
    }
    break;
    case 7:
    case 8:
    {
      sg1 = -1.;
      sg2 = 1.;
    }
    break;
    default:
      sg1 = sg2 = -1.;
  }
}

void BlendFunc_EvolRad::Set(const BlendFunc_SectionShape TypeSection)
{
  mySShape = TypeSection;
}

bool BlendFunc_EvolRad::ComputeValues(const math_Vector& X,
                                      const int          Order,
                                      const bool         byParam,
                                      const double       Param)
{

  static gp_Vec d3u1, d3v1, d3uuv1, d3uvv1, d3u2, d3v2, d3uuv2, d3uvv2;
  static gp_Vec d1gui, d2gui, d3gui;
  static gp_Pnt ptgui;
  static double invnormtg, dinvnormtg;
  double        T = Param, aux;

  if (!byParam)
  {
    T = param;
  }

  bool lX_OK = (Order <= myXOrder);
  int  ii;
  for (ii = 1; ((ii <= X.Length()) && lX_OK); ii++)
  {
    lX_OK = (X(ii) == xval(ii));
  }

  bool t_OK = ((T == tval) && ((Order <= myTOrder) || (!byParam)));

  if (lX_OK && (t_OK))
  {
    return true;
  }

  if (!t_OK)
  {
    tval = T;
    if (byParam)
    {
      myTOrder = Order;
    }
    else
    {
      myTOrder = 0;
    }

    switch (myTOrder)
    {
      case 0:
      {
        tcurv->D1(T, ptgui, d1gui);
        nplan = d1gui.Normalized();
        ray   = tevol->Value(T);
      }
      break;

      case 1:
      {
        tcurv->D2(T, ptgui, d1gui, d2gui);
        nplan     = d1gui.Normalized();
        invnormtg = ((double)1) / d1gui.Magnitude();
        dnplan.SetLinearForm(invnormtg, d2gui, -invnormtg * (nplan.Dot(d2gui)), nplan);

        tevol->D1(T, ray, dray);
      }
      break;
      case 2:
      {
        tcurv->D3(T, ptgui, d1gui, d2gui, d3gui);
        nplan     = d1gui.Normalized();
        invnormtg = ((double)1) / d1gui.Magnitude();
        dnplan.SetLinearForm(invnormtg, d2gui, -invnormtg * (nplan.Dot(d2gui)), nplan);
        dinvnormtg = -nplan.Dot(d2gui) * invnormtg * invnormtg;
        d2nplan.SetLinearForm(invnormtg, d3gui, dinvnormtg, d2gui);
        aux = dinvnormtg * (nplan.Dot(d2gui)) + invnormtg * (dnplan.Dot(d2gui) + nplan.Dot(d3gui));
        d2nplan.SetLinearForm(-invnormtg * (nplan.Dot(d2gui)), dnplan, -aux, nplan, d2nplan);

        tevol->D2(T, ray, dray, d2ray);
        break;
      }
      default:
        return false;
    }
  }

  if (!lX_OK)
  {
    xval     = X;
    myXOrder = Order;

    switch (myXOrder)
    {
      case 0:
      {
        surf1->D1(X(1), X(2), pts1, d1u1, d1v1);
        nsurf1 = d1u1.Crossed(d1v1);
        surf2->D1(X(3), X(4), pts2, d1u2, d1v2);
        nsurf2 = d1u2.Crossed(d1v2);
        break;
      }
      case 1:
      {
        surf1->D2(X(1), X(2), pts1, d1u1, d1v1, d2u1, d2v1, d2uv1);
        nsurf1 = d1u1.Crossed(d1v1);
        dns1u1 = d2u1.Crossed(d1v1).Added(d1u1.Crossed(d2uv1));
        dns1v1 = d2uv1.Crossed(d1v1).Added(d1u1.Crossed(d2v1));

        surf2->D2(X(3), X(4), pts2, d1u2, d1v2, d2u2, d2v2, d2uv2);
        nsurf2 = d1u2.Crossed(d1v2);
        dns1u2 = d2u2.Crossed(d1v2).Added(d1u2.Crossed(d2uv2));
        dns1v2 = d2uv2.Crossed(d1v2).Added(d1u2.Crossed(d2v2));

        break;
      }
      case 2:
      {
        surf1->D3(X(1), X(2), pts1, d1u1, d1v1, d2u1, d2v1, d2uv1, d3u1, d3v1, d3uuv1, d3uvv1);
        nsurf1 = d1u1.Crossed(d1v1);
        surf2->D3(X(3), X(4), pts2, d1u2, d1v2, d2u2, d2v2, d2uv2, d3u2, d3v2, d3uuv2, d3uvv2);
        nsurf2 = d1u2.Crossed(d1v2);
        break;
      }
      default:
        return false;
    }

    if (nsurf1.Magnitude() < Eps)
    {

      gp_Pnt2d P(X(1), X(2));
      if (Order == 0)
        BlendFunc::ComputeNormal(surf1, P, nsurf1);
      else
        BlendFunc::ComputeDNormal(surf1, P, nsurf1, dns1u1, dns1v1);
    }
    if (nsurf2.Magnitude() < Eps)
    {

      gp_Pnt2d P(X(3), X(4));
      if (Order == 0)
        BlendFunc::ComputeNormal(surf2, P, nsurf2);
      else
        BlendFunc::ComputeDNormal(surf2, P, nsurf2, dns1u2, dns1v2);
    }
  }

  double invnorm1, invnorm2, ndotns1, ndotns2, theD;
  double ray1 = sg1 * ray;
  double ray2 = sg2 * ray;
  gp_Vec ncrossns1, ncrossns2, resul, temp, n1, n2;

  theD = -(nplan.XYZ().Dot(ptgui.XYZ()));

  E(1) = (nplan.X() * (pts1.X() + pts2.X()) + nplan.Y() * (pts1.Y() + pts2.Y())
          + nplan.Z() * (pts1.Z() + pts2.Z()))
           / 2
         + theD;

  ncrossns1 = nplan.Crossed(nsurf1);
  ncrossns2 = nplan.Crossed(nsurf2);
  invnorm1  = ncrossns1.Magnitude();
  invnorm2  = ncrossns2.Magnitude();

  if (invnorm1 > Eps)
    invnorm1 = ((double)1) / invnorm1;
  else
  {
    invnorm1 = 1;
#ifdef OCCT_DEBUG
    std::cout << " EvolRad : Surface singuliere " << std::endl;
#endif
  }
  if (invnorm2 > Eps)
    invnorm2 = ((double)1) / invnorm2;
  else
  {
    invnorm2 = 1;
#ifdef OCCT_DEBUG
    std::cout << " EvolRad : Surface singuliere " << std::endl;
#endif
  }

  ndotns1 = nplan.Dot(nsurf1);
  ndotns2 = nplan.Dot(nsurf2);

  n1.SetLinearForm(ndotns1, nplan, -1., nsurf1);
  n1.Multiply(invnorm1);
  n2.SetLinearForm(ndotns2, nplan, -1., nsurf2);
  n2.Multiply(invnorm2);

  resul.SetLinearForm(ray1, n1, -ray2, n2, gp_Vec(pts2, pts1));

  E(2) = resul.X();
  E(3) = resul.Y();
  E(4) = resul.Z();

  if (Order >= 1)
  {
    double grosterme, cube, carre;

    DEDX(1, 1) = nplan.Dot(d1u1) / 2;
    DEDX(1, 2) = nplan.Dot(d1v1) / 2;
    DEDX(1, 3) = nplan.Dot(d1u2) / 2;
    DEDX(1, 4) = nplan.Dot(d1v2) / 2;

    cube = invnorm1 * invnorm1 * invnorm1;

    grosterme = -ncrossns1.Dot(nplan.Crossed(dns1u1)) * cube;
    dndu1.SetLinearForm(grosterme * ndotns1 + invnorm1 * nplan.Dot(dns1u1),
                        nplan,
                        -grosterme,
                        nsurf1,
                        -invnorm1,
                        dns1u1);

    resul.SetLinearForm(ray1, dndu1, d1u1);
    DEDX(2, 1) = resul.X();
    DEDX(3, 1) = resul.Y();
    DEDX(4, 1) = resul.Z();

    grosterme = -ncrossns1.Dot(nplan.Crossed(dns1v1)) * cube;
    dndv1.SetLinearForm(grosterme * ndotns1 + invnorm1 * nplan.Dot(dns1v1),
                        nplan,
                        -grosterme,
                        nsurf1,
                        -invnorm1,
                        dns1v1);

    resul.SetLinearForm(ray1, dndv1, d1v1);
    DEDX(2, 2) = resul.X();
    DEDX(3, 2) = resul.Y();
    DEDX(4, 2) = resul.Z();

    cube = invnorm2 * invnorm2 * invnorm2;

    grosterme = -ncrossns2.Dot(nplan.Crossed(dns1u2)) * cube;
    dndu2.SetLinearForm(grosterme * ndotns2 + invnorm2 * nplan.Dot(dns1u2),
                        nplan,
                        -grosterme,
                        nsurf2,
                        -invnorm2,
                        dns1u2);

    resul.SetLinearForm(-ray2, dndu2, -1, d1u2);
    DEDX(2, 3) = resul.X();
    DEDX(3, 3) = resul.Y();
    DEDX(4, 3) = resul.Z();

    grosterme = -ncrossns2.Dot(nplan.Crossed(dns1v2)) * cube;
    dndv2.SetLinearForm(grosterme * ndotns2 + invnorm2 * nplan.Dot(dns1v2),
                        nplan,
                        -grosterme,
                        nsurf2,
                        -invnorm2,
                        dns1v2);

    resul.SetLinearForm(-ray2, dndv2, -1, d1v2);
    DEDX(2, 4) = resul.X();
    DEDX(3, 4) = resul.Y();
    DEDX(4, 4) = resul.Z();

    if (byParam)
    {
      temp.SetXYZ((pts1.XYZ() + pts2.XYZ()) / 2 - ptgui.XYZ());

      grosterme = ncrossns1.Dot(dnplan.Crossed(nsurf1)) * invnorm1 * invnorm1;
      dn1w.SetLinearForm((dnplan.Dot(nsurf1) - grosterme * ndotns1) * invnorm1,
                         nplan,
                         ndotns1 * invnorm1,
                         dnplan,
                         grosterme * invnorm1,
                         nsurf1);

      grosterme = ncrossns2.Dot(dnplan.Crossed(nsurf2)) * invnorm2 * invnorm2;
      dn2w.SetLinearForm((dnplan.Dot(nsurf2) - grosterme * ndotns2) * invnorm2,
                         nplan,
                         ndotns2 * invnorm2,
                         dnplan,
                         grosterme * invnorm2,
                         nsurf2);

      DEDT(1) = dnplan.Dot(temp) - 1. / invnormtg;
      temp.SetLinearForm(ray2, dn2w, sg2 * dray, n2);
      resul.SetLinearForm(ray1, dn1w, sg1 * dray, n1, -1, temp);
      DEDT(2) = resul.X();
      DEDT(3) = resul.Y();
      DEDT(4) = resul.Z();
    }

    if (Order == 2)
    {

      gp_Vec d2ns1u1, d2ns1u2, d2ns1v1, d2ns1v2, d2ns1uv1, d2ns1uv2;
      double uterm, vterm, smallterm, p1, p2, p12;
      double DPrim, DSecn;
      D2EDX2.Init(0);

      D2EDX2(1, 1, 1) = nplan.Dot(d2u1) / 2;
      D2EDX2(1, 2, 1) = D2EDX2(1, 1, 2) = nplan.Dot(d2uv1) / 2;
      D2EDX2(1, 2, 2)                   = nplan.Dot(d2v1) / 2;

      D2EDX2(1, 3, 3) = nplan.Dot(d2u2) / 2;
      D2EDX2(1, 4, 3) = D2EDX2(1, 3, 4) = nplan.Dot(d2uv2) / 2;
      D2EDX2(1, 4, 4)                   = nplan.Dot(d2v2) / 2;

      carre = invnorm1 * invnorm1;
      cube  = carre * invnorm1;

      d2ns1u1.SetLinearForm(1, d3u1.Crossed(d1v1), 2, d2u1.Crossed(d2uv1), 1, d1u1.Crossed(d3uuv1));
      DPrim     = ncrossns1.Dot(nplan.Crossed(dns1u1));
      smallterm = -2 * DPrim * cube;
      DSecn     = ncrossns1.Dot(nplan.Crossed(d2ns1u1)) + (nplan.Crossed(dns1u1)).SquareMagnitude();
      grosterme = (3 * DPrim * DPrim * carre - DSecn) * cube;

      temp.SetLinearForm(grosterme * ndotns1, nplan, -grosterme, nsurf1);
      p1 = nplan.Dot(dns1u1);
      p2 = nplan.Dot(d2ns1u1);
      d2ndu1.SetLinearForm(invnorm1 * p2 + smallterm * p1,
                           nplan,
                           -smallterm,
                           dns1u1,
                           -invnorm1,
                           d2ns1u1);
      d2ndu1 += temp;
      resul.SetLinearForm(ray1, d2ndu1, d2u1);
      D2EDX2(2, 1, 1) = resul.X();
      D2EDX2(3, 1, 1) = resul.Y();
      D2EDX2(4, 1, 1) = resul.Z();

      d2ns1uv1 = (d3uuv1.Crossed(d1v1)) + (d2u1.Crossed(d2v1)) + (d1u1.Crossed(d3uvv1));
      uterm    = ncrossns1.Dot(nplan.Crossed(dns1u1));
      vterm    = ncrossns1.Dot(nplan.Crossed(dns1v1));
      DSecn =
        (nplan.Crossed(dns1v1)).Dot(nplan.Crossed(dns1u1)) + ncrossns1.Dot(nplan.Crossed(d2ns1uv1));
      grosterme = (3 * uterm * vterm * carre - DSecn) * cube;
      uterm *= -cube;
      vterm *= -cube;

      p1 = nplan.Dot(dns1u1);
      p2 = nplan.Dot(dns1v1);
      temp.SetLinearForm(grosterme * ndotns1, nplan, -grosterme, nsurf1, -invnorm1, d2ns1uv1);
      d2nduv1.SetLinearForm(invnorm1 * nplan.Dot(d2ns1uv1) + uterm * p2 + vterm * p1,
                            nplan,
                            -uterm,
                            dns1v1,
                            -vterm,
                            dns1u1);

      d2nduv1 += temp;
      resul.SetLinearForm(ray1, d2nduv1, d2uv1);

      D2EDX2(2, 2, 1) = D2EDX2(2, 1, 2) = resul.X();
      D2EDX2(3, 2, 1) = D2EDX2(3, 1, 2) = resul.Y();
      D2EDX2(4, 2, 1) = D2EDX2(4, 1, 2) = resul.Z();

      d2ns1v1.SetLinearForm(1, d1u1.Crossed(d3v1), 2, d2uv1.Crossed(d2v1), 1, d3uvv1.Crossed(d1v1));
      DPrim     = ncrossns1.Dot(nplan.Crossed(dns1v1));
      smallterm = -2 * DPrim * cube;
      DSecn     = ncrossns1.Dot(nplan.Crossed(d2ns1v1)) + (nplan.Crossed(dns1v1)).SquareMagnitude();
      grosterme = (3 * DPrim * DPrim * carre - DSecn) * cube;

      p1 = nplan.Dot(dns1v1);
      p2 = nplan.Dot(d2ns1v1);
      temp.SetLinearForm(grosterme * ndotns1, nplan, -grosterme, nsurf1);
      d2ndv1.SetLinearForm(invnorm1 * p2 + smallterm * p1,
                           nplan,
                           -smallterm,
                           dns1v1,
                           -invnorm1,
                           d2ns1v1);
      d2ndv1 += temp;
      resul.SetLinearForm(ray1, d2ndv1, d2v1);

      D2EDX2(2, 2, 2) = resul.X();
      D2EDX2(3, 2, 2) = resul.Y();
      D2EDX2(4, 2, 2) = resul.Z();

      carre = invnorm2 * invnorm2;
      cube  = carre * invnorm2;

      d2ns1u2.SetLinearForm(1, d3u2.Crossed(d1v2), 2, d2u2.Crossed(d2uv2), 1, d1u2.Crossed(d3uuv2));
      DPrim     = ncrossns2.Dot(nplan.Crossed(dns1u2));
      smallterm = -2 * DPrim * cube;
      DSecn     = ncrossns2.Dot(nplan.Crossed(d2ns1u2)) + (nplan.Crossed(dns1u2)).SquareMagnitude();
      grosterme = (3 * DPrim * DPrim * carre - DSecn) * cube;

      temp.SetLinearForm(grosterme * ndotns2, nplan, -grosterme, nsurf2);
      p1 = nplan.Dot(dns1u2);
      p2 = nplan.Dot(d2ns1u2);
      d2ndu2.SetLinearForm(invnorm2 * p2 + smallterm * p1,
                           nplan,
                           -smallterm,
                           dns1u2,
                           -invnorm2,
                           d2ns1u2);
      d2ndu2 += temp;
      resul.SetLinearForm(-ray2, d2ndu2, -1, d2u2);
      D2EDX2(2, 3, 3) = resul.X();
      D2EDX2(3, 3, 3) = resul.Y();
      D2EDX2(4, 3, 3) = resul.Z();

      d2ns1uv2 = (d3uuv2.Crossed(d1v2)) + (d2u2.Crossed(d2v2)) + (d1u2.Crossed(d3uvv2));
      uterm    = ncrossns2.Dot(nplan.Crossed(dns1u2));
      vterm    = ncrossns2.Dot(nplan.Crossed(dns1v2));
      DSecn =
        (nplan.Crossed(dns1v2)).Dot(nplan.Crossed(dns1u2)) + ncrossns2.Dot(nplan.Crossed(d2ns1uv2));
      grosterme = (3 * uterm * vterm * carre - DSecn) * cube;
      uterm *= -cube;
      vterm *= -cube;

      p1 = nplan.Dot(dns1u2);
      p2 = nplan.Dot(dns1v2);
      temp.SetLinearForm(grosterme * ndotns2, nplan, -grosterme, nsurf2, -invnorm2, d2ns1uv2);
      d2nduv2.SetLinearForm(invnorm2 * nplan.Dot(d2ns1uv2) + uterm * p2 + vterm * p1,
                            nplan,
                            -uterm,
                            dns1v2,
                            -vterm,
                            dns1u2);

      d2nduv2 += temp;
      resul.SetLinearForm(-ray2, d2nduv2, -1, d2uv2);

      D2EDX2(2, 4, 3) = D2EDX2(2, 3, 4) = resul.X();
      D2EDX2(3, 4, 3) = D2EDX2(3, 3, 4) = resul.Y();
      D2EDX2(4, 4, 3) = D2EDX2(4, 3, 4) = resul.Z();

      d2ns1v2.SetLinearForm(1, d1u2.Crossed(d3v2), 2, d2uv2.Crossed(d2v2), 1, d3uvv2.Crossed(d1v2));
      DPrim     = ncrossns2.Dot(nplan.Crossed(dns1v2));
      smallterm = -2 * DPrim * cube;
      DSecn     = ncrossns2.Dot(nplan.Crossed(d2ns1v2)) + (nplan.Crossed(dns1v2)).SquareMagnitude();
      grosterme = (3 * DPrim * DPrim * carre - DSecn) * cube;

      p1 = nplan.Dot(dns1v2);
      p2 = nplan.Dot(d2ns1v2);
      temp.SetLinearForm(grosterme * ndotns2, nplan, -grosterme, nsurf2);
      d2ndv2.SetLinearForm(invnorm2 * p2 + smallterm * p1,
                           nplan,
                           -smallterm,
                           dns1v2,
                           -invnorm2,
                           d2ns1v2);
      d2ndv2 += temp;
      resul.SetLinearForm(-ray2, d2ndv2, -1, d2v2);

      D2EDX2(2, 4, 4) = resul.X();
      D2EDX2(3, 4, 4) = resul.Y();
      D2EDX2(4, 4, 4) = resul.Z();

      if (byParam)
      {
        double tterm;

        D2EDXDT(1, 1) = dnplan.Dot(d1u1) / 2;
        D2EDXDT(1, 2) = dnplan.Dot(d1v1) / 2;
        D2EDXDT(1, 3) = dnplan.Dot(d1u2) / 2;
        D2EDXDT(1, 4) = dnplan.Dot(d1v2) / 2;

        carre = invnorm1 * invnorm1;
        cube  = carre * invnorm1;

        tterm     = ncrossns1.Dot(dnplan.Crossed(nsurf1));
        smallterm = -tterm * cube;

        uterm = ncrossns1.Dot(nplan.Crossed(dns1u1));
        DSecn = (nplan.Crossed(dns1u1)).Dot(dnplan.Crossed(nsurf1))
                + ncrossns1.Dot(dnplan.Crossed(dns1u1));
        grosterme = (3 * uterm * tterm * carre - DSecn) * cube;
        uterm *= -cube;

        p1  = dnplan.Dot(nsurf1);
        p2  = nplan.Dot(dns1u1);
        p12 = dnplan.Dot(dns1u1);

        d2ndtu1.SetLinearForm(invnorm1 * p12 + smallterm * p2 + uterm * p1 + grosterme * ndotns1,
                              nplan,
                              invnorm1 * p2 + uterm * ndotns1,
                              dnplan,
                              -smallterm,
                              dns1u1);
        d2ndtu1 -= grosterme * nsurf1;

        resul.SetLinearForm(ray1, d2ndtu1, sg1 * dray, dndu1);
        D2EDXDT(2, 1) = resul.X();
        D2EDXDT(3, 1) = resul.Y();
        D2EDXDT(4, 1) = resul.Z();

        uterm = ncrossns1.Dot(nplan.Crossed(dns1v1));
        DSecn = (nplan.Crossed(dns1v1)).Dot(dnplan.Crossed(nsurf1))
                + ncrossns1.Dot(dnplan.Crossed(dns1v1));
        grosterme = (3 * uterm * tterm * carre - DSecn) * cube;
        uterm *= -cube;

        p1  = dnplan.Dot(nsurf1);
        p2  = nplan.Dot(dns1v1);
        p12 = dnplan.Dot(dns1v1);
        d2ndtv1.SetLinearForm(invnorm1 * p12 + uterm * p1 + smallterm * p2 + grosterme * ndotns1,
                              nplan,
                              invnorm1 * p2 + uterm * ndotns1,
                              dnplan,
                              -smallterm,
                              dns1v1);
        d2ndtv1 -= grosterme * nsurf1;

        resul.SetLinearForm(ray1, d2ndtv1, sg1 * dray, dndv1);
        D2EDXDT(2, 2) = resul.X();
        D2EDXDT(3, 2) = resul.Y();
        D2EDXDT(4, 2) = resul.Z();

        carre = invnorm2 * invnorm2;
        cube  = carre * invnorm2;

        tterm     = ncrossns2.Dot(dnplan.Crossed(nsurf2));
        smallterm = -tterm * cube;

        uterm = ncrossns2.Dot(nplan.Crossed(dns1u2));
        DSecn = (nplan.Crossed(dns1u2)).Dot(dnplan.Crossed(nsurf2))
                + ncrossns2.Dot(dnplan.Crossed(dns1u2));
        grosterme = (3 * uterm * tterm * carre - DSecn) * cube;
        uterm *= -cube;

        p1  = dnplan.Dot(nsurf2);
        p2  = nplan.Dot(dns1u2);
        p12 = dnplan.Dot(dns1u2);

        d2ndtu2.SetLinearForm(invnorm2 * p12 + smallterm * p2 + uterm * p1 + grosterme * ndotns2,
                              nplan,
                              invnorm2 * p2 + uterm * ndotns2,
                              dnplan,
                              -smallterm,
                              dns1u2);
        d2ndtu2 -= grosterme * nsurf2;

        resul.SetLinearForm(-ray2, d2ndtu2, -sg2 * dray, dndu2);
        D2EDXDT(2, 3) = resul.X();
        D2EDXDT(3, 3) = resul.Y();
        D2EDXDT(4, 3) = resul.Z();

        uterm = ncrossns2.Dot(nplan.Crossed(dns1v2));
        DSecn = (nplan.Crossed(dns1v2)).Dot(dnplan.Crossed(nsurf2))
                + ncrossns2.Dot(dnplan.Crossed(dns1v2));
        grosterme = (3 * uterm * tterm * carre - DSecn) * cube;
        uterm *= -cube;

        p1  = dnplan.Dot(nsurf2);
        p2  = nplan.Dot(dns1v2);
        p12 = dnplan.Dot(dns1v2);

        d2ndtv2.SetLinearForm(invnorm2 * p12 + smallterm * p2 + uterm * p1 + grosterme * ndotns2,
                              nplan,
                              invnorm2 * p2 + uterm * ndotns2,
                              dnplan,
                              -smallterm,
                              dns1v2);
        d2ndtv2 -= grosterme * nsurf2;

        resul.SetLinearForm(-ray2, d2ndtv2, -sg2 * dray, dndv2);
        D2EDXDT(2, 4) = resul.X();
        D2EDXDT(3, 4) = resul.Y();
        D2EDXDT(4, 4) = resul.Z();

        carre = invnorm1 * invnorm1;
        cube  = carre * invnorm1;

        DPrim     = ncrossns1.Dot(dnplan.Crossed(nsurf1));
        smallterm = -2 * DPrim * cube;
        DSecn = (dnplan.Crossed(nsurf1)).SquareMagnitude() + ncrossns1.Dot(d2nplan.Crossed(nsurf1));
        grosterme = (3 * DPrim * DPrim * carre - DSecn) * cube;

        p1 = dnplan.Dot(nsurf1);
        p2 = d2nplan.Dot(nsurf1);

        temp.SetLinearForm(grosterme * ndotns1, nplan, -grosterme, nsurf1);
        d2n1w.SetLinearForm(smallterm * p1 + invnorm1 * p2,
                            nplan,
                            smallterm * ndotns1 + 2 * invnorm1 * p1,
                            dnplan,
                            ndotns1 * invnorm1,
                            d2nplan);
        d2n1w += temp;

        carre = invnorm2 * invnorm2;
        cube  = carre * invnorm2;

        DPrim     = ncrossns2.Dot(dnplan.Crossed(nsurf2));
        smallterm = -2 * DPrim * cube;
        DSecn = (dnplan.Crossed(nsurf2)).SquareMagnitude() + ncrossns2.Dot(d2nplan.Crossed(nsurf2));
        grosterme = (3 * DPrim * DPrim * carre - DSecn) * cube;

        p1 = dnplan.Dot(nsurf2);
        p2 = d2nplan.Dot(nsurf2);

        temp.SetLinearForm(grosterme * ndotns2, nplan, -grosterme, nsurf2);
        d2n2w.SetLinearForm(smallterm * p1 + invnorm2 * p2,
                            nplan,
                            smallterm * ndotns2 + 2 * invnorm2 * p1,
                            dnplan,
                            ndotns2 * invnorm2,
                            d2nplan);
        d2n2w += temp;

        temp.SetXYZ((pts1.XYZ() + pts2.XYZ()) / 2 - ptgui.XYZ());
        D2EDT2(1) = d2nplan.Dot(temp) - 2 * dnplan.Dot(d1gui) - nplan.Dot(d2gui);

        resul.SetLinearForm(ray1, d2n1w, 2 * sg1 * dray, dn1w, sg1 * d2ray, n1);
        temp.SetLinearForm(ray2, d2n2w, 2 * sg2 * dray, dn2w, sg2 * d2ray, n2);
        resul -= temp;

        D2EDT2(2) = resul.X();
        D2EDT2(3) = resul.Y();
        D2EDT2(4) = resul.Z();
      }
    }
  }
  return true;
}

void BlendFunc_EvolRad::Set(const double Param)
{
  param = Param;
}

void BlendFunc_EvolRad::Set(const double First, const double Last)
{
  tcurv = curv->Trim(First, Last, 1.e-12);
  tevol = fevol->Trim(First, Last, 1.e-12);
}

void BlendFunc_EvolRad::GetTolerance(math_Vector& Tolerance, const double Tol) const
{
  Tolerance(1) = surf1->UResolution(Tol);
  Tolerance(2) = surf1->VResolution(Tol);
  Tolerance(3) = surf2->UResolution(Tol);
  Tolerance(4) = surf2->VResolution(Tol);
}

void BlendFunc_EvolRad::GetBounds(math_Vector& InfBound, math_Vector& SupBound) const
{
  InfBound(1) = surf1->FirstUParameter();
  InfBound(2) = surf1->FirstVParameter();
  InfBound(3) = surf2->FirstUParameter();
  InfBound(4) = surf2->FirstVParameter();
  SupBound(1) = surf1->LastUParameter();
  SupBound(2) = surf1->LastVParameter();
  SupBound(3) = surf2->LastUParameter();
  SupBound(4) = surf2->LastVParameter();

  for (int i = 1; i <= 4; i++)
  {
    if (!Precision::IsInfinite(InfBound(i)) && !Precision::IsInfinite(SupBound(i)))
    {
      double range = (SupBound(i) - InfBound(i));
      InfBound(i) -= range;
      SupBound(i) += range;
    }
  }
}

bool BlendFunc_EvolRad::IsSolution(const math_Vector& Sol, const double Tol)

{
  double norm, Cosa, Sina, Angle;
  bool   Ok = true;

  Ok = ComputeValues(Sol, 1, true, param);

  if (std::abs(E(1)) <= Tol && E(2) * E(2) + E(3) * E(3) + E(4) * E(4) <= Tol * Tol)
  {

    gp_Vec ns1, ns2, np;
    ns1 = nsurf1;
    ns2 = nsurf2;
    np  = nplan;

    norm = nplan.Crossed(ns1).Magnitude();
    if (norm < Eps)
    {
      norm = 1;
    }
    ns1.SetLinearForm(nplan.Dot(ns1) / norm, nplan, -1. / norm, ns1);

    norm = nplan.Crossed(ns2).Magnitude();
    if (norm < Eps)
    {
      norm = 1;
    }
    ns2.SetLinearForm(nplan.Dot(ns2) / norm, nplan, -1. / norm, ns2);

    double     maxpiv = 1.e-14;
    math_Gauss Resol(DEDX, maxpiv);
    istangent = false;
    if (Resol.IsDone())
    {
      math_Vector controle(1, 4), solution(1, 4), tolerances(1, 4);
      GetTolerance(tolerances, Tol);
      Resol.Solve(-DEDT, solution);
      controle = DEDT.Added(DEDX.Multiplied(solution));
      if (std::abs(controle(1)) > tolerances(1) || std::abs(controle(2)) > tolerances(2)
          || std::abs(controle(3)) > tolerances(3) || std::abs(controle(4)) > tolerances(4))
      {
#ifdef OCCT_DEBUG
        std::cout << "Cheminement : echec calcul des derivees" << std::endl;
#endif
        istangent = true;
      }
      if (!istangent)
      {
        tg1.SetLinearForm(solution(1), d1u1, solution(2), d1v1);
        tg2.SetLinearForm(solution(3), d1u2, solution(4), d1v2);
        tg12d.SetCoord(solution(1), solution(2));
        tg22d.SetCoord(solution(3), solution(4));
      }
    }
    else
    {
      istangent = true;
    }

    if (sg1 > 0.)
    {
      ns1.Reverse();
    }
    if (sg2 > 0.)
    {
      ns2.Reverse();
    }
    Cosa = ns1.Dot(ns2);
    Sina = nplan.Dot(ns1.Crossed(ns2));
    if (choix % 2 != 0)
    {
      Sina = -Sina;
    }

    if (Cosa > 1.)
    {
      Cosa = 1.;
      Sina = 0.;
    }
    Angle = std::acos(Cosa);

    if (Sina < 0.)
    {
      if (Cosa > 0.)
        Angle = -Angle;
      else
        Angle = 2. * M_PI - Angle;
    }

    if (std::abs(Angle) > maxang)
    {
      maxang = std::abs(Angle);
    }
    if (std::abs(Angle) < minang)
    {
      minang = std::abs(Angle);
    }
    if (std::abs(Angle * ray) < lengthmin)
    {
      lengthmin = std::abs(Angle * ray);
    }
    if (std::abs(Angle * ray) > lengthmax)
    {
      lengthmax = std::abs(Angle * ray);
    }
    distmin = std::min(distmin, pts1.Distance(pts2));

    return Ok;
  }
  istangent = true;
  return false;
}

double BlendFunc_EvolRad::GetMinimalDistance() const
{
  return distmin;
}

bool BlendFunc_EvolRad::Value(const math_Vector& X, math_Vector& F)
{
  bool Ok;
  Ok = ComputeValues(X, 0);
  F  = E;
  return Ok;
}

bool BlendFunc_EvolRad::Derivatives(const math_Vector& X, math_Matrix& D)
{
  bool Ok;
  Ok = ComputeValues(X, 1);
  D  = DEDX;
  return Ok;
}

bool BlendFunc_EvolRad::Values(const math_Vector& X, math_Vector& F, math_Matrix& D)
{
  bool Ok;
  Ok = ComputeValues(X, 1);
  F  = E;
  D  = DEDX;
  return Ok;
}

void BlendFunc_EvolRad::Tangent(const double U1,
                                const double V1,
                                const double U2,
                                const double V2,
                                gp_Vec&      TgF,
                                gp_Vec&      TgL,
                                gp_Vec&      NmF,
                                gp_Vec&      NmL) const
{
  gp_Pnt Center;
  gp_Vec ns1;
  double invnorm1;

  if ((U1 != xval(1)) || (V1 != xval(2)) || (U2 != xval(3)) || (V2 != xval(4)))
  {
    gp_Vec d1u, d1v;
    gp_Pnt bid;
#ifdef OCCT_DEBUG
    std::cout << " erreur de tengent !!!!!!!!!!!!!!!!!!!!" << std::endl;
#endif
    surf1->D1(U1, V1, bid, d1u, d1v);
    NmF = ns1 = d1u.Crossed(d1v);
    surf2->D1(U2, V2, bid, d1u, d1v);
    NmL = d1u.Crossed(d1v);
  }
  else
  {
    NmF = ns1 = nsurf1;
    NmL       = nsurf2;
  }

  invnorm1 = nplan.Crossed(ns1).Magnitude();
  if (invnorm1 < Eps)
    invnorm1 = 1;
  else
    invnorm1 = 1. / invnorm1;
  ns1.SetLinearForm(nplan.Dot(ns1) * invnorm1, nplan, -invnorm1, ns1);

  Center.SetXYZ(pts1.XYZ() + sg1 * ray * ns1.XYZ());

  TgF = nplan.Crossed(gp_Vec(Center, pts1));
  TgL = nplan.Crossed(gp_Vec(Center, pts2));
  if (choix % 2 == 1)
  {
    TgF.Reverse();
    TgL.Reverse();
  }
}

bool BlendFunc_EvolRad::TwistOnS1() const
{
  if (istangent)
  {
    throw Standard_DomainError();
  }
  return tg1.Dot(nplan) < 0.;
}

bool BlendFunc_EvolRad::TwistOnS2() const
{
  if (istangent)
  {
    throw Standard_DomainError();
  }
  return tg2.Dot(nplan) < 0.;
}

void BlendFunc_EvolRad::Section(const double Param,
                                const double U1,
                                const double V1,
                                const double U2,
                                const double V2,
                                double&      Pdeb,
                                double&      Pfin,
                                gp_Circ&     C)
{
  gp_Pnt Center;
  gp_Vec ns1, np;

  math_Vector X(1, 4);
  X(1)       = U1;
  X(2)       = V1;
  X(3)       = U2;
  X(4)       = V2;
  double prm = Param;

  ComputeValues(X, 0, true, prm);

  ns1 = nsurf1;
  np  = nplan;

  double norm1;
  norm1 = nplan.Crossed(ns1).Magnitude();
  if (norm1 < Eps)
  {
    norm1 = 1;
  }
  ns1.SetLinearForm(nplan.Dot(ns1) / norm1, nplan, -1. / norm1, ns1);

  Center.SetXYZ(pts1.XYZ() + sg1 * ray * ns1.XYZ());

  if (sg1 > 0.)
  {
    ns1.Reverse();
  }
  if (choix % 2 != 0)
  {
    np.Reverse();
  }
  C.SetRadius(std::abs(ray));
  C.SetPosition(gp_Ax2(Center, np, ns1));
  Pdeb = 0.;
  Pfin = ElCLib::Parameter(C, pts2);

  if (Pfin > 1.5 * M_PI)
  {
    np.Reverse();
    C.SetPosition(gp_Ax2(Center, np, ns1));
    Pfin = ElCLib::Parameter(C, pts2);
  }
  if (Pfin < Precision::PConfusion())
    Pfin += Precision::PConfusion();
}

const gp_Pnt& BlendFunc_EvolRad::PointOnS1() const
{
  return pts1;
}

const gp_Pnt& BlendFunc_EvolRad::PointOnS2() const
{
  return pts2;
}

bool BlendFunc_EvolRad::IsTangencyPoint() const
{
  return istangent;
}

const gp_Vec& BlendFunc_EvolRad::TangentOnS1() const
{
  if (istangent)
  {
    throw Standard_DomainError();
  }
  return tg1;
}

const gp_Vec& BlendFunc_EvolRad::TangentOnS2() const
{
  if (istangent)
  {
    throw Standard_DomainError();
  }
  return tg2;
}

const gp_Vec2d& BlendFunc_EvolRad::Tangent2dOnS1() const
{
  if (istangent)
  {
    throw Standard_DomainError();
  }
  return tg12d;
}

const gp_Vec2d& BlendFunc_EvolRad::Tangent2dOnS2() const
{
  if (istangent)
  {
    throw Standard_DomainError();
  }
  return tg22d;
}

bool BlendFunc_EvolRad::IsRational() const
{
  return (mySShape == BlendFunc_Rational || mySShape == BlendFunc_QuasiAngular);
}

double BlendFunc_EvolRad::GetSectionSize() const
{
  return lengthmax;
}

void BlendFunc_EvolRad::GetMinimalWeight(NCollection_Array1<double>& Weights) const
{
  BlendFunc::GetMinimalWeights(mySShape, myTConv, minang, maxang, Weights);
}

int BlendFunc_EvolRad::NbIntervals(const GeomAbs_Shape S) const
{
  int Nb_Int_Courbe, Nb_Int_Loi;
  Nb_Int_Courbe = curv->NbIntervals(BlendFunc::NextShape(S));
  Nb_Int_Loi    = fevol->NbIntervals(S);

  if (Nb_Int_Loi == 1)
  {
    return Nb_Int_Courbe;
  }

  NCollection_Array1<double>   IntC(1, Nb_Int_Courbe + 1);
  NCollection_Array1<double>   IntL(1, Nb_Int_Loi + 1);
  NCollection_Sequence<double> Inter;
  curv->Intervals(IntC, BlendFunc::NextShape(S));
  fevol->Intervals(IntL, S);

  FusionneIntervalles(IntC, IntL, Inter);
  return Inter.Length() - 1;
}

void BlendFunc_EvolRad::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  int Nb_Int_Courbe, Nb_Int_Loi;
  Nb_Int_Courbe = curv->NbIntervals(BlendFunc::NextShape(S));
  Nb_Int_Loi    = fevol->NbIntervals(S);

  if (Nb_Int_Loi == 1)
  {
    curv->Intervals(T, BlendFunc::NextShape(S));
  }
  else
  {
    NCollection_Array1<double>   IntC(1, Nb_Int_Courbe + 1);
    NCollection_Array1<double>   IntL(1, Nb_Int_Loi + 1);
    NCollection_Sequence<double> Inter;
    curv->Intervals(IntC, BlendFunc::NextShape(S));
    fevol->Intervals(IntL, S);

    FusionneIntervalles(IntC, IntL, Inter);
    for (int ii = 1; ii <= Inter.Length(); ii++)
    {
      T(ii) = Inter(ii);
    }
  }
}

void BlendFunc_EvolRad::GetShape(int& NbPoles, int& NbKnots, int& Degree, int& NbPoles2d)
{
  NbPoles2d = 2;
  BlendFunc::GetShape(mySShape, maxang, NbPoles, NbKnots, Degree, myTConv);
}

void BlendFunc_EvolRad::GetTolerance(const double BoundTol,
                                     const double SurfTol,
                                     const double AngleTol,
                                     math_Vector& Tol3d,
                                     math_Vector& Tol1d) const
{
  int    low = Tol3d.Lower(), up = Tol3d.Upper();
  double rayon = lengthmin / maxang;
  double Tol;
  Tol = GeomFill::GetTolerance(myTConv, maxang, rayon, AngleTol, SurfTol);
  Tol1d.Init(SurfTol);
  Tol3d.Init(SurfTol);
  Tol3d(low + 1) = Tol3d(up - 1) = std::min(Tol, SurfTol);
  Tol3d(low) = Tol3d(up) = std::min(Tol, BoundTol);
}

void BlendFunc_EvolRad::Knots(NCollection_Array1<double>& TKnots)
{
  GeomFill::Knots(myTConv, TKnots);
}

void BlendFunc_EvolRad::Mults(NCollection_Array1<int>& TMults)
{
  GeomFill::Mults(myTConv, TMults);
}

void BlendFunc_EvolRad::Section(const Blend_Point&            P,
                                NCollection_Array1<gp_Pnt>&   Poles,
                                NCollection_Array1<gp_Pnt2d>& Poles2d,
                                NCollection_Array1<double>&   Weights)
{
  gp_Pnt Center;
  gp_Vec ns1, ns2, np;

  math_Vector X(1, 4);
  double      prm = P.Parameter();

  int low = Poles.Lower();
  int upp = Poles.Upper();

  P.ParametersOnS1(X(1), X(2));
  P.ParametersOnS2(X(3), X(4));

  ComputeValues(X, 0, true, prm);
  distmin = std::min(distmin, pts1.Distance(pts2));

  ns1 = nsurf1;
  ns2 = nsurf2;
  np  = nplan;

  Poles2d(Poles2d.Lower()).SetCoord(X(1), X(2));
  Poles2d(Poles2d.Upper()).SetCoord(X(3), X(4));

  if (mySShape == BlendFunc_Linear)
  {
    Poles(low)   = pts1;
    Poles(upp)   = pts2;
    Weights(low) = 1.0;
    Weights(upp) = 1.0;
    return;
  }

  double norm1, norm2;
  norm1 = nplan.Crossed(ns1).Magnitude();
  norm2 = nplan.Crossed(ns2).Magnitude();
  if (norm1 < Eps)
  {
    norm1 = 1;
#ifdef OCCT_DEBUG
    std::cout << " EvolRad : Surface singuliere " << std::endl;
#endif
  }
  if (norm2 < Eps)
  {
    norm2 = 1;
#ifdef OCCT_DEBUG
    std::cout << " EvolRad : Surface singuliere " << std::endl;
#endif
  }

  ns1.SetLinearForm(nplan.Dot(ns1) / norm1, nplan, -1. / norm1, ns1);
  ns2.SetLinearForm(nplan.Dot(ns2) / norm2, nplan, -1. / norm2, ns2);

  Center.SetXYZ(pts1.XYZ() + sg1 * ray * ns1.XYZ());

  if (sg1 > 0.)
  {
    ns1.Reverse();
  }
  if (sg2 > 0.)
  {
    ns2.Reverse();
  }
  if (choix % 2 != 0)
  {
    np.Reverse();
  }

  GeomFill::GetCircle(myTConv, ns1, ns2, np, pts1, pts2, std::abs(ray), Center, Poles, Weights);
}

bool BlendFunc_EvolRad::Section(const Blend_Point&            P,
                                NCollection_Array1<gp_Pnt>&   Poles,
                                NCollection_Array1<gp_Vec>&   DPoles,
                                NCollection_Array1<gp_Pnt2d>& Poles2d,
                                NCollection_Array1<gp_Vec2d>& DPoles2d,
                                NCollection_Array1<double>&   Weights,
                                NCollection_Array1<double>&   DWeights)
{
  gp_Vec ns1, ns2, np, dnp, dnorm1w, dnorm2w, tgc;
  double norm1, norm2, rayprim;

  gp_Pnt      Center;
  math_Vector sol(1, 4), secmember(1, 4);

  double prm   = P.Parameter();
  int    low   = Poles.Lower();
  int    upp   = Poles.Upper();
  bool   istgt = true;

  P.ParametersOnS1(sol(1), sol(2));
  P.ParametersOnS2(sol(3), sol(4));

  ComputeValues(sol, 1, true, prm);
  distmin = std::min(distmin, pts1.Distance(pts2));

  ns1     = nsurf1;
  ns2     = nsurf2;
  np      = nplan;
  dnp     = dnplan;
  rayprim = dray;

  if (!pts1.IsEqual(pts2, 1.e-4))
  {

    math_Gauss Resol(DEDX, 1.e-9);

    if (Resol.IsDone())
    {
      Resol.Solve(-DEDT, secmember);
      istgt = false;
    }
  }

  if (istgt)
  {
    math_SVD SingRS(DEDX);
    if (SingRS.IsDone())
    {
      SingRS.Solve(-DEDT, secmember, 1.e-6);
      istgt = false;
    }
  }

  if (!istgt)
  {
    tg1.SetLinearForm(secmember(1), d1u1, secmember(2), d1v1);
    tg2.SetLinearForm(secmember(3), d1u2, secmember(4), d1v2);

    dnorm1w.SetLinearForm(secmember(1), dndu1, secmember(2), dndv1, dn1w);
    dnorm2w.SetLinearForm(secmember(3), dndu2, secmember(4), dndv2, dn2w);

    istgt = false;
  }

  Poles2d(Poles2d.Lower()).SetCoord(sol(1), sol(2));
  Poles2d(Poles2d.Upper()).SetCoord(sol(3), sol(4));
  if (!istgt)
  {
    DPoles2d(Poles2d.Lower()).SetCoord(secmember(1), secmember(2));
    DPoles2d(Poles2d.Upper()).SetCoord(secmember(3), secmember(4));
  }

  if (mySShape == BlendFunc_Linear)
  {
    Poles(low)   = pts1;
    Poles(upp)   = pts2;
    Weights(low) = 1.0;
    Weights(upp) = 1.0;
    if (!istgt)
    {
      DPoles(low)   = tg1;
      DPoles(upp)   = tg2;
      DWeights(low) = 0.0;
      DWeights(upp) = 0.0;
    }
    return (!istgt);
  }

  norm1 = nplan.Crossed(ns1).Magnitude();
  norm2 = nplan.Crossed(ns2).Magnitude();
  if (norm1 < Eps)
  {
    norm1 = 1;
#ifdef OCCT_DEBUG
    std::cout << " EvolRad : Surface singuliere " << std::endl;
#endif
  }
  if (norm2 < Eps)
  {
    norm2 = 1;
#ifdef OCCT_DEBUG
    std::cout << " EvolRad : Surface singuliere " << std::endl;
#endif
  }

  ns1.SetLinearForm(nplan.Dot(ns1) / norm1, nplan, -1. / norm1, ns1);
  ns2.SetLinearForm(nplan.Dot(ns2) / norm2, nplan, -1. / norm2, ns2);

  Center.SetXYZ(pts1.XYZ() + sg1 * ray * ns1.XYZ());
  if (!istgt)
  {
    tgc.SetLinearForm(sg1 * ray, dnorm1w, sg1 * dray, ns1, tg1);
  }

  if (sg1 > 0.)
  {
    ns1.Reverse();
    if (!istgt)
    {
      dnorm1w.Reverse();
    }
  }
  if (sg2 > 0.)
  {
    ns2.Reverse();
    if (!istgt)
    {
      dnorm2w.Reverse();
    }
  }
  if (choix % 2 != 0)
  {
    np.Reverse();
    dnp.Reverse();
  }

  if (ray < 0.)
  {
    rayprim = -rayprim;
  }

  if (!istgt)
  {
    return GeomFill::GetCircle(myTConv,
                               ns1,
                               ns2,
                               dnorm1w,
                               dnorm2w,
                               np,
                               dnp,
                               pts1,
                               pts2,
                               tg1,
                               tg2,
                               std::abs(ray),
                               rayprim,
                               Center,
                               tgc,
                               Poles,
                               DPoles,
                               Weights,
                               DWeights);
  }
  else
  {
    GeomFill::GetCircle(myTConv, ns1, ns2, np, pts1, pts2, std::abs(ray), Center, Poles, Weights);
    return false;
  }
}

bool BlendFunc_EvolRad::Section(const Blend_Point&            P,
                                NCollection_Array1<gp_Pnt>&   Poles,
                                NCollection_Array1<gp_Vec>&   DPoles,
                                NCollection_Array1<gp_Vec>&   D2Poles,
                                NCollection_Array1<gp_Pnt2d>& Poles2d,
                                NCollection_Array1<gp_Vec2d>& DPoles2d,
                                NCollection_Array1<gp_Vec2d>& D2Poles2d,
                                NCollection_Array1<double>&   Weights,
                                NCollection_Array1<double>&   DWeights,
                                NCollection_Array1<double>&   D2Weights)
{
  gp_Vec ns1, ns2, np, dnp, d2np, dnorm1w, dnorm2w, d2norm1w, d2norm2w;
  gp_Vec tgc, dtgc, dtg1, dtg2, temp, tempbis;
  double norm1, norm2, rayprim, raysecn;

  gp_Pnt      Center;
  math_Vector X(1, 4), sol(1, 4), secmember(1, 4);
  math_Matrix D2DXdSdt(1, 4, 1, 4);

  double prm   = P.Parameter();
  int    low   = Poles.Lower();
  int    upp   = Poles.Upper();
  bool   istgt = true;

  P.ParametersOnS1(X(1), X(2));
  P.ParametersOnS2(X(3), X(4));

  ComputeValues(X, 2, true, prm);
  distmin = std::min(distmin, pts1.Distance(pts2));

  ns1     = nsurf1;
  ns2     = nsurf2;
  np      = nplan;
  dnp     = dnplan;
  d2np    = d2nplan;
  rayprim = dray;
  raysecn = d2ray;

  if (!pts1.IsEqual(pts2, 1.e-4))
  {
    math_Gauss Resol(DEDX, 1.e-9);

    if (Resol.IsDone())
    {
      Resol.Solve(-DEDT, sol);
      D2EDX2.Multiply(sol, D2DXdSdt);
      secmember = -(D2EDT2 + (2 * D2EDXDT + D2DXdSdt) * sol);
      Resol.Solve(secmember);
      istgt = false;
    }
  }

  if (istgt)
  {
    math_SVD    SingRS(DEDX);
    math_Vector Vbis(1, 4);
    if (SingRS.IsDone())
    {
      SingRS.Solve(-DEDT, sol, 1.e-6);
      D2EDX2.Multiply(sol, D2DXdSdt);
      Vbis = -(D2EDT2 + (2 * D2EDXDT + D2DXdSdt) * sol);
      SingRS.Solve(Vbis, secmember, 1.e-6);
      istgt = false;
    }
  }

  if (!istgt)
  {
    tg1.SetLinearForm(sol(1), d1u1, sol(2), d1v1);
    tg2.SetLinearForm(sol(3), d1u2, sol(4), d1v2);

    dnorm1w.SetLinearForm(sol(1), dndu1, sol(2), dndv1, dn1w);
    dnorm2w.SetLinearForm(sol(3), dndu2, sol(4), dndv2, dn2w);
    temp.SetLinearForm(sol(1) * sol(1), d2u1, 2 * sol(1) * sol(2), d2uv1, sol(2) * sol(2), d2v1);

    dtg1.SetLinearForm(secmember(1), d1u1, secmember(2), d1v1, temp);

    temp.SetLinearForm(sol(3) * sol(3), d2u2, 2 * sol(3) * sol(4), d2uv2, sol(4) * sol(4), d2v2);
    dtg2.SetLinearForm(secmember(3), d1u2, secmember(4), d1v2, temp);

    temp.SetLinearForm(sol(1) * sol(1),
                       d2ndu1,
                       2 * sol(1) * sol(2),
                       d2nduv1,
                       sol(2) * sol(2),
                       d2ndv1);

    tempbis.SetLinearForm(2 * sol(1), d2ndtu1, 2 * sol(2), d2ndtv1, d2n1w);
    temp += tempbis;
    d2norm1w.SetLinearForm(secmember(1), dndu1, secmember(2), dndv1, temp);

    temp.SetLinearForm(sol(3) * sol(3),
                       d2ndu2,
                       2 * sol(3) * sol(4),
                       d2nduv2,
                       sol(4) * sol(4),
                       d2ndv2);
    tempbis.SetLinearForm(2 * sol(3), d2ndtu2, 2 * sol(4), d2ndtv2, d2n2w);
    temp += tempbis;
    d2norm2w.SetLinearForm(secmember(3), dndu2, secmember(4), dndv2, temp);
  }

  Poles2d(Poles2d.Lower()).SetCoord(X(1), X(2));
  Poles2d(Poles2d.Upper()).SetCoord(X(3), X(4));
  if (!istgt)
  {
    DPoles2d(Poles2d.Lower()).SetCoord(sol(1), sol(2));
    DPoles2d(Poles2d.Upper()).SetCoord(sol(3), sol(4));
    D2Poles2d(Poles2d.Lower()).SetCoord(secmember(1), secmember(2));
    D2Poles2d(Poles2d.Upper()).SetCoord(secmember(3), secmember(4));
  }

  if (mySShape == BlendFunc_Linear)
  {
    Poles(low)   = pts1;
    Poles(upp)   = pts2;
    Weights(low) = 1.0;
    Weights(upp) = 1.0;
    if (!istgt)
    {
      DPoles(low)    = tg1;
      DPoles(upp)    = tg2;
      DPoles(low)    = dtg1;
      DPoles(upp)    = dtg2;
      DWeights(low)  = 0.0;
      DWeights(upp)  = 0.0;
      D2Weights(low) = 0.0;
      D2Weights(upp) = 0.0;
    }
    return (!istgt);
  }

  norm1 = nplan.Crossed(ns1).Magnitude();
  norm2 = nplan.Crossed(ns2).Magnitude();
  if (norm1 < Eps)
  {
    norm1 = 1;
#ifdef OCCT_DEBUG
    std::cout << " EvolRad : Surface singuliere " << std::endl;
#endif
  }
  if (norm2 < Eps)
  {
    norm2 = 1;
#ifdef OCCT_DEBUG
    std::cout << " EvolRad : Surface singuliere " << std::endl;
#endif
  }

  ns1.SetLinearForm(nplan.Dot(ns1) / norm1, nplan, -1. / norm1, ns1);
  ns2.SetLinearForm(nplan.Dot(ns2) / norm2, nplan, -1. / norm2, ns2);

  Center.SetXYZ(pts1.XYZ() + sg1 * ray * ns1.XYZ());
  if (!istgt)
  {
    tgc.SetLinearForm(sg1 * ray, dnorm1w, sg1 * dray, ns1, tg1);
    dtgc.SetLinearForm(sg1 * ray, d2norm1w, 2 * sg1 * dray, dnorm1w, sg1 * d2ray, ns1);
    dtgc += dtg1;
  }

  if (sg1 > 0.)
  {
    ns1.Reverse();
    if (!istgt)
    {
      dnorm1w.Reverse();
      d2norm1w.Reverse();
    }
  }
  if (sg2 > 0.)
  {
    ns2.Reverse();
    if (!istgt)
    {
      dnorm2w.Reverse();
      d2norm2w.Reverse();
    }
  }
  if (choix % 2 != 0)
  {
    np.Reverse();
    dnp.Reverse();
    d2np.Reverse();
  }

  if (ray < 0.)
  {
    rayprim = -rayprim;
    raysecn = -raysecn;
  }

  if (!istgt)
  {
    return GeomFill::GetCircle(myTConv,
                               ns1,
                               ns2,
                               dnorm1w,
                               dnorm2w,
                               d2norm1w,
                               d2norm2w,
                               np,
                               dnp,
                               d2np,
                               pts1,
                               pts2,
                               tg1,
                               tg2,
                               dtg1,
                               dtg2,
                               std::abs(ray),
                               rayprim,
                               raysecn,
                               Center,
                               tgc,
                               dtgc,
                               Poles,
                               DPoles,
                               D2Poles,
                               Weights,
                               DWeights,
                               D2Weights);
  }
  else
  {
    GeomFill::GetCircle(myTConv,
                        ns1,
                        ns2,
                        nplan,
                        pts1,
                        pts2,
                        std::abs(ray),
                        Center,
                        Poles,
                        Weights);
    return false;
  }
}

void BlendFunc_EvolRad::Resolution(const int    IC2d,
                                   const double Tol,
                                   double&      TolU,
                                   double&      TolV) const
{
  if (IC2d == 1)
  {
    TolU = surf1->UResolution(Tol);
    TolV = surf1->VResolution(Tol);
  }
  else
  {
    TolU = surf2->UResolution(Tol);
    TolV = surf2->VResolution(Tol);
  }
}

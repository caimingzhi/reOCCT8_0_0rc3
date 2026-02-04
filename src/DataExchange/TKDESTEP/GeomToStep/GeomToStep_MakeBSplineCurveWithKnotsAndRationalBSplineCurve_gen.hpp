occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve> BSWK;
int                                                                Deg, N, i, Nknots, itampon;
double                                                             rtampon;
occ::handle<StepGeom_CartesianPoint>                               Pt = new StepGeom_CartesianPoint;
occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> Listpoints;
StepGeom_BSplineCurveForm                                              Form;
StepData_Logical                                                       Fermeture, Selfinter;
occ::handle<NCollection_HArray1<int>>                                  Mult;
occ::handle<NCollection_HArray1<double>>                               ListKnots, ListWeights;
GeomAbs_BSplKnotDistribution                                           Distribution;
StepGeom_KnotType                                                      KnotSpec;

Deg = BS->Degree();

N = BS->NbPoles();
Array1OfPnt_gen P(1, N);
BS->Poles(P);
Listpoints = new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, N);
for (i = P.Lower(); i <= P.Upper(); i++)
{
  GeomToStep_MakeCartesianPoint MkPoint(P.Value(i), theLocalFactors.LengthFactor());
  Pt = MkPoint.Value();
  Listpoints->SetValue(i, Pt);
}

Form = StepGeom_bscfUnspecified;

if (BS->IsClosed())
  Fermeture = StepData_LTrue;
else
  Fermeture = StepData_LFalse;

Selfinter = StepData_LFalse;

Nknots = BS->NbKnots();
NCollection_Array1<int> M(1, Nknots);
BS->Multiplicities(M);
Mult = new NCollection_HArray1<int>(1, Nknots);
for (i = M.Lower(); i <= M.Upper(); i++)
{
  itampon = M.Value(i);
  Mult->SetValue(i, itampon);
}

NCollection_Array1<double> K(1, Nknots);
BS->Knots(K);
ListKnots = new NCollection_HArray1<double>(1, Nknots);
for (i = K.Lower(); i <= K.Upper(); i++)
{
  rtampon = K.Value(i);
  ListKnots->SetValue(i, rtampon);
}

Distribution = BS->KnotDistribution();
if (Distribution == GeomAbs_NonUniform)
  KnotSpec = StepGeom_ktUnspecified;
else if (Distribution == GeomAbs_Uniform)
  KnotSpec = StepGeom_ktUniformKnots;
else if (Distribution == GeomAbs_QuasiUniform)
  KnotSpec = StepGeom_ktQuasiUniformKnots;
else
  KnotSpec = StepGeom_ktPiecewiseBezierKnots;

NCollection_Array1<double> W(1, N);
BS->Weights(W);
ListWeights = new NCollection_HArray1<double>(1, N);
for (i = W.Lower(); i <= W.Upper(); i++)
{
  rtampon = W.Value(i);
  ListWeights->SetValue(i, rtampon);
}

BSWK = new StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve;
occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
BSWK
  ->Init(name, Deg, Listpoints, Form, Fermeture, Selfinter, Mult, ListKnots, KnotSpec, ListWeights);

theBSplineCurveWithKnotsAndRationalBSplineCurve = BSWK;
done                                            = true;

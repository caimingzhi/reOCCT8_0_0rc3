occ::handle<StepGeom_Circle>           CStep = new StepGeom_Circle;
StepGeom_Axis2Placement                Ax2;
occ::handle<StepGeom_Axis2Placement3d> Ax2Step;
double                                 Rayon;

GeomToStep_MakeAxis2Placement3d MkAxis2(C.Position(), theLocalFactors);
Ax2Step = MkAxis2.Value();
Rayon   = C.Radius();
Ax2.SetValue(Ax2Step);
occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
CStep->Init(name, Ax2, Rayon / theLocalFactors.LengthFactor());
theCircle = CStep;
done      = true;

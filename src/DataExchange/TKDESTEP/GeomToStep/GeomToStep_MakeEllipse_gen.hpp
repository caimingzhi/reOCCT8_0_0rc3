occ::handle<StepGeom_Ellipse>          EStep = new StepGeom_Ellipse;
StepGeom_Axis2Placement                Ax2;
occ::handle<StepGeom_Axis2Placement3d> Ax2Step;
double                                 majorR, minorR;

GeomToStep_MakeAxis2Placement3d MkAxis2(E.Position(), theLocalFactors);
Ax2Step = MkAxis2.Value();
majorR  = E.MajorRadius();
minorR  = E.MinorRadius();
Ax2.SetValue(Ax2Step);
occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
double                                fact = theLocalFactors.LengthFactor();
EStep->Init(name, Ax2, majorR / fact, minorR / fact);
theEllipse = EStep;
done       = true;

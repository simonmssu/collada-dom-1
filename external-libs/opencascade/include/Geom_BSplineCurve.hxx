// File generated by CPPExt (Transient)
//
//
//                     Copyright (C) 1991 - 2000 by  
//                      Matra Datavision SA.  All rights reserved.
//  
//                     Copyright (C) 2001 - 2004 by
//                     Open CASCADE SA.  All rights reserved.
// 
// This file is part of the Open CASCADE Technology software.
//
// This software may be distributed and/or modified under the terms and
// conditions of the Open CASCADE Public License as defined by Open CASCADE SA
// and appearing in the file LICENSE included in the packaging of this file.
//  
// This software is distributed on an "AS IS" basis, without warranty of any
// kind, and Open CASCADE SA hereby disclaims all such warranties,
// including without limitation, any warranties of merchantability, fitness
// for a particular purpose or non-infringement. Please see the License for
// the specific terms and conditions governing rights and limitations under the
// License.

#ifndef _Geom_BSplineCurve_HeaderFile
#define _Geom_BSplineCurve_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Handle_Geom_BSplineCurve_HeaderFile
#include <Handle_Geom_BSplineCurve.hxx>
#endif

#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _GeomAbs_BSplKnotDistribution_HeaderFile
#include <GeomAbs_BSplKnotDistribution.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_TColgp_HArray1OfPnt_HeaderFile
#include <Handle_TColgp_HArray1OfPnt.hxx>
#endif
#ifndef _Handle_TColStd_HArray1OfReal_HeaderFile
#include <Handle_TColStd_HArray1OfReal.hxx>
#endif
#ifndef _Handle_TColStd_HArray1OfInteger_HeaderFile
#include <Handle_TColStd_HArray1OfInteger.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Geom_BoundedCurve_HeaderFile
#include <Geom_BoundedCurve.hxx>
#endif
#ifndef _Handle_Geom_Geometry_HeaderFile
#include <Handle_Geom_Geometry.hxx>
#endif
class TColgp_HArray1OfPnt;
class TColStd_HArray1OfReal;
class TColStd_HArray1OfInteger;
class Standard_ConstructionError;
class Standard_DimensionError;
class Standard_DomainError;
class Standard_OutOfRange;
class Standard_RangeError;
class Standard_NoSuchObject;
class Geom_UndefinedDerivative;
class TColgp_Array1OfPnt;
class TColStd_Array1OfReal;
class TColStd_Array1OfInteger;
class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class Geom_Geometry;


//! Definition of the B_spline curve. <br>
//!       A B-spline curve can be <br>
//!         Uniform  or non-uniform <br>
//!         Rational or non-rational <br>
//!         Periodic or non-periodic <br>
//! <br>
//!  a b-spline curve is defined by : <br>
//!  its degree; the degree for a <br>
//!   Geom_BSplineCurve is limited to a value (25) <br>
//!   which is defined and controlled by the system. <br>
//!   This value is returned by the function MaxDegree; <br>
//! - its periodic or non-periodic nature; <br>
//! - a table of poles (also called control points), with <br>
//!   their associated weights if the BSpline curve is <br>
//!   rational. The poles of the curve are "control <br>
//!   points" used to deform the curve. If the curve is <br>
//!   non-periodic, the first pole is the start point of <br>
//!   the curve, and the last pole is the end point of <br>
//!   the curve. The segment which joins the first pole <br>
//!   to the second pole is the tangent to the curve at <br>
//!   its start point, and the segment which joins the <br>
//!   last pole to the second-from-last pole is the <br>
//!   tangent to the curve at its end point. If the curve <br>
//!   is periodic, these geometric properties are not <br>
//!   verified. It is more difficult to give a geometric <br>
//!   signification to the weights but are useful for <br>
//!   providing exact representations of the arcs of a <br>
//!   circle or ellipse. Moreover, if the weights of all the <br>
//!   poles are equal, the curve has a polynomial <br>
//!   equation; it is therefore a non-rational curve. <br>
//! - a table of knots with their multiplicities. For a <br>
//!   Geom_BSplineCurve, the table of knots is an <br>
//!   increasing sequence of reals without repetition; <br>
//!   the multiplicities define the repetition of the knots. <br>
//!   A BSpline curve is a piecewise polynomial or <br>
//!   rational curve. The knots are the parameters of <br>
//!   junction points between two pieces. The <br>
//!   multiplicity Mult(i) of the knot Knot(i) of <br>
//!   the BSpline curve is related to the degree of <br>
//!   continuity of the curve at the knot Knot(i), <br>
//!   which is equal to Degree - Mult(i) <br>
//!   where Degree is the degree of the BSpline curve. <br>
//!   If the knots are regularly spaced (i.e. the difference <br>
//!   between two consecutive knots is a constant), three <br>
//!   specific and frequently used cases of knot <br>
//!   distribution can be identified: <br>
//! - "uniform" if all multiplicities are equal to 1, <br>
//! - "quasi-uniform" if all multiplicities are equal to 1, <br>
//!   except the first and the last knot which have a <br>
//!   multiplicity of Degree + 1, where Degree is <br>
//!   the degree of the BSpline curve, <br>
//! - "Piecewise Bezier" if all multiplicities are equal to <br>
//!   Degree except the first and last knot which <br>
//!   have a multiplicity of Degree + 1, where <br>
//!   Degree is the degree of the BSpline curve. A <br>
//!   curve of this type is a concatenation of arcs of Bezier curves. <br>
//! If the BSpline curve is not periodic: <br>
//! - the bounds of the Poles and Weights tables are 1 <br>
//!   and NbPoles, where NbPoles is the number <br>
//!   of poles of the BSpline curve, <br>
//! - the bounds of the Knots and Multiplicities tables <br>
//!   are 1 and NbKnots, where NbKnots is the <br>
//!   number of knots of the BSpline curve. <br>
//! If the BSpline curve is periodic, and if there are k <br>
//! periodic knots and p periodic poles, the period is: <br>
//! period = Knot(k + 1) - Knot(1) <br>
//! and the poles and knots tables can be considered <br>
//! as infinite tables, verifying: <br>
//! - Knot(i+k) = Knot(i) + period <br>
//! - Pole(i+p) = Pole(i) <br>
//! Note: data structures of a periodic BSpline curve <br>
//! are more complex than those of a non-periodic one. <br>
//! Warning <br>
//! In this class, weight value is considered to be zero if <br>
//! the weight is less than or equal to gp::Resolution(). <br>
//! <br>
//! References : <br>
//!  . A survey of curve and surface methods in CADG Wolfgang BOHM <br>
//!    CAGD 1 (1984) <br>
//!  . On de Boor-like algorithms and blossoming Wolfgang BOEHM <br>
//!    cagd 5 (1988) <br>
//!  . Blossoming and knot insertion algorithms for B-spline curves <br>
//!    Ronald N. GOLDMAN <br>
//!  . Modelisation des surfaces en CAO, Henri GIAUME Peugeot SA <br>
//!  . Curves and Surfaces for Computer Aided Geometric Design, <br>
//!    a practical guide Gerald Farin <br>
class Geom_BSplineCurve : public Geom_BoundedCurve {

public:
 // Methods PUBLIC
 // 

//!  Creates a  non-rational B_spline curve   on  the <br>
//!         basis <Knots, Multiplicities> of degree <Degree>. <br>
Standard_EXPORT Geom_BSplineCurve(const TColgp_Array1OfPnt& Poles,const TColStd_Array1OfReal& Knots,const TColStd_Array1OfInteger& Multiplicities,const Standard_Integer Degree,const Standard_Boolean Periodic = Standard_False);

//! Creates  a rational B_spline  curve  on the basis <br>
//!         <Knots, Multiplicities> of degree <Degree>. <br>
//!  Raises ConstructionError subject to the following conditions <br>
//!  0 < Degree <= MaxDegree. <br>
//! <br>
//!  Weights.Length() == Poles.Length() <br>
//! <br>
//!  Knots.Length() == Mults.Length() >= 2 <br>
//! <br>
//!  Knots(i) < Knots(i+1) (Knots are increasing) <br>
//! <br>
//!  1 <= Mults(i) <= Degree <br>
//! <br>
//!   On a non periodic curve the first and last multiplicities <br>
//!   may be Degree+1 (this is even recommanded if you want the <br>
//!   curve to start and finish on the first and last pole). <br>
//! <br>
//!   On a periodic  curve the first  and  the last multicities <br>
//!   must be the same. <br>
//! <br>
//!   on non-periodic curves <br>
//! <br>
//!     Poles.Length() == Sum(Mults(i)) - Degree - 1 >= 2 <br>
//! <br>
//!   on periodic curves <br>
//! <br>
//!     Poles.Length() == Sum(Mults(i)) except the first or last <br>
Standard_EXPORT Geom_BSplineCurve(const TColgp_Array1OfPnt& Poles,const TColStd_Array1OfReal& Weights,const TColStd_Array1OfReal& Knots,const TColStd_Array1OfInteger& Multiplicities,const Standard_Integer Degree,const Standard_Boolean Periodic = Standard_False,const Standard_Boolean CheckRational = Standard_True);

//! Increases the degree of this BSpline curve to <br>
//! Degree. As a result, the poles, weights and <br>
//! multiplicities tables are modified; the knots table is <br>
//! not changed. Nothing is done if Degree is less than <br>
//! or equal to the current degree. <br>
//! Exceptions <br>
//! Standard_ConstructionError if Degree is greater than <br>
//! Geom_BSplineCurve::MaxDegree(). <br>
Standard_EXPORT   void IncreaseDegree(const Standard_Integer Degree) ;

//!Increases the multiplicity  of the knot <Index> to <br>
//!         <M>. <br>
//! <br>
//!         If   <M>   is   lower   or  equal   to  the current <br>
//!         multiplicity nothing is done. If <M> is higher than <br>
//!         the degree the degree is used. <br>//! If <Index> is not in [FirstUKnotIndex, LastUKnotIndex] <br>
Standard_EXPORT   void IncreaseMultiplicity(const Standard_Integer Index,const Standard_Integer M) ;

//!Increases  the  multiplicities   of  the knots  in <br>
//!         [I1,I2] to <M>. <br>
//! <br>
//!         For each knot if  <M>  is  lower  or equal  to  the <br>
//!         current multiplicity  nothing  is  done. If <M>  is <br>
//!         higher than the degree the degree is used. <br>//! If <I1,I2> are not in [FirstUKnotIndex, LastUKnotIndex] <br>
Standard_EXPORT   void IncreaseMultiplicity(const Standard_Integer I1,const Standard_Integer I2,const Standard_Integer M) ;

//!Increment  the  multiplicities   of  the knots  in <br>
//!         [I1,I2] by <M>. <br>
//! <br>
//!         If <M> is not positive nithing is done. <br>
//! <br>
//!         For   each  knot   the resulting   multiplicity  is <br>
//!         limited to the Degree. <br>//! If <I1,I2> are not in [FirstUKnotIndex, LastUKnotIndex] <br>
Standard_EXPORT   void IncrementMultiplicity(const Standard_Integer I1,const Standard_Integer I2,const Standard_Integer M) ;

//! Inserts a knot value in the sequence of knots.  If <br>
//!          <U>  is an  existing knot     the multiplicity  is <br>
//!          increased by <M>. <br>
//! <br>
//!          If U  is  not  on the parameter  range  nothing is <br>
//!          done. <br>
//! <br>
//!          If the multiplicity is negative or null nothing is <br>
//!          done. The  new   multiplicity  is limited  to  the <br>
//!          degree. <br>
//! <br>
//!          The  tolerance criterion  for  knots  equality  is <br>
//!          the max of Epsilon(U) and ParametricTolerance. <br>
Standard_EXPORT   void InsertKnot(const Standard_Real U,const Standard_Integer M = 1,const Standard_Real ParametricTolerance = 0.0,const Standard_Boolean Add = Standard_True) ;

//! Inserts a set of knots  values in  the sequence of <br>
//!          knots. <br>
//! <br>
//!          For each U = Knots(i), M = Mults(i) <br>
//! <br>
//!          If <U>  is an existing  knot  the  multiplicity is <br>
//!          increased by  <M> if  <Add>  is True, increased to <br>
//!          <M> if <Add> is False. <br>
//! <br>
//!          If U  is  not  on the parameter  range  nothing is <br>
//!          done. <br>
//! <br>
//!          If the multiplicity is negative or null nothing is <br>
//!          done. The  new   multiplicity  is limited  to  the <br>
//!          degree. <br>
//! <br>
//!          The  tolerance criterion  for  knots  equality  is <br>
//!          the max of Epsilon(U) and ParametricTolerance. <br>
Standard_EXPORT   void InsertKnots(const TColStd_Array1OfReal& Knots,const TColStd_Array1OfInteger& Mults,const Standard_Real ParametricTolerance = 0.0,const Standard_Boolean Add = Standard_False) ;

//! Reduces the multiplicity of the knot of index Index <br>
//! to M. If M is equal to 0, the knot is removed. <br>
//! With a modification of this type, the array of poles is also modified. <br>
//! Two different algorithms are systematically used to <br>
//! compute the new poles of the curve. If, for each <br>
//! pole, the distance between the pole calculated <br>
//! using the first algorithm and the same pole <br>
//! calculated using the second algorithm, is less than <br>
//! Tolerance, this ensures that the curve is not <br>
//! modified by more than Tolerance. Under these <br>
//! conditions, true is returned; otherwise, false is returned. <br>
//! A low tolerance is used to prevent modification of <br>
//! the curve. A high tolerance is used to "smooth" the curve. <br>
//! Exceptions <br>
//! Standard_OutOfRange if Index is outside the <br>
//! bounds of the knots table. <br>//! pole insertion and pole removing <br>
//!  this operation is limited to the Uniform or QuasiUniform <br>
//!  BSplineCurve. The knot values are modified . If the BSpline is <br>
//!  NonUniform or Piecewise Bezier an exception Construction error <br>
//!  is raised. <br>
Standard_EXPORT   Standard_Boolean RemoveKnot(const Standard_Integer Index,const Standard_Integer M,const Standard_Real Tolerance) ;


//!  Changes the direction of parametrization of <me>. The Knot <br>
//!  sequence is modified, the FirstParameter and the <br>
//!  LastParameter are not modified. The StartPoint of the <br>
//!  initial curve becomes the EndPoint of the reversed curve <br>
//!  and the EndPoint of the initial curve becomes the StartPoint <br>
//!  of the reversed curve. <br>
Standard_EXPORT   void Reverse() ;

//! Returns the  parameter on the  reversed  curve for <br>
//!          the point of parameter U on <me>. <br>
//! <br>
//!          returns UFirst + ULast - U <br>
Standard_EXPORT   Standard_Real ReversedParameter(const Standard_Real U) const;

//! Modifies this BSpline curve by segmenting it between <br>
//! U1 and U2. Either of these values can be outside the <br>
//! bounds of the curve, but U2 must be greater than U1. <br>
//! All data structure tables of this BSpline curve are <br>
//! modified, but the knots located between U1 and U2 <br>
//! are retained. The degree of the curve is not modified. <br>
//!  Warnings : <br>
//!  Even if <me> is not closed it can become closed after the <br>
//!  segmentation for example if U1 or U2 are out of the bounds <br>
//!  of the curve <me> or if the curve makes loop. <br>
//!  After the segmentation the length of a curve can be null. <br>//! raises if U2 < U1. <br>
Standard_EXPORT   void Segment(const Standard_Real U1,const Standard_Real U2) ;

//! Modifies this BSpline curve by assigning the value K <br>
//! to the knot of index Index in the knots table. This is a <br>
//! relatively local modification because K must be such that: <br>
//! Knots(Index - 1) < K < Knots(Index + 1) <br>
//! The second syntax allows you also to increase the <br>
//! multiplicity of the knot to M (but it is not possible to <br>
//! decrease the multiplicity of the knot with this function). <br>
//! Standard_ConstructionError if: <br>
//! - K is not such that: <br>
//! Knots(Index - 1) < K < Knots(Index + 1) <br>
//! - M is greater than the degree of this BSpline curve <br>
//!   or lower than the previous multiplicity of knot of <br>
//!   index Index in the knots table. <br>
//!  Standard_OutOfRange if Index is outside the bounds of the knots table. <br>
Standard_EXPORT   void SetKnot(const Standard_Integer Index,const Standard_Real K) ;

//!  Modifies this BSpline curve by assigning the array <br>
//! K to its knots table. The multiplicity of the knots is not modified. <br>
//! Exceptions <br>
//! Standard_ConstructionError if the values in the <br>
//! array K are not in ascending order. <br>
//! Standard_OutOfRange if the bounds of the array <br>
//! K are not respectively 1 and the number of knots of this BSpline curve. <br>
Standard_EXPORT   void SetKnots(const TColStd_Array1OfReal& K) ;


//!  Changes the knot of range Index with its multiplicity. <br>
//!  You can increase the multiplicity of a knot but it is <br>
//!  not allowed to decrease the multiplicity of an existing knot. <br>
//!  Raised if K >= Knots(Index+1) or K <= Knots(Index-1). <br>
//!  Raised if M is greater than Degree or lower than the previous <br>
//!  multiplicity of knot of range Index. <br>//! Raised if Index < 1 || Index > NbKnots <br>
Standard_EXPORT   void SetKnot(const Standard_Integer Index,const Standard_Real K,const Standard_Integer M) ;

//! returns the parameter normalized within <br>
//!         the period if the curve is periodic : otherwise <br>
//!         does not do anything <br>
Standard_EXPORT   void PeriodicNormalization(Standard_Real& U) const;

//! Changes this BSpline curve into a periodic curve. <br>
//! To become periodic, the curve must first be closed. <br>
//! Next, the knot sequence must be periodic. For this, <br>
//! FirstUKnotIndex and LastUKnotIndex are used <br>
//! to compute I1 and I2, the indexes in the knots <br>
//! array of the knots corresponding to the first and <br>
//! last parameters of this BSpline curve. <br>
//! The period is therefore: Knots(I2) - Knots(I1). <br>
//! Consequently, the knots and poles tables are modified. <br>
//! Exceptions <br>
//! Standard_ConstructionError if this BSpline curve is not closed. <br>
Standard_EXPORT   void SetPeriodic() ;

//! Assigns the knot of index Index in the knots table as <br>
//! the origin of this periodic BSpline curve. As a <br>
//! consequence, the knots and poles tables are modified. <br>
//! Exceptions <br>
//! Standard_NoSuchObject if this curve is not periodic. <br>
//! Standard_DomainError if Index is outside the bounds of the knots table. <br>
Standard_EXPORT   void SetOrigin(const Standard_Integer Index) ;

//! Set the origin of a periodic curve at Knot U. If U <br>
//!          is  not a  knot  of  the  BSpline  a  new knot  is <br>
//!          inseted. KnotVector and poles are modified. <br>//! Raised if the curve is not periodic <br>
Standard_EXPORT   void SetOrigin(const Standard_Real U,const Standard_Real Tol) ;

//! Changes this BSpline curve into a non-periodic <br>
//! curve. If this curve is already non-periodic, it is not modified. <br>
//! Note: the poles and knots tables are modified. <br>
//! Warning <br>
//! If this curve is periodic, as the multiplicity of the first <br>
//! and last knots is not modified, and is not equal to <br>
//! Degree + 1, where Degree is the degree of <br>
//! this BSpline curve, the start and end points of the <br>
//! curve are not its first and last poles. <br>
Standard_EXPORT   void SetNotPeriodic() ;

//! Modifies this BSpline curve by assigning P to the pole <br>
//! of index Index in the poles table. <br>
//! Exceptions <br>
//! Standard_OutOfRange if Index is outside the <br>
//! bounds of the poles table. <br>
//! Standard_ConstructionError if Weight is negative or null. <br>
Standard_EXPORT   void SetPole(const Standard_Integer Index,const gp_Pnt& P) ;

//! Modifies this BSpline curve by assigning P to the pole <br>
//! of index Index in the poles table. <br>
//! This syntax also allows you to modify the <br>
//! weight of the modified pole, which becomes Weight. <br>
//! In this case, if this BSpline curve is non-rational, it <br>
//! can become rational and vice versa. <br>
//! Exceptions <br>
//! Standard_OutOfRange if Index is outside the <br>
//! bounds of the poles table. <br>
//! Standard_ConstructionError if Weight is negative or null. <br>
Standard_EXPORT   void SetPole(const Standard_Integer Index,const gp_Pnt& P,const Standard_Real Weight) ;


//!  Changes the weight for the pole of range Index. <br>
//!  If the curve was non rational it can become rational. <br>
//!  If the curve was rational it can become non rational. <br>
//!  Raised if Index < 1 || Index > NbPoles <br>//! Raised if Weight <= 0.0 <br>
Standard_EXPORT   void SetWeight(const Standard_Integer Index,const Standard_Real Weight) ;

//! Moves the point of parameter U of this BSpline curve <br>
//! to P. Index1 and Index2 are the indexes in the table <br>
//! of poles of this BSpline curve of the first and last <br>
//! poles designated to be moved. <br>
//! FirstModifiedPole and LastModifiedPole are the <br>
//! indexes of the first and last poles which are effectively modified. <br>
//! In the event of incompatibility between Index1, Index2 and the value U: <br>
//! - no change is made to this BSpline curve, and <br>
//! - the FirstModifiedPole and LastModifiedPole are returned null. <br>
//!   Exceptions <br>
//! Standard_OutOfRange if: <br>
//! - Index1 is greater than or equal to Index2, or <br>
//! - Index1 or Index2 is less than 1 or greater than the <br>
//!   number of poles of this BSpline curve. <br>
Standard_EXPORT   void MovePoint(const Standard_Real U,const gp_Pnt& P,const Standard_Integer Index1,const Standard_Integer Index2,Standard_Integer& FirstModifiedPole,Standard_Integer& LastModifiedPole) ;


//! Move a point with parameter U to P. <br>
//! and makes it tangent at U be Tangent. <br>
//! StartingCondition = -1 means first can move <br>
//! EndingCondition   = -1 means last point can move <br>
//! StartingCondition = 0 means the first point cannot move <br>
//! EndingCondition   = 0 means the last point cannot move <br>
//! StartingCondition = 1 means the first point and tangent cannot move <br>
//! EndingCondition   = 1 means the last point and tangent cannot move <br>
//! and so forth <br>
//! ErrorStatus != 0 means that there are not enought degree of freedom <br>
//! with the constrain to deform the curve accordingly <br>
//! <br>
Standard_EXPORT   void MovePointAndTangent(const Standard_Real U,const gp_Pnt& P,const gp_Vec& Tangent,const Standard_Real Tolerance,const Standard_Integer StartingCondition,const Standard_Integer EndingCondition,Standard_Integer& ErrorStatus) ;


//!  Returns the continuity of the curve, the curve is at least C0. <br>//! Raised if N < 0. <br>
Standard_EXPORT   Standard_Boolean IsCN(const Standard_Integer N) const;


//!  Returns true if the distance between the first point and the <br>
//!  last point of the curve is lower or equal to Resolution <br>
//!  from package gp. <br>
//! Warnings : <br>
//!  The first and the last point can be different from the first <br>
//!  pole and the last pole of the curve. <br>
Standard_EXPORT   Standard_Boolean IsClosed() const;

//! Returns True if the curve is periodic. <br>
Standard_EXPORT   Standard_Boolean IsPeriodic() const;


//!  Returns True if the weights are not identical. <br>
//!  The tolerance criterion is Epsilon of the class Real. <br>
Standard_EXPORT   Standard_Boolean IsRational() const;


//!  Returns the global continuity of the curve : <br>
//!  C0 : only geometric continuity, <br>
//!  C1 : continuity of the first derivative all along the Curve, <br>
//!  C2 : continuity of the second derivative all along the Curve, <br>
//!  C3 : continuity of the third derivative all along the Curve, <br>
//!  CN : the order of continuity is infinite. <br>
//!  For a B-spline curve of degree d if a knot Ui has a <br>
//!  multiplicity p the B-spline curve is only Cd-p continuous <br>
//!  at Ui. So the global continuity of the curve can't be greater <br>
//!  than Cd-p where p is the maximum multiplicity of the interior <br>
//!  Knots. In the interior of a knot span the curve is infinitely <br>
//!  continuously differentiable. <br>
Standard_EXPORT   GeomAbs_Shape Continuity() const;

//! Returns the degree of this BSpline curve. <br>
//! The degree of a Geom_BSplineCurve curve cannot <br>
//! be greater than Geom_BSplineCurve::MaxDegree(). <br>//! Computation of value and derivatives <br>
Standard_EXPORT   Standard_Integer Degree() const;

//! Returns in P the point of parameter U. <br>
Standard_EXPORT   void D0(const Standard_Real U,gp_Pnt& P) const;

//! Raised if the continuity of the curve is not C1. <br>
Standard_EXPORT   void D1(const Standard_Real U,gp_Pnt& P,gp_Vec& V1) const;

//! Raised if the continuity of the curve is not C2. <br>
Standard_EXPORT   void D2(const Standard_Real U,gp_Pnt& P,gp_Vec& V1,gp_Vec& V2) const;

//! Raised if the continuity of the curve is not C3. <br>
Standard_EXPORT   void D3(const Standard_Real U,gp_Pnt& P,gp_Vec& V1,gp_Vec& V2,gp_Vec& V3) const;

//! For the point of parameter U of this BSpline curve, <br>
//! computes the vector corresponding to the Nth derivative. <br>
//! Warning <br>
//! On a point where the continuity of the curve is not the <br>
//! one requested, this function impacts the part defined <br>
//! by the parameter with a value greater than U, i.e. the <br>
//! part of the curve to the "right" of the singularity. <br>
//! Exceptions <br>
//! Standard_RangeError if N is less than 1. <br>
//!  The following functions compute the point of parameter U <br>
//!  and the derivatives at this point on the B-spline curve <br>
//!  arc defined between the knot FromK1 and the knot ToK2. <br>
//!  U can be out of bounds [Knot (FromK1),  Knot (ToK2)] but <br>
//!  for the computation we only use the definition of the curve <br>
//!  between these two knots. This method is useful to compute <br>
//!  local derivative, if the order of continuity of the whole <br>
//!  curve is not greater enough.    Inside the parametric <br>
//!  domain Knot (FromK1), Knot (ToK2) the evaluations are <br>
//!  the same as if we consider the whole definition of the <br>
//!  curve. Of course the evaluations are different outside <br>
//!  this parametric domain. <br>
Standard_EXPORT   gp_Vec DN(const Standard_Real U,const Standard_Integer N) const;

//! Raised if FromK1 = ToK2. <br>
//!  Raised if FromK1 and ToK2 are not in the range <br>
//!  [FirstUKnotIndex, LastUKnotIndex]. <br>
Standard_EXPORT   gp_Pnt LocalValue(const Standard_Real U,const Standard_Integer FromK1,const Standard_Integer ToK2) const;

//! Raised if FromK1 = ToK2. <br>
//!  Raised if FromK1 and ToK2 are not in the range <br>
//!  [FirstUKnotIndex, LastUKnotIndex]. <br>
Standard_EXPORT   void LocalD0(const Standard_Real U,const Standard_Integer FromK1,const Standard_Integer ToK2,gp_Pnt& P) const;


//!  Raised if the local continuity of the curve is not C1 <br>
//!  between the knot K1 and the knot K2. <br>//! Raised if FromK1 = ToK2. <br>
//!  Raised if FromK1 and ToK2 are not in the range <br>
//!  [FirstUKnotIndex, LastUKnotIndex]. <br>
Standard_EXPORT   void LocalD1(const Standard_Real U,const Standard_Integer FromK1,const Standard_Integer ToK2,gp_Pnt& P,gp_Vec& V1) const;


//!  Raised if the local continuity of the curve is not C2 <br>
//!  between the knot K1 and the knot K2. <br>//! Raised if FromK1 = ToK2. <br>
//!  Raised if FromK1 and ToK2 are not in the range <br>
//!  [FirstUKnotIndex, LastUKnotIndex]. <br>
Standard_EXPORT   void LocalD2(const Standard_Real U,const Standard_Integer FromK1,const Standard_Integer ToK2,gp_Pnt& P,gp_Vec& V1,gp_Vec& V2) const;


//!  Raised if the local continuity of the curve is not C3 <br>
//!  between the knot K1 and the knot K2. <br>//! Raised if FromK1 = ToK2. <br>
//!  Raised if FromK1 and ToK2 are not in the range <br>
//!  [FirstUKnotIndex, LastUKnotIndex]. <br>
Standard_EXPORT   void LocalD3(const Standard_Real U,const Standard_Integer FromK1,const Standard_Integer ToK2,gp_Pnt& P,gp_Vec& V1,gp_Vec& V2,gp_Vec& V3) const;


//!  Raised if the local continuity of the curve is not CN <br>
//!  between the knot K1 and the knot K2. <br>//! Raised if FromK1 = ToK2. <br>//! Raised if N < 1. <br>
//!  Raises if FromK1 and ToK2 are not in the range <br>
//!  [FirstUKnotIndex, LastUKnotIndex]. <br>
Standard_EXPORT   gp_Vec LocalDN(const Standard_Real U,const Standard_Integer FromK1,const Standard_Integer ToK2,const Standard_Integer N) const;


//!  Returns the last point of the curve. <br>
//! Warnings : <br>
//!  The last point of the curve is different from the last <br>
//!  pole of the curve if the multiplicity of the last knot <br>
//!  is lower than Degree. <br>
Standard_EXPORT   gp_Pnt EndPoint() const;

//! Returns the index in the knot array of the knot <br>
//! corresponding to the first or last parameter of this BSpline curve. <br>
//! For a BSpline curve, the first (or last) parameter <br>
//! (which gives the start (or end) point of the curve) is a <br>
//! knot value. However, if the multiplicity of the first (or <br>
//! last) knot is less than Degree + 1, where <br>
//! Degree is the degree of the curve, it is not the first <br>
//! (or last) knot of the curve. <br>
Standard_EXPORT   Standard_Integer FirstUKnotIndex() const;

//! Returns the value of the first parameter of this <br>
//! BSpline curve. This is a knot value. <br>
//! The first parameter is the one of the start point of the BSpline curve. <br>
Standard_EXPORT   Standard_Real FirstParameter() const;


//!  Returns the knot of range Index. When there is a knot <br>
//!  with a multiplicity greater than 1 the knot is not repeated. <br>
//!  The method Multiplicity can be used to get the multiplicity <br>
//!  of the Knot. <br>//! Raised if Index < 1 or Index > NbKnots <br>
Standard_EXPORT   Standard_Real Knot(const Standard_Integer Index) const;

//! returns the knot values of the B-spline curve; <br>
//! Warning <br>
//! A knot with a multiplicity greater than 1 is not <br>
//! repeated in the knot table. The Multiplicity function <br>
//! can be used to obtain the multiplicity of each knot. <br>
//!  Raised if the length of K is not equal to the number of knots. <br>
Standard_EXPORT   void Knots(TColStd_Array1OfReal& K) const;

//! Returns K, the knots sequence of this BSpline curve. <br>
//! In this sequence, knots with a multiplicity greater than 1 are repeated. <br>
//! In the case of a non-periodic curve the length of the <br>
//! sequence must be equal to the sum of the NbKnots <br>
//! multiplicities of the knots of the curve (where <br>
//! NbKnots is the number of knots of this BSpline <br>
//! curve). This sum is also equal to : NbPoles + Degree + 1 <br>
//! where NbPoles is the number of poles and <br>
//! Degree the degree of this BSpline curve. <br>
//! In the case of a periodic curve, if there are k periodic <br>
//! knots, the period is Knot(k+1) - Knot(1). <br>
//! The initial sequence is built by writing knots 1 to k+1, <br>
//! which are repeated according to their corresponding multiplicities. <br>
//! If Degree is the degree of the curve, the degree of <br>
//! continuity of the curve at the knot of index 1 (or k+1) <br>
//! is equal to c = Degree + 1 - Mult(1). c <br>
//! knots are then inserted at the beginning and end of <br>
//! the initial sequence: <br>
//! - the c values of knots preceding the first item <br>
//!   Knot(k+1) in the initial sequence are inserted <br>
//!   at the beginning; the period is subtracted from these c values; <br>
//! - the c values of knots following the last item <br>
//!   Knot(1) in the initial sequence are inserted at <br>
//!   the end; the period is added to these c values. <br>
//! The length of the sequence must therefore be equal to: <br>
//! NbPoles + 2*Degree - Mult(1) + 2. <br>
//! Example <br>
//! For a non-periodic BSpline curve of degree 2 where: <br>
//! - the array of knots is: { k1 k2 k3 k4 }, <br>
//! - with associated multiplicities: { 3 1 2 3 }, <br>
//! the knot sequence is: <br>
//! K = { k1 k1 k1 k2 k3 k3 k4 k4 k4 } <br>
//! For a periodic BSpline curve of degree 4 , which is <br>
//! "C1" continuous at the first knot, and where : <br>
//! - the periodic knots are: { k1 k2 k3 (k4) } <br>
//!   (3 periodic knots: the points of parameter k1 and k4 <br>
//!   are identical, the period is p = k4 - k1), <br>
//! - with associated multiplicities: { 3 1 2 (3) }, <br>
//! the degree of continuity at knots k1 and k4 is: <br>
//! Degree + 1 - Mult(i) = 2. <br>
//! 2 supplementary knots are added at the beginning <br>
//! and end of the sequence: <br>
//! - at the beginning: the 2 knots preceding k4 minus <br>
//!   the period; in this example, this is k3 - p both times; <br>
//! - at the end: the 2 knots following k1 plus the period; <br>
//!   in this example, this is k2 + p and k3 + p. <br>
//! The knot sequence is therefore: <br>
//! K = { k3-p k3-p k1 k1 k1 k2 k3 k3 <br>
//! k4 k4 k4 k2+p k3+p } <br>
//! Exceptions <br>
//! Standard_DimensionError if the array K is not of <br>
//! the appropriate length.Returns the knots sequence. <br>
Standard_EXPORT   void KnotSequence(TColStd_Array1OfReal& K) const;


//!  Returns NonUniform or Uniform or QuasiUniform or PiecewiseBezier. <br>
//!  If all the knots differ by a positive constant from the <br>
//!  preceding knot the BSpline Curve can be : <br>
//!  - Uniform if all the knots are of multiplicity 1, <br>
//!  - QuasiUniform if all the knots are of multiplicity 1 except for <br>
//!    the first and last knot which are of multiplicity Degree + 1, <br>
//!  - PiecewiseBezier if the first and last knots have multiplicity <br>
//!    Degree + 1 and if interior knots have multiplicity Degree <br>
//!    A piecewise Bezier with only two knots is a BezierCurve. <br>
//!  else the curve is non uniform. <br>
//!  The tolerance criterion is Epsilon from class Real. <br>
Standard_EXPORT   GeomAbs_BSplKnotDistribution KnotDistribution() const;


//!  For a BSpline curve the last parameter (which gives the <br>
//!  end point of the curve) is a knot value but if the <br>
//!  multiplicity of the last knot index is lower than <br>
//!  Degree + 1 it is not the last knot of the curve. This <br>
//!  method computes the index of the knot corresponding to <br>
//!  the last parameter. <br>
Standard_EXPORT   Standard_Integer LastUKnotIndex() const;


//!  Computes the parametric value of the end point of the curve. <br>
//!  It is a knot value. <br>
Standard_EXPORT   Standard_Real LastParameter() const;


//!  Locates the parametric value U in the sequence of knots. <br>
//!  If "WithKnotRepetition" is True we consider the knot's <br>
//!  representation with repetition of multiple knot value, <br>
//!  otherwise  we consider the knot's representation with <br>
//!  no repetition of multiple knot values. <br>
//!  Knots (I1) <= U <= Knots (I2) <br>
//!  . if I1 = I2  U is a knot value (the tolerance criterion <br>
//!    ParametricTolerance is used). <br>
//!  . if I1 < 1  => U < Knots (1) - Abs(ParametricTolerance) <br>
//!  . if I2 > NbKnots => U > Knots (NbKnots) + Abs(ParametricTolerance) <br>
Standard_EXPORT   void LocateU(const Standard_Real U,const Standard_Real ParametricTolerance,Standard_Integer& I1,Standard_Integer& I2,const Standard_Boolean WithKnotRepetition = Standard_False) const;


//!  Returns the multiplicity of the knots of range Index. <br>//! Raised if Index < 1 or Index > NbKnots <br>
Standard_EXPORT   Standard_Integer Multiplicity(const Standard_Integer Index) const;


//!  Returns the multiplicity of the knots of the curve. <br>
//!  Raised if the length of M is not equal to NbKnots. <br>
Standard_EXPORT   void Multiplicities(TColStd_Array1OfInteger& M) const;


//!  Returns the number of knots. This method returns the number of <br>
//!  knot without repetition of multiple knots. <br>
Standard_EXPORT   Standard_Integer NbKnots() const;

//! Returns the number of poles <br>
Standard_EXPORT   Standard_Integer NbPoles() const;

//! Returns the pole of range Index. <br>//! Raised if Index < 1 or Index > NbPoles. <br>
Standard_EXPORT   gp_Pnt Pole(const Standard_Integer Index) const;

//! Returns the poles of the B-spline curve; <br>
//!  Raised if the length of P is not equal to the number of poles. <br>
Standard_EXPORT   void Poles(TColgp_Array1OfPnt& P) const;


//!  Returns the start point of the curve. <br>
//! Warnings : <br>
//!  This point is different from the first pole of the curve if the <br>
//!  multiplicity of the first knot is lower than Degree. <br>
Standard_EXPORT   gp_Pnt StartPoint() const;

//! Returns the weight of the pole of range Index . <br>//! Raised if Index < 1 or Index > NbPoles. <br>
Standard_EXPORT   Standard_Real Weight(const Standard_Integer Index) const;

//! Returns the weights of the B-spline curve; <br>
//!  Raised if the length of W is not equal to NbPoles. <br>
Standard_EXPORT   void Weights(TColStd_Array1OfReal& W) const;

//! Applies the transformation T to this BSpline curve. <br>
Standard_EXPORT   void Transform(const gp_Trsf& T) ;


//!  Returns the value of the maximum degree of the normalized <br>
//!  B-spline basis functions in this package. <br>
Standard_EXPORT static  Standard_Integer MaxDegree() ;

//!  Computes for this BSpline curve the parametric <br>
//! tolerance UTolerance for a given 3D tolerance Tolerance3D. <br>
//! If f(t) is the equation of this BSpline curve, <br>
//! UTolerance ensures that: <br>
//!           | t1 - t0| < Utolerance ===> <br>
//!           |f(t1) - f(t0)| < Tolerance3D <br>
Standard_EXPORT   void Resolution(const Standard_Real Tolerance3D,Standard_Real& UTolerance) ;

//! Creates a new object which is a copy of this BSpline curve. <br>
Standard_EXPORT   Handle_Geom_Geometry Copy() const;
//Standard_EXPORT ~Geom_BSplineCurve();




 // Type management
 //
 Standard_EXPORT const Handle(Standard_Type)& DynamicType() const;
 //Standard_EXPORT Standard_Boolean	       IsKind(const Handle(Standard_Type)&) const;

protected:

 // Methods PROTECTED
 // 


 // Fields PROTECTED
 //


private: 

 // Methods PRIVATE
 // 


//!           Tells whether the Cache is valid for the <br>
//!           given parameter <br>
//! Warnings : the parameter must be normalized within <br>
//! the period if the curve is periodic. Otherwise <br>
//! the answer will be false <br>
//! <br>
Standard_EXPORT   Standard_Boolean IsCacheValid(const Standard_Real Parameter) const;

//! Invalidates the cache. This has to be private <br>
//! this has to be private <br>
Standard_EXPORT   void InvalidateCache() ;

//! Recompute  the  flatknots,  the knotsdistribution, the continuity. <br>
Standard_EXPORT   void UpdateKnots() ;

//! updates the cache and validates it <br>
Standard_EXPORT   void ValidateCache(const Standard_Real Parameter) ;


 // Fields PRIVATE
 //
Standard_Boolean rational;
Standard_Boolean periodic;
GeomAbs_BSplKnotDistribution knotSet;
GeomAbs_Shape smooth;
Standard_Integer deg;
Handle_TColgp_HArray1OfPnt poles;
Handle_TColStd_HArray1OfReal weights;
Handle_TColStd_HArray1OfReal flatknots;
Handle_TColStd_HArray1OfReal knots;
Handle_TColStd_HArray1OfInteger mults;
Handle_TColgp_HArray1OfPnt cachepoles;
Handle_TColStd_HArray1OfReal cacheweights;
Standard_Integer validcache;
Standard_Real parametercache;
Standard_Real spanlenghtcache;
Standard_Integer spanindexcache;
Standard_Real maxderivinv;
Standard_Boolean maxderivinvok;


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif
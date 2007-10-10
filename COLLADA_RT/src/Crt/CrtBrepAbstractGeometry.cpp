#include "Crt/CrtBrepBuilder.h"
#include "Crt/CrtUtils.h"

gp_Pnt AbsCurve_OCC_Parser::o(0.0, 0.0, 0.0 );
gp_Dir AbsCurve_OCC_Parser::x(1.0, 0.0, 0.0 );
gp_Dir AbsCurve_OCC_Parser::n(0.0, 0.0, 1.0 ); // z-up

// define variable for knotOCC
vector <int> knotOCC::m;
vector <double> knotOCC::kv;
TColStd_Array1OfReal* knotOCC::knots = NULL;
TColStd_Array1OfInteger* knotOCC::mults = NULL;
bool knotOCC::IsPeriodic = false;
size_t knotOCC::lastMult = 0;
size_t knotOCC::size = 0;
size_t knotOCC::size_cv = 0;

// init the number of size of knots and control vertices
void knotOCC::PreProcess(size_t size_, size_t size_cv_) 
{
	size = size_;size_cv = size_cv_;return;
}

void knotOCC::GetValueAt(domFloat k, size_t i)
{
	if (i > 0)
	{
		if ( (k - kv.at(kv.size() - 1) ) < Precision::Confusion() )
		{
			lastMult++;
		}
		else
		{
			m.push_back(lastMult);
			lastMult = 1;
			kv.push_back( kv.at(kv.size() - 1) );
		}
	}
	else
		kv.push_back( k );

	return;
}

void knotOCC::PostProcess()
{
	// ToDo: add last element

	// 
/*	if ( IsPeriodic )
	{
		int test =  size  - m[ 0 ];
		int cRemove = ( test - poles->Length() ) / 4;
		int s = m.size();
		m.erase( m.end() - cRemove, m.end() );
		s = m.size();
		m.erase( m.begin(), m.begin() + cRemove );
		s = m.size();
		kv.erase( kv.end() - cRemove, kv.end() );
		kv.erase( kv.begin(), kv.begin() + cRemove );
	}

	if ( m.size() == k.size() )
	{
		mults = new TColStd_Array1OfInteger( 1, m.size() );
		knots = new TColStd_Array1OfReal( 1, k.size() );

		for ( int j = 0; j < k.size(); j++ )
		{
			mults->SetValue( ( j + 1 ), m[ j ] );
			knots->SetValue( ( j + 1 ), k[ j ] );
		}
	}
	*/
}

// PRE: ele should be a curve element: why can't we use const here???
bool AbsCurve_OCC_Parser::ReadCurve(daeElement *ele, Handle_Geom_Curve &curve)
{
	// get curve child element of current curve
	daeElementRefArray elements;
	ele->getChildren(elements);

	// when curve is NULL: corresponding degenerated edge.
	if (elements.getCount() == 0)
	{
		curve = NULL;
		return true;
	}

	for (size_t i = 0;i < elements.getCount();i++)
	{
		daeElement * e = elements.get(i);

		// find name of this curve
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		// find correct parser for it
		if (CrtCmp(name, COLLADA_ELEMENT_CIRCLE)) // it is circle
		{
			// load the circle 
			ReadCircle(e, curve);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_LINE)) // it is a line
		{
			// load the line
			ReadLine(e, curve);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_ELLIPSE)) // ellipse
		{
			// load ellipse
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_PARABOLA)) // parabola
		{
			// load parabola
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_HYPERBOLA)) // HYPERBOLA
		{
			// load hyperbola
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_SPLINE)) // BSPLINE curve
		{
			// load bspline
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_ROTATE))
		{
			domFloat4 axis_angle = ((domRotate * )e)->getValue();

			// build OCC rotation:
			// Do we need the unit dir????
			gp_Dir dir(axis_angle.get(0), axis_angle.get(1), axis_angle.get(2));
			gp_Ax1 ax(AbsCurve_OCC_Parser::o, dir);
			gp_Trsf rot;
			// from angle to radian unit
			rot.SetRotation(ax, axis_angle.get(3) * PI / 180.0);
			// Why invert????
			rot.Invert();

			// If there is not a null curve, then apply the transformation
			if ( !curve.IsNull() )
			{
				curve->Transform( rot );
			}
			else
				return false;

		}
		else if (CrtCmp(name, COLLADA_ELEMENT_TRANSLATE))
		{
			domFloat3 trans_xyz = ((domTranslate * ) e)->getValue();

			// build OCC translation
			gp_Vec vec( trans_xyz.get( 0 ), trans_xyz.get( 1 ), trans_xyz.get( 2 ) );
			gp_Trsf trans;
			trans.SetTranslation( vec );

			if ( !curve.IsNull() )
			{
				curve->Transform( trans );
			}
			else
				return false;
		}
		else
		{
			// extra element here: not defined in schema
			return false;
		}
	}
	return true;
}

// Loading circles
// PRE: e is type of circle

bool AbsCurve_OCC_Parser::ReadCircle(const daeElement *ele, Handle_Geom_Curve &curve)
{
	// daeElement must be circle type
	domCircle *circle = NULL;
	circle = daeSafeCast <domCircle>((daeElement*)ele);
	if (circle == NULL)
	{
		CrtPrint("Error: circle is not from correct type conversion.\n");
		return false;
	}
	daeElementRefArray elements;
	circle->getChildren(elements);

	double r = -1.0;

	// scan the circle children
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		// check the radius
		if (CrtCmp(name, COLLADA_ELEMENT_RADIUS)) // this is radius?
		{
			// init the radius
			r = ((domCircle::domRadius *)e)->getValue();

			// Judge whether it is in the correct domain
			if (r <=0.0)
				return false;
			else
			{
				// generate the curve for OCC
				gp_Ax2 ax(AbsCurve_OCC_Parser::o, AbsCurve_OCC_Parser::n, AbsCurve_OCC_Parser::x);
				curve = new Geom_Circle(ax, r);
				return true;
			}
		}
	}

	// did not find any radius information
	return false;
}

// Loading line
// PRE: e is type of Line
bool AbsCurve_OCC_Parser::ReadLine(const daeElement *ele, Handle_Geom_Curve &curve)
{
	// init the Line element
	domLine *line = NULL;
	line = daeSafeCast <domLine> ( (daeElement *)ele );
	if (line == NULL)
		return false;

	domFloat3 originDom;
	domFloat3 dirDom;

	// get two elements of line:
	daeElementRefArray elements;
	line->getChildren(elements);
	
	// scan children of line
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		if (CrtCmp(name, COLLADA_ELEMENT_ORIGIN))
		{
			originDom = ((domLine::domOrigin *)e)->getValue();
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_DIRECTION))
		{
			dirDom = ((domLine::domDirection *)e)->getValue();
		}
	}

	// build the OCC data format:
	gp_Pnt origin;
    gp_Dir direction;

	origin.SetCoord(originDom.get(0), originDom.get(1), originDom.get(2));
	direction.SetCoord(dirDom.get(0), dirDom.get(1), dirDom.get(2));

	curve = new Geom_Line (origin, direction);

	return true;
}

// Loading Ellipse
// PRE: e is type of Ellipse
bool AbsCurve_OCC_Parser::ReadEllipse(const daeElement *ele, Handle_Geom_Curve &curve)
{
	// init Ellipse
	domEllipse * ellipse = NULL;
	ellipse = daeSafeCast <domEllipse> ( (daeElement *)ele );
	domFloat2 r2;
	domFloat r_maj, r_min;

	// init two data
	// get two elements of ellipse:
	daeElementRefArray elements;
	ellipse->getChildren(elements);
	
	// scan children of line
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		if (CrtCmp(name, COLLADA_ELEMENT_RADIUS))
		{
			r2 = ( (domEllipse::domRadius *)e )->getValue(); 
		}
	}

	r2.get2at(0, r_maj, r_min);

	// build the OCC data format:
	if (r_maj < 0 || r_min < 0) // not fit domain of radius
		return false;
	else
	{
		// generate the ellipse for OCC
		gp_Ax2 ax(AbsCurve_OCC_Parser::o, AbsCurve_OCC_Parser::n, AbsCurve_OCC_Parser::x);
		curve = new Geom_Ellipse(ax, r_maj, r_min);
		return true;
	}
}

bool AbsCurve_OCC_Parser::ReadHyperbola(const daeElement *ele, Handle_Geom_Curve &curve)
{
	// init Hyperbolic:
	domHyperbola *hyperbola = NULL;
	hyperbola = daeSafeCast <domHyperbola> ( (daeElement *)ele );
	if (hyperbola == NULL)
		return false;

	// init two data
	domFloat2 r2;
	domFloat r_maj, r_min;

	// get two elements of Hyperbola:
	daeElementRefArray elements;
	hyperbola->getChildren(elements);

	// get children
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		if (CrtCmp(name, COLLADA_ELEMENT_RADIUS))
		{
			r2 = ( (domHyperbola::domRadius *)e )->getValue(); 
		}
	}

	r2.get2at(0, r_maj, r_min);

	// build the OCC data format:
	if (r_maj < 0 || r_min < 0) // not fit domain of radius
		return false;
	else
	{
		// generate the ellipse for OCC
		gp_Ax2 ax(AbsCurve_OCC_Parser::o, AbsCurve_OCC_Parser::n, AbsCurve_OCC_Parser::x);
		curve = new Geom_Hyperbola( ax, r_maj, r_min );
		return true;
	}
}

// T: template and P: policy
template <class T, class P> void processInput(daeTArray< T > & arrayInput, domSource *source)
{
	domSource::domTechnique_common* tech = source->getTechnique_common();
    domAccessor *acc = tech->getAccessor();
    size_t size = arrayInput.getCount() / acc->getStride();

	P::PreProcess();

	for (size_t i = 0; i < size;i++)
	{
		P::GetValueAt(arrayInput.get(i));
	}

	P::PostProcess();
}

bool AbsCurve_OCC_Parser::ReadBSplineCurve(const daeElement *ele, Handle( Geom_Curve ) &curve)
{
	domSpline *splinecurve = daeSafeCast <domSpline> ( (daeElement *) ele);
	if (splinecurve == NULL)
		return false;

	domSpline::domControl_verticesRef cv = splinecurve->getControl_vertices();
	domInputLocal_Array &inputs = cv->getInput_array();

	// These input arrays contains information such as interpolation...
	for (size_t i = 0;i < inputs.getCount();i++)
	{
		domInputLocal * input = inputs.get(i);
		// get source
		domSource * source = daeSafeCast <domSource> (input->getSource().getElement() );
	}
}

bool AbsSurface_OCC_Parser::ReadSurface(daeElement *ele, Handle_Geom_Surface &surface)
{
	// surface type
	// get curve child element of current surface
	daeElementRefArray elements;
	ele->getChildren(elements);

	// when surface is NULL: return error
	if (elements.getCount() == 0)
	{
		return false;
	}

	for (size_t i = 0;i < elements.getCount();i++)
	{
		daeElement * e = elements.get(i);

		// find name of this surface
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		// find correct parser for it
		if (CrtCmp(name, COLLADA_ELEMENT_CYLINDER))
		{
			ReadCylinder( e, surface);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_PLANE))
		{
			ReadPlane( e, surface);
		}
		else
			return false;
	}
	return true;
}

bool AbsSurface_OCC_Parser::ReadPlane(daeElement *ele, Handle_Geom_Surface &surface)
{
	domPlane * e = NULL;
	e = daeSafeCast <domPlane> (( (daeElement *) ele));
	if (e == NULL)
		return false;

	domPlane::domEquation * equation = e->getEquation();

	domFloat4 &v = equation->getValue();
    double a, b, c, d;
    v.get4at( 0, a, b, c, d );

    surface = new Geom_Plane( a, b, c, d );

	return true;
}

bool AbsSurface_OCC_Parser::ReadCylinder(daeElement *ele, Handle_Geom_Surface &surface)
{
	domCylinder * e = NULL;
	e = daeSafeCast <domCylinder> (( (daeElement *) ele));
	if (e == NULL)
		return false;

	gp_Pnt o( 0.0, 0.0, 0.0 );
	gp_Dir x( 1.0, 0.0, 0.0 );
	gp_Dir n( 0.0, 0.0, 1.0 );
	gp_Ax3 ax( o, n, x );

	double radius, tmp;

	domCylinder::domRadius * radiuses = e->getRadius();
	domFloat2 &v = radiuses->getValue();
	v.get2at(0, radius, tmp);

	surface = new Geom_CylindricalSurface( ax, radius );

	return true;
}
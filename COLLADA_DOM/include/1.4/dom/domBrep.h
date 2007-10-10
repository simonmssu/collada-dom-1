/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */
#ifndef __domBrep_h__
#define __domBrep_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domCurves.h>
#include <dom/domSurfaces.h>
#include <dom/domSource.h>
#include <dom/domVertices.h>
#include <dom/domEdges.h>
#include <dom/domWires.h>
#include <dom/domFaces.h>
#include <dom/domShells.h>
#include <dom/domSolids.h>
#include <dom/domExtra.h>

/**
 * The brep element contains the complete topological     description of a
 * static structure. There are also the     corresponding geometrical descriptions
 * of the vertices,     edges and faces.
 */
class domBrep : public daeElement
{
public:
	COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::BREP; }
protected:  // Attributes
/**
 *        The id of a brep structure.      
 */
	xsID attrId;
/**
 *        The optional name of the brep structure.      
 */
	xsNCName attrName;

protected:  // Elements
/**
 *  The curves element holds all the curves that are needed for the brep structure.
 * Here are the curves that describes the kind of an edge, but here are also
 * the curves that are needed to create a extrusion for a surface. This element
 * is needed, if the edges element is present.  @see domCurves
 */
	domCurvesRef elemCurves;
/**
 *  The surfaces element holds all the surfaces that are needed for the brep
 * structure. Here are the surfaces that describes the kind of a face. This
 * element is needed, if the faces element is present.  @see domSurfaces
 */
	domSurfacesRef elemSurfaces;
/**
 *  The source elements define the access of the elements vertices, edges
 * and faces to their geometric entities. At least one source element is needed
 * for the vertices. If there are edges a second source element is needed
 * for accessing the curves in the curve element by an IDREF_array. If there
 * are faces the third source element is needed for accessing the surfaces
 * in the surface element by an IDREF_array.  @see domSource
 */
	domSource_Array elemSource_array;
/**
 *  This element defines all the vertices of an brep structure. Vertices are
 * the base topological entity for all brep structures, so this element is
 * ever needed.  @see domVertices
 */
	domVerticesRef elemVertices;
/**
 *  This element defines all the edges of the brep structure.  @see domEdges
 */
	domEdgesRef elemEdges;
/**
 *  This element defines all the wires of the brep structure.  @see domWires
 */
	domWiresRef elemWires;
/**
 *  This element defines all the faces of the brep structure.  @see domFaces
 */
	domFacesRef elemFaces;
/**
 *  This element defines all the shells of the brep structure.  @see domShells
 */
	domShellsRef elemShells;
/**
 *  This element defines all the solids of the brep structure.  @see domSolids
 */
	domSolidsRef elemSolids;
	domExtraRef elemExtra;

public:	//Accessors and Mutators
	/**
	 * Gets the id attribute.
	 * @return Returns a xsID of the id attribute.
	 */
	xsID getId() const { return attrId; }
	/**
	 * Sets the id attribute.
	 * @param atId The new value for the id attribute.
	 */
	void setId( xsID atId ) { *(daeStringRef*)&attrId = atId; _validAttributeArray[0] = true; 
		if( _document != NULL ) _document->changeElementID( this, attrId );
	}

	/**
	 * Gets the name attribute.
	 * @return Returns a xsNCName of the name attribute.
	 */
	xsNCName getName() const { return attrName; }
	/**
	 * Sets the name attribute.
	 * @param atName The new value for the name attribute.
	 */
	void setName( xsNCName atName ) { *(daeStringRef*)&attrName = atName; _validAttributeArray[1] = true; }

	/**
	 * Gets the curves element.
	 * @return a daeSmartRef to the curves element.
	 */
	const domCurvesRef getCurves() const { return elemCurves; }
	/**
	 * Gets the surfaces element.
	 * @return a daeSmartRef to the surfaces element.
	 */
	const domSurfacesRef getSurfaces() const { return elemSurfaces; }
	/**
	 * Gets the source element array.
	 * @return Returns a reference to the array of source elements.
	 */
	domSource_Array &getSource_array() { return elemSource_array; }
	/**
	 * Gets the source element array.
	 * @return Returns a constant reference to the array of source elements.
	 */
	const domSource_Array &getSource_array() const { return elemSource_array; }
	/**
	 * Gets the vertices element.
	 * @return a daeSmartRef to the vertices element.
	 */
	const domVerticesRef getVertices() const { return elemVertices; }
	/**
	 * Gets the edges element.
	 * @return a daeSmartRef to the edges element.
	 */
	const domEdgesRef getEdges() const { return elemEdges; }
	/**
	 * Gets the wires element.
	 * @return a daeSmartRef to the wires element.
	 */
	const domWiresRef getWires() const { return elemWires; }
	/**
	 * Gets the faces element.
	 * @return a daeSmartRef to the faces element.
	 */
	const domFacesRef getFaces() const { return elemFaces; }
	/**
	 * Gets the shells element.
	 * @return a daeSmartRef to the shells element.
	 */
	const domShellsRef getShells() const { return elemShells; }
	/**
	 * Gets the solids element.
	 * @return a daeSmartRef to the solids element.
	 */
	const domSolidsRef getSolids() const { return elemSolids; }
	/**
	 * Gets the extra element.
	 * @return a daeSmartRef to the extra element.
	 */
	const domExtraRef getExtra() const { return elemExtra; }
protected:
	/**
	 * Constructor
	 */
	domBrep() : attrId(), attrName(), elemCurves(), elemSurfaces(), elemSource_array(), elemVertices(), elemEdges(), elemWires(), elemFaces(), elemShells(), elemSolids(), elemExtra() {}
	/**
	 * Destructor
	 */
	virtual ~domBrep() {}
	/**
	 * Copy Constructor
	 */
	domBrep( const domBrep &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domBrep &operator=( const domBrep &cpy ) { (void)cpy; return *this; }

public: // STATIC METHODS
	/**
	 * Creates an instance of this class and returns a daeElementRef referencing it.
	 * @param bytes The size allocated for this instance.
	 * @return a daeElementRef referencing an instance of this object.
	 */
	static DLLSPEC daeElementRef create(daeInt bytes);
	/**
	 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
	 * If a daeMetaElement already exists it will return that instead of creating a new one. 
	 * @return A daeMetaElement describing this COLLADA element.
	 */
	static DLLSPEC daeMetaElement* registerElement();

public: // STATIC MEMBERS
	/**
	 * The daeMetaElement that describes this element in the meta object reflection framework.
	 */
	static DLLSPEC daeMetaElement* _Meta;
};


#endif

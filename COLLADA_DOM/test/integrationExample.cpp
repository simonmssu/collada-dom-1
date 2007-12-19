// The DOM used to provide an "integration library", which was a mechanism for
// converting the DOM's representation of a Collada model to the user's representation.
// The integration classes were very clumsy and not particularly useful, so they
// were removed in December 08. This file shows how you might write a Collada
// importer without using the integration library.

#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include "domTest.h"

using namespace std;
class ConversionData;

#define Check(val) if (!(val)) throw exception();


// Our material structure, which we create by converting a domMaterial object
class Material {
public:
	vector<float> diffuseColor;
	string diffuseTexture;
	// ... and lots of other parameters
	
	Material(domMaterial& mtl, ConversionData& convData) {
		// Grab the <effect> from the <material> and initalize the parameters
	}
};


// Our mesh structure, which we create by converting a domGeometry object
class Mesh {
public:
	Material* mtl;
	// Vertex info, etc

	Mesh(domGeometry& geom, ConversionData& convData) {
		// Parse the <geometry> element, extract vertex data, etc
	}
};


// Our node structure, which we create by converting a domNode object
class Node {
public:
	list<Mesh*> meshes;
	list<Node*> childNodes;

	// This is defined later to work around a circular dependency on ConversionData
	Node(domNode& node, ConversionData& convData);
};


// Basically all the integration library ever provided was an easy way to associate
// a user's myWhatever object with a domWhatever object. But it's just as easy to provide
// that functionality ourselves as it was to use the integration templates. This class
// is an example of how you might use the std::map class to provide a mapping from
// domWhatever objects to myWhatever objects.
template<typename MyType, typename DomType>
class LookupTable {
private:
	ConversionData& convData;
	map<DomType*, MyType*> table;

public:
	LookupTable(ConversionData& convData) : convData(convData) { }
	
	~LookupTable() {
		typename map<DomType*, MyType*>::iterator iter;
		for (iter = table.begin(); iter != table.end(); iter++)
			delete iter->second;
	}
	
	MyType& lookup(DomType* domObject) {
		typename map<DomType*, MyType*>::iterator iter = table.find(domObject);
		if (iter == table.end()) {
			iter = table.insert(pair<DomType*, MyType*>(
				domObject, new MyType(*domObject, convData))).first;
		}
		return *iter->second;
	}

	size_t getCount() {
		return table.size();
	}
};


// This class stores the various LookupTables for the different types of objects
// we have.
class ConversionData {
public:
	ConversionData() : mtlTable(*this), meshTable(*this), nodeTable(*this) { }
	
	LookupTable<Material, domMaterial> mtlTable;
	LookupTable<Mesh, domGeometry> meshTable;
	LookupTable<Node, domNode> nodeTable;
};


Node::Node(domNode& node, ConversionData& convData) {
	// Recursively convert all child nodes. First iterate over the <node> elements.
	for (size_t i = 0; i < node.getNode_array().getCount(); i++)
		childNodes.push_back(&convData.nodeTable.lookup(node.getNode_array()[i]));

	// Then iterate over the <instance_node> elements.
	for (size_t i = 0; i < node.getInstance_node_array().getCount(); i++) {
		domNode* child = daeSafeCast<domNode>(
			node.getInstance_node_array()[i]->getUrl().getElement());
			Check(child);
			childNodes.push_back(&convData.nodeTable.lookup(child));
	}

	// Iterate over all the <instance_geometry> elements
	for (size_t i = 0; i < node.getInstance_geometry_array().getCount(); i++) {
		domInstance_geometry* instanceGeom = node.getInstance_geometry_array()[i];
		domGeometry* geom = daeSafeCast<domGeometry>(instanceGeom->getUrl().getElement());
		Check(geom);

		// Lookup the material that we should apply to the <geometry>. In a real app
		// we'd need to worry about having multiple <instance_material>s, but in this
		// test let's just convert the first <instance_material> we find.
		domInstance_material* instanceMtl = daeSafeCast<domInstance_material>(
			instanceGeom->getDescendant("instance_material"));
		Check(instanceMtl);
		domMaterial* mtl = daeSafeCast<domMaterial>(instanceMtl->getTarget().getElement());
		Check(mtl);
		Material& convertedMtl = convData.mtlTable.lookup(mtl);

		// Now convert the geometry, add the result to our list of meshes, and assign
		// the mesh a material.
		meshes.push_back(&convData.meshTable.lookup(geom));
		meshes.back()->mtl = &convertedMtl;
	}
}


void convertModel(domCOLLADA& root, ConversionData& convData) {
	// We need to convert the model from the DOM's representation to our internal representation.
	// First find a <visual_scene> to load. In a real app we would look for and load all
	// the <visual_scene>s in a document, but for this app we just convert the first
	// <visual_scene> we find.
	daeElement* visualScene = root.getDescendant("visual_scene");
	Check(visualScene);

	// Now covert all the <node>s in the <visual_scene>. This is a recursive process,
	// so any child nodes will also be converted.
	daeElementRefArray children = visualScene->getChildren();
	for (size_t i = 0; i < children.getCount(); i++)
		if (string(children[i]->getElementName()) == "node")
			convData.nodeTable.lookup(daeSafeCast<domNode>(children[i]));
}
	

DefineTest(integration) {
	// Load a document from disk
	string file = lookupTestFile("cube.dae");
	DAE dae;
	CheckResult(dae.loadFile(file.c_str()) == DAE_OK);

	// Do the conversion. The conversion process throws an exception on error, so
	// we'll include a try/catch handler.
	try {
		ConversionData convData;
		convertModel(*dae.getDomFile(file.c_str()), convData);

		// Make sure our object counts match up.
		CheckResult(dae.getDatabase()->getElementCount(NULL, "node") == convData.nodeTable.getCount());
		CheckResult(dae.getDatabase()->getElementCount(NULL, "geometry") == convData.meshTable.getCount());
		CheckResult(dae.getDatabase()->getElementCount(NULL, "material") == convData.mtlTable.getCount());
	}
	catch (const exception& e) {
		return testResult(false);
	}

	return testResult(true);
}

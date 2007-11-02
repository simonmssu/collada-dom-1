#include <cstdarg>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <memory>
#include <map>
#include <vector>
#include <set>
#include <dae.h>
#include <dom/domConstants.h>
#include <dom/domCOLLADA.h>
#include <dom/domProfile_COMMON.h>
#include <dae/daeSIDResolver.h>
#include <dom/domInstance_controller.h>
#include <dae/domAny.h>
#include <dae/daeErrorHandler.h>
#include <dom/domFx_surface_init_from_common.h>
#include <../include/modules/stdErrPlugin.h>

// We use the boost filesystem library for cross-platform file system support. You'll need
// to have boost on your machine for this to work. For the Windows build boost is provided
// in the external-libs folder, but for Linux/Mac it's expected that you'll install a boost
// obtained via your distro's package manager. For example on Debian/Ubuntu, you can run
//   apt-get install libboost-filesystem-dev
// to install the boost filesystem library on your machine.
#include <boost/filesystem/convenience.hpp>
namespace fs = boost::filesystem;

using namespace std;

float toFloat(const string& s) {
	istringstream stream(s);
	float f;
	stream >> f;
	return f;
}

template<typename T>
string toString(const T& val) {
	ostringstream stream;
	stream << val;
	return stream.str();
}


#define CheckResult(val) \
	if (!(val)) { \
		return testResult(false, __LINE__); \
	}

#define CheckResultWithMsg(val, msg) \
	if (!(val)) { \
		return testResult(false, __LINE__, msg); \
	}

#define CompareDocs(dae, uri1, uri2) \
	{ \
		domCOLLADA *root1 = (dae).getDom((uri1).c_str()), \
		           *root2 = (dae).getDom((uri2).c_str()); \
		elementCompareResult result = compareElements(*root1, *root2); \
		if (result.compareValue != 0) { \
			return testResult(false, __LINE__, result.format()); \
		} \
	}

struct domTest;
map<string, domTest*> g_tests;

struct testResult {
	bool passed;
	int line; // If the test failed, the line number it failed on, or -1 if the line
	          // number isn't available.
	string msg; // An error message for the user. Usually empty.

	testResult() : passed(true), line(-1) { }
	testResult(bool passed, int line = -1, const string& msg = "")
	  : passed(passed),
	    line(line),
	    msg(msg) {
	}
};

struct domTest {
	string name;
	domTest(const string& name) : name(name) {
		g_tests[name] = this;
	}
	virtual ~domTest() { };
	virtual testResult run() = 0;
};

#define DefineTest(testName) \
	struct domTest_##testName : public domTest { \
		domTest_##testName() : domTest(#testName) { } \
		testResult run();	\
	}; \
	domTest_##testName domTest_##testName##Obj; \
	testResult domTest_##testName::run()

#define RunTest(testName) \
	{ \
		map<string, domTest*>::iterator iter = g_tests.find(#testName); \
		CheckResult(iter != g_tests.end()); \
		CheckResult(iter->second->run()); \
	}


fs::path g_dataPath;
string lookupTestFile(const string& fileName) {
	return (g_dataPath / fileName).string();
}

fs::path g_tmpPath;
string getTmpFile(const string& fileName) {
	return (g_tmpPath / fileName).string();
}


string chopWS(const string& s) {
	string ws = " \t\n\r";
	size_t beginPos = s.find_first_not_of(ws);
	size_t endPos = s.find_last_not_of(ws);
	if (beginPos == string::npos)
		return "";
	return s.substr(beginPos, endPos-beginPos+1);
}

DefineTest(chopWS) {
	CheckResult(chopWS("") == "");
	CheckResult(chopWS("") == "");
	CheckResult(chopWS(" ") == "");
	CheckResult(chopWS(" test") == "test");
	CheckResult(chopWS("test ") == "test");
	CheckResult(chopWS(" test ") == "test");
	CheckResult(chopWS(" a ") == "a");
	return testResult(true);
}


string replace(const string& s, const string& replace, const string& replaceWith) {
	if (replace.empty())
		return s;
	
	string result;
	size_t pos1 = 0, pos2 = s.find(replace);
	while (pos2 != string::npos) {
		result += s.substr(pos1, pos2-pos1);
		result += replaceWith;
		pos1 = pos2 + replace.length();
		pos2 = s.find(replace, pos1);
	}

	result += s.substr(pos1, s.length()-pos1);
	return result;
}

DefineTest(stringReplace) {
	CheckResult(replace("abc", "abc", "def") == "def");
	CheckResult(replace("abc", "a", "1") == "1bc");
	CheckResult(replace("abc", "c", "1") == "ab1");
	CheckResult(replace("abc123", "bc12", "b") == "ab3");
	CheckResult(replace("abracadabra", "a", "") == "brcdbr");
	return testResult(true);
}


// Split the string into substrings according to the specified character
vector<string> split(const string& s, const char c) {
	vector<string> result;
	size_t currentIndex = 0, nextTokenIndex = 0;
	while (currentIndex < s.length() &&
	       (nextTokenIndex = s.find_first_of(c, currentIndex)) != string::npos) {
		if ((nextTokenIndex - currentIndex) > 0)
			result.push_back(s.substr(currentIndex, nextTokenIndex-currentIndex));
		currentIndex = nextTokenIndex+1;
	}

	if (currentIndex < s.length())
		result.push_back(s.substr(currentIndex, s.length()-currentIndex));

	return result;
}

vector<string> makeStringArray(const char* s, ...) {
	va_list args;
	va_start(args, s);
	vector<string> result;
	while (s) {
		result.push_back(s);
		s = va_arg(args, const char*);
	}
	va_end(args);
	return result;
}

daeTArray<int> makeIntArray(int i, ...) {
	va_list args;
	va_start(args, i);
	daeTArray<int> result;
	while (i != INT_MAX) {
		result.append(i);
		i = va_arg(args, int);
	}
	va_end(args);
	return result;
}

void printStringArray(const vector<string>& array) {
	for (size_t i = 0; i < array.size(); i++)
		cout << array[i] << endl;
}

DefineTest(stringSplit) {
	CheckResult(split("1|2|3|4", '|')   == makeStringArray("1", "2", "3", "4", 0));
	CheckResult(split("|1|", '|')       == makeStringArray("1", 0));
	CheckResult(split("1|||2||3|", '|') == makeStringArray("1", "2", "3", 0));
	return testResult(true);
}


daeElement* findDescendant(daeElement* root, const string& name) {
	if (!root)
		return NULL;
	if (root->getElementName() == name)
		return root;

	daeElementRefArray children = root->getChildren();
	for (size_t i = 0; i < children.getCount(); i++) {
		if (daeElement* matchingEl = findDescendant(children[i], name))
			return matchingEl;
	}

	return NULL;
}

// Return the name of the first descendant we couldn't find
string checkAllDescendants(daeElement* root, const vector<string>& names) {
	for (size_t i = 0; i < names.size(); i++)
		if (!findDescendant(root, names[i]))
			return names[i];
	return "";
}


struct elementCompareResult {
	int compareValue; // > 0 if elt1 > elt2,
	                  // < 0 if elt1 < elt2,
	                  // = 0 if elt1 = elt2
	daeElement* elt1;
	daeElement* elt2;
	bool nameMismatch; // true if the names didn't match
	bool attrCountMismatch; // true if the number of attributes didn't match
	int attrIndex; // The index of the mismatched attribute, or -1 if there is no attr mismatch
	bool charDataMismatch; // true if the char data didn't match
	bool childCountMismatch; // true if the number of children didn't match

	elementCompareResult()
		: compareValue(0),
			elt1(NULL),
			elt2(NULL),
			nameMismatch(false),
			attrCountMismatch(false),
			attrIndex(-1),
			charDataMismatch(false),
			childCountMismatch(false) {
	}

	size_t getNecessaryColumnWidth(const vector<string>& tokens) {
		size_t result = 0;
		for (size_t i = 0; i < tokens.size(); i++) {
			size_t tokenLength = tokens[i].length() > 0 ? tokens[i].length()+2 : 0;
			result = max(tokenLength, result);
		}
		return result;
	}

	string formatToken(const string& token) {
		if (token.length() <= 50)
			return token;
		return token.substr(0, 47) + "...";
	}
	
	string format() {
		if (!elt1 || !elt2)
			return "";

		// Gather the data we'll be printing
		string name1 = formatToken(elt1->getElementName()),
		       name2 = formatToken(elt2->getElementName()),
		       type1 = formatToken(elt1->getTypeName()),
		       type2 = formatToken(elt2->getTypeName()),
		       id1 = formatToken(elt1->getAttribute("id")),
		       id2 = formatToken(elt2->getAttribute("id")),
		       attrCount1 = formatToken(toString(elt1->getAttributeCount())),
		       attrCount2 = formatToken(toString(elt2->getAttributeCount())),
		       attrName1 = formatToken(elt1->getAttributeName(attrIndex)),
		       attrName2 = formatToken(elt2->getAttributeName(attrIndex)),
		       attrValue1 = formatToken(elt1->getAttribute(attrIndex)),
		       attrValue2 = formatToken(elt2->getAttribute(attrIndex)),
		       charData1 = formatToken(elt1->getCharData()),
		       charData2 = formatToken(elt2->getCharData()),
		       childCount1 = formatToken(toString(elt1->getChildren().getCount())),
		       childCount2 = formatToken(toString(elt2->getChildren().getCount()));
		
		// Compute formatting information
		vector<string> col1Tokens = makeStringArray("Name", "Type", "ID", "Attr count",
			"Attr name", "Attr value", "Char data", "Child count", 0);
		vector<string> col2Tokens = makeStringArray("Element 1", name1.c_str(),
			type1.c_str(), id1.c_str(), attrCount1.c_str(), attrName1.c_str(), attrValue1.c_str(),
			charData1.c_str(), childCount1.c_str(), 0);
		
		size_t c1w = getNecessaryColumnWidth(col1Tokens),
		       c2w = getNecessaryColumnWidth(col2Tokens);
		ostringstream msg;
		msg << setw(c1w) << left << ""            << setw(c2w) << left << "Element 1" << "Element 2\n"
		    << setw(c1w) << left << ""            << setw(c2w) << left << "---------" << "---------\n"
		    << setw(c1w) << left << "Name"        << setw(c2w) << left << name1 << name2 << endl
		    << setw(c1w) << left << "Type"        << setw(c2w) << left << type1 << type2 << endl
		    << setw(c1w) << left << "ID"          << setw(c2w) << left << id1 << id2 << endl
		    << setw(c1w) << left << "Attr count"  << setw(c2w) << left << attrCount1 << attrCount2 << endl
		    << setw(c1w) << left << "Attr name"   << setw(c2w) << left << attrName1 << attrName2 << endl
		    << setw(c1w) << left << "Attr value"  << setw(c2w) << left << attrValue1 << attrValue2 << endl
		    << setw(c1w) << left << "Char data"   << setw(c2w) << left << charData1 << charData2 << endl
		    << setw(c1w) << left << "Child count" << setw(c2w) << left << childCount1 << childCount2;

		return msg.str();
	}
};

elementCompareResult compareMatch() {
	elementCompareResult result;
	result.compareValue = 0;
	return result;
}

elementCompareResult nameMismatch(daeElement& elt1, daeElement& elt2) {
	elementCompareResult result;
	result.elt1 = &elt1;
	result.elt2 = &elt2;
	result.compareValue = strcmp(elt1.getElementName(), elt2.getElementName());
	result.nameMismatch = true;
	return result;
}

elementCompareResult attrCountMismatch(daeElement& elt1, daeElement& elt2) {
	elementCompareResult result;
	result.elt1 = &elt1;
	result.elt2 = &elt2;
	result.compareValue = elt1.getAttributeCount() - elt2.getAttributeCount();
	result.attrCountMismatch = true;
	return result;
}

elementCompareResult attrMismatch(daeElement& elt1, daeElement& elt2, int attr) {
	elementCompareResult result;
	result.elt1 = &elt1;
	result.elt2 = &elt2;
	result.compareValue = strcmp(elt1.getAttribute(attr).c_str(),
	                             elt2.getAttribute(attr).c_str());
	result.attrIndex = attr;
	return result;
}

elementCompareResult charDataMismatch(daeElement& elt1, daeElement& elt2) {
	elementCompareResult result;
	result.elt1 = &elt1;
	result.elt2 = &elt2;
	result.compareValue = strcmp(elt1.getCharData().c_str(),
	                             elt2.getCharData().c_str());
	result.charDataMismatch = true;
	return result;
}

elementCompareResult childCountMismatch(daeElement& elt1, daeElement& elt2) {
	elementCompareResult result;
	result.elt1 = &elt1;
	result.elt2 = &elt2;
	daeElementRefArray children1 = elt1.getChildren(),
	                   children2 = elt2.getChildren();
	result.compareValue = children1.getCount() - children2.getCount();
	result.childCountMismatch = true;
	return result;
}


elementCompareResult compareElements(daeElement& elt1, daeElement& elt2);
	
elementCompareResult compareElementsSameType(daeElement& elt1, daeElement& elt2) {
	// Compare attributes
 	for (size_t i = 0; i < elt1.getAttributeCount(); i++)
 		if (elt1.getAttributeObject(i)->compare(&elt1, &elt2) != 0)
 			return attrMismatch(elt1, elt2, i);

	// Compare character data
	if (elt1.getCharDataObject())
		if (elt1.getCharDataObject()->compare(&elt1, &elt2) != 0)
			return charDataMismatch(elt1, elt2);

	// Compare children
	daeElementRefArray children1 = elt1.getChildren(),
	                   children2 = elt2.getChildren();
	if (children1.getCount() != children2.getCount())
		return childCountMismatch(elt1, elt2);
	for (size_t i = 0; i < children1.getCount(); i++) {
		elementCompareResult result = compareElements(*children1[i], *children2[i]);
		if (result.compareValue != 0)
			return result;
	}
	
	return compareMatch();
}

// There's a bug in this function. It takes attribute order into account, but attribute
// order doesn't matter in XML. This is unlikely to be a problem though.
elementCompareResult compareElementsDifferentTypes(daeElement& elt1, daeElement& elt2) {
	string value1, value2;

	// Compare attributes
	size_t attrCount1 = elt1.getAttributeCount(),
	       attrCount2 = elt2.getAttributeCount();
	if (attrCount1 != attrCount2)
		return attrCountMismatch(elt1, elt2);
	for (size_t i = 0; i < attrCount1; i++) {
		elt1.getAttribute(i, value1);
		elt2.getAttribute(i, value2);
		if (value1 != value2)
			return attrMismatch(elt1, elt2, i);
	}

	// Compare character data
	elt1.getCharData(value1);
	elt2.getCharData(value2);
	if (value1 != value2)
		return charDataMismatch(elt1, elt2);

	// Compare children
	daeElementRefArray children1 = elt1.getChildren(),
	                   children2 = elt2.getChildren();
	if (children1.getCount() != children2.getCount())
		return childCountMismatch(elt1, elt2);
	for (size_t i = 0; i < children1.getCount(); i++) {
		elementCompareResult result = compareElements(*children1[i], *children2[i]);
		if (result.compareValue != 0)
			return result;
	}
	
	return compareMatch();
}

// Recursive comparison. Return -1 if elt1 < elt2, 0 if elt1 == elt2, and 1 if elt1 > elt2.
elementCompareResult compareElements(daeElement& elt1, daeElement& elt2) {
	// Check the element name
	if (strcmp(elt1.getElementName(), elt2.getElementName()) != 0)
		return nameMismatch(elt1, elt2);

	// Dispatch to a specific function based on whether or not the types are the same
	if (strcmp(elt1.getTypeName(), elt2.getTypeName())  ||  strcmp(elt1.getTypeName(), "any") == 0)
		return compareElementsDifferentTypes(elt1, elt2);
	else
		return compareElementsSameType(elt1, elt2);
}

DefineTest(elementCompareResultTest) {
	DAE dae;
	string seymourOrig     = lookupTestFile("Seymour.dae"),
	       seymourModified = lookupTestFile("Seymour_roundTrip.dae");
	CheckResult(dae.load(seymourOrig.c_str()) == DAE_OK);
	CheckResult(dae.load(seymourModified.c_str()) == DAE_OK);
	CompareDocs(dae, seymourOrig, seymourModified);

	return testResult(true);
}


DefineTest(loadClipPlane) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("clipPlane.dae").c_str()) == DAE_OK);
	return testResult(true);
}


DefineTest(renderStates) {
	string memoryUri = "renderStates_create.dae";
	string fileUri = getTmpFile("renderStates.dae");
	
	DAE dae;
	CheckResult(dae.getDatabase()->insertDocument(memoryUri.c_str()) == DAE_OK);

	daeElement* element = dae.getDom(memoryUri.c_str());
	element = element->createAndPlace("library_effects");
	element = element->createAndPlace("effect");
	element = element->createAndPlace("profile_CG");
	element = element->createAndPlace("technique");
	element = element->createAndPlace("pass");
	element->createAndPlace("color_clear")->setCharData("0 0 0 0");
	element->createAndPlace("depth_mask")->setAttribute("value", "true");
	element->createAndPlace("cull_face_enable")->setAttribute("value", "true");
	element->createAndPlace("blend_enable")->setAttribute("value", "true");
	element->createAndPlace("blend_func_separate")->setAttribute("value", "true");
	element->createAndPlace("cull_face")->setAttribute("value", "FRONT");
	element->createAndPlace("polygon_offset_fill_enable")->setAttribute("value", "true");
	element->createAndPlace("clear_color")->setAttribute("value", "0 0 0 0");
	
	// Write the document to disk
	CheckResult(dae.saveAs(fileUri.c_str(),	memoryUri.c_str()) == DAE_OK);

	// Load up the saved document and see if it's the same as our in-memory document
	CheckResult(dae.load(fileUri.c_str()) == DAE_OK);
	CompareDocs(dae, memoryUri, fileUri);
	domCOLLADA* root = dae.getDom(fileUri.c_str());
	CheckResult(root);

	// Check default attribute value suppression
	CheckResult(findDescendant(root, "depth_mask")->isAttributeSet("value") == false);
	CheckResult(findDescendant(root, "clear_color")->isAttributeSet("value") == false);
	CheckResult(findDescendant(root, "color_clear")->getCharData() != "");
	CheckResult(findDescendant(root, "polygon_offset_fill_enable")->isAttributeSet("value"));
		
	return testResult(true);
}


DefineTest(writeCamera) {
	string memoryUri = "camera_create.dae";
	string fileUri = getTmpFile("camera.dae");

	DAE dae;
	CheckResult(dae.getDatabase()->insertDocument(memoryUri.c_str()) == DAE_OK);

	daeElement* element = dae.getDom(memoryUri.c_str());
	element = element->createAndPlace("library_cameras");
	element = element->createAndPlace("camera");
	element = element->createAndPlace("optics");
	element = element->createAndPlace("technique_common");
	element = element->createAndPlace("perspective");
	element = element->createAndPlace("xfov");
	element->setCharData("1.0");

	CheckResult(dae.saveAs(fileUri.c_str(), memoryUri.c_str()) == DAE_OK);
	CheckResult(dae.load(fileUri.c_str()) == DAE_OK);
	CompareDocs(dae, memoryUri, fileUri);
	domCOLLADA* root = dae.getDom(fileUri.c_str());
	CheckResult(root);
	CheckResult(toFloat(findDescendant(root, "xfov")->getCharData()) == 1.0f);
	
	return testResult(true);
}


string getRoundTripFile(const string& name) {
	return getTmpFile(fs::basename(fs::path(name)) + "_roundTrip.dae");
}

bool roundTrip(const string& file) {
	DAE dae;
	if (dae.load(file.c_str()) != DAE_OK)
		return false;
	return dae.saveAs(getRoundTripFile(file).c_str(), file.c_str()) == DAE_OK;
}

DefineTest(roundTripSeymour) {
	string uri1 = lookupTestFile("Seymour.dae"),
	       uri2 = getRoundTripFile(uri1);
	DAE dae;
	CheckResult(dae.load(uri1.c_str()) == DAE_OK);
	CheckResult(dae.saveAs(uri2.c_str(), uri1.c_str()) == DAE_OK);
	CheckResult(dae.load(uri2.c_str()) == DAE_OK);
	CompareDocs(dae, uri1, uri2);
	return testResult(true);
}


DefineTest(rawSupport) {
	string seymourOrig = lookupTestFile("Seymour.dae"),
	       seymourRaw  = getTmpFile("Seymour_raw.dae");
	DAE dae;

	CheckResult(dae.load(seymourOrig.c_str()) == DAE_OK);
	dae.getIOPlugin()->setOption("saveRawBinary", "true");
	CheckResult(dae.saveAs(seymourRaw.c_str(), seymourOrig.c_str()) == DAE_OK);

	// Make sure the .raw file is there
	CheckResult(fs::exists(fs::path(seymourRaw + ".raw")));

	CheckResult(dae.load(seymourRaw.c_str()) == DAE_OK);
	daeElement* el = 0;
	dae.getDatabase()->getElement(&el, 0,
		"l_hip_rotateY_l_hip_rotateY_ANGLE-input", seymourRaw.c_str());
	CheckResult(el);

	return testResult(true);
}

DefineTest(extraTypeTest) {
	DAE dae;
	string docUri = lookupTestFile("extraTest.dae");
	CheckResult(dae.load(docUri.c_str()) == DAE_OK);
	daeElement* root = dae.getDom(docUri.c_str());
	CheckResult(root);

	daeElement *technique = findDescendant(root, "technique"),
	           *expectedTypesElt = findDescendant(root, "expected_types");
	CheckResult(technique && expectedTypesElt);

	istringstream expectedTypesStream(expectedTypesElt->getCharData());
	vector<string> expectedTypes;
	string tmp;
	while (expectedTypesStream >> tmp)
		expectedTypes.push_back(tmp);

	daeElementRefArray elements = technique->getChildren();

	CheckResult(expectedTypes.size() == elements.getCount()-1);
	for (size_t i = 0; i < elements.getCount()-1; i++) {
		ostringstream msg;
		msg << "Actual type - " << elements[i]->getTypeName() << ", Expected type - " << expectedTypes[i];
		CheckResultWithMsg(expectedTypes[i] == elements[i]->getTypeName(), msg.str());
	}

	return testResult(true);
}

#if defined(TINYXML)
#include <dae/daeTinyXMLPlugin.h>
DefineTest(tinyXmlLoad) {
	string seymourOrig = lookupTestFile("Seymour.dae"),
	       seymourTinyXml = getTmpFile("Seymour_tinyXml.dae");

	// Plan: Load Seymour with libxml, then save with TinyXml and immediately reload the
	// saved document, and make sure the results are the same.
	DAE dae;
	CheckResult(dae.load(seymourOrig.c_str()) == DAE_OK);
	auto_ptr<daeTinyXMLPlugin> tinyXmlPlugin(new daeTinyXMLPlugin);
	dae.setIOPlugin(tinyXmlPlugin.get());
	CheckResult(dae.saveAs(seymourTinyXml.c_str(), seymourOrig.c_str()) == DAE_OK);
	CheckResult(dae.load(seymourTinyXml.c_str()) == DAE_OK);
	CompareDocs(dae, seymourOrig, seymourTinyXml);

	return testResult(true);
}
#endif


string resolveResultToString(daeSIDResolver::ResolveState state) {
	switch(state) {
		case daeSIDResolver::target_empty: return "target empty"; break;
		case daeSIDResolver::target_loaded: return "target loaded"; break;
		case daeSIDResolver::sid_failed_not_found: return "failed"; break;
		case daeSIDResolver::sid_success_element: return "element"; break;
		case daeSIDResolver::sid_success_array: return "array"; break;
		case daeSIDResolver::sid_success_double: return "double"; break;
	}

	return "unknown error";
}

daeSIDResolver::ResolveState resolveSidToState(const string& sid, daeElement* container) {
	daeSIDResolver sidResolver(container, sid.c_str());
	sidResolver.getElement();
	return sidResolver.getState();
}

DefineTest(sidResolveTest) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("sidResolveTest.dae").c_str()) == DAE_OK);

	daeElement *effect = 0,
	           *effectExtra = 0;
	dae.getDatabase()->getElement(&effect, 0, "myEffect");
	dae.getDatabase()->getElement(&effectExtra, 0, "effectExtra");
	CheckResult(effect && effectExtra);

	istringstream stream(effectExtra->getCharData());
	string sidRef, expectedResult;
	while (stream >> sidRef >> expectedResult) {
		string result = resolveResultToString(resolveSidToState(sidRef, effect));
		CheckResultWithMsg(result == expectedResult,
		                   string("sid ref=") + sidRef + ", expectedResult=" + expectedResult + ", actualResult=" + result);
	}

	daeElement *root = 0,
	           *nodeSidRefExtra = 0;
	dae.getDatabase()->getElement(&root, 0, 0, COLLADA_TYPE_COLLADA);
	dae.getDatabase()->getElement(&nodeSidRefExtra, 0, "nodeSidRefExtra");
	CheckResult(root && nodeSidRefExtra);

	stream.clear();
	stream.str(nodeSidRefExtra->getCharData());
	while (stream >> sidRef >> expectedResult) {
		string result = resolveResultToString(resolveSidToState(sidRef, root));
		CheckResultWithMsg(result == expectedResult,
		                   string("sid ref=") + sidRef + ", expectedResult=" + expectedResult + ", actualResult=" + result);
	}

	dae.getDatabase()->getElement(&nodeSidRefExtra, 0, "nodeSidRefExtra2");
	CheckResult(nodeSidRefExtra);

	stream.clear();
	stream.str(nodeSidRefExtra->getCharData());
	while (stream >> sidRef >> expectedResult) {
		daeElement* elt = cdom::resolveSid(root, sidRef);
		string result = elt ? elt->getAttribute("id") : "failed";
		CheckResultWithMsg(result == expectedResult,
		                   string("sid ref=") + sidRef + ", expectedResult=" + expectedResult + ", actualResult=" + result);
	}

	dae.getDatabase()->getElement(&nodeSidRefExtra, 0, "nodeSidRefExtra3");
	CheckResult(nodeSidRefExtra);

	stream.clear();
	stream.str(nodeSidRefExtra->getCharData());
	string profile;
	while (stream >> sidRef >> profile >> expectedResult) {
		daeElement* elt = cdom::resolveSid(root, sidRef, profile);
		string result = elt ? elt->getAttribute("id") : "failed";
		CheckResultWithMsg(result == expectedResult,
		                   string("sid ref=") + sidRef + ", profile=" + profile +
		                   ", expectedResult=" + expectedResult + ", actualResult=" + result);
	}


	return testResult(true);
}

daeElement* findChildByName(daeElement* el, daeString name) {
	if (!el)
		return 0;

	daeElementRefArray children = el->getChildren();
	for (size_t i = 0; i < children.getCount(); i++)
		if (strcmp(children[i]->getElementName(), name) == 0)
			return children[i];

	return 0;
}

daeElement* findAncestorByType(daeElement* el, daeString type) {
	if (el == 0  ||  strcmp(el->getTypeName(), type) == 0)
		return el;
	return findAncestorByType(el->getParentElement(), type);
}

daeElement* resolveID(daeString id, daeDocument& document) {
	daeElement* el = 0;
	document.getDatabase()->getElement(&el, 0, id);
	return el;
}

daeElement* resolveSid(const string& sid, daeElement& container) {
	daeSIDResolver sidResolver(&container, sid.c_str());
	return sidResolver.getElement();
}

string getCharData(daeElement* el) {
	return el ? el->getCharData() : "";
}

daeURI* getTextureUri(const string& samplerSid, daeElement& effect) {
	daeElement* sampler = findChildByName(resolveSid(samplerSid, effect), "sampler2D");
	string surfaceSid = getCharData(findChildByName(sampler, "source"));
	daeElement* surface = findChildByName(resolveSid(surfaceSid, effect), "surface");
	domImage* image = daeSafeCast<domImage>(
		resolveID(getCharData(findChildByName(surface, "init_from")).c_str(), *effect.getDocument()));
	if (image && image->getInit_from())
		return &image->getInit_from()->getValue();
	return 0;
}

DefineTest(getTexture) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("Seymour.dae").c_str()) == DAE_OK);

	daeElement* effect = 0;
 	dae.getDatabase()->getElement(&effect, 0, "face-fx");
	CheckResult(effect);
	daeElement* texture = findDescendant(effect, "texture");
	CheckResult(texture);

	daeURI* uri = getTextureUri(texture->getAttribute("texture"), *effect);
	CheckResult(uri);
	CheckResult(string(uri->getFile()) == "boy_10.tga");

	return testResult(true);
}
	

DefineTest(removeElement) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("Seymour.dae").c_str()) == DAE_OK);

	daeElement *asset = 0, *animLib = 0, *collada = 0;
	dae.getDatabase()->getElement(&collada, 0, 0, COLLADA_TYPE_COLLADA);
	dae.getDatabase()->getElement(&asset, 0, 0, COLLADA_TYPE_ASSET);
	dae.getDatabase()->getElement(&animLib, 0, 0, COLLADA_TYPE_LIBRARY_ANIMATIONS);
	CheckResult(asset && animLib && collada);

	collada->removeChildElement(asset);
	daeElement::removeFromParent(animLib);

	CheckResult(findDescendant(collada, "asset") == NULL);
	CheckResult(findDescendant(collada, "library_animations") == NULL);

	CheckResult(dae.saveAs(getTmpFile("Seymour_removeElements.dae").c_str(),
	                       lookupTestFile("Seymour.dae").c_str()) == DAE_OK);
	return testResult(true);
}


DefineTest(cloneCrash) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("duck.dae").c_str()) == DAE_OK);

	daeElement* effect;
	dae.getDatabase()->getElement(&effect, 0, NULL, COLLADA_TYPE_EFFECT);
	daeElementRef clonedEffect = effect->clone();

	daeIDRef idRef("MayaNativePhysicsScene");
	idRef.setContainer(effect);
	daeElement* el = idRef.getElement();
	CheckResult(el);
	
	dae.getDatabase()->getElement(&el, 0, NULL, COLLADA_TYPE_FX_SURFACE_INIT_FROM_COMMON);
	domFx_surface_init_from_common* initFrom = daeSafeCast<domFx_surface_init_from_common>(el);
	CheckResult(initFrom && initFrom->getValue().getElement());

	// The DOM used to crash here
	daeElement::resolveAll();

	return testResult(true);
}


void nameArraySet(domListOfNames& names, size_t index, const char* name) {
	*(daeStringRef*)&names[index] = name;
}

void nameArrayAppend(domListOfNames& names, const char* name) {
	names.append(NULL);
	nameArraySet(names, names.getCount()-1, name);
}

DefineTest(nameArray) {
	domListOfNames names;
	for (int i = 0; i < 10; i++)
		nameArrayAppend(names, (string("name") + toString(i)).c_str());
	for (int i = 0; i < 10; i++) {
		CheckResult(string("name") + toString(i) == names[i]);
	}
	
	return testResult(true);
}

template<typename T>
void printArray(const daeTArray<T>& array) {
	for (size_t i = 0; i < array.getCount(); i++)
		cout << array[i] << " ";
	cout << endl;
}

DefineTest(arrayOps) {
	daeTArray<int> zeroToFour = makeIntArray(0, 1, 2, 3, 4, INT_MAX);

	// Test removeIndex
	daeTArray<int> array = zeroToFour;
	array.removeIndex(2);
	CheckResult(array == makeIntArray(0, 1, 3, 4, INT_MAX));

	// Insert several values into the middle of an array
	array = zeroToFour;
	array.insert(3, 5, 9); // Insert five copies of '9' at the third element of the array
	CheckResult(array == makeIntArray(0, 1, 2, 9, 9, 9, 9, 9, 3, 4, INT_MAX));

	// Insert several values beyond the end of an array
	array = zeroToFour;
	array.insert(7, 2, 5);
	CheckResult(array == makeIntArray(0, 1, 2, 3, 4, 5, 5, 5, 5, INT_MAX));

	return testResult(true);
}


void printMemoryToStringResult(daeAtomicType& type, daeMemoryRef value) {
	ostringstream buffer;
	type.memoryToString(value, buffer);
	cout << buffer.str() << endl;
}

string toString(daeAtomicType& type, daeMemoryRef value) {
	ostringstream buffer;
	type.memoryToString(value, buffer);
	return buffer.str();
}

DefineTest(atomicTypeOps) {
	daeUIntType UIntType;
	daeIntType IntType;
	daeLongType LongType;
	daeShortType ShortType;
	daeULongType ULongType;
	daeFloatType FloatType;
	daeDoubleType DoubleType;
	daeStringRefType StringRefType;
	daeElementRefType ElementRefType;
	daeEnumType EnumType;
	daeRawRefType RawRefType;
	daeResolverType ResolverType;
	daeIDResolverType IDResolverType;
	daeBoolType BoolType;
	daeTokenType TokenType;

	EnumType._values = new daeEnumArray;
	EnumType._strings = new daeStringRefArray;
	EnumType._values->append(0);
	EnumType._strings->append("myEnumValue");

	daeUInt UInt(1);
	daeInt Int(2);
	daeLong Long(3);
	daeShort Short(4);
	daeULong ULong(5);
	daeFloat Float(6.123);
	daeDouble Double(7.456);
	daeStringRef StringRef("StringRef");
	//	daeElementRef ElementRef(0x12345678);
	daeEnum Enum(0);
	daeRawRef RawRef((void*)0x12345678);
	daeURI uri("http://www.example.com/#fragment");
	daeIDRef IDRef("sampleID");
	daeBool Bool(false);
	daeStringRef Token("token");

	
	CheckResult(toString(UIntType, (daeMemoryRef)&UInt) == "1");
	CheckResult(toString(IntType, (daeMemoryRef)&Int) == "2");
	CheckResult(toString(LongType, (daeMemoryRef)&Long) == "3");
	CheckResult(toString(ShortType, (daeMemoryRef)&Short) == "4");
	CheckResult(toString(ULongType, (daeMemoryRef)&ULong) == "5");
	CheckResult(toString(FloatType, (daeMemoryRef)&Float) == "6.123");
	CheckResult(toString(DoubleType, (daeMemoryRef)&Double) == "7.456");
	CheckResult(toString(StringRefType, (daeMemoryRef)&StringRef) == "StringRef");
	//	CheckResult(toString(ElementRefType, (daeMemoryRef)&ElementRef) == "");
	CheckResult(toString(EnumType, (daeMemoryRef)&Enum) == "myEnumValue");
	CheckResult(toString(RawRefType, (daeMemoryRef)&RawRef) == "0x12345678");
	CheckResult(toString(ResolverType, (daeMemoryRef)&uri) == "http://www.example.com/#fragment");
	CheckResult(toString(IDResolverType, (daeMemoryRef)&IDRef) == "sampleID");
	CheckResult(toString(BoolType, (daeMemoryRef)&Bool) == "false");
	CheckResult(toString(TokenType, (daeMemoryRef)&Token) == "token");

	return testResult(true);
}


DefineTest(clone) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("Seymour.dae").c_str()) == DAE_OK);

	daeElement* el = 0;
	dae.getDatabase()->getElement(&el, 0, "l_ulna");
	CheckResult(el);

	daeElementRef clone = el->clone("-foo", "-bar");
	el->getParentElement()->placeElement(clone);

	CheckResult(dae.saveAs(getTmpFile("cloneTest.dae").c_str(),
	            lookupTestFile("Seymour.dae").c_str()) == DAE_OK);

	return testResult(true);
}


DefineTest(genericOps) {
	string uri = lookupTestFile("cube.dae");
	DAE dae;
	CheckResult(dae.load(uri.c_str()) == DAE_OK)

	// Attribute getter/setter tests
	daeElement* el = 0;
	dae.getDatabase()->getElement(&el, 0, "box-lib-positions-array");
	CheckResult(el);

	CheckResult(el->hasAttribute("digits"));
 	CheckResult(el->getAttribute("count") == "24");
	CheckResult(el->setAttribute("blah", "hey") == false);
	CheckResult(el->setAttribute("magnitude", "30"));

	dae.getDatabase()->getElement(&el, 0, "Blue-fx");
	CheckResult(el);
	CheckResult(el->hasAttribute("name"));
	CheckResult(el->isAttributeSet("name") == false);
	CheckResult(el->isAttributeSet("hello") == false);

	// Character data getter/setter tests
	dae.getDatabase()->getElement(&el, 0, NULL, COLLADA_TYPE_UP_AXIS);
	CheckResult(el);

	CheckResult(el->getCharData() == "Y_UP");
	el->setCharData("X_UP");

	dae.getDatabase()->getElement(&el, 0, "PerspCamera");
	CheckResult(el && !el->hasCharData());

	// <extra> tests using daeElement interface
	dae.getDatabase()->getElement(&el, 0, "my_test_element");
	CheckResult(el);
 	daeElementRef clone = el->clone("-clone", "-clone");

	CheckResult(el->getAttribute("attr1") == "value1" &&
	            el->getAttribute("attr2") == "value2");
	CheckResult(el->setAttribute("attr1", "value_1"));
	CheckResult(el->setAttribute("attr3", "value3"));
	
	CheckResult(chopWS(el->getCharData()) == "this is some text");
	el->setCharData("reset text");

	// <extra> tests using domAny interface
	el->getParentElement()->placeElementAfter(el, clone);
	domAny* any = (domAny*)clone.cast();
	CheckResult(any);
	CheckResult(any->getAttributeCount() == 3);
	CheckResult(string(any->getAttributeName(0)) == "id");
	CheckResult(string(any->getAttributeValue(1)) == "value1");
	CheckResult(chopWS(any->getValue()) == "this is some text");
	any->setValue("reset text 2");

	// Test for lots of attributes
 	for (size_t i = 0; i < 50; i++) {
		ostringstream name, value;
		name << "attr" << i;
		value << "value" << i;
		any->setAttribute(name.str().c_str(), value.str().c_str());
	}

	CheckResult(dae.saveAs(getTmpFile(fs::basename(fs::path(uri)) + "_genericOps.dae").c_str(),
	                       uri.c_str()) == DAE_OK);

	return testResult(true);
}


daeArray* getSkewArray(daeElement* node, const string& sid) {
	if (!node)
		return NULL;
	
	daeElement* skew = resolveSid(sid, *node);
	if (!skew || skew->getElementType() != COLLADA_TYPE::SKEW)
		return NULL;

	return (daeArray*)skew->getCharDataObject()->get(skew);
}

DefineTest(badSkew) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("badSkew.dae").c_str()) == DAE_OK);

	daeElement* node = 0;
	dae.getDatabase()->getElement(&node, 0, "my-node");
	CheckResult(node);

	daeArray* array1 = getSkewArray(node, "tooFew");
	daeArray* array2 = getSkewArray(node, "justRight");
	daeArray* array3 = getSkewArray(node, "tooMany");
	CheckResult(array1 && array2 && array3);

	CheckResult(array1->getCount() == 4);
	CheckResult(array2->getCount() == 7);
	CheckResult(array3->getCount() == 11);
	
	return testResult(true);
}


DefineTest(stringTable) {
	daeStringTable stringTable;
	stringTable.allocString("hello");
	// These next two lines used to cause an abort
	stringTable.clear(); 
	stringTable.allocString("goodbye");
	return testResult(true);
}


// We can only do this test if we have breps
#if 0
DefineTest(sidResolveSpeed) {
	DAE dae;
	string file = lookupTestFile("crankarm.dae");
	CheckResult(dae.load(file.c_str()) == DAE_OK);
	domCOLLADA* root = dae.getDom(file.c_str());
	CheckResult(root);
		
	size_t count = dae.getDatabase()->getElementCount(NULL, COLLADA_TYPE_SIDREF_ARRAY);
	for (size_t i = 0; i < count; i++) {
		daeElement* elt = 0;
		dae.getDatabase()->getElement(&elt, 0, NULL, COLLADA_TYPE_SIDREF_ARRAY);
		CheckResult(elt);
		domSIDREF_array* sidRefsElt = daeSafeCast<domSIDREF_array>(elt);
		CheckResult(sidRefsElt);
		
		domListOfNames& sidRefs = sidRefsElt->getValue();
		for (size_t j = 0; j < sidRefs.getCount(); j++) {
			CheckResult(cdom::resolveSid(root, sidRefs[i]));
		}
	}

	return testResult(true);
}
#endif


DefineTest(seymourSidResolve) {
	DAE dae;
	string file = lookupTestFile("Seymour.dae");
	CheckResult(dae.load(file.c_str()) == DAE_OK);

	size_t count = dae.getDatabase()->getElementCount(NULL, COLLADA_TYPE_NODE);
	for (size_t i = 0; i < count; i++) {
		daeElement* elt = NULL;
		dae.getDatabase()->getElement(&elt, 0, NULL, COLLADA_TYPE_NODE);
		CheckResult(elt);
		daeElementRefArray children;
		elt->getChildren(children);
		for (size_t j = 0; j < children.getCount(); j++) {
			string sid = children[j]->getAttribute("sid");
			if (!sid.empty()) {
				CheckResult(cdom::resolveSid(elt, sid));
			}
		}
	}

	return testResult(true);
}


vector<string> getChildNames(daeElement* elt) {
	vector<string> result;
	if (!elt)
		return result;

	daeElementRefArray children = elt->getChildren();
	for (size_t i = 0; i < children.getCount(); i++)
		result.push_back(children[i]->getElementName());

	return result;
}

DefineTest(placeElement) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("cube.dae").c_str()) == DAE_OK);

	daeElement* node = 0;
	dae.getDatabase()->getElement(&node, 0, "Box");
	CheckResult(node);

	CheckResult(getChildNames(node) == makeStringArray(
		"rotate", "rotate", "rotate", "instance_geometry", 0));

	// Place a new <translate> after the first <rotate> using placeElementAfter, and
	// make sure the <translate> shows up in the right spot.
	node->placeElementAfter(node->getChildren()[0], node->createElement("translate"));
	CheckResult(getChildNames(node) == makeStringArray(
		"rotate", "translate", "rotate", "rotate", "instance_geometry", 0));

	node->placeElementBefore(node->getChildren()[0], node->createElement("scale"));
	CheckResult(getChildNames(node) == makeStringArray(
		"scale", "rotate", "translate", "rotate", "rotate", "instance_geometry", 0));

	return testResult(true);
};


DefineTest(uriConversion) {
	// Windows file path to URI
	CheckResult(cdom::filePathToUri("C:\\myFolder\\myFile.dae") == "/C:/myFolder/myFile.dae");
	CheckResult(cdom::filePathToUri("\\myFolder\\myFile.dae") == "file:////myFolder/myFile.dae");
	CheckResult(cdom::filePathToUri("..\\myFolder\\myFile.dae") == "../myFolder/myFile.dae");
	CheckResult(cdom::filePathToUri("\\\\otherComputer\\myFile.dae") == "file://///otherComputer/myFile.dae");

	// Linux/Mac file path to URI
	CheckResult(cdom::filePathToUri("/myFolder/myFile.dae") == "/myFolder/myFile.dae");
	CheckResult(cdom::filePathToUri("../myFolder/myFile.dae") == "../myFolder/myFile.dae");
	CheckResult(cdom::filePathToUri("/my folder/my file.dae") == "/my%20folder/my%20file.dae");

#ifdef WIN32
	// URI to Windows file path
	CheckResult(cdom::uriToFilePath("../folder/file.dae") == "..\\folder\\file.dae");
	CheckResult(cdom::uriToFilePath("file:///C:/folder/file.dae") == "C:\\folder\\file.dae");
	CheckResult(cdom::uriToFilePath("file://///otherComputer/file.dae") == "\\\\otherComputer\\file.dae");
	CheckResult(cdom::uriToFilePath("http://www.slashdot.org") == "");
#else
	// URI to Linux/Mac file path
	CheckResult(cdom::uriToFilePath("../folder/file.dae") == "../folder/file.dae");
	CheckResult(cdom::uriToFilePath("file:///folder/file.dae") == "/folder/file.dae");
	CheckResult(cdom::uriToFilePath("http://www.slashdot.org") == "");
#endif

	return testResult(true);
}


// Returns true if all tests names are valid
bool checkTests(const set<string>& tests) {
	bool invalidTestFound = false;
	for (set<string>::const_iterator iter = tests.begin(); iter != tests.end(); iter++) {
		if (g_tests.find(*iter) == g_tests.end()) {
			if (!invalidTestFound)
				cout << "Invalid arguments:\n";
			cout << "  " << *iter << endl;
			invalidTestFound = true;
		}
	}

	return !invalidTestFound;
}

// Returns the set of tests that failed
map<string, testResult> runTests(const set<string>& tests) {
	map<string, testResult> failedTests;
	for (set<string>::const_iterator iter = tests.begin(); iter != tests.end(); iter++) {
		testResult result = g_tests[*iter]->run();
		if (!result.passed)
			failedTests[*iter] = result;
	}
	return failedTests;
}

void printTestResults(const map<string, testResult>& failedTests) {
	if (!failedTests.empty()) {
		cout << "Failed tests:\n";
		for (map<string, testResult>::const_iterator iter = failedTests.begin();
		     iter != failedTests.end();
		     iter++) {
			cout << "    " << iter->first;
			if (iter->second.line != -1)
				cout << " (line " << iter->second.line << ")";
			cout << endl;
			if (!iter->second.msg.empty()) // Make sure to indent the message
				cout << "        " << replace(iter->second.msg, "\n", "\n        ") << "\n";
		}
	}
	else {
		cout << "All tests passed.\n";
	}
}

struct tmpDir {
	fs::path path;
	bool deleteWhenDone;
	
	tmpDir(fs::path& path, bool deleteWhenDone)
		: path(path),
			deleteWhenDone(deleteWhenDone) {
		fs::create_directories(path);
	}

	~tmpDir() {
		if (deleteWhenDone)
			fs::remove_all(path);
	}
};


int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << "Usage:\n"
		        "  -printTests - Print the names of all available tests\n"
		        "  -all - Run all tests\n"
		        "  -leaveTmpFiles - Don't delete the tmp folder containing the generated test files\n"
		        "  test1 test2 ... - Run the named tests\n";
		return 0;
	}

	bool printTests = false;
	bool allTests = false;
	bool leaveTmpFiles = false;
	set<string> tests;
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "-printTests")
			printTests = true;
		else if (string(argv[i]) == "-all")
			allTests = true;
		else if (string(argv[i]) == "-leaveTmpFiles")
			leaveTmpFiles = true;
		else
			tests.insert(argv[i]);
	}

	// Shut the DOM up
	daeErrorHandler::setErrorHandler(&quietErrorHandler::getInstance());

	g_dataPath = (fs::path(argv[0]).branch_path()/"../../test/data/").normalize();
	g_tmpPath = g_dataPath / "tmp";
	tmpDir tmp(g_tmpPath, !leaveTmpFiles);

	if (checkTests(tests) == false)
		return 0;

	// -printTest
	if (printTests) {
		for (map<string, domTest*>::iterator iter = g_tests.begin(); iter != g_tests.end(); iter++)
			cout << iter->second->name << endl;
		return 0;
	}

	// -all
	if (allTests)
		for (map<string, domTest*>::iterator iter = g_tests.begin(); iter != g_tests.end(); iter++)
			tests.insert(iter->first);

	// test1 test2 ...
 	printTestResults(runTests(tests));

	return 0;
}

#include <cstdarg>
#include <iostream>
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

#define CheckResult(val)									\
	if (!(val)) {														\
		cout << "line: " << __LINE__ << endl; \
		return false;													\
	}

struct domTest;
map<string, domTest*> g_tests;

struct domTest {
	string name;
	domTest(const string& name) : name(name) {
		g_tests[name] = this;
	}
	virtual ~domTest() { };
	virtual bool run() = 0;
};

#define DefineTest(testName)											\
	struct domTest_##testName : public domTest {		\
		domTest_##testName() : domTest(#testName) { }	\
		bool run();																		\
	};																							\
	domTest_##testName domTest_##testName##Obj;			\
	bool domTest_##testName::run()

#define RunTest(testName)																						\
	{																																	\
		map<string, domTest*>::iterator iter = g_tests.find(#testName);	\
		CheckResult(iter != g_tests.end());															\
		CheckResult(iter->second->run());																\
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
	return true;
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
	return true;
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

void printStringArray(const vector<string>& array) {
	for (size_t i = 0; i < array.size(); i++)
		cout << array[i] << endl;
}

DefineTest(stringSplit) {
	CheckResult(split("1|2|3|4", '|')   == makeStringArray("1", "2", "3", "4", 0));
	CheckResult(split("|1|", '|')       == makeStringArray("1", 0));
	CheckResult(split("1|||2||3|", '|') == makeStringArray("1", "2", "3", 0));
	return true;
}


DefineTest(loadClipPlane) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("clipPlane.dae").c_str()) == DAE_OK);
	return true;
}


DefineTest(renderStates) {
	DAE dae;

	string docUri = getTmpFile("renderStates.dae");
	dae.getDatabase()->insertDocument(docUri.c_str());
	daeElement* element;
	dae.getDatabase()->getElement(&element, 0, 0, "COLLADA");

	element = element->createAndPlace("library_effects");
	element = element->createAndPlace("effect");
	element = element->createAndPlace("profile_CG");
	element = element->createAndPlace("technique");
	element = element->createAndPlace("pass");
	element->createAndPlace("depth_mask")->setAttribute("value", "true");
	element->createAndPlace("cull_face_enable")->setAttribute("value", "true");
	element->createAndPlace("blend_enable")->setAttribute("value", "true");
	element->createAndPlace("blend_func_separate")->setAttribute("value", "true");
	element->createAndPlace("cull_face")->setAttribute("value", "FRONT");
	element->createAndPlace("polygon_offset_fill_enable")->setAttribute("value", "true");
	element->createAndPlace("clear_color")->setAttribute("value", "0 0 0 0");
	daeElement* colorClear = element->createAndPlace("color_clear");
	colorClear->getMeta()->getValueAttribute()->set(colorClear, "0 0 0 0");

	CheckResult(dae.save(docUri.c_str()) == DAE_OK);
	/// !!!steveT Now load the file we just saved and examine its contents.
	return true;
}


DefineTest(writeCamera) {
	DAE dae;

	string docUri = getTmpFile("camera.dae");
	dae.getDatabase()->insertDocument(docUri.c_str());
	daeElement* element;
	dae.getDatabase()->getElement(&element, 0, 0, "COLLADA");

	element = element->createAndPlace("library_cameras");
	element = element->createAndPlace("camera");
	element = element->createAndPlace("optics");
	element = element->createAndPlace("technique_common");
	element = element->createAndPlace("perspective");

	domCamera::domOptics::domTechnique_common::domPerspective* perspective =
		daeSafeCast<domCamera::domOptics::domTechnique_common::domPerspective>(element);
	domTargetableFloat* xfov = daeSafeCast<domTargetableFloat>(perspective->createAndPlace("xfov"));
	xfov->setValue(1.0);

	dae.save(docUri.c_str());
	// !!!steveT Now load the file we just saved and examine its contents.
	return true;
}


bool roundTrip(const string& uri) {
	DAE dae;
	CheckResult(dae.load(uri.c_str()) == DAE_OK);
	return dae.saveAs(getTmpFile(fs::basename(fs::path(uri)) + "_roundTrip.dae").c_str(),
										uri.c_str()) == DAE_OK;
}

DefineTest(roundTripSeymour) {
	return roundTrip(lookupTestFile("Seymour.dae"));
}


// !!!steveT Merge saveSeymourRaw and loadSeymourRaw into a single test
DefineTest(saveSeymourRaw) {
	DAE dae;
	string docUri = lookupTestFile("Seymour.dae");
	CheckResult(dae.load(docUri.c_str()) == DAE_OK);
	dae.getIOPlugin()->setOption("saveRawBinary", "true");
	return dae.saveAs(getTmpFile("Seymour_raw.dae").c_str(), docUri.c_str()) == DAE_OK;
}

DefineTest(loadSeymourRaw) {
	RunTest(saveSeymourRaw);
	
	DAE dae;
	string docUri = getTmpFile("Seymour_raw.dae");
	CheckResult(dae.load(docUri.c_str()) == DAE_OK);

	daeElement* el = 0;
	dae.getDatabase()->getElement(&el, 0, "l_hip_rotateY_l_hip_rotateY_ANGLE-input");
	CheckResult(el);
	return true;
}


DefineTest(extraTypeTest) {
	DAE dae;
	string docUri = lookupTestFile("extraTest.dae");
	CheckResult(dae.load(docUri.c_str()) == DAE_OK);

	daeElement* element = 0;
	dae.getDatabase()->getElement(&element, 0, 0, "technique");
	CheckResult(element);

	daeElementRefArray elements;
	element->getChildren(elements);

	// !!!steveT What exactly am I trying to test here?
	for (size_t i = 0; i < elements.getCount(); i++) {
		daeElement* e = elements[i];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		cout << "name: " << name << ", type: " << e->getTypeName() << "\n";
	}

	return true;
}

#if defined(TINYXML)
#include <dae/daeTinyXMLPlugin.h>
DefineTest(tinyXmlLoad) {
	auto_ptr<daeTinyXMLPlugin> tinyXmlPlugin(new daeTinyXMLPlugin);
	DAE dae(NULL, tinyXmlPlugin.get());
	char* docUri = lookupTestFile("Seymour.dae").c_str();
	CheckResult(dae.load(docUri) == DAE_OK);
	CheckResult(dae.saveAs(getTmpFile("Seymour_tinyXml.dae").c_str(), docUri) == DAE_OK);
	return true;
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

void resolveSid(const string& sid, daeElement* container) {
	daeSIDResolver sidResolver(container, sid.c_str());
	sidResolver.getElement();
	cout << "Attempting to resolve \"" << sid << "\": " << resolveResultToString(sidResolver.getState()) << endl;
}

DefineTest(sidResolveTest) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("sidResolveTest.dae").c_str()) == DAE_OK);

	daeElement* effect = 0;
	domAny* effectExtra = 0;
	dae.getDatabase()->getElement(&effect, 0, "myEffect");
	dae.getDatabase()->getElement((daeElement**)&effectExtra, 0, "effectExtra");
	CheckResult(effect && effectExtra);

	istringstream stream(effectExtra->getValue());
	string sid;
	while (stream >> sid)
		resolveSid(string("./") + sid, effect);

	daeElement* root = 0;
	domAny* nodeSidRefExtra = 0;
	dae.getDatabase()->getElement(&root, 0, 0, COLLADA_TYPE_COLLADA);
	dae.getDatabase()->getElement((daeElement**)&nodeSidRefExtra, 0, "nodeSidRefExtra");
	CheckResult(root && nodeSidRefExtra);

	cout << endl;
	stream.clear();
	stream.str(nodeSidRefExtra->getValue());
	while (stream >> sid)
		resolveSid(sid, root);

	return true;
}

daeElement* findChildByName(daeElement* el, daeString name) {
	if (!el)
		return 0;

	daeElementRefArray children;
	el->getChildren(children);

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

daeElement* resolveSid(daeString sid, daeElement& container) {
	daeSIDResolver sidResolver(&container, (string("./") + sid).c_str());
	return sidResolver.getElement();
}

string getCharData(daeElement* el) {
	return el ? el->getCharData() : "";
}

daeURI* getTextureUri(daeString samplerSid, domEffect& effect) {
	daeElement* sampler = findChildByName(resolveSid(samplerSid, effect), "sampler2D");
	string surfaceSid = getCharData(findChildByName(sampler, "source"));
	daeElement* surface = findChildByName(resolveSid(surfaceSid.c_str(), effect), "surface");
	domImage* image =
		daeSafeCast<domImage>(resolveID(getCharData(findChildByName(surface, "init_from")).c_str(),
																		*effect.getDocument()));
	if (image && image->getInit_from())
		return &image->getInit_from()->getValue();
	return 0;
}

DefineTest(getTexture) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("Seymour.dae").c_str()) == DAE_OK);

	daeElement* el = 0;
 	dae.getDatabase()->getElement(&el, 0, 0, COLLADA_TYPE_TEXTURE);
	domCommon_color_or_texture_type_complexType::domTexture* texture =
		daeSafeCast<domCommon_color_or_texture_type_complexType::domTexture>(el);
	CheckResult(texture);

	domEffect* effect = daeSafeCast<domEffect>(findAncestorByType(texture, COLLADA_TYPE_EFFECT));
	CheckResult(effect);

	daeURI* uri = getTextureUri(texture->getTexture(), *effect);
	CheckResult(uri);
	cout << uri->getURI() << endl;
	return true;
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

	CheckResult(dae.saveAs(getTmpFile("Seymour_removeElements.dae").c_str(),
												 lookupTestFile("Seymour.dae").c_str()) == DAE_OK);
	return true;
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

	// Now the DOM will crash
	daeElement::resolveAll();

	return true;
}


void nameArraySet(domListOfNames& names, size_t index, const char* name) {
	*(daeStringRef*)&names[index] = name;
}

void nameArrayAppend(domListOfNames& names, const char* name) {
	names.append(NULL);
	nameArraySet(names, names.getCount()-1, name);
}

DefineTest(nameArray) {
	DAE dae;
	CheckResult(dae.load(lookupTestFile("Seymour.dae").c_str()) == DAE_OK);

	daeElement* el = 0;
	dae.getDatabase()->getElement(&el, 0, 0, COLLADA_TYPE_NAME_ARRAY);
	domName_array* nameArray = daeSafeCast<domName_array>(el);
	CheckResult(nameArray);

	domListOfNames& names = nameArray->getValue();
	names.clear();
	nameArrayAppend(names, "name1");
	nameArrayAppend(names, "name2");
	nameArrayAppend(names, "name3");
	nameArray->setCount(names.getCount());
	for (size_t i = 0; i < names.getCount(); i++)
		cout << names[i] << "\n";
	
	return true;
}

template<typename T>
void printArray(const daeTArray<T>& array) {
	for (size_t i = 0; i < array.getCount(); i++)
		cout << array[i] << " ";
	cout << endl;
}

DefineTest(arrayOps) {
	// Test default array value suppression
	RunTest(renderStates);

	// Test Heinrich's original code that crashed
	RunTest(cloneCrash);

	// Test removeIndex
	daeTArray<int> array;
	for (size_t i = 0; i < 10; i++)
		array.append(i);
	printArray(array);
	array.removeIndex(4);
	printArray(array);

	// Test insert
	array.insertAt(4, 4);
	printArray(array);
	return true;
}


void printMemoryToStringResult(daeAtomicType& type, daeMemoryRef value) {
	ostringstream buffer;
	type.memoryToString(value, buffer);
	cout << buffer.str() << endl;
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

	printMemoryToStringResult(UIntType, (daeMemoryRef)&UInt);
	printMemoryToStringResult(IntType, (daeMemoryRef)&Int);
	printMemoryToStringResult(LongType, (daeMemoryRef)&Long);
	printMemoryToStringResult(ShortType, (daeMemoryRef)&Short);
	printMemoryToStringResult(ULongType, (daeMemoryRef)&ULong);
	printMemoryToStringResult(FloatType, (daeMemoryRef)&Float);
	printMemoryToStringResult(DoubleType, (daeMemoryRef)&Double);
	printMemoryToStringResult(StringRefType, (daeMemoryRef)&StringRef);
	//	printMemoryToStringResult(ElementRefType, (daeMemoryRef)&ElementRef);
	printMemoryToStringResult(EnumType, (daeMemoryRef)&Enum);
	printMemoryToStringResult(RawRefType, (daeMemoryRef)&RawRef);
	printMemoryToStringResult(ResolverType, (daeMemoryRef)&uri);
	printMemoryToStringResult(IDResolverType, (daeMemoryRef)&IDRef);
	printMemoryToStringResult(BoolType, (daeMemoryRef)&Bool);
	printMemoryToStringResult(TokenType, (daeMemoryRef)&Token);

	return true;
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

	return true;
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

	return true;
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
set<string> runTests(const set<string>& tests) {
	set<string> failedTests;
	for (set<string>::const_iterator iter = tests.begin(); iter != tests.end(); iter++) {
		cout << "Running " << *iter << endl;
		if (!g_tests[*iter]->run())
			failedTests.insert(*iter);
	}
	return failedTests;
}

void printTestResults(const set<string>& failedTests) {
	if (!failedTests.empty()) {
		cout << "Failed tests:\n";
		for (set<string>::const_iterator iter = failedTests.begin(); iter != failedTests.end(); iter++)
			cout << "  " << *iter << endl;
	} else {
		cout << "All tests passed.\n";
	}
}

struct tmpDir {
	fs::path path;
	
	tmpDir(fs::path& path) : path(path) {
		fs::create_directories(path);
	}

	~tmpDir() {
		fs::remove_all(path);
	}
};


int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << "Usage:\n"
			"  -printTests - Print the names of all available tests\n"
			"  -all - Run all tests\n"
			"  test1 test2 ... - Run the named tests\n";
		return 0;
	}

	// Shut the DOM up
	daeErrorHandler::setErrorHandler(&quietErrorHandler::getInstance());

	g_dataPath = (fs::path(argv[0]).branch_path()/"../../test/data/").normalize();
	g_tmpPath = g_dataPath / "tmp";
	tmpDir tmp(g_tmpPath);

	bool printTests = false;
	bool allTests = false;
	set<string> tests;
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "-printTests")
			printTests = true;
		else if (string(argv[i]) == "-all")
			allTests = true;
		else
			tests.insert(argv[i]);
	}

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

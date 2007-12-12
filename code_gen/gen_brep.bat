rem Copyright Sony Computer Ententainment Inc., 2007. 
rem All Rights Reserved.
rem CONFIDENTIAL INFORMATION

rem clear the old files
del .\gen\dom\include\*.h
del .\gen\dom\src\*.cpp

rem generate new code
bin\php gen.php "../brepdemo/COLLADA_DOM/doc/COLLADASchema_brep.xsd" cprt

rem clear the target code
del ..\brepdemo\collada_dom\src\1.4\dom\*.cpp
del ..\brepdemo\collada_dom\include\1.4\dom\*.h

rem copy the new code there
copy .\gen\dom\include\*.h ..\brepdemo\collada_dom\include\1.4\dom\
copy .\gen\dom\src\*.cpp ..\brepdemo\collada_dom\src\1.4\dom\

rem copy some mannually changed files from backup directory:
copy ..\brepdemo\collada_dom\include\1.4_backups\dom\domCommon_transparent_type.h ..\brepdemo\collada_dom\include\1.4\dom
copy ..\brepdemo\collada_dom\include\1.4_backups\dom\domFx_surface_common.h ..\brepdemo\collada_dom\include\1.4\dom
copy ..\brepdemo\collada_dom\src\1.4_backups\dom\domFx_surface_common.cpp ..\brepdemo\collada_dom\src\1.4\dom

rem update the new schema
copy ..\brepdemo\COLLADA_DOM\doc\COLLADASchema_brep.xsd C:\wguo\libxml2-2.6.28.win32\bin\
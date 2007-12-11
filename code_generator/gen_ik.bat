rem Copyright Sony Computer Ententainment Inc., 2007. 
rem All Rights Reserved.
rem CONFIDENTIAL INFORMATION

rem clear the old files
del .\gen\dom\include\*.h
del .\gen\dom\src\*.cpp

rem generate new code
bin\php gen.php "../ikdemo/COLLADA_DOM/doc/schema/COLLADASchema_ik.xsd" cprt

rem clear the target code
del ..\ikdemo\collada_dom\src\1.4\dom\*.cpp
del ..\ikdemo\collada_dom\include\1.4\dom\*.h

rem copy the new code there
copy .\gen\dom\include\*.h ..\ikdemo\collada_dom\include\1.4\dom\
copy .\gen\dom\src\*.cpp ..\ikdemo\collada_dom\src\1.4\dom\

rem copy some mannually changed files from backup directory:
copy ..\ikdemo\collada_dom\include\1.4_backups\dom\domCommon_transparent_type.h ..\ikdemo\collada_dom\include\1.4\dom
copy ..\ikdemo\collada_dom\include\1.4_backups\dom\domFx_surface_common.h ..\ikdemo\collada_dom\include\1.4\dom
copy ..\ikdemo\collada_dom\src\1.4_backups\dom\domFx_surface_common.cpp ..\ikdemo\collada_dom\src\1.4\dom
copy ..\ikdemo\collada_dom\src\1.4_backups\dom\domCamera.cpp ..\ikdemo\collada_dom\src\1.4\dom

rem update the new schema
copy ..\ikdemo\COLLADA_DOM\doc\schema\COLLADASchema_ik.xsd C:\wguo\libxml2-2.6.28.win32\bin\
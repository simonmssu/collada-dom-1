Copyright Sony Computer Ententainment Inc., 2007. 
All Rights Reserved.
CONFIDENTIAL INFORMATION

Code Generator USAGE

bin/php.exe gen.php schema [min] [cprt]

schema    filename of the COLLADA schema document
min       generate the minimal integration code (default is full)
cprt      generate the files using a full copyright instead of the snip comment

One thing to watch out for: use the php provided in the bin directory. Don't install the latest
php and try to use that. The latest php comes with a php.ini file whose settings are totally
incompatible with the code used in the DOM code generator. If you get tons of errors when you
run the code generator, it may be because php is using a php.ini file that's incompatible with
the code generator. Check C:\Program Files\PHP and delete php.ini if it's there. Be careful
though, as this will affect any other PHP programs as well.

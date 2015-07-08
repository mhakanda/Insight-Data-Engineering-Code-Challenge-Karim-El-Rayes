/****************************************************************/
/*	Insight Data Engineering - Coding Challenge         	*/
/*	Author: Karim El-Rayes				    	*/
/*	Document: README.md				    	*/
/*	Description: Instructions and guidelines for 	    	*/
/*	build and run of the coding challenge source files. 	*/
/*								*/
/****************************************************************/

Introduction:
-------------
- This project is in submission of "Insight Data Engineering - Coding Challenge".
- This code has been designed and developed in C language to provide maximum portability between different operating systems with minimum impact or changes on the code.
- This project has been developed under Microsoft Windows 8.1 operating system, slight changes might be required for build and run under any other operating systems, please refer to "insight_fellowship_src.cpp" source code file for details.

Included files and folders:
---------------------------
* Insight Fellowship Code Challenge.vcxproj : Visual Studio VC++ project file.
* Insight Fellowship Code Challenge.vcxproj.filters : Visual Studio VC++ filters file.
* insight_fellowship_src.cpp: Source code file.
* tweet_input (Directory): directory includes the input file.
* tweet_output (Directory): directory includes the output files of the project. 
* tweets.txt (in "tweet_input" directory): input file containing tweets to be processed.
* ft1.txt (in "tweet_output" directory): output file containing processed data for feature 1.
* ft2.txt (in "tweet_output" directory): output file containing processed data for feature 2.

Build and Run requirements:
---------------------------
- This project requires Microsoft Visual Studio VC++ tool to build and compile, Microsoft Visual Studio VC++ Express Edition is available for free from Microsoft website: https://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx
- Download and install Visual Studion VC++ express edition from the link mentioned previously.
- After installation is completed please double click "Insight Fellowship Code Challenge.vcxproj" project file to open it.
- Press "F5" on your keyboard to build and run the project.

Notes:
------
- The project creates "tweets_output" directory if it is not found.
- This project builds and run successfully on the following platforms:
* Microsoft Windows 8.1 operating system.
* Linux Raspbian operating system (kernel v3.18.16).
- To compile & build the source code under Linux just remove "#include <direct.h>" directive in the headers section, the source code is fully portable to any platform.
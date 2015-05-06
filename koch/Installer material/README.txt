Koch Curve  - readme.txt

© Horopter Inc. - 2015


How To Run "klin":
     Run "klin" using requirements ("--req"), zenity interface ("-z"), or Gtkdialog interface ("-g").  If
no option is specified, we default to zenity mode of interface.  Below is the general command:

	   ./klin -options



Files Includes With This Project:
	fractal.png	glc    		graph.out   	kgtk  koch.cpp  LICENSE      printw.h   zoom.cpp
	GL		graph.h		horopter.jpg	klin  kzen      LICENSE.txt  README.md
     



Design Decisions & Project Issues:
     We have implemented our kgtk and kzen as follows: Both execute from klin, the default script
and decides which interface to implement depending on availability, the zenity mode which is installed
in most linux systems by default or Gtkdialog mode which is available in most environments of linux.
In the cpp files, we have prompted user to close first window display in output to start the second one.
It avoids taking input multiple times and gives continuity of output. The zoom() function in koch.cpp is
different from zooming functions in zoom.cpp. The difference is that zoom() in koch.cpp is zoom to center
which serves no purpose in 2D implementation of koch curve but is  merely an academic exercise. 
	The counter position is adjusted according to size entered by the user in koch.cpp. The implementation
of zoom functions in zoom.cpp distorts the screen reshape in koch.cpp. The library of necessary GL headers
is provided by the software. klin in linux takes care of setting path. We must give credit to my friends at
ask.fedoraproject.org who have helped me in writing interface of 
the program and suggesting DCP setup maker for RAD tools. 



Profiling Results:
Yet to be created



Algorithm Analysis Results: 
Yet to be created.

	Included are the following screenshots:
		screenshot of Gtkdialog input interface    :
		screenshot of zenity input interface	   :
		screenshot of koch curve synthesis program :
		screenshot of koch curve analysis program  :

Console Whiteboard Poster {#mainpage}
=====================================
\tableofcontents

The MiPal infrastructure uses plain Makefiles that compile with BSD make. On Linux, you
therefore need to have installed bmake (see [Getting Started](http://docs.lab.mipal.net/GettingStarted.pdf)).
The Make infrastructure uses small makefiles for individual sub-projects
(such as the Whiteboard, CDL, the Nao robot software, etc.).
All software that is related to the robots should live in the corresponding subfolder underneath GUNao. However, none of the modules should live directly underneath GUNao (and no changes should be committed to legacy modules still there – they are just used for reference and files should be moved into their corresponding folders using git mv). The makefile fragments are inside is the `mk` folder in the hierarchy  This folder contains all the makefile fragments that are used for individual sub-projects. Here is where you should put your makefile to allow compiling and linking against your own sub-project.

# User-Visible Makefiles #



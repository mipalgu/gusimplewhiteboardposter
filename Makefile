#
#	$Id$
#
# GU whiteboard poster module Makefile
#
ALL_TARGETS=host atom atom1 geode analyse xc doc
CI_SERVER_DOC_SUBDIR=utils
CATKIN_COMPILE_UTIL=YES

.ifndef TARGET
USE_READLINE=yes
.else
SPECIFIC_CPPFLAGS+=-DWITHOUT_READLINE
.endif

CC_SRCS=gusimplewhiteboardposter.cc
HDRS=

NEW_WHITEBOARD_SRCS+=guwhiteboardgetter.cpp guwhiteboardposter.cpp

.include "../../mk/c++11.mk"
.include "../../mk/whiteboard.mk"	# required for whiteboard clients
.include "../../mk/mipal.mk"		# comes last!

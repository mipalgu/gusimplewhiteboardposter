#
#	$Id$
#
# GU whiteboard poster module Makefile
#
ALL_TARGETS=host robot analyse xc doc
CI_SERVER_DOC_SUBDIR=utils
CATKIN_COMPILE_UTIL=YES

USE_READLINE=yes

CC_SRCS=gusimplewhiteboardposter.cc
HDRS=

NEW_WHITEBOARD_SRCS+=guwhiteboardgetter.cpp guwhiteboardposter.cpp

.include "../../mk/c++11.mk"
.include "../../mk/whiteboard.mk"	# required for whiteboard clients
.include "../../mk/mipal.mk"		# comes last!

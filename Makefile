#
#	$Id$
#
# GU whiteboard poster module Makefile
#
BIN=gusimplewhiteboardposter

ALL_TARGETS=host robot

USE_READLINE=yes

CC_SRCS=gusimplewhiteboardposter.cc
HDRS=

NEW_WHITEBOARD_SRCS+=guwhiteboardgetter.cpp guwhiteboardposter.cpp

.include "../../mk/libcxx.mk"
.include "../../mk/whiteboard.mk"	# required for whiteboard clients
.include "../../mk/mipal.mk"		# comes last!

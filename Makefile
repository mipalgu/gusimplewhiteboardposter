#
#	$Id$
#
# GU whiteboard poster module Makefile
#
BIN=gusimplewhiteboardposter

WERROR=	# FIXME: needs fixing of the code generating the warnings

ALL_TARGETS=host robot

USE_READLINE=yes

CC_SRCS=gusimplewhiteboardposter.cc
HDRS=

NEW_WHITEBOARD_SRCS+=guwhiteboardgetter.cpp guwhiteboardposter.cpp

.include "../../mk/whiteboard.mk"	# required for whiteboard clients
.include "../../mk/mipal.mk"		# comes last!

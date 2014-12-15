#
#	$Id$
#
# GU whiteboard poster module Makefile
#
BIN=gusimplewhiteboardposter

ALL_TARGETS=host robot doc

USE_READLINE=yes

CC_SRCS=gusimplewhiteboardposter.cc
HDRS=

NEW_WHITEBOARD_SRCS+=guwhiteboardgetter.cpp guwhiteboardposter.cpp

WEB_SERVER_DIR=/Users/Shared/www/mipal.net
UTIL_DOC_DIR=${WEB_SERVER_DIR}/Docs/utils
BIN_DOC_DIR=${UTIL_DOC_DIR}/${BIN}

.if defined(IGNORE_RECURSIVE_JENKINS)
CI_EXTRA_COMMANDS=      
.else
CI_EXTRA_COMMANDS=                                                      \
        if [ -e ${WEB_SERVER_DIR} ] ; then				\
        	mkdir -p ${UTIL_DOC_DIR} ;				\
        	rm -rf ${BIN_DOC_DIR} ;					\
        	cp -R ${DOCUMENTATION} ${BIN_DOC_DIR} ;			\
	fi
.endif

.include "../../mk/c++11.mk"
.include "../../mk/whiteboard.mk"	# required for whiteboard clients
.include "../../mk/mipal.mk"		# comes last!

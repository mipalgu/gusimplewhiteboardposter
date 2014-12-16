Console Whiteboard Poster {#mainpage}
=====================================
\tableofcontents

The `gusimplewhiteboardposter` uses the readline library to offer a simple text-based
interface to the whiteboard.  All whiteboard messages that have proper string conversion
can be used with this tool.

# Usage #

`gusimplewhiteboardposter`

# Posting Messages #

The program will alternately prompt for a message type
(any message type defined in `guwhiteboardtypelist.tsl`
that has a valid sting constructor can be used) and
message content (the prompt for message content shows
the current value on the whieboard).
The message content needs to be entered in the exact format
required by the message `from_string()` parser for the
corresponding message type.

## Examples ##

    $ ./build.host/gusimplewhiteboardposter 
    msg type (SHUTDOWN_WHITEBOARD)? Say
    value ()? Hello
    msg type (Say)? XEyesPos
    value (0,0)? 100,50
    msg type (XEyesPos)? quit
    $

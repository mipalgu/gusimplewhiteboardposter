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


# Compiling #

### Building for the Host ###
To build the tool for the host use `bmake host`.
To install under `$PREFIX`, use `sudo bmake install`

### Building for a Target ###
To build the tool for the default target, simply use
`bmake robot`.
Alternatively, to build the tool for a different target, use
`bmake target TARGET=`*targetname*.

### Creating the ROS Makefile ###

In order to compile for ROS, you first need to
export the sources into `catkin_ws` for ROS using `bmake catkin`.

## ROS ##

To build the tool for ROS, make sure you have copied the
sources into `catkin_ws` as described above, then simply use
`catkin_make`.
To permanently install the tool, use `catkin_make install`.


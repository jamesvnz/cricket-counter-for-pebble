Cricket Counter For Pebble
==========================

A basic cricket umpire's counter app for Pebble. It saves taking an actual counter out! It can currently track balls, overs and wickets.

To reset the app state (for example, when a new innings starts), simply exit the app and restart it.

## Building

You will need the [Pebble SDK](http://developer.getpebble.com/) installed before building. At least version 1.12 is required. You'll also need to symlink the various bits and pieces the Pebble SDK requires to build into place, which is most easily done by changing into the top level project directory (ie where this file lives) and running:

    $PEBBLE_TOPLEVEL/Pebble/tools/create_pebble_project.py --symlink-only $PEBBLE_TOPLEVEL/Pebble/sdk .

Where `$PEBBLE_TOPLEVEL` is the location of the Pebble SDK (with Android and Pebble directories).

From there, you can use waf in the usual way:

    ./waf configure
    ./waf build

After that, get the pbw in the `build` directory to your phone paired with your Pebble, and install it to your watch.


Kid's Cricket Counter For Pebble
================================

A basic Kid's cricket umpire's counter app for Pebble. It saves taking an actual counter out! It can currently track balls, overs and wides/no balls.

This is a Fork of https://github.com/LawnGnome/cricket-counter-for-pebble which has been adapted to suit Kid's cricket.

This app enforces no more than 8 balls per over. Therefore once the number of no balls or Wides exceeds 2, it adds to the ball count.

The app will vibrate at the end of the over.

To reset the app state (for example, when a new innings starts), long press the wicket button (the middle button on the right).

## Building

You will need the [Pebble SDK](http://developer.getpebble.com/) installed before building. I've only tested the current version against SDK 2.3, although I suspect slightly older versions would also be OK.

It's a standard build from here, so:

    pebble build

Should get you a PBW to install.

Happy hacking!

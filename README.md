<pre>
 .__ __      __                   
 |__/  \    /  \_____ _______     The Intelligent Wardialer
 |  \   \/\/   /\__  \_  __ \     By Da Beave (dabeave@gmail.com / Twitter: @dabeave)
 |  |\        /  / __ \|  | \/    Copyright (C) 2005-2019
 |__| \__/\  /  (____  /__|       
           \/        \/ 

</pre>


![iWar Screenshot](https://github.com/beave/iwar/raw/master/screenshots/iwar-2.png)


__iWar - The unix 'Intelligent' war dialer.__

iWar is a Linux/Unix [wardialing tool](https://en.wikipedia.org/wiki/Wardialing) security tool 
used to audit the PSTN (public switched telephone network).  This version of iWar uses a
computers serial port and modem to "scan" phone numbers.

_Features_

- Nice "curses" front-end with color coded display (see below).
- Terminal window to display connection and communications with the modem.
- "Banner detection" and "recording" to assist with identification of connections.
- "Tone location" (aka - similar to "Toneloc") support via ATDT5551212W;
- Random [default] or sequentially dialing.
- "Key stroke" marking of "interesting" phone numbers.
- Full control over the modem.  iWar controls baud rate, parity, DTR, CTS/RTS, etc. 
- The ability to "save state" of the dialing session.  This allows you to stop/restart a war dialing session.
- A "blacklist" of phone numbers to never dial.
- The ability to load a pre-generated list of phone numbers. 
- iWar is open source and released under the GNU/GPLv2 license. 


__iWar command line arguments__

<pre>

Usage: iwar [parameters] --range [dial range]

 --help / -h 		:  Prints this screen
 --speed / -s 		:  Speed/Baud rate [Serial default: 1200]
 --parity / -p 		:  Parity (None/Even/Odd) [Default (N)one]
 --databits / -d 	:  Data bits [Serial default: 8]
 --device / -t 		:  TTY to use (modem) [Default /dev/ttyUSB0]
 --xonxoff / -c		:  Use software handshaking (XON/XOFF) [Default is hardware flow control]
 --log / -f 		:  Output log file [Default: iwar.log]
 --predial / -e 	:  Pre-dial string/NPA to scan [Optional]
 --postdial / -g 	:  Post-dial string [Optional]
 --tonedetect / -a 	:  Tone Location (Toneloc W; method) [Default: disabled]
 --range  / -r 		:  Range to scan (ie - 19045551212-19045551313)
 --sequential / -x 	:  Sequential dialing [Default: Random]
 --full-logging /-F 	:  Full logging (BUSY, NO CARRIER, Timeouts, Skipped, etc)
 --disable-banner / -b 	:  Disable banners check [Default: enabled]
 --disable-record / -o 	:  Disable recording banner data [Dfault: enabled].
 --load / -L 		:  Load numbers to dial from file.
 --load-state / -l 	:  Load 'saved state' file (previously dialed numbers)
 --config / -C          :  Load iWar configuration file.
 --random-time / -R     :  Sleep a random amount of time between dialing.

</pre>

__iWar keyboard assigments__

<pre>

 'a' or 'ESC'		: Abort wardialing and quit.
 'b'			: Enable terminal 'beep' on carrier discovery.
 '0'			: Turn off modem speaker during dialing.
 '1' - '3'		: Turn up/down modem speaker during dialing.
 '+'			: Add 5 seconds to the connection timer.
 '-'			: Subtract 5 seconds from the connection timer.
 's'			: Save dialing state.
 'q'			: Quite and save dialing state.
 'p'			: Pause dialing.

</pre>

__iWar hot key assignments__

<pre>

 'm'			: Mark number as 'interesting'.
 'c'			: Mark number as having a 'carrier'.
 'f'			: Mark number as a 'fax'.
 't'			: Mark number as having a 'tone'.
 'x'			: Mark number as a PBX.
 'v'			: Mark number as voicemail.
 '['			: Mark number as 'interesting' and pause the scan.
 'l'			: Mark number with a customer/user input note.

</pre>

__iWar terminal color coding assignments__

<pre>

 WHITE / A_NORMAL	: NO CARRIER
 YELLOW / A_BOLD	: BUSY
 GREEN / A_BLINK	: CONNECT
 BLUE / A_UNDERLINE	: VOICE
 WHITE / A_DIM		: NO ANSWER
 MAGENTA / A_NORMAL	: Already scanned (loaded from file).
 CYAN / A_REVERSE	: Blacklisted phone number.
 RED / A_NORMAL		: Number skipped by user via spacebar.
 GREEN / A_STANDOUT	: Manually marked.
 BLUE / A_STANDOUT	: Possible 'interesting' number (via Toneloc W;).

</pre>


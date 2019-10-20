<pre>
 .__ __      __                   
 |__/  \    /  \_____ _______     The Intelligent Wardialer
 |  \   \/\/   /\__  \_  __ \     By Da Beave (dabeave@gmail.com / Twitter: @dabeave)
 |  |\        /  / __ \|  | \/    Copyright (C) 2005-2019
 |__| \__/\  /  (____  /__|       
           \/        \/ 

</pre>

__iWar - The unix 'Intelligent' war dialer.__




__iWar command line arguments__

<pre>

Usage: iwar [parameters] --range [dial range]

 --help / -h 		:  Prints this screen
 --speed / -s 		:  Speed/Baud rate [Serial default: 1200]
 --parity / -p 		:  Parity (None/Even/Odd) [Default (N)one]
 --databits / -d 	:  Data bits [Serial default: 8]
 --device / -t 		:  TTY to use (modem) [Default /dev/ttyUSB0]
 --software / -c	:  Use software handshaking (XON/XOFF) [Default is hardware flow control]
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

</pre>




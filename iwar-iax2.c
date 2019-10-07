/*
** Copyright (C) 2005,2006 Softwink,  Inc. <beave@softwink.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"             /* From autoconf */
#endif


#ifdef HAVE_LIBIAXCLIENT

void iax2_list_devices( void );
#include <iaxclient.h>


void iax2_list_devices()
{
       struct iaxc_audio_device *devs;
       int nDevs, input, output, ring;
       int i;

       iaxc_audio_devices_get(&devs,&nDevs, &input, &output, &ring);
       for(i=0;i<nDevs;i++) 
       {
       fprintf(stderr, "DEVICE ID=%d NAME=%s CAPS=%x\n", devs[i].devID, devs[i] .name, devs[i].capabilities);
       }      
}

#endif


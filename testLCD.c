/*Command ScreenDetect
 * 
 * build commands
 * cc -Wall -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM  -I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I./  -c main.c -o main.o -Wno-deprecated-declarations -s -O2
 * cc -o screendetect -Wl,--whole-archive main.o -L/opt/vc/lib/ -lbcm_host -lvcos -lvchiq_arm  -Wl,--no-whole-archive -rdynamic
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include <string.h>

#include "interface/vmcs_host/vc_tvservice.h"

int main()
{
   VCHI_INSTANCE_T    vchi_instance;
   VCHI_CONNECTION_T *vchi_connection;

   // Initialize VCOS
   vcos_init();
  
//ret = 
  vchi_initialise( &vchi_instance );
   vchi_connect( NULL, 0, vchi_instance );

   // Initialize the tvservice
   vc_vchi_tv_init( vchi_instance, &vchi_connection, 1 );


   TV_DISPLAY_STATE_T tvstate;
   int ret = 2;
   if( vc_tv_get_display_state( &tvstate ) == 0) {
      if (tvstate.state & 1) ret = 1;
      else if (tvstate.state & 2) ret = 0;
      // fprintf(stderr,"%x\n", tvstate.state);
   }
   // Stop the tvservice

   vc_vchi_tv_stop();


   // Disconnect the VCHI connection

   vchi_disconnect( vchi_instance );


   exit( ret );

}

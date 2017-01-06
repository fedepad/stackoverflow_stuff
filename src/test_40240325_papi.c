#include <stdio.h>
#include <stdlib.h>
#include "papi.h" /* This needs to be included every time you use PAPI */
#include <unistd.h>

#define NUM_EVENTS 2
#define ERROR_RETURN(retval) { fprintf(stderr, "Error %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval); }

int main(int argc, char *argv[])
{

    if(argc<=1) {
        printf("Pid is not provided, I will die now :( ...\n");
        exit(1);
    }  //otherwise continue on our merry way....

    int EventSet = PAPI_NULL;
    int tmp, i;
    /*must be initialized to PAPI_NULL before calling PAPI_create_event*/

    long long values[NUM_EVENTS];
    /*This is where we store the values we read from the eventset */

    /* We use number to keep track of the number of events in the EventSet */
    int retval, number;

    char errstring[PAPI_MAX_STR_LEN];
    pid_t pid = atoi(argv[1]);

    int l2miss = PAPI_NULL;
    int data_all_from_l2 = PAPI_NULL;
    /*****************************************************************************
     ** This part initializes the library and compares the version number of the *
     ** header file, to the version of the library, if these don't match then it *
     ** is likely that PAPI won't work correctly.If there is an error, retval    *
     ** keeps track of the version number.                                       *
     ****************************************************************************/


    if((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT )
        ERROR_RETURN(retval);


    /* Creating the eventset */
    if ( (retval = PAPI_create_eventset(&EventSet)) != PAPI_OK)
        ERROR_RETURN(retval);


    /* Add Native event to the EventSet */
    //if ( (retval = PAPI_event_name_to_code("PM_DATA_FROM_L2MISS",&l2miss)) != PAPI_OK)    
    if ( (retval = PAPI_event_name_to_code("PAPI_L1_DCM",&l2miss)) != PAPI_OK)
        //         if ( (retval = PAPI_event_name_to_code("PM_L3_CO_MEM",&l2miss)) != PAPI_OK)
        ERROR_RETURN(retval);

    if ( (retval = PAPI_add_event(EventSet, l2miss)) != PAPI_OK)
        ERROR_RETURN(retval);
    /* Add Native event to the EventSet */
    //if ( (retval = PAPI_event_name_to_code("PM_DATA_ALL_FROM_L2",&data_all_from_l2)) != PAPI_OK)
    if ( (retval = PAPI_event_name_to_code("PAPI_L2_DCM",&data_all_from_l2)) != PAPI_OK) 
        ERROR_RETURN(retval);
    if ( (retval = PAPI_add_event(EventSet, data_all_from_l2)) != PAPI_OK)
        ERROR_RETURN(retval);

    /* get the number of events in the event set */
    number = 0;
    if ( (retval = PAPI_list_events(EventSet, NULL, &number)) != PAPI_OK)
        ERROR_RETURN(retval);
    printf("There are %d events in the event set\n", number);
    retval = PAPI_attach( EventSet, ( unsigned long ) pid );
    if ( retval != PAPI_OK )
        ERROR_RETURN(retval);


    /* Start counting */
    if ( (retval = PAPI_start(EventSet)) != PAPI_OK)
        ERROR_RETURN(retval);

    while(kill(pid,0)==0) {
        if ( (retval=PAPI_read(EventSet, values)) != PAPI_OK)
            ERROR_RETURN(retval);

        printf("The L2 Miss are %lld \n",values[0]);
        printf("The data_all_from_l2 are %lld \n",values[1]);
        sleep(1);
    }//while

    /* Stop counting and store the values into the array */
    if ( (retval = PAPI_stop(EventSet, values)) != PAPI_OK)
        ERROR_RETURN(retval);

    printf("Total L2 Miss are %lld \n",values[0]);
    printf("Total data_all_from_l2 are %lld \n",values[1]);
    /* free the resources used by PAPI */
    PAPI_shutdown();
    exit(0);

}

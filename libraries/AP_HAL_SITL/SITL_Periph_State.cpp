#include <AP_HAL/AP_HAL.h>

#if CONFIG_HAL_BOARD == HAL_BOARD_SITL && defined(HAL_BUILD_AP_PERIPH)

#include "AP_HAL_SITL.h"
#include "AP_HAL_SITL_Namespace.h"
#include "HAL_SITL_Class.h"
#include "UARTDriver.h"
#include "Scheduler.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>

#include <AP_Param/AP_Param.h>
#include <SITL/SIM_JSBSim.h>
#include <AP_HAL/utility/Socket.h>
#include <AP_HAL/utility/getopt_cpp.h>

extern const AP_HAL::HAL& hal;

using namespace HALSITL;

void SITL_State::init(int argc, char * const argv[]) {
    int opt;
    const struct GetOptLong::option options[] = {
        {"help",            false,  0, 'h'},
        {"instance",        true,   0, 'I'},
    };

    setvbuf(stdout, (char *)0, _IONBF, 0);
    setvbuf(stderr, (char *)0, _IONBF, 0);

    GetOptLong gopt(argc, argv, "hI:",
                    options);

    while((opt = gopt.getoption()) != -1) {
        switch (opt) {
            case 'I':
                _instance = atoi(gopt.optarg);
                break;
            default:
                printf("Options:\n"
                    "\t--help|-h                display this help information\n"
                    "\t--instance|-I N          set instance of SITL Periph\n");
                exit(1);
        }
    }

    printf("Running Instance: %d\n", _instance);
}

void SITL_State::wait_clock(uint64_t wait_time_usec) {
    while (AP_HAL::native_micros64() < wait_time_usec) {
        usleep(1000);
    }
}


int SITL_State::sim_fd(const char *name, const char *arg) {
    return 0;
}

int SITL_State::sim_fd_write(const char *name) {
    return 0;
}


#endif //CONFIG_HAL_BOARD == HAL_BOARD_SITL && defined(HAL_BUILD_AP_PERIPH)

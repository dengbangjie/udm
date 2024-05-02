//
// Created by dbj on 24-5-3.
//

#include "ocldevice.h"
#include "../udm.h"

typedef struct OCLDeviceContext_s {
    void *device_handle;
    void *compute_pipe;
    void *command_queue;
} OCLDeviceContext;


UDM_ERRORCODE OCLDeviceContext_Create(OCLDeviceContext *context, const char *device_name) {


    return kUDM_SUCCESS;
};

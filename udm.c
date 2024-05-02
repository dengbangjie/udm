#include "udm.h"
#include <stdio.h>
#include "udm_device.h"

UDM_ERRORCODE
UDM_MdArray_Alloc(UDM_MdArray *p, UDM_IP dim, UDM_ILP *shape, UDM_ALLOC_POLICY policy, void* device, UDM_TaskQueue *queue) {

    UDM_ILP total_size = 1;

    for (UDM_IP i = 0; i < dim; ++i) {
        total_size *= shape[i];
    }

    total_size = (total_size / 2 + 1) * 2;

    p->policy = policy;
    p->capacity = total_size;
    p->dim = dim;
    p->extends = calloc(dim, sizeof(UDM_ILP));

    for (int i = 0; i < dim; ++i) {
        p->extends[i] = shape[i];
    }

    if (policy & kUDM_ALLOC_HOST_MASK) {
        p->h_data = aligned_alloc(UDM_ALIGNED_SIZE, total_size * sizeof(UDM_FP));
    }

    if (policy & kUDM_ALLOC_DEVICE_MASK) {
    }

    if (p->h_data == NULL) {
        return kUDM_OUT_OF_MEMORY;
    }

    return kUDM_SUCCESS;
}

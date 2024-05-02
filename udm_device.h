//
// Created by dbj on 24-5-3.
//

#ifndef UDM_UDMDEV_H
#define UDM_UDMDEV_H

typedef enum UDM_DEVICE_TYPE_ENUM {
    kMutiCore = 0,
    kCUDA = 1,
    kOpenCL = 2
} UDM_DEVICE_TYPE;


typedef int (*calloc_dev_func)(uint64_t nelem, uint64_t size);

struct UDMDeviceContext {
    calloc_dev_func calloc_dev;
};

void UDMDeviceContext_CreateFactory(struct UDMDeviceContext *context, UDM_DEVICE_TYPE deviceType);


#endif //UDM_UDMDEV_H

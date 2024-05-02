#ifndef UDM_UDM_H
#define UDM_UDM_H

#include "stdint.h"
#include "string.h"
#include "assert.h"
#include "memory.h"
#include "stdlib.h"
#include "omp.h"

typedef double UDM_FP;
typedef int UDM_IP;
typedef uint64_t UDM_ILP;

static const int UDM_ALIGNED_SIZE = 64;

typedef enum UDM_ERRORCODE_ENUM {
    kUDM_SUCCESS = 0,
    kUDM_UNKNOWN_ERROR = -1,
    kUDM_OUT_OF_MEMORY = -2,
    kUDM_ERROR_LAST = -999,
} UDM_ERRORCODE;

typedef enum UDM_ALLOC_POLICY_ENUM {
    kUDM_ALLOC_HOST = 1,
    kUDM_ALLOC_DEVICE = 2,
    kUDM_ALLOC_BOTH = 3,
    kUDM_ALLOC_LAST = 999,
} UDM_ALLOC_POLICY;

static const int kUDM_ALLOC_HOST_MASK = 1 << 1;
static const int kUDM_ALLOC_DEVICE_MASK = 1 << 2;
static int kUDM_ALLOC_BOTH_MASK = kUDM_ALLOC_HOST_MASK | kUDM_ALLOC_DEVICE_MASK;


typedef struct UDM_TaskQueue_s {
    int task_id;
    void *context;
} UDM_TaskQueue;

struct UDM_DefaultMemory {
    UDM_ILP size;
    UDM_FP *__restrict data;
};

/**
 * UDM_MdArray_s is a struct that represents a multi-dimensional array.
 */
typedef struct UDM_MdArray_s {
    UDM_IP dim; // the number of dimensions
    UDM_ILP capacity; // the maximum size of the array
    UDM_ALLOC_POLICY policy; // the allocation policy
    UDM_ILP *extends; // the size of each dimension
    UDM_FP *__restrict h_data; // host data
    UDM_FP *__restrict d_data; // device data
} UDM_MdArray;


UDM_ERRORCODE
UDM_MdArray_Alloc(UDM_MdArray *__restrict p, UDM_IP dim, UDM_ILP *__restrict shape, UDM_ALLOC_POLICY policy,
                  void *device,
                  UDM_TaskQueue *queue);


#endif //UDM_UDM_H

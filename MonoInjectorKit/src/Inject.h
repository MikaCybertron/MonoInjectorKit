//
// Inject.h
// Created by MJ on 5/4/2019.
//

#ifndef INJECT_H
#define INJECT_H

#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "Utils.h"
#include "Mono.h"

using namespace Mono;

typedef enum {
    GET_DOMAIN_FAILED = 0,
    THREAD_ATTACH_FAILED = 1,
    FILE_STAT_FAILED = 2,
    FILE_READ_FAILED = 3,
    DATA_ALLOC_FAILED = 4,
    IMAGE_OPEN_FAILED = 5,
    ASSEMBLY_LOAD_FAILED = 6,
    CLASS_GET_FAILED = 7,
    METHOD_GET_FAILED = 8,
    SUCCESS = 9,
} Inject_Status;


struct Inject_Params {
    const char *dll_path;
    const char *image_name;
    const char *namespace_name;
    const char *class_name;
    const char *method_name;
};


extern "C" __attribute__ ((visibility ("default")))
Inject_Status InjectDLL(Inject_Params *params);

#endif //INJECT_H

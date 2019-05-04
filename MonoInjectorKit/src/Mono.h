//
// Mono.h
// Created by MJ on 5/4/2019.
//

#ifndef MONO_H
#define MONO_H

#include <dlfcn.h>
#include <string>
#include "Logger.h"
#include "Utils.h"

namespace Mono {

    typedef struct _MonoThread MonoThread;
    typedef struct _MonoImage MonoImage;
    typedef struct _MonoClass MonoClass;
    typedef struct _MonoMethod MonoMethod;
    typedef struct _MonoObject MonoObject;
    typedef struct _MonoProperty MonoProperty;
    typedef struct _MonoEvent MonoEvent;
    typedef struct _MonoDomain MonoDomain;
    typedef struct _MonoAssembly MonoAssembly;

    typedef enum {
        MONO_IMAGE_OK,
        MONO_IMAGE_ERROR_ERRNO,
        MONO_IMAGE_MISSING_ASSEMBLYREF,
        MONO_IMAGE_IMAGE_INVALID
    } MonoImageOpenStatus;

// 1- Domain //
    extern MonoDomain *(*mono_get_root_domain)(void);

// 2- Thread //
    extern MonoThread *(*mono_thread_attach)(MonoDomain *mDomain);

// 3- Image //
    extern MonoImage *(*mono_image_open_from_data_with_name)(char *data, uint32_t data_len,
            bool need_copy, MonoImageOpenStatus *status, bool refonly, const char *name);

// 4- Assembly //
    extern MonoAssembly *(*mono_assembly_load_from)(MonoImage *image, const char *fname,
            MonoImageOpenStatus *status);

// 5- Class //
    extern MonoClass *(*mono_class_from_name)(MonoImage *image, const char *name_space,
            const char *name);

// 6- Method //
    extern MonoMethod *(*mono_class_get_method_from_name)(MonoClass *mclass, const char *name,
            int param_count);

// finally invoke //
    extern MonoObject *(*mono_runtime_invoke)(MonoMethod *method, void *obj, void **params,
            MonoObject **exc);


    void initialize_exports();
};

#endif //MONO_H

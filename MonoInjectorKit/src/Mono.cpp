//
// Mono.cpp
// Created by MJ on 5/4/2019.
//

#include "Mono.h"

#define SET_MONO_FPTR(x, fptr) *(void **)(&fptr) = dlsym(x, #fptr)

namespace Mono {

// 1- Domain //
    MonoDomain *(*mono_get_root_domain)(void) = NULL;

// 2- Thread //
    MonoThread *(*mono_thread_attach)(MonoDomain *mDomain) = NULL;

// 3- Image //
    MonoImage *(*mono_image_open_from_data_with_name)(char *data, uint32_t data_len, bool need_copy,
                                                      MonoImageOpenStatus *status, bool refonly,
                                                      const char *name) = NULL;

// 4- Assembly //
    MonoAssembly *(*mono_assembly_load_from)(MonoImage *image, const char *fname,
            MonoImageOpenStatus *status) = NULL;

// 5- Class //
    MonoClass *(*mono_class_from_name)(MonoImage *image, const char *name_space,
            const char *name) = NULL;

// 6- Method //
    MonoMethod *(*mono_class_get_method_from_name)(MonoClass *mclass, const char *name,
            int param_count) = NULL;

// finally invoke //
    MonoObject *(*mono_runtime_invoke)(MonoMethod *method, void *obj, void **params,
            MonoObject **exc) = NULL;



    void initialize_exports() {
        void *mono = dlopen("libmono.so", RTLD_LAZY);
        if (!mono) {
            LOGD("%s", dlerror());
            return;
        }
        LOGD("Mono handle: %p", mono);

        SET_MONO_FPTR(mono, mono_get_root_domain);
        SET_MONO_FPTR(mono, mono_thread_attach);
        SET_MONO_FPTR(mono, mono_image_open_from_data_with_name);
        SET_MONO_FPTR(mono, mono_assembly_load_from);
        SET_MONO_FPTR(mono, mono_class_from_name);
        SET_MONO_FPTR(mono, mono_class_get_method_from_name);
        SET_MONO_FPTR(mono, mono_runtime_invoke);

        dlclose(mono);
    }
};
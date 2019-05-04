//
//  Inject.cpp
//
// Created by MJ on 5/4/2019.
//

#include "Inject.h"


Inject_Status InjectDLL(Inject_Params *params) {

    // initialize mono functions
    initialize_exports();

    // get root domain
    MonoDomain *domain = mono_get_root_domain();
    if (!domain) {
        return GET_DOMAIN_FAILED;
    }

    // attach to thread
    MonoThread *thread = mono_thread_attach(domain);
    if (!thread) {
        return THREAD_ATTACH_FAILED;
    }

    // get dll file info
    struct stat dllStat;
    if (!getFileStat(params->dll_path, &dllStat)) {
        return FILE_STAT_FAILED;
    }

    // map dll file into memory
    int sfd = open(params->dll_path, O_RDWR);
    if (sfd <= 0) {
        return FILE_READ_FAILED;
    }
    void *data = mmap(NULL, (size_t) dllStat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, sfd, 0);
    if (data == MAP_FAILED) {
        return DATA_ALLOC_FAILED;
    }


    // return mono image from mapped data
    MonoImage *image = mono_image_open_from_data_with_name((char *) data,
                                                           (uint32_t) dllStat.st_size,
                                                           false, NULL,
                                                           false,
                                                           params->image_name);
    if (!image) {
        return IMAGE_OPEN_FAILED;
    }

    // load dll from returned mono image
    MonoAssembly *assembly = mono_assembly_load_from(image, params->dll_path, NULL);
    if (!assembly) {
        return ASSEMBLY_LOAD_FAILED;
    }

    // find our class
    MonoClass *klass = mono_class_from_name(image, params->namespace_name, params->class_name);
    if (!klass) {
        return CLASS_GET_FAILED;
    }

    // find our method
    MonoMethod *method = mono_class_get_method_from_name(klass, params->method_name, 0);
    if (!method) {
        return METHOD_GET_FAILED;
    }

    // invoke our method
    mono_runtime_invoke(method, NULL, NULL, NULL);
    return SUCCESS;
}


// usage example
/*
 void inject_test() {
    Inject_Params params;
    params.dll_path = "/sdcard/mydll.dll";
    params.image_name = "mydll";
    params.namespace_name  = "mynamespace";
    params.class_name = "myclass";
    params.method_name = "mystaticmethod";
    InjectDLL(&params);
}
 */
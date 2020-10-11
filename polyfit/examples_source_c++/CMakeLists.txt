cmake_minimum_required(VERSION 3.16)
project(examples)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(examples
        main.cpp
        main.h
        polyfit_initialize.cpp
        polyfit_initialize.h
        polyfit_terminate.cpp
        polyfit_terminate.h
        rt_nonfinite.cpp
        rt_nonfinite.h
        rtGetNaN.cpp
        rtGetNaN.h
        polyfit_emxAPI.cpp
        polyfit_emxAPI.h
        polyfit.cpp
        polyfit.h
        rtGetInf.cpp
        rtGetInf.h
        polyfit_emxutil.cpp
        polyfit_emxutil.h
        std.cpp
        std.h
        xgeqrf.cpp
        xgeqrf.h
        xzlarf.cpp
        xzlarf.h
        xscal.cpp
        xscal.h
        mldivide.cpp
        mldivide.h
        xnrm2.cpp
        xnrm2.h
        polyfit_rtwutil.cpp
        polyfit_rtwutil.h
        colon.cpp
        colon.h
        xgeqp3.cpp
        xgeqp3.h
        qr.cpp
        qr.h
        xzlarfg.h
        xzlarfg.cpp


        )
include_directories(../)
# Enable FetchContent.
include(FetchContent)

# Knitro.
add_library(KnitroCpp_knitro INTERFACE)
target_include_directories(KnitroCpp_knitro INTERFACE
    "$ENV{KNITRODIR}/include")
target_link_directories(KnitroCpp_knitro INTERFACE
    "$ENV{KNITRODIR}/lib")
if(UNIX AND NOT APPLE)
    target_link_libraries(KnitroCpp_knitro INTERFACE
        knitro.so)
endif()
if(APPLE)
    target_link_libraries(KnitroCpp_knitro INTERFACE
        knitro.dylib)
endif()
if(WIN32)
    FILE(GLOB KNITROLIB $ENV{KNITRODIR}/lib/knitro*.lib)
    target_link_libraries(KnitroCpp_knitro INTERFACE
        ${KNITROLIB})
endif()
add_library(KnitroCpp::knitro ALIAS KnitroCpp_knitro)

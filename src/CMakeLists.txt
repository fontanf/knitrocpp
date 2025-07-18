add_library(KnitroCpp_knitrocpp INTERFACE)
target_include_directories(KnitroCpp_knitrocpp INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(KnitroCpp_knitrocpp INTERFACE
    KnitroCpp_knitro)
add_library(KnitroCpp::knitrocpp ALIAS KnitroCpp_knitrocpp)

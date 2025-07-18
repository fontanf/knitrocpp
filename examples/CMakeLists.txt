add_executable(KnitroCpp_hs15)
target_sources(KnitroCpp_hs15 PRIVATE
    hs15.cpp)
target_link_libraries(KnitroCpp_hs15 PUBLIC
    KnitroCpp_knitrocpp)
set_target_properties(KnitroCpp_hs15 PROPERTIES OUTPUT_NAME "knitrocpp_hs15")
install(TARGETS KnitroCpp_hs15)

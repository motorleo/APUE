add_executable(demoWebServer demoServer.cc)
target_link_libraries(demoWebServer ${muduo_net})
target_link_libraries(demoWebServer ${muduo_base})
target_link_libraries(demoWebServer pthread maxiaoda)

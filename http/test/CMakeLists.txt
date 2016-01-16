add_executable(Context_test ./Context_test.cc)
target_link_libraries(Context_test ${muduo_net})
target_link_libraries(Context_test ${muduo_base})
target_link_libraries(Context_test pthread maxiaoda)

add_executable(HttpServer_test ./HttpServer_test.cc)
target_link_libraries(HttpServer_test ${muduo_net})
target_link_libraries(HttpServer_test ${muduo_base})
target_link_libraries(HttpServer_test pthread maxiaoda)



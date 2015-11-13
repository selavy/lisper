# tst/

add_executable(
  unittest
  unittest.cpp
  )

add_custom_command(TARGET unittest POST_BUILD COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittest")
add_custom_target(tests "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittest" DEPENDS unittest COMMENT "Running tests...")

target_link_libraries(unittest ${Boost_LIBRARIES})
target_link_libraries(unittest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(unittest ${CPPUNIT_LIBRARIES})
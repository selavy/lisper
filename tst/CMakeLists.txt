# tst/

include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(
  unittest
  ../src/tokenize.cpp
  ../src/object.cpp
  ../src/number.cpp
  ../src/integer.cpp
  ../src/str.cpp
  ../src/boolean.cpp
  #BEGIN TESTS
  test_tokenize.cpp
  test_integer.cpp
  test_string.cpp
  test_boolean.cpp
  #END TESTS
  unittest.cpp
  )

add_custom_command(TARGET unittest POST_BUILD COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittest")
add_custom_target(tests "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittest" DEPENDS unittest COMMENT "Running tests...")

target_link_libraries(unittest ${Boost_LIBRARIES})
target_link_libraries(unittest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(unittest ${CPPUNIT_LIBRARIES})



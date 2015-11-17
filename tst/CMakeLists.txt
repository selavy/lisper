# tst/

include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(
  unittest
  ../src/parse_number.cpp
  ../src/tokenize.cpp
  ../src/object.cpp
  ../src/empty.cpp
  ../src/boolean.cpp
  test_parse_number.cpp
  test_tokenize.cpp
  test_types.cpp
  unittest.cpp
  )

add_custom_command(TARGET unittest POST_BUILD COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittest")
add_custom_target(tests "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittest" DEPENDS unittest COMMENT "Running tests...")

target_link_libraries(unittest ${Boost_LIBRARIES})
target_link_libraries(unittest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(unittest ${CPPUNIT_LIBRARIES})
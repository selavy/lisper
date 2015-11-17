# src/

add_executable(
  lisper
  parse_number.cpp
  tokenize.cpp
  object.cpp
  empty.cpp
  boolean.cpp
  main.cpp
  )

target_link_libraries(lisper ${Boost_LIBRARIES})
target_link_libraries(lisper ${CMAKE_THREAD_LIBS_INIT})
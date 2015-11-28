# src/

add_executable(
  lisper
  # parse_number.cpp
  tokenize.cpp
  object.cpp
  number.cpp
  integer.cpp
  abstract_syntax_tree.cpp
  object_factory.cpp
  # empty.cpp
  # boolean.cpp
  str.cpp
  # vec.cpp

  # symbol.cpp
  # procedure.cpp
  # primitive.cpp
  main.cpp
  )

target_link_libraries(lisper ${Boost_LIBRARIES})
target_link_libraries(lisper ${CMAKE_THREAD_LIBS_INIT})
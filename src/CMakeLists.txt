# src/

add_executable(
  lisper
  tokenize.cpp
  object.cpp
  number.cpp
  integer.cpp
  boolean.cpp  
  pair.cpp
  str.cpp
  symbol.cpp
  empty.cpp
  procedure.cpp
  primitive.cpp
  environment.cpp
  vec.cpp
  main.cpp
  )

target_link_libraries(lisper ${Boost_LIBRARIES})
target_link_libraries(lisper ${CMAKE_THREAD_LIBS_INIT})

add_library(gypsum gypsum.c stack.c)

# target_link_libraries(gypsum acid)

set_target_properties(gypsum PROPERTIES PUBLIC_HEADER "../include/gypsum.h")

install(TARGETS gypsum
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

add_executable(run main.c)
target_link_libraries(run gypsum acid ${CMAKE_THREAD_LIBS_INIT})
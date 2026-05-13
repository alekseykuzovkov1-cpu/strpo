# cобираем все .cpp файлы в папке src, кроме основного lab3.cpp
file(GLOB LIB_SOURCES "*.cpp")
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lab3.cpp")
# cоздаем статическую библиотеку
add_library(lab3_lib STATIC ${LIB_SOURCES})
# указываем, где искать заголовочные файлы
target_include_directories(lab3_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
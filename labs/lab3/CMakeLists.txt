cmake_minimum_required(VERSION 3.10)
project(DataStructures_Lab3)
# настройки стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# добавляем поддиректорию с исходниками библиотеки
add_subdirectory(src)
# сборка основного исполняемого файла
add_executable(lab3_app src/lab3.cpp)
# подключаем библиотеку к основному файлу
target_link_libraries(lab3_app PRIVATE lab3_lib)
# включаем поддержку тестирования
enable_testing()
add_subdirectory(test)
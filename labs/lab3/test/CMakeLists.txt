file(GLOB TEST_FILES "*.cpp")
foreach(test_file ${TEST_FILES})
    # получаем имя файла без расширения для названия цели
    get_filename_component(test_name ${test_file} NAME_WE)
    # создаем исполняемый файл для каждого теста
    add_executable(${test_name} ${test_file})
    # линкуем с основной библиотекой
    target_link_libraries(${test_name} PRIVATE lab3_lib)
    # добавляем в систему CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
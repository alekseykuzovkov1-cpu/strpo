# Лабораторная №6

## Ход работы

### 1. Базовые хуки в Git на стороне клиента

* **Git-хуки** -- это скрипты, которые автоматически запускаются системой контроля версий при наступлении определенных событий. Клиентские хуки выполняются на локальном компьютере разработчика и не переносятся в репозиторий при push (их нужно настраивать отдельно или использовать инструменты вроде Husky)

* Операции и этапы, к которым можно добавить код:

    * Рабочий процесс коммита (Committing-Workflow):
        * **pre-commit**: запускается перед тем, как будет введено сообщение коммита. Используется для проверки кода (линтинг, тесты, форматирование)

        * **prepare-commit-msg**: запускается перед созданием сообщения коммита, но после определения стандартного шаблона. Позволяет динамически изменять сообщение (например, вставлять номер задачи из ветки)

        * **commit-msg**: запускается после ввода сообщения пользователем. Позволяет проверять соответствие сообщения стандартам (например, Conventional Commits)

        * **post-commit**: запускается сразу после завершения процесса коммита. Обычно используется для уведомлений

    * Рабочий процесс электронной почты (Email Workflow):

        * **applypatch-msg**, **pre-applypatch**, **post-applypatch**: используются при работе с патчами (`git am`)

    * Другие клиентские операции:
        * **pre-rebase**: запускается перед началом операции `rebase`

        * **post-checkout**: срабатывает после успешного выполнения `git checkout` или `git switch`. Удобно для очистки временных файлов или настройки окружения

        * **post-merge**: запускается после успешного слияния веток (`merge`)

        * **pre-push**: запускается непосредственно перед отправкой данных на удаленный сервер (`git push`)

* Клиентские Git-хуки с возможностью прерывания операций:

    * `pre-commit`

        **Прерывает**: `git commit`

        **Применение**: проверка кода линтерами, запуск модульных тестов или поиск забытых отладочных данных (например, console.log или print). Если скрипт находит ошибки, коммит не будет создан

    * `prepare-commit-msg`

        **Прерывает**: `git commit`

        **Применение**: обычно используется для вставки шаблонов, но может остановить процесс, если не удается динамически сформировать сообщение (например, если скрипт не смог извлечь ID задачи из названия ветки)

    * `commit-msg`

        **Прерывает**: `git commit`

        **Применение**: валидация текста сообщения. Если комментарий не соответствует правилам (например, слишком короткий или не следует стандарту Conventional Commits), операция создания коммита прерывается

    * `pre-rebase`

        **Прерывает**: `git rebase`

        **Применение**: защита от изменения истории. Скрипт может запретить `rebase`, если пользователь пытается применить его к защищенным веткам (например, main) или к коммитам, которые уже были отправлены в общий репозиторий

    * `pre-push`

        **Прерывает**: `git push`

        **Применение**: финальный барьер перед отправкой кода на сервер. Здесь часто запускают тяжелые интеграционные тесты или проверяют код на наличие случайно оставленных секретов (паролей, ключей доступа)

    * `pre-applypatch`

        **Прерывает**: `git am`

        **Применение**: срабатывает после применения патча, но до того, как изменения будут зафиксированы. Позволяет проверить состояние рабочего дерева и отменить наложение патча, если оно нарушает целостность проекта

    * `pre-merge-commit`

        **Прерывает**: `git merge`

        **Применение**: вызывается при слиянии веток (если оно проходит без конфликтов) непосредственно перед созданием коммита слияния. Позволяет провести дополнительные проверки итогового состояния кода

[Источник](https://git-scm.com/book/ru/v2/Настройка-Git-Хуки-в-Git)

* Добавлен хук, который проверяет код, добавляемый в коммит, на предмет наличия запрещенных слов или паттернов

    * В файл "**pre-commit.sample**" (расширение нужно убрать для работы хука) из папки **.git/hooks** был добавлен следующий блок:

        ```
        PATTERNS="BEGIN (RSA|OPENSSH|DSA) PRIVATE KEY|password\s*=|token\s*=|TODO"

        # получаем список файлов в индексе
        STAGED_FILES=$(git diff --cached --name-only --diff-filter=d | grep -v '\.md$')

        for FILE in $STAGED_FILES; do
            # проверяем только добавленные строки в файле на наличие паттернов
            if git diff --cached "$FILE" | grep -qE "$PATTERNS"; then
                echo "В файле '$FILE' обнаружены потенциальные секреты или маркеры отладки!"
                git diff --cached "$FILE" | grep -nE "$PATTERNS"
                echo "Коммит отклонен. Удалите конфиденциальные данные!"
                exit 1
            fi
        done
        ```

    * Данный код защищает от случайного добавления SSH-ключей, SSL-сертификатов, паролей, токенов и TODO

    * Демонстрация работы хука:
        ![демо1](image.png)
        ![демо2](image-1.png)


* Добавлен хук, который проверяет сообщение коммита и останавливает процесс фиксации, если что-то не так с сообщением коммита

    * В файл "**commit-msg.sample**" (расширение нужно убрать для работы хука) из папки **.git/hooks** был добавлен следующий блок:
        ```
        COMMIT_MSG_FILE="$1"
        COMMIT_MSG=$(cat "$COMMIT_MSG_FILE")

        if [ ${#COMMIT_MSG} -lt 10 ]; then
            echo >&2 "Сообщение слишком короткое (минимум 10 символов)"
            exit 1
        fi
        ```

    * Данный код защищает от слишком короткого сообщения коммита

    * Демонстрация работа хука:
        ![демо3](image-2.png)


### 2. Хуки Git на стороне сервера
* Создание репозитория
    * Была создана копия моего репозитория на моем компьютере (уровнем выше рабочего репозитория strpo, на Рабочем столе):
        ```
        mkdir -p /C/Users/aleks/Desktop/strpo/server_repo.git
        cd /C/Users/aleks/Desktop/strpo/server_repo.git
        git init --bare
        ```
        * Использование ключа --bare критически важно для сервера, так как Git запрещает делать push в обычный репозиторий, если в нем открыта та же ветка

    * Копия была добавлена в качестве удаленного репозитория в мой основной репозиторий:
        ```
        cd ~/Desktop/strpo/reports
        git remote add local-server /C/Users/aleks/Desktop/strpo/server_repo.git
        ```

    * `push` в копию командой `git push local-server strpo-lab6` происходит успешно:
        ```
        aleks@DESKTOP-7T3I5UT MINGW64 ~/Desktop/strpo/reports (strpo-lab6)
        $ git push local-server strpo-lab6
        Enumerating objects: 119, done.
        Counting objects: 100% (119/119), done.
        Delta compression using up to 12 threads
        Compressing objects: 100% (102/102), done.
        Writing objects: 100% (119/119), 49.71 KiB | 1018.00 KiB/s, done.
        Total 119 (delta 25), reused 0 (delta 0), pack-reused 0 (from 0)
        remote: Resolving deltas: 100% (25/25), done.
        To C:/Users/aleks/Desktop/strpo/server_repo.git
        * [new branch]      strpo-lab6 -> strpo-lab6

        ```

* Был изучен вопрос конвертации Markdown в HTML

    * Для конвертации Markdown в HTML существует несколько подходящих способов:

        * Pandoc

            * **Pandoc** - мощный инструмент для конвертации документов. Он поддерживает практически все форматы

                **Команда**:
                ```
                pandoc lab6.md -o lab6.html
                ```
                **Стилизация**: флаг -s создает полноценный файл с тегами head и body:
                ```
                pandoc lab6.md -s -o lab6.html
                ```

        * VS Code

            1. Установить расширение "Markdown All in One" или "Markdown PDF"
            2. Открыть нужный .md файл
            3. Нажать `Ctrl + Shift + P` и ввести `Markdown: Export to HTML`

        Источники:
        1. [Официальное руководство VS Code по Markdown](https://code.visualstudio.com/docs/languages/markdown)
        2. [Pandoc](https://pandoc.org/)

* В моей копии был настроен хук, который будет создавать html-версию отчета из md-файла по последней версии из указанной ветки, а также проведет тестовый пуш

    * В папке **server_repo.git/hooks/** был создан серверный хук "**post-receive.sample**" (расширение нужно убрать для работы хука) со следующим содержанием:
        ```
        #!/bin/bash

        # настройки путей
        TARGET="/C/Users/aleks/Desktop/www"
        GIT_DIR="/C/Users/aleks/Desktop/server_repo.git"
        BRANCH="strpo-lab6"

        # создаем целевую папку, если ее нет
        mkdir -p $TARGET

        # выгружаем последнюю версию файлов из ветки strpo-lab6 в папку www
        git --work-tree=$TARGET --git-dir=$GIT_DIR checkout -f $BRANCH

        # конвертация Markdown в HTML
        FILE_MD="$TARGET/reports/lab6.md"
        FILE_HTML="$TARGET/reports/lab6.html"

        if [ -f "$FILE_MD" ]; then
            if command -v pandoc &> /dev/null; then
                pandoc "$FILE_MD" -s -o "$FILE_HTML"
                echo "Отчет успешно сконвертирован в HTML: $FILE_HTML"
            else
                echo "Pandoc не найден. Файлы обновлены, но HTML не создан"
            fi
        else
            echo "Файл $FILE_MD не найден для конвертации"
        fi
        ```
    * Выдача прав на выполнение:
        ```
        chmod +x /C/Users/aleks/Desktop/server_repo.git/hooks/post-receive
        ```
    * В ходе тестового пуша получаем html-файл, значит пуш прошел успешно, при изменениях html-файл успешно обновляется:
        ```
        git commit -m "тест конвертации"
        git push local-server strpo-lab6
        ```
        ![html](image-4.png)

### 3. Сборка с помощью CMake

* `CMake` — это не система сборки сама по себе, а генератор, который создает файлы для других систем (например, для Make или Visual Studio). Он позволяет описывать процесс сборки на языке высокого уровня

* Был установлен CMake с помощью команды ` winget install kitware.cmake`:
    ```
    winget install kitware.cmake
    Found CMake [Kitware.CMake] Version 4.3.2
    This application is licensed to you by its owner.
    Microsoft is not responsible for, nor does it grant any licenses to, third-party packages.
    Downloading https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-windows-x86_64.msi
    ██████████████████████████████  36.3 MB / 36.3 MB
    Successfully verified installer hash
    Starting package install...
    Successfully installed
    ```

* Основые понятия CMake (проекты, цели, библиотеки, исполняемые файлы), конструкции для работы с этими сущностями:

    * Основные понятия:

        * Проект (Project): это весь программный продукт. В одном проекте может быть несколько исполняемых файлов и библиотек

        * Цель (Target): это то, что CMake должен собрать. Основными целями являются либо исполняемый файл, либо библиотека. Почти все настройки в CMake (пути к заголовкам, зависимости) привязываются именно к конкретной цели

        * Исполняемый файл (Executable): финальная программа, которую можно запустить (например, main.exe)

        * Библиотека (Library): набор скомпилированного кода, который не запускается сам по себе, а используется другими целями. Бывают статическими (.lib, .a) и динамическими (.dll, .so)

    * Основные конструкции:

        * Для работы с этими сущностями используются следующие команды в файле `CMakeLists.txt`:

            1. Инициализация проекта
                ```
                #минимально необходимая версия CMake
                cmake_minimum_required(VERSION 3.10)

                #название проекта и версия
                project(MyDataStructuresProject VERSION 1.0)
                ```
            2. Создание сущностей

                `add_executable(name sources)`:	создает исполняемый файл из исходников

                `add_library(name TYPE sources)`: создает библиотеку. TYPE может быть STATIC или SHARED

            3. Работа с зависимостями

                `target_link_libraries(target private/public lib)`: связывает цель с библиотекой

                `target_include_directories(target type path)`: указывает, где искать заголовочные файлы для цели

    * Переменные и управление:

        * set(VAR_NAME value): создание переменной
        * ${VAR_NAME}: обращение к значению переменной
        * message("Text"): вывод отладочного сообщения в консоль при генерации

* Были переписаны цели сборки последней выполненной работы по "Структурам данных" c Make на CMake:

    * Был создан `CMakeLists.txt` в корневой папке проекта со следующим содержанием:
        ```
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
        ```

    * Был создан `src/CMakeLists.txt`, отвечающий за создание библиотеки из классов, со следующим содержанием:
        ```
        # cобираем все .cpp файлы в папке src, кроме основного lab3.cpp
        file(GLOB LIB_SOURCES "*.cpp")
        list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lab3.cpp")

        # cоздаем статическую библиотеку
        add_library(lab3_lib STATIC ${LIB_SOURCES})

        # указываем, где искать заголовочные файлы
        target_include_directories(lab3_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
        ```

    * Был создан `test/CMakeLists.txt`, отвечающий за сборку тестов, со следующим содержанием:
        ```
        # поиск всех файлов с тестами
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
        ```
* Демонстрация работы CMake:

    * Генерация файлов сборки
        ```
        cmake -B build
        -- Building for: Visual Studio 17 2022
        -- Selecting Windows SDK version 10.0.26100.0 to target Windows 10.0.26200.
        -- The C compiler identification is MSVC 19.44.35219.0
        -- The CXX compiler identification is MSVC 19.44.35219.0
        -- Detecting C compiler ABI info
        -- Detecting C compiler ABI info - done
        -- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64/cl.exe - skipped
        -- Detecting C compile features
        -- Detecting C compile features - done
        -- Detecting CXX compiler ABI info
        -- Detecting CXX compiler ABI info - done
        -- Check for working CXX compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64/cl.exe - skipped
        -- Detecting CXX compile features
        -- Detecting CXX compile features - done
        -- Configuring done (9.0s)
        -- Generating done (0.1s)
        -- Build files have been written to: C:/Users/aleks/Desktop/strpo/labs/lab3/build
        ```

    * Компиляция
        ```
        cmake --build build
        Версия MSBuild 17.14.23+b0019275e для .NET Framework

        1>Checking Build System
        Building Custom Rule C:/Users/aleks/Desktop/strpo/labs/lab3/src/CMakeLists.tx
        t
        basefile.cpp
        boolarray.cpp
        matrix.cpp
        mystring.cpp
        notifications.cpp
        notifications_oop.cpp
        notifications_priority_queue.cpp
        notificationsqueue.cpp
        workerdb.cpp
        Создание кода...
        lab3_lib.vcxproj -> C:\Users\aleks\Desktop\strpo\labs\lab3\build\src\Debug\la
        b3_lib.lib
        Building Custom Rule C:/Users/aleks/Desktop/strpo/labs/lab3/CMakeLists.txt
        lab3.cpp
        lab3_app.vcxproj -> C:\Users\aleks\Desktop\strpo\labs\lab3\build\Debug\lab3_a
        pp.exe
        Building Custom Rule C:/Users/aleks/Desktop/strpo/labs/lab3/test/CMakeLists.t
        xt
        test_priority.cpp
        test_priority.vcxproj -> C:\Users\aleks\Desktop\strpo\labs\lab3\build\test\De
        bug\test_priority.exe
        Building Custom Rule C:/Users/aleks/Desktop/strpo/labs/lab3/CMakeLists.txt
        ```

    * Запуск тестов
        ```
        cd build
        ctest -С Debug
        Test project C:/Users/aleks/Desktop/strpo/labs/lab3/build
            Start 1: test_priority
        1/1 Test #1: test_priority ....................   Passed    1.15 sec

        100% tests passed, 0 tests failed out of 1

        Total Test time (real) =   1.24 sec

        ```

### 4. Автоматизация задач CMake в git

* В репозиторий была добавлена ветка `dev`
    ```
    git checkout -b dev
    git push local-server dev
    ```

* Добавлен хук, который будет на каждый коммит в `dev` прогонять тесты CMake и обрывать коммит, если тесты не прошли

    * В папке **.git/hooks/** в хуки "**pre-commit.sample**" и "**pre-marge-commit.sample**" (расширение нужно убрать для работы хука) были добавлены следующие изменения:
        ```
        CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)

        if [ "$CURRENT_BRANCH" = "dev" ]; then
            echo "Запуск проверки сборки и тестов для ветки '$CURRENT_BRANCH'"

            ROOT_DIR=$(pwd)
            cd labs/lab3 || { echo "Ошибка: папка labs/lab3 не найдена!"; exit 1; }

            if [ ! -d "build" ]; then
                echo "Создание директории сборки..."
                cmake -B build > /dev/null || { echo "Ошибка конфигурации CMake"; cd "$ROOT_DIR"; exit 1; }
            fi

            # сборка проекта
            echo "Сборка проекта (Debug)..."
            cmake --build build --config Debug > /dev/null
            if [ $? -ne 0 ]; then
                echo "Ошибка: проект не собирается! Коммит отклонен"
                cd "$ROOT_DIR"
                exit 1
            fi

            # запуск тестов
            echo "Запуск тестов через CTest..."
            ctest --test-dir build -C Debug --output-on-failure --no-compress-output
                    
            RESULT=$?
            
            cd "$ROOT_DIR"

            if [ $RESULT -eq 0 ]; then
                echo "Успех: все тесты пройдены"
            else
                echo "Ошибка: тесты провалены! Коммит отклонен"
                exit 1
            fi
        fi
        ```

* Были проведены тесты хуков:
    * Случай обычного коммита в `dev`:
        ![проверка коммита](image.png)
    * Случай `merge`:
        ![проверка слияния](image-1.png)

* Был добавлен хук для сборки библиотеки по коммиту в `dev`:
    * Код, который мы добавляли в позапрошлом пункте в хуки "**pre-commit.sample**" и "**pre-marge-commit.sample**" (расширение нужно убрать для работы хука), был подредактирован для сборки библиотеки по коммиту:
        ```
        CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)

        if [ "$CURRENT_BRANCH" = "dev" ]; then
            echo "Запуск проверки сборки и тестов для ветки '$CURRENT_BRANCH'"

            ROOT_DIR=$(pwd)
            cd labs/lab3 || { echo "Ошибка: папка labs/lab3 не найдена!"; exit 1; }

            if [ ! -d "build" ]; then
                echo "Создание директории сборки..."
                cmake -B build > /dev/null || { echo "Ошибка конфигурации CMake"; cd "$ROOT_DIR"; exit 1; }
            fi
            
            # НОВЫЙ КОД!!!
            echo "Сборка библиотеки lab3_lib (Debug)..."
            cmake --build build --config Debug --target lab3_lib > /dev/null
            if [ $? -ne 0 ]; then
                echo "Ошибка: библиотека не собирается! Коммит отклонен"
                cd "$ROOT_DIR"
                exit 1
            fi
            # НОВЫЙ КОД!!!

            # сборка проекта
            echo "Сборка проекта (Debug)..."
            cmake --build build --config Debug > /dev/null
            if [ $? -ne 0 ]; then
                echo "Ошибка: проект не собирается! Коммит отклонен"
                cd "$ROOT_DIR"
                exit 1
            fi

            # запуск тестов
            echo "Запуск тестов через CTest..."
            ctest --test-dir build -C Debug --output-on-failure --no-compress-output
                    
            RESULT=$?
            
            cd "$ROOT_DIR"

            if [ $RESULT -eq 0 ]; then
                echo "Успех: библиотека собрана, все тесты пройдены"
            else
                echo "Ошибка: тесты провалены! Коммит отклонен"
                exit 1
            fi
        fi
        ```

### 5. Автоматизация с помощью Github Actions

* Основной синтаксис языка YAML и конструкции, которые можно задать этим языком
    * ***Синтаксис***:

        **YAML (Yet Another Markup Language / YAML Ain't Markup Language)** — это простой текстовый формат для конфигурационных файлов. Он человекочитаем и не использует скобки или теги. Вместо этого структура задается отступами

        **Основные правила синтаксиса**:

        1. Чувствительность к отступам: отступы определяют вложенность (структуру). Используются только пробелы (обычно по 2 или 4 пробела). Табуляции (\t) запрещены - они сломают парсер
        2. Регистрозависимость: ключи build и Build - это разные ключи
        3. Символ `:`: ключ и значение разделяются двоеточием с обязательным пробелом после него (key: value)
        4. Комментарии: начинаются с символа #
    
    * ***Конструкции***:
        1. **Cловари (Пары Ключ-Значение)**:
            ```
            project: lab3
            language: cpp
            ```
        2. **Списки (Массивы)**: задаются дефисом с пробелом:
            ```
            branches:
              - main
              - dev
            ```
        3. **Вложенные структуры (Объекты)**:
            ```
            compiler:
              name: gcc
              version: 11
            ```
        4. **Многострочные строки**: если нужно написать многострочный скрипт bash (как в наших хуках), используются символы | (сохраняет переносы строк) или > (склеивает строки в одну):
            ```
            script: |
              cmake -B build
              cmake --build build
            ```
    
* Основные возможности Github Actions и тарифы, доступные для использования
    
    * ***Основные возможности GitHub Actions***:

        **GitHub Actions** — это встроенная система CI/CD от GitHub, которая позволяет автоматизировать сборку, тестирование и деплой кода прямо в репозитории

        **Ключевые понятия**:
        * **Workflow**: автоматизированная процедура, которая описывается в YAML-файле в папке .github/workflows/
        * **Events**: триггеры, которые запускают воркфлоу (например: push в ветку dev, создание pull request, или запуск по расписанию)
        * **Jobs**: набор шагов, выполняемых на одном виртуальном сервере. По умолчанию задачи выполняются параллельно
        * **Steps**: конкретные команды. Это может быть запуск скрипта в консоли (run) или готовый плагин из маркетплейса GitHub (uses)
        * **Runners**: виртуальные машины, на которых крутится код. GitHub предоставляет на выбор сервера с Linux (Ubuntu), Windows Server и macOS
    
    * ***Тарифные планы GitHub Actions***:

        GitHub предоставляет Actions на всех тарифных планах, но с разным количеством бесплатных минут и ресурсов. Для публичных репозиториев GitHub Actions абсолютно бесплатны всегда и без ограничений по минутам.

        Для приватных репозиториев действуют следующие тарифы (квоты обновляются каждый месяц):

        * **GitHub Free**: 2000 CI/CD минут в месяц, 0$ за пользователя в месяц, 500 МБ объём хранилища артефактов
        * **GitHub Pro**: 3000 CI/CD минут в месяц, 4$ за пользователя в месяц, 1 ГБ объём хранилища артефактов
        * **GitHub Team**: 10000 CI/CD минут в месяц, 4$ за пользователя в месяц, 2 ГБ объём хранилища артефактов
        * **GitHub Enterprice**: 50000 CI/CD минут в месяц, 21$ за пользователя в месяц, 50 ГБ объём хранилища артефактов
    

    Источники: 
    * [Официальный сайт и спецификация YAML](https://yaml.org/)
    * [Understanding GitHub Actions](https://docs.github.com/en/actions/get-started/understand-github-actions?versionId=free-pro-team%40latest&productId=actions)
    * [Справочник по синтаксису Workflow](https://docs.github.com/en/actions/reference/workflows-and-actions/workflow-syntax)
    * [Тарифы GitHub](https://github.com/pricing)

* Добавление в репозиторий в Github определения ci-cd пайплайнов для автоматизации задач CMake из прошлого раздела
    * на ветке `dev` была создана папка `.github` с папкой `workflows` внутри. В папке `workflows` был создан файл `cmake-ci.yml` со следующим содержанием:
        ```
        name: CMake CI/CD Pipeline

        # пайплайн запускается при каждом пуше или мерже в ветку dev
        on:
          push:
            branches: [ "dev" ]
          pull_request:
            branches: [ "dev" ]

        jobs:
          build-and-test:
            # использование виртуальной машины на Windows с предустановленным MSVC и CMake
            runs-on: windows-latest

            steps:
            # клонируем репозиторий на удаленный сервер GitHub
              - name: Checkout repository
                uses: actions/checkout@v4

            # настраиваем окружение CMake и генерируем файлы сборки
            # так как CMakeLists.txt лежит в labs/lab3, явно указываем рабочую директорию
              - name: Configure CMake
                run: cmake -B build
                working-directory: labs/lab3

            # изолированная сборка только библиотеки lab3_lib
              - name: Build Library (lab3_lib)
                run: cmake --build build --config Debug --target lab3_lib
                working-directory: labs/lab3

            # полная сборка проекта (включая исполняемый файл тестов)
              - name: Build Entire Project
                run: cmake --build build --config Debug
                working-directory: labs/lab3

            # автоматический прогон тестов через CTest
              - name: Run Tests
                run: ctest --test-dir build -C Debug --output-on-failure
                working-directory: labs/lab3        
        ```
    
    * После пуша в репозиторий результат показывается во вкладке Actions на странице проекта в GitHub
        ![actions](image-2.png)

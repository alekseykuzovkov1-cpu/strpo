# Лабораторная №1

## Ход работы

### 1. Установка и настройка:
#### 1.1. Установка Git
        ``apt install git
#### 1.2. Настройка пользовательских данных:
        ```
        git config --global user.name "aleksey"
        git config --global user.email "aleksey.kuzovkov1@gmail.com"
        ```
### 2. Начало работы с новым проектом
#### 2.1. Создание директории для проекта и репозитория
        ```
        mkdir C:/Users/aleks/Desktop/strpo
        git init
        ```
#### 2.2. Создание README.md, директории reports и файла reports/lab1.md
        ```
        touch README.md
        mkdir reports
        touch reports/lab1.md
        ```
#### 2.3. Добавление информации в README.md
#### 2.4. Коммит с файлами README.md и reports/lab1.md
        ```
        git commit -m "добавлены README.md и lab1.md"
        ```
### 3. Отслеживание состояния кода
#### 3.1. Выполнение команды git status и git diff
        ```
        git status показывает текущее состояние рабочей директории и области подготовленных файлов
        git diff показывает разницу между изменениями в файлах. Без аргументов показывает незакоммиченные изменения
        ```
#### 3.2. Повторное выполнение команд
        ```
        git status показывает, что файл reports/lab1.md был изменен
        git diff показывает заметки, которые мы перенесли в тот файл
        ```
#### 3.3. Добавление изменения в файле отчета в индекс
        ```
        git status пкоазывает, что файл lab1.md был изменен и эти изменения готовы для коммита 
        ```
### 4. Откат изменений
#### 4.1. Откат изменений в README.md с помощью git restore
        ```
        git restore README.md
        ```
#### 4.2. Выполнение команды git status после удаления lab1.md
        ```
        git status показывает, что lab1.md был удалён
        ```
#### 4.3. Восстановление файла lab1.md с помощью git restore
        ```
        git restore reports/lab1.md
        ```
### 5. Ветвление версий
#### 5.1. Создание новой ветки lab1-1 и переключение на нее
        ```
        git branch lab1-1
        git checkout lab1-1
        ```
#### 5.2. Переключение на ветку lab1-1 после изменения README.md
        ```
        переключение не произошло, т.к. Git защищает нас от потери незакоммиченных изченений 
        ```
### 6. Слияние веток, конфликты
#### 6.1. Откат изменений в README.md
        ```
        git restore README.md
        ```
#### 6.2. Слияние ветки master с lab1-1
        ```
        git merge lab1-1
        ```
#### 6.3. Коммит изменений lab1-1
        ```
        ошибка слияния, т.к. файл изменен в обеих ветках в одном и том же месте и Git не знает, что выбрать
        ```
#### 6.4. Разрешение конфликтов и коммит
        ```
        удаляем изменение заголовка в README.md в одной из веток
        ```
#### 6.5. Удаление ветки lab1-1
        ``git branch -d lab1-1
### 7. Работа с удаленным репозиторием
#### 7.1. Добавление SSH ключа и его конфигурация
        ``ssh-keygen -o
#### 7.2. Добавление удаленного репозитория
        ``git remote add
#### 7.3. Отправка данных из локального репозитория в удаленный
        ``git push
### 8. Синхронизация с удаленным репозиторием
#### 8.1. Создание папки вне репозитория
        ``создаем папку strpo1
#### 8.2. Получение копии репозитория в папке strpo1
        ``git clone  https://github.com/alekseykuzovkov1-cpu/strpo.git
#### 8.3. Добавление протоколов в отчет и коммит
        ``git add .
        ```git commit -m "последний коммит"
#### 8.4. Запрос изменений из удаленного репозитория с помощью `git fetch`
        ```
        remote: Enumerating objects: 5, done.
        remote: Counting objects: 100% (5/5), done.
        remote: Compressing objects: 100% (3/3), done.
        remote: Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
        Unpacking objects: 100% (3/3), 320 bytes | 32.00 KiB/s, done.
        From https://github.com/alekseykuzovkov1-cpu/strpo
        `git fetch`скачивает изменения, но не применяет их рабочим файлам
        ```
#### 8.5. Синхронизация содержимого репозитория для основной ветки с git pull
        ```
        git pull origin master
        ```
### 9. История изменений
        ```
        git log
        commit 88ab390853dc750f9cf3073485aaf472f3591b1e (HEAD -> master, origin/master, origin/HEAD)
        Merge: 52367cb 5334b1a
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Fri Mar 6 12:26:49 2026 +0300

                исправление конфликта

        commit 52367cb0255017f1ca2c26361582dc2066c7e2a4
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Fri Mar 6 12:21:11 2026 +0300

                добавбление информации в отчет

        commit 5334b1a5e3b81a1a519e2c96b5fb4414605ef661
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Tue Mar 3 15:26:31 2026 +0300

                последний коммит

        commit 2afc153fa3e06331bc123b0effcbbadb122f07ad
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Sat Feb 28 00:17:25 2026 +0300

                коммит пункта

        commit 48fedea802eb958202ad826a780b67317df1e4a2
        Merge: fe73e7a b804943
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Sat Feb 28 00:05:14 2026 +0300

                слияние ветки 'lab1-1'

        commit b804943ef50f204b00380a242f4ff64d08483180
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Fri Feb 27 23:16:07 2026 +0300

        коммит изменений в lab1-1

        commit fe73e7a2e3e65d4bdadf586c209a019f2983a7fe
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Fri Feb 27 23:11:28 2026 +0300

        изменение readme в master

        commit 5d5d4637b375226baf4de4f95f113641a3f91613
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Fri Feb 27 23:07:04 2026 +0300

        изменение в ветке lab1-1

        commit 4968511eb8bf12728353084552943bf25ed3f2ab
        Author: aleksey <aleksey.kuzovkov1@gmail.com>
        Date:   Fri Feb 27 22:30:32 2026 +0300

        сохранение изменений перед переходом в master
        ```

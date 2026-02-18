# Лабораторная №1

## Ход работы

### 1. Установка и настройка:
#### 1.1. Установка Git
        ``apt install git
#### 1.2. Настройка пользовательских данных:
        ``git config --global user.name "aleksey"
        ```git config --global user.email "aleksey.kuzovkov1@gmail.com"
### 2. Начало работы с новым проектом
#### 2.1. Создание директории для проекта и репозитория
        ``mkdir C:/Users/aleks/Desktop/strpo
        ```git init
#### 2.2. Создание README.md, директории reports и файла reports/lab1.md
        ``touch README.md
        ```mkdir reports
        ```touch reports/lab1.md
#### 2.3. Добавление информации в README.md
#### 2.4. Коммит с файлами README.md и reports/lab1.md
        ``git commit -m "добавлены README.md и lab1.md"
### 3. Отслеживание состояния кода
#### 3.1. Выполнение команды git status и git diff
        ``git status показывает текущее состояние рабочей директории и области подготовленных файлов
        ```git diff показывает разницу между изменениями в файлах. Без аргументов показывает незакоммиченные изменения
#### 3.2. Повторное выполнение команд
        ``git status показывает, что файл reports/lab1.md был изменен
        ```git diff показывает заметки, которые мы перенесли в тот файл
#### 3.3. 
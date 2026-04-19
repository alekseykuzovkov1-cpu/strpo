# Лабораторная №2

## Ход работы

### 1. Подготовка репозитория
#### 1.1. Создание папки `labs` и добавление кода лабораторной
Была создана папка `labs` и `lab1` внутри, добавлен код первой и второй лабораторных работ по "Структурам данных"
#### 1.2. Значение и принцип работы `.gitignore` 
* `.gitignore` — это специальный файл в git, который указывает, какие файлы и директории следует намеренно игнорировать и не добавлять в репозиторий. Предотвращает попадание ненужных файлов в систему контроля версий, однако работает только с файлами, которые еще не были добавлены в Git (`git add`). Если файл уже отслеживается, .gitignore на него не действует
#### 1.3. Добавление `.gitignore` и его настройка
```
nano .gitignore
```
Содержимое `.gitignore`:
```
# игнорировать файлы сборки
*.o
*.d
*.exe
*.out
build/
obj/
.vscode/
```
#### 1.4. Коммит изменений и пуш в удаленный репозиторий
```
git commit -m "коммит .gitignore"
git push origin master
```
### 2. Защита веток
#### 2.1. Возможности защиты веток
* Защита веток — это механизм GitHub, который позволяет установить правила для важных веток репозитория (например, `main` или `master`), чтобы предотвратить случайные или неавторизованные изменения и обеспечить контроль качества кода.
* Основные возможности:
    - Запрет прямых отправок - блокирует возможность напрямую отправлять изменения в защищенную ветку. Все изменения должны проходить через pull request
    - Требование проверок:
        + Утверждения — необходимо указанное количество одобрений от рецензентов
        + Отклонение устаревших утверждений — если после утверждения в PR добавлены новые коммиты, утверждение сбрасывается
        + Последний проверяемый push — требует, чтобы последние изменения были одобрены кем-то, кроме автора
#### 2.2. Защита ветки `master`
Через настройки репозитория были выставлены следующие параметры для ветки `master`:
- Block force pushes - запретить force push
- Restrict deletions - запретить удаление ветки
- Require a pull request before merging - требовать pull request
    + Require approvals - 0 (чтобы смочь принять самому)
#### 2.3. Проверка защиты
```
echo "тест защиты" > test-protection.txt
git add test-protection.txt
git commit -m "добавление файла из ветки pr-test"
git push origin master
```
Выполнение последней команды даёт следующий вывод:
```
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 12 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 326 bytes | 326.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
remote: error: GH013: Repository rule violations found for refs/heads/master.
remote: Review all repository rules at https://github.com/alekseykuzovkov1-cpu/strpo/rules?ref=refs%2Fheads%2Fmaster
remote:
remote: - Changes must be made through a pull request.
remote:
To https://github.com/alekseykuzovkov1-cpu/strpo.git
 ! [remote rejected] master -> master (push declined due to repository rule violations)
error: failed to push some refs to 'https://github.com/alekseykuzovkov1-cpu/strpo.git'
```
Из этого следует, что защита работает исправно
#### 2.4. Создание новой ветки `pr-test` из основной
```
git checkout -b pr-test
```
### 3. Запросы на слияние
#### 3.1. Добавление изменений в ветку pr-test и отправка их в удаленный репозиторий
* Были добавлены новые пункты в отчёт
```
git add .
git commit -m "пуш из новой ветки"
git push origin pr-test
```
#### 3.2. Слияние через `pull request`
Через web-интерфейс GitHub был создан запрос на слияние (`pull request`) ветки pr-test с основной, после чего собственноручно принят. Слияние прошло успешно
#### 3.3. Принятие последних обновлений основной ветки
```
git checkout master
git pull origin master
```
### 4. Pull Request

#### 4.1. Выполнение лабораторной работы №2 по Структурам Данных
* За время выполнения лабораторной было сделано 6 коммитов
#### 4.2. Отправка PR

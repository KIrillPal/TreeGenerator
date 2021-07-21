# TreeGenerator
Это учебный проект по сжатию текстов с помощью деревьев Хаффмана. У него есть следующие возможности:
- создавать, сохранять и загружать деревья
- кодировать и декодировать тексты
- работать с информацией в консоли и в файлах

Проект написан на C++ в Visual Studio.
# Подключение и использование
Чтобы запустить приложение, скачайте файл [Release.exe](https://github.com/KIrillPal/TreeGenerator/blob/main/Release.exe) из корня проекта и запустите. 
Откроется консоль. В ней заранее отображается список команд. Подробно о них будет рассказано ниже. 

Команды, требующие ввод, могут просить ввести текст в консоль или открывать файловый диалог для выбора текстового файла. Их поведение зависит от "файлового режима", т.е. режима, 
в котором программа вводит и выводит информацию. Файловый режим изменется с помощью команды `f`, т.е. если команда `g` просит дать ей строку текста, 
то после выполнения команды `f` она будет просить текстовый файл.
# Список команд и структура проекта
Единственный файл проекта - TreeGenerator.cpp.
Всё взаимодействие с консолью ведется через функцию main. Чтение файлов выполняет функция `openFileDialog`.
## Дерево символов
Клчевую роль в работе программы имеет сгенерированное или загруженное из файла дерево символов. На его основе производится кодирование и декодирование кода. Создаётся таблица символов. 
Дерево хранится в виде списка чисел и имеет следующий формат. Кадое число описывает состояние какой-то вершины дерева. Если число - 0, то у вершины есть 2 предка, иначе - это лист. Например, если дерево записано так: `0 99 0 97 98`, 
то первый 0 - показывает состояние корня, т.е. что он не являтся листом. Затем 99 - левый предок корня, т. к. идёт сразу за ним. 99 - лист с кодом буквы 'c'. Затем правый предок корня. Он тоже не лист. Затем 2 его потомка: буквы 'a' и 'b'.

В любой момент времени в программе существует только один экземпляр дерева Хаффмана. Он же будет использоваться для кодирования и декодирования. 
Приведём список команд с описанием и связанными функцями.
## 1. "g" - Генерация дерева Хаффмана
Программа просит на вход строку текста или текстовый файл. Затем по всем симолам строится дерево с учётом частоты их вхождения. 
Результат работы - дерево - хранится в виде `std::vector mainTree` внутри программы. 
Далее по дереву строится таблица соответствия кодов символам и хранится в `std::map mainMap`. При успешной работе команды таблица выводится на экран. 

Для генерации используется функция `generate`.
## 2. "l" - Загрузка дерева Хаффмана
Программа просит на вход текстовый файл с деревом. Результат работы - дерево - хранится в виде `std::vector mainTree`.
Далее по дереву строится таблица соответствия кодов символам и хранится в `std::map mainMap`. При успешной работе команды таблица выводится на экран. 

Для загрузки используется функция `loadTree`.
## 3. "t" - Загрузка таблицы символов
Программа просит на вход текстовый файл с таблицей. Результат работы - таблица соответствия кодов символам - хранится в виде `std::map mainMap`. 
При этом выбранное до этого дерево не меняется.

Для загрузки используется функция `loadTable`.
## 4. "c" - Кодирование текста
Программа просит на вход строку текста или текстовый файл. При наличии таблицы символов происходит кодирование введённого текста и вывод кода в консоль или сохранение в файл (в зависимости от файлового режима).
Замечу, что код не записывается побитово, а передаётся текстом из нулей и единиц. Это требовалось в ТЗ.
Для кодирования используется функция `encode`.
## 5. "d" - Декодирование текста
Программа просит на вход строку текста или текстовый файл. При наличии выбранного дерева Хаффмана происходит декодирование введённого текста и вывод в консоль или сохранение в файл (в зависимости от файлового режима).
Код можно ввести вручную, набрав нули и единицы на клавиатуре.
Для декодирования используется функция `decode`.
## 6. "s" - Сохранение дерева Хаффмана.
При наличии выбранного дерева Хаффмана программа сохраняет его в файл.
Для сохранения используется функция `saveTree`.
## 7. "z" - Сохранение таблицы символов.
При наличии выбранной таблицы символов программа сохраняет её в файл.
Для сохранения используется функция `saveTable`.
## 8. "f" - Переключение файлового режима.
Переключает файловый режим. От режима зависит, вводится и выводится ли текст с помощью консоли или файла.
# Особенности проекта
Это простой проект, выданный в 11 классе в качестве практики использования алгоритма Хаффмана и файлов. Особенное внимание уделено устойчивости к ошибкам, т.е. к неверному вводу пользователя или ошибках во внутренних файлах.
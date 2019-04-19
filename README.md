# Лабораторная Работа №4. Межсетевое взаимодействие между процессами
## Цель работы
Организация межсетевого взаимодействия средствами WinAPI и POSIX.

## Задание
Организовать взаимодействие типа клиент-сервер средствами WinAPI и POSIX в соответствии с индивидуальным заданием.

1. Вычислить номер варианта задания как остаток от деления порядкового номера студента по списку в журнале на количество вариантов заданий. Если остаток равен нулю, выбрать последнее задание.  
**Nвар = Nв_списке mod K**,  
где Nвар - искомый номер варианта, Nв_списке - порядковый номер студента по списку в журнале, K - количество вариантов заданий на данную лабораторную работу.
2. Выбрать индивидуальное задание в соответствии с номером варианта. По номеру варианта также определить: 
- протокол, с использованием которого должен происходить обмен данными между сервером и клиентами;
- операционную систему, под которую необходимо разработать приложение сервера;
- операционную систему, под которую необходимо разработать приложение клиента.
3. В разделе [Issues](../../issues) репозитория создать не менее трех задач: "Разработка приложения сервера", "Разработка приложения клиента", "Отладка клиент-серверного взаимодействия". Последовательно выполнить эти задачи, написав код и разместив его в репозитории. Решению каждой задачи должен соответствовать свой отдельный коммит, ссылка на который должна быть приведена в комментарии к задаче. Итого не менее трех коммитов в репозитории. Структуру каталогов для хранения файлов с кодом в репозитории организовать самостоятельно. При необходимости создать дополнительные задачи.
4. Автоматические тесты отсутствуют. Необходимо загрузить рабочий код в репозиторий, а затем защитить лабораторную работу в аудитории, продемонстрировав корректную совместную работу клиентского и серверного приложений.
5. Допускается выполнение задания не в полном объеме. Правила начисления рейтинга для этого случая приведены в разделе [Рейтинг](#Рейтинг).

---

**NB!** Для получения максимально возможного количества баллов на защите лабораторной работы необходимо продемонстрировать работу системы на нескольких компьютерах, объединенных в локальную сеть. Для этого можно использовать локальную сеть между машинами в аудитории университета или виртуальную локальную сеть в системе виртуализации VM Ware или Virtual Box. Следует продемонстрировать корректную совместную работу по сети приложений клиента и сервера, запущенных в разных операционных системах (Windows и Linux/Mac OS).

---

## Содержание отчета
- Титульный лист 
- Цель работы
- Задание на лабораторную работу
- Схема взаимодействия между клиентом и сервером
- Результат выполнения лабораторной работы
- Исходный код программы с комментариями
- Выводы

## Варианты заданий
| № варианта    | Индивидуальное задание | Протокол  | Сервер  | Клиент  |
| ------------- |:----------------------:|:---------:|:-------:|:-------:|
| **1**         | 10                     | TCP       | Linux   | Windows |
| **2**         | 9                      | UDP       | Windows | Linux   |
| **3**         | 8                      | TCP       | Linux   | Windows |
| **4**         | 7                      | UDP       | Windows | Linux   |
| **5**         | 6                      | TCP       | Linux   | Windows |
| **6**         | 5                      | UDP       | Windows | Linux   |
| **7**         | 4                      | TCP       | Linux   | Windows |
| **8**         | 3                      | UDP       | Windows | Linux   |
| **9**         | 2                      | TCP       | Linux   | Windows |
| **10**        | 1                      | UDP       | Windows | Linux   |
| **11**        | 10                     | UDP       | Windows | Linux   |
| **12**        | 9                      | TCP       | Linux   | Windows |
| **13**        | 8                      | UDP       | Windows | Linux   |
| **14**        | 7                      | TCP       | Linux   | Windows |
| **15**        | 6                      | UDP       | Windows | Linux   |
| **16**        | 5                      | TCP       | Linux   | Windows |
| **17**        | 4                      | UDP       | Windows | Linux   |
| **18**        | 3                      | TCP       | Linux   | Windows |
| **19**        | 2                      | UDP       | Windows | Linux   |
| **20**        | 1                      | TCP       | Linux   | Windows |

## Индивидуальные задания
Во всех вариантах номер порта, на котором работает сервер, указывается при запуске сервера через аргуметы командной строки.

1.	Клиент обращается к серверу с запросом на выполнение какой-либо из следующих команд: "содержимое директории по указанному пути" (аналог `ls` / `dir`);  "количество файлов в указанной директории"; "версия операционной системы". Выбор команды и ее параметры (путь к директории) определяются пользователем, запустившим приложение клиента, через аргументы командной строки. Сервер выполняет поступившую от клиента команду и возвращает ему результаты.
2.	Клиент обращается к серверу с запросом о наличии файлов с определенным расширением в указанной директории. Сервер сканирует указанную директорию и отправляет клиенту список файлов, удовлетворяющих запросу. Расширение и путь к директории задаются пользователем, запустившим приложение клиента, через аргументы командной строки.
3.	При подключении клиента сервер высылает ему список IP-адресов уже подключенных клиентов, а остальным клиентам рассылается сообщение с информацией об IP-адресе нового клиента. При поступлении нового сообщений от сервера, клиент должен вывести его в консоль. Продемонстрировать работу приложения с одним сервером и не менее чем с 2 клиентами. Информация о сервере (его IP-адрес и порт) передаются клиенту через аргументы командной строки.
4.	При подключении к серверу клиент должен ввести пароль. Разрешено сделать три попытки. Если пароль неверен, сервер должен блокировать IP-адрес клиента на 2 минуты. Продемонстрировать, что во время блокировки одного клиента, к серверу может подключиться клиент с другим IP-адресом. Информация о сервере (его IP-адрес и порт) передаются клиенту через аргументы командной строки.
5.	Клиент подключается к серверу и запрашивает файл. Если файл найден – он пересылается клиенту, в противном случае клиенту высылается сообщение, что такого файла нет. Имя файла задается пользователем, запустившим приложение клиента, через аргументы командной строки.
6.	К серверу одновременно может подключиться только один клиент. Остальные клиенты заносятся в очередь, и им высылается сообщение об ожидании освобождения сервера. Когда сервер освобождается, всем клиентам делается рассылка сообщения с указанием их порядкового номера в очереди. Информация о сервере (его IP-адрес и порт) передаются клиенту через аргументы командной строки.
7.	Клиент отсылает строку серверу. Сервер пересылает данную строку всем остальным подключенным к нему клиентам, а затем осуществляет поиск файлов, содержащих данную строку. Результаты поиска отсылаются первому клиенту, инициировавшему запрос. Отсылаемая на сервер строка задается при запуске клиента через аргументы командной строки.
8.	Организовать чат. К серверу подключаются клиенты. При подключении клиента сервер спрашивает имя, под которым клиент будет известен в соединении. Сервер хранит IP-адреса подключаемых клиентов и их имена. Все сообщения клиентов рассылаются остальным в виде "имя клиента" - "сообщение". При подключении или отключении какого-либо клиента сервером также рассылается соответствующее уведомление всем клиентам. Имя, под которым клиент будет известен в чате, указывается при запуске каждого экземпляра приложения клиента через аргументы командной строки.
9.	Клиент подключается к серверу. Сервер генерирует 3 случайных числа. Если эти числа образуют стороны треугольника, то они передаются клиенту, иначе сервер их просто выводит на экран. Процедура повторяется до тех пор, пока сервер не сгенерирует хотя бы одну тройку чисел, образующую стороны треугольника. Клиент, если он получил тройку чисел от сервера, выводит их на экран. Информация о сервере (его IP-адрес и порт) передаются клиенту через аргументы командной строки.
10.	Клиент передает файл серверу. Сервер принимает файл и начинает подсчитывать количество каждой из букв английского алфавита в этом файле. При каждой сотой обработанной букве сервер передает текущие результаты подсчета по всем буквам клиенту, который выводит их на экран. Информация о сервере (его IP-адрес и порт) передаются клиенту через аргументы командной строки.

## Рейтинг
За 100% принято максимальное количество баллов, которое студент может получить при выполнении данной лабораторной работы (указано в журнале). Например, если студент набрал 90% рейтинга, а максимальное количество баллов равно 15, то итоговое количество баллов за эту лабораторную составит `15*90% = 13,5`.

| Пункт задания                                                                                                  | Рейтинг |
| -------------------------------------------------------------------------------------------------------------- |:-------:|
| В разделе Issues репозитория создано не менее трех осмысленных задач и они оформлены в соответствии с заданием | 15%     |
| В репозитории присутствует не менее трех осмысленных коммитов                                                  | 15%     |
| Клиентское и серверное приложения компилируются и успешно запускаются без ошибок                               | 10%     |
| Продемонстрирована корректная совместная работа клиента (-ов) и сервера по сети с разных IP-адресов            | 50%     |
| Сервер поддерживает одновременное подключение (попытку подключения) к нему нескольких клиентов                 | 10%     |


# Лабораторная Работа №5. Непрерывная интеграция в облаке с использованием Travis CI
## Цель работы
Изучение принципов организации непрерывной интеграции приложений с использованием облачных технологий.

## Задание
1. Сообщить преподавателю по электронной почте о необходимости подключить непрерывную интеграцию к репозиторию предыдущей лабораторной работы (речь про репозиторий, в котором размещен файл с этим текстом). В письме указать ФИО, номер группы и ссылку на репозиторий.
2. Добавить в репозиторий предыдущей лабораторной работы файл конфигурации `.travis.yml`, управляющий созданием виртуальной машины в облаке, на которой автоматически будет запускаться сборка проекта. Примеры содержимого файла `.travis.yml` можно посмотреть в репозиториях лабораторных работ №1, №2, а также в Интернете. Команды в разделе `script` файла конфигурации должны запускать сборку той части предыдущей лабораторной работы, которая в соответствии с вариантом была выполнена в ОС Linux (или Mac OS). Например, если по варианту задания на предыдущую лабораторную работу необходимо было разработать серверную часть приложения под ОС Linux, а клиентскую часть приложения под ОС Windows, то в данной лабораторной работе необходимо осуществить автоматическую сборку серверной части приложения. Сборка должна осуществляться упешно (без ошибок).
3. (**NB**! Этот пункт задания необязателен к выполнению) *Разработать как минимум один тест для проверки правильности функционирования приложения, автоматическая сборка которого была обеспечена на предыдущем шаге. Добавить сборку и запуск теста (-ов) в файл конфигурации `.travis.yml`.*
4. По аналогии с предыдущей работой процесс выполнения задания должен быть разбит на задачи, которые должны быть описаны в разделе Issues репозитория. Решению каждой задачи должен соответствовать как минимум один коммит.


## Содержание отчета
- Титульный лист 
- Цель работы
- Задание на лабораторную работу
- Описание структуры конфигурационного файла
- Содержимое написанного конфигурационного файла
- Логи сборки проекта в облаке
- Исходный код тестов (при наличии)
- Выводы


## Рейтинг
За 100% принято максимальное количество баллов, которое студент может получить при выполнении данной лабораторной работы (указано в журнале). Например, если студент набрал 150% рейтинга, а максимальное количество баллов равно 8, то итоговое количество баллов за эту лабораторную составит `8*150% = 12`.

| Пункт задания                                                                                                  | Рейтинг |
| -------------------------------------------------------------------------------------------------------------- |:-------:|
| В разделе Issues репозитория создано не менее одной осмысленной задачи в соответствии с заданием               | 15%     |
| В репозитории присутствует не менее одного осмысленного коммита (помимо тех, что были сделаны ранее)           | 15%     |
| При создании нового коммита запускается процесс сборки приложения под ОС Linux. Сборка проходит без ошибок     | 45%     |
| В репозитории присутствует тест, проверяющий аварийное завершение работы программы при следующих ситуациях: неправильное количество аргументов командной строки, неправильные значения аргументов командной строки (обработать минимум два разных случая с неправильными значениями). См. [пример подхода](#footnote1) ниже | 25%     |
| В зависимости от варианта реализовать приложение-заглушку для клиента (нечетный вариант) или сервера (четный вариант) под ОС Linux для тестирования факта установления соединения между клиентом и сервером по интерфейсу обратной петли (loopback) | 50%     |

---

<a name="footnote1">Пример</a> подхода к тестированию аргументов командной строки. 

Пусть необходимо протестировать работу сервера. Если сервер принимает на вход одно число (номер порта), то это число должно быть целым и лежать в определенном диапазоне. В этом случае потенциальными тестами могут быть: 
- проверка, что программа завершится аварийно, если количество аргументов командной строки равно нулю или более одного;
- проверка, что программа завершится аварийно, если аргумент командной строки не является целым числом;
- проверка, что программа завершится аварийно, если аргумент командной строки является числом, не соответствующим допустимым значениям для номера порта.

В случае тестирования аргументов командной строки клиента действовать по аналогии.

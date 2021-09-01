Данный репозиторий содержит пример реализации части протокола ТРК172, а именно формирование сообщений от ККМ на ТРК.

Приведённые в данном примере функции не выделяют память и предполагают наличие буфера достаточного размера чтобы разместить одно сообщение. О выделении и освобождении памяти должна позаботиться вызывающая сторона. Помимо указателя на буфер, передаётся размер буфера. Все функции возвращают POSIX совместимый код ошибки. Все функции возвращают код ошибки _EOK_ если функция успешно заполнила буфер команды. Если размер буфера недостаточный для формирования команды все функции возвращают код ошибки _ENOMEM_. В случае передачи противоречивых или неверных входных параметров, все функции возвращают код ошибки _EINVAL_.

В данном примере содержится проектный файл для среды разработки Visual Studio Express 2017, а также используется Google Test. Для компиляции и запуска модульных тестов необходимо наличие переменных среды GMOCK_HOME и GTEST_HOME с указанием пути расположения библиотеки Google Test. По результатам тестов можно убедиться в правильности формирования сообщений ККМ на ТРК.

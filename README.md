Симулятор движения модели трактора.
----------------------------------

Модель трактора может управляться как с реальных данных (GPS) так и данных симулированных программно.
Приложение реализовано на языке c++ c использованием библиотеки opengl и glut(для упращения создания окна программы),
представляет собой вид с верху карты местности и модели трактора на ней.
Так же проект являеться примером реализации простого 2d движка на opengl,
при дальнейшем развитии можно что нибудь на нём зафигачить, например "марио" или "супер контру"

Управление виртуальной камерой:
------------------------------
    Управление осуществляеться с помошью мышки, удерживая левую клавишу можно перемещать камеру в плоскости экрана.
    Вращая колесо мышки изменяеться масштаб.

Управление симулированной моделью, клавиши:
--------------------------------------------------------------------

    'w' - увеличить скорость, переключиться на модель симуляции 
    's' - уменьшить скорость, переключиться на модель симуляции
    'a' - повернуть колеса в лево на шаг, переключиться на модель симуляции
    'd' - повернуть колеса в право на шаг, переключиться на модель симуляции
    'space' - остановить движение тракота, переключиться на модель симуляции

    'e' - запуск движения модели на базе реальных данных GPS из файла
    'r' - остановить воспроизведение движения по gps

Сборка и запуск приложения под linux(ubuntu):
---------------------------------------------

    1) установить библиотеки: libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev
        sudo apt-get install libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev

    2) Соберите проект:ы
        make

    3) Запуск приложения:
        ./main [gps.dat]
        gps.dat - опционалый параметр, путь к файлу с треком gps. пример трека в папке tasks

Сборка под windows:
-------------------

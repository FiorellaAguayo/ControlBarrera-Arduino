# ControlBarrera-Arduino

# Hardware - Tinkercad
![Primera parte](https://github.com/FiorellaAguayo/ControlBarrera-Arduino/blob/main/images/arduino.png)

# Link a Tinkerdad
https://www.tinkercad.com/things/ix5gpBy4X4Q-2-examen-parcial-entrega-27-11-23

# Consigna

 Solo en el modo de funcionamiento (ni programacion ni informacion ni cambio de angulos), al presionar la tecla #, se debe encender o apagar el backlight del display
 
 Para cambiar los angulos de apertura y cierre de las barreras, se debe presionar la tecla "B", en este momento, la segunda linea cambia por la frase "Cambio de Angulo", lo que habilita la modificacion de ángulos con los presets, y presionando nuevamente la tecla "B", se vuelve al modo normal de funcionamiento. 

 El funcionamiento de todos los componentes conenctados al Arduino,
 debe controlarse mediante funciones llamadas desde la función Loop
 El preset de la derecha, debe indicar la posición (en grados) inicial de la barrera (entre 0° y 45°)
 El preset de la izquierda, debe indicar la posicón (en grados) final de la barrera. (entre 150° y 180°)
 En el display deben verse en la línea superior los ángulos de apertura y cierre.
 En la segunda linea de este modelo, debe verse la leyenda "****" centrada en el display.

 En la función Setup, debe inicializarse una clave de 4 valores numericos, en un array (global) de tipo int, como clave inicial
 Al presionar la tecla "*" se ingresa en el modo de programación de una nueva clave, indicandolo en el display con la leyenda "Programacion" en la segunda línea del display
 al entrar en este modo, la línea superior se borra y se reemplaza por "----" esperando el ingreso de la nueva clave
 al ingresar 4 teclas numericas, la clave se muestra en la 1° linea reemplazando a los guiones, por ejemplo si se presiona 1234 se ira viendo sucesivamente:

1---
12--
123-
1234

Recien luego de presionar 4 teclas numericas se puede permitir la grabacion de la nueva clave al presionar nuevamente "*" 
Se debe validar que se hayan presionado 4 teclas numéricas para validar la grabacion, si esto no ocurre, en la segunda linea se debe imprimir la leyenda "falla" 
durante 2 segundos y luego, volver al modo de en el que el display muestra los datos de apertura y cierre
Si se dan las condiciones para que la nueva clave sea grabada, en la segunda linea se imprime la leyenda "clave grabada" durante dos segundos y vuelve al modo de mostrar los ángulos de apertura y cierre, y los "*" centrados. 
 
Al presionar la tecla #, la segunda linea debe mostrar la leyenda "informacion" y la primera linea se debe borrar.
En este momento, si se presionan las teclas "DACB" en ese orden y luego la tecla # nuevamente, el display muestra por dos segundos la clave grabada en la primera línea y luego vuelve a mostrar los datos de ángulos de apertura y cierre, y los "*" centrados.
Dicha clave grabada se debe mostrar por el monitor en serie.
Si se presiona una secuecia diferente, se vuelve al modo de funcionamiento y en el monitor serie la leyenda "secuencia incorrecta"

En el modo normal de funcionamiento, (cuando se ven los datos de ángulo de apertura y cierre) y los "*" centrados0 al presionar la clave grabada correctamente, 
y luego presionando la tecla "A" la barrera se mueve hasta la posición de Apertura. A medida que se van presionando los numeros (antes de la tecla "A") 
se van reemplazando los asteriscos, por las teclas presionadas (si se presiona una tecla no numerica, no se avanza, como si se no se hubiese presionado 
ninguna tecla). Si se presiona la clave correcta, luego de la "A" se debe ver la leyenda "Abre Barrera" en la segunda linea durante dos segundos, 
abrir la barrera al ángulo grabado y luego vuelve a los "****"
En este mismo modo, para que la barrera se cierre, se debe escribir la clave en sentido inverso y luego la letra "C", es decir, si la clave es 1234, 
para cerrar la barrera, debe presionarse 4321 y luego la "C".
En el caso del cierre se repite el formato de la apertura, con la leyenda "Cierra Barrera" durante dos segundos y luego vuelve a los "****"


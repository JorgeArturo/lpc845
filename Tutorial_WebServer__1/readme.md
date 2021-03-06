# LPC845-BRK con Modulo ESP8266

El microcontrolador LPC845 es una pequeña familia de la compañia de NXP, donde el procesador es un ARM CORTEX M0+ contiene varios perifericos de comunicacion tales como son:

<a href="https://www.nxp.com/assets/images/en/block-diagrams"><img src="https://www.nxp.com/assets/images/en/block-diagrams/LPC84x-MCU-FAMILY-BD.jpg" alt="LPC84x-MCU-FAMILY-BD" border="0" width="50%" height="50%"></a>

Lo que podemos ver es que contiene cinco perifericos de tipo USART esto es muy bueno si se desea realizar varias comunicaciones con modulos seriales, por dar un ejemplo, utilizar un puerto USART para la comunicacion con un GPS, y utilizar otro USART para el GSM, por ultimo para conectar un ESP8266, sin la necesidad de simular pines seriales.

La tarjeta LPC845-BRK contiene lo necesario para iniciar la programacion y depuracion del codigo que vallamos a implementar:

* Contiene un potenciometro
* Led tricolor
* Conexion para medir el consumo
* un programador y depurador

<a href="https://www.nxp.com/assets/images/en/dev-board-image"><img src="https://www.nxp.com/assets/images/en/dev-board-image/LPC845-BRK-1.JPG" alt="LPC845-BRK-1.JPG" border="0" width="50%" height="50%"></a>
<a href="https://www.nxp.com/assets/images/en/block-diagrams"><img src="https://www.nxp.com/assets/images/en/block-diagrams/LPC845-BRK-BD2.png" alt="LPC845-BRK-BD2.png.JPG" border="0" width="50%" height="50%"></a>

## ESP8266

<a href="https://upload.wikimedia.org/wikipedia/commons/8/84"><img src="https://upload.wikimedia.org/wikipedia/commons/8/84/ESP-01.jpg" alt="ESP-01.jpg" border="0" width="50%" height="50%"></a>

Este modulo contiene un stack completo de TCP/IP y UDP, donde nos permitiriá realizar servidores WEB, la imagen de arriba contiene solamente 8 pines de los cuales son los siguientes:

<a href="https://circuits4you.com/wp-content/uploads/2016/12/ESP-01-Pin-Out.png"><img src="https://circuits4you.com/wp-content/uploads/2016/12/ESP-01-Pin-Out.png" alt="ESP-01-Pin-Out.png" border="0"></a>

El GPIO0 nos permite entrar en modo de actualizar el firmware del cual se requiere que el pin este bajo (0 volts) cuando se realize un reset de poder o por el PIN de RESET.
En nuestro caso vamos a utilizarlo para realizar un servidor web, donde la comunicacion sera por serial hacia el microcontrolador LPC845, para intercambiar informacion utilizaremos los comandos AT, del cual podemos encontrar informacion en la pagina oficial de ESPRESSIF.

https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf

Los comandos de Inicializacion que se utiliza en el codigo principal del LPC845 son los siguientes:

* AT+RST\r\n : Nos permite reiniciar el esp8266 sin necesidad de utilizar el pin fisico.
* AT+ATE0\r\n : Elimina el eco de cada mensaje enviado
* AT\r\n : Validamos que no tenga ECO y tambien que el sistema esta funcionando
* AT+CWMODE_CUR=1\r\n : Pondemos en modo estacion para realizar la conexion a un router de WIFI.
* AT+CWJAP_CUR="SSID","PWD"\r\n : Nos conectamos a la red WIFI que tenemos de nuestro codigo.
* AT+CIPSTATUS\r\n : Preguntamos si ya tenemos IP del router asignados al dispositivo
* AT+CIPMUX=1\r\n : Multiples Conexiones
* AT+CIPSERVER=1,80\r\n : Iniciamos el servidor web (HTTP) en el puerto 80
* AT+CIPSTO=30\r\n : Si el cliente se conecta solamente estara disponible por 30 segundos la conexion

Ahora bien, la pagina que vallamos a utilizar se encuentra almacenada en el lpc845 como un arreglo, cuando el cliente entra a la IP del servidor en algun navegador, se enviara la pagina como una respuesta.

<img src="https://i.ibb.co/71K2SKz/servidor-web.jpg" alt="servidor-web" border="0">

Cuando el cliente presione un boton, por ejemplo el LED ON, enviara datos al servidor en nuestro caso un "/?LED=ON0", el codigo del lpc845 esta preparado para encontrar esta palabra y realizar una accion correspondiente, donde sera prender un led verde, de igualmanera si se presiona el boton de LED OFF, tendremos una respuesta de tipo "/?LED=OFF0" donde buscará este texto para apagar el led.

La conexion entre el ESP8266 y el LPC845 es la siguiente:

<img src="https://i.ibb.co/cDhr92H/Conexion-esp8266-y-lpc845.jpg" alt="Conexion-esp8266-y-lpc845" border="0">



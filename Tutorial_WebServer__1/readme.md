# LPC845-BRK con Modulo8266

El microcontrolador LPC845 es una pequeña familia de la compañia de NXP, donde el procesador es un ARM CORTEX M0+ contiene varios perifericos de comunicacion tales como son:

<a href="https://www.nxp.com/assets/images/en/block-diagrams"><img src="https://www.nxp.com/assets/images/en/block-diagrams/LPC84x-MCU-FAMILY-BD.jpg" alt="LPC84x-MCU-FAMILY-BD" border="0" width="50%" height="50%"></a>

Lo que podemos ver es que contiene cinco perifericos de tipo USART esto es muy bueno si se desea realizar varias comunicaciones con modulos seriales, por dar un ejemplo, utilizar un puerto USART para la comunicacion con un GPS, y utilizar otro USART para el GSM, por ultimo para conectar un ESP8266, sin la necesidad de simular pines seriales.

La tarjeta LPC845-BRK contiene lo necesario para iniciar la programacion y depuracion del codigo que vallamos a implementar:

*Contiene un potenciometro
*Led tricolor
*Conexion para medir el consumo
*un programador y depurador

<a href="https://www.nxp.com/assets/images/en/dev-board-image"><img src="https://www.nxp.com/assets/images/en/dev-board-image/LPC845-BRK-1.JPG" alt="LPC845-BRK-1.JPG" border="0"></a>
<a href="https://www.nxp.com/assets/images/en/block-diagrams"><img src="https://www.nxp.com/assets/images/en/block-diagrams/LPC845-BRK-BD2.png" alt="LPC845-BRK-BD2.png.JPG" border="0"></a>

## ESP8266

<a href="https://upload.wikimedia.org/wikipedia/commons/8/84"><img src="https://upload.wikimedia.org/wikipedia/commons/8/84/ESP-01.jpg" alt="ESP-01.jpg" border="0"></a>


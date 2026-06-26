# IA - MDVRP-TW

ROL: 202173650-6
Pablo Retamales Jara

### Sobre la documentación

* La documentación se encuentra en los archivos de cabecera (`.h`), donde se declaran las funciones y estructuras públicas del proyecto.
* No se replica en los archivos de implementación (`.cpp`) para evitar duplicidad y mantener la documentación en un único lugar. Esta es la práctica recomendada en C++ para documentar la interfaz pública del código.
* Dentro de las funciones se incluyen comentarios adicionales únicamente cuando es necesario, especialmente para explicar decisiones de diseño, lógica no evidente o partes del algoritmo que no son triviales.
* En general, el código está escrito de forma que sea lo suficientemente claro y autoexplicativo, minimizando la necesidad de comentarios línea por línea.

### Estructura del proyecto

El proyecto está modularizado, separando interfaz, implementación y datos de entrada/salida.

- `include/`: contiene los archivos de cabecera (`.h`), donde se declaran las estructuras, funciones y la interfaz pública del sistema.
- `src/`: contiene las implementaciones (`.cpp`) de las funciones declaradas en `include/`.
- `Instancias/`: almacena las instancias de prueba del problema MDVRPTW.
- `Soluciones/`: almacena los resultados generados por el algoritmo, organizados por tamaño de instancia.

  Para que la escritura de soluciones en formato `.txt` funcione correctamente, deben existir previamente las carpetas con el formato:
  `Soluciones/instancias_{tamaño_instancia}/`

  Si esta estructura no existe, el programa no podrá guardar los resultados debido a que no se crea automáticamente la ruta de salida.

- `evaluate.sh`: script de ejecución para pruebas o evaluación automática del sistema.
- `Makefile`: archivo de compilación del proyecto.

El proyecto está organizado por responsabilidades funcionales, por ejemplo:
- Evaluación de soluciones
- Parser de instancias
- Generación de soluciones iniciales
- Movimientos de búsqueda local
- Algoritmo principal (Simulated Annealing)

Esta separación permite mantener el código modular, reutilizable y fácil de extender.

### Instrucciones de compilación y ejecución
El proyecto debe ejecutarse desde la raíz del código, donde se encuentra el Makefile.

* make
  Compilación normal del proyecto MDVRP-TW

* make debug
  Compila el modo debug del proyecto MDVRP-TW

* make run
  Ejecuta el MDVRPTW

  Se deben especificar los parámetros de entrada. Ejemplo:

  ```bash
  make run INSTANCE_PATH=./Instancias/instancias_100/C101.txt ALPHA=0.5 INITIAL_TEMPERATURE=5000 COOLING_RATE=0.98 MAX_ITERATIONS=1000000 COOLING_INTERVAL=50 MAX_STAGNATION=20000 SEED=42
  ```

  INSTANCE_PATH: ruta a la instancia del problema
  ALPHA: factor de penalización para las violaciones de ventanas de tiempo.
  INITIAL_TEMPERATURE: temperatura inicial
  COOLING_RATE: tasa de enfriamiento
  MAX_ITERATIONS: iteraciones máximas
  COOLING_INTERVAL: intervalo de enfriamiento
  MAX_STAGNATION: criterio de estancamiento
  SEED: semilla aleatoria para reproducibilidad

* make clean
  Sirve para limpiar los archivos compilados

         &
      .-"`"-.
     /       \
     |   __  _|
     |  /  \/ \
    WW  \_o/_o/
    (        _)
     |   .----\
     ;  | '----'
      \__'--;`
      |___/\| omero
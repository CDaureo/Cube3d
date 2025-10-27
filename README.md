# cub3D

## Mi primer RayCaster con miniLibX

## 🎮 Parte Obligatoria

### Nombre del Programa
`cub3D`

### Argumentos
Un archivo de descripción de escena con extensión `.cub`

### Funciones Externas Permitidas
- `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`
- `gettimeofday`
- Todas las funciones de la librería matemática (`-lm`)
- Todas las funciones de miniLibX

### Funcionalidades Requeridas

#### 1. **Renderizado 3D**
- Crear una representación gráfica 3D "realista" del interior de un laberinto desde perspectiva de primera persona
- Usar principios de ray-casting

#### 2. **Texturas**
- Mostrar diferentes texturas de pared según la orientación:
  - Norte (NO)
  - Sur (SO)
  - Este (EA)
  - Oeste (WE)

#### 3. **Colores**
- Configurar colores diferentes para:
  - Suelo (Floor - F)
  - Techo (Ceiling - C)
- Formato RGB en rango [0,255]

#### 4. **Controles**
- **Flechas izquierda/derecha**: Mirar a izquierda/derecha en el laberinto
- **W, A, S, D**: Mover el punto de vista a través del laberinto
- **ESC**: Cerrar ventana y salir del programa
- **Cruz roja de la ventana**: Cerrar ventana y salir del programa

#### 5. **Archivo de Configuración (.cub)**

##### Caracteres del Mapa
- `0` - Espacio vacío
- `1` - Pared
- `N`, `S`, `E`, `W` - Posición inicial y orientación del jugador

##### Ejemplo de Mapa Válido
```
111111
100101
101001
1100N1
111111
```

##### Reglas del Mapa
- El mapa debe estar cerrado/rodeado por paredes
- Los espacios son válidos y deben manejarse correctamente
- El mapa debe ser la última sección del archivo
- Cada elemento puede estar separado por una o más líneas vacías

##### Formato de Elementos
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
...
```

##### Ejemplo Completo de .cub
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

#### 6. **Manejo de Errores**
- Si hay algún error de configuración, el programa debe:
  - Salir correctamente
  - Mostrar `"Error\n"`
  - Seguido de un mensaje de error explícito

---

## 🌟 Parte Bonus

Los bonus **solo se evaluarán** si la parte obligatoria es **perfecta**.

**Perfecta significa**:
- Completa en todos los aspectos
- Sin fallos, incluso con uso incorrecto
- Obtener TODOS los puntos en la parte obligatoria

Si la parte obligatoria no obtiene todos los puntos, los bonus serán **completamente IGNORADOS**.

### Posibles Bonus (a implementar según criterio)
- Colisiones con las paredes
- Un minimapa
- Puertas que se pueden abrir/cerrar
- Objetos animados
- Rotación del mouse
- Etc.

---

## 🛠️ Compilación

```bash
make        # Compila el proyecto
make clean  # Elimina objetos
make fclean # Elimina objetos y ejecutable
make re     # Recompila todo
make bonus  # Compila con bonuses (si aplica)
```

---

## 🚀 Uso

```bash
./cub3D <archivo_de_mapa.cub>
```

Ejemplo:
```bash
./cub3D maps/map.cub
```

## 📖 Recursos Útiles

- [Wolfenstein 3D Original](http://users.atw.hu/wolf3d/)
- Documentación de miniLibX
- Tutoriales de ray-casting disponibles en internet
- Documentación de la librería matemática (`man 3 math`)
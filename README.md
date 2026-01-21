# cub3D - Plan de Desarrollo 🎯

Este documento describe **el plan completo de desarrollo** del proyecto **cub3D**, organizado por fases y prioridades, siguiendo los requisitos habituales del proyecto (42 / miniLibX).

---

## 📋 Orden de Implementación por Prioridad

---

## 🧱 Fase 1: Configuración Inicial (PRIORITARIA)

### 📁 Estructura del proyecto
      (HECHO PERO ES ESCALABLE)
* Configurar **Makefile básico**
* Crear estructura de directorios:

  * `src/`
  * `include/`
  * `maps/`
  * `textures/`
* Incluir **libft** si es necesaria

---

### 📄 Parsing del archivo `.cub`

* ✅ Validar extensión `.cub`
* ✅ Leer y almacenar rutas de texturas:

  * `NO`, `SO`, `WE`, `EA`
* ❌ Parsear colores:

  * Suelo `F` (RGB)
  * Techo `C` (RGB)
* ❌ Extraer y almacenar el mapa

---

### 🧩 Validación del mapa

* ❌ Verificar caracteres válidos:

  * `0`, `1`, `N`, `S`, `E`, `W`
* ❌ Encontrar posición inicial del jugador

  * Solo **una** posición válida
* ❌ Determinar orientación inicial del jugador
* ❌ Validar que el mapa esté **cerrado por paredes**
* ❌ Manejar espacios correctamente dentro del mapa

---

### 🚨 Manejo de errores

* ❌ Mostrar errores con el formato:

  ```
  Error\n<mensaje explicativo>
  ```
* ❌ Liberar **toda la memoria** correctamente en caso de error
* ❌ Validar existencia y accesibilidad de las rutas de texturas

---

## 🖼️ Fase 2: Configuración de miniLibX (CRÍTICA)

### 🪟 Inicialización de ventana

* Inicializar **miniLibX**
* Crear ventana con tamaño definido
* Configurar hooks básicos:

  * Cierre de ventana (X roja)

---

### 🖌️ Gestión de imágenes

* Cargar texturas desde archivos
* Crear **buffer de imagen** para el renderizado
* Implementar `pixel_put` optimizado (uso de imagen, no ventana directa)

---

## 🧠 Fase 3: Motor de Ray-Casting (CORE DEL PROYECTO)

### 📐 Algoritmo DDA (Digital Differential Analyzer)

* Implementar cálculo de rayos por columna
* Detectar colisiones con paredes
* Determinar distancia **perpendicular** al muro

---

### 🧱 Renderizado de paredes

* Calcular altura de las líneas de pared
* Seleccionar textura según orientación:

  * Norte / Sur / Este / Oeste
* Mapear correctamente texturas a columnas de píxeles
* Aplicar **corrección de distorsión fisheye**

---

### 🎨 Renderizado de suelo y techo

* Rellenar píxeles superiores con color `C`
* Rellenar píxeles inferiores con color `F`

---

## 🎮 Fase 4: Controles y Movimiento (JUGABILIDAD)

### ⌨️ Sistema de input

* Capturar eventos de teclado
* Implementar rotación:

  * Flecha izquierda
  * Flecha derecha
* Implementar movimiento:

  * `W` avanzar
  * `S` retroceder
  * `A` strafe izquierda
  * `D` strafe derecha

---

### 🧭 Cálculo de movimiento

* Actualizar posición del jugador
* Actualizar vector de dirección
* Validar colisiones básicas

  * El jugador **no puede atravesar paredes**

---

### ❌ Eventos de cierre

* Tecla `ESC` para salir
* Click en la cruz roja para cerrar la ventana

---

## 🧪 Fase 5: Testing y Optimización (PRE-ENTREGA)

### ❌ Validación completa

* Probar mapas válidos e inválidos
* Verificar fugas de memoria con **valgrind**
* Probar texturas corruptas o inexistentes
* Validar gestión de ventana:

  * Minimizar
  * Cambiar de foco

---

### 🚀 Optimización

* Mejorar rendimiento del renderizado
* Optimizar cálculos del ray-casting
* Asegurar **mínimo 60 FPS**

---

## 🌟 Fase 6: Bonus (SOLO SI LA PARTE OBLIGATORIA ES PERFECTA)

### 🧱 Colisiones mejoradas

* Sliding wall collision
* Hitboxes más precisas

---

### 🗺️ Minimap

* Vista 2D del mapa
* Indicador de posición y dirección del jugador

---

### 🚪 Puertas interactivas

* Abrir / cerrar con tecla (ej: `E`)
* Animación de apertura

---

### 👾 Sprites animados

* Objetos estáticos y dinámicos
* Sistema de sprites ordenados por distancia

---

### 🖱️ Rotación con mouse

* Capturar movimiento del mouse
* Rotación suave de cámara

---

## 📊 Checklist de Funciones Externas Permitidas

* `open`, `close`, `read`, `write`
* `printf`, `malloc`, `free`
* `perror`, `strerror`, `exit`
* `gettimeofday`
* Librería matemática (`-lm`):

  * `sin`, `cos`, `tan`, `sqrt`, etc.
* **Todas las funciones de miniLibX**

---

## ⚠️ Criterios de Éxito

* ✅ Renderizado 3D fluido
* ✅ Texturas correctas según orientación
* ✅ Colores de suelo y techo configurables
* ✅ Controles responsivos
* ✅ Parsing robusto con manejo de errores
* ✅ Sin fugas de memoria
* ✅ Gestión de ventana impecable

---

## 🚨 Errores Comunes a Evitar

* ❌ No validar correctamente el cierre del mapa
* ❌ No manejar espacios dentro del mapa
* ❌ Distorsión fisheye sin corregir
* ❌ Fugas de memoria en texturas o ventana
* ❌ No liberar recursos al cerrar el programa

---

💡 **Consejo final:** Implementa cada fase de forma incremental y verifica su estabilidad antes de continuar. Un parser sólido y un ray-casting limpio son la base del éxito en **cub3D**.

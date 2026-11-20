# Junimo Crop Assistant

Asistente de optimización agrícola diseñado para jugadores de *Stardew Valley*. Permite cargar un catálogo de cultivos desde un archivo de texto, consultar sus estadísticas, filtrarlos por temporada o capacidad de re-cosecha, y ordenarlos por rentabilidad diaria neta a lo largo de una temporada estándar de 28 días.

---

## Descripción y Utilidad

En *Stardew Valley*, maximizar las ganancias requiere calcular el retorno neto diario de cada semilla considerando su costo inicial, el tiempo de maduración y si el cultivo produce múltiples cosechas dentro de una temporada de 28 días. Este programa automatiza dichos cálculos y organiza la información para facilitar la toma de decisiones estratégicas.

### Fórmulas de Rentabilidad Implementadas

* **Cultivos de cosecha única:**
  $$\text{Ganancia Diaria} = \frac{\text{Precio de Venta} - \text{Costo de Semilla}}{\text{Días de Crecimiento}}$$

* **Cultivos de multi-cosecha (regrow):**
  $$\text{Cosechas Totales} = 1 + \left\lfloor \frac{28 - \text{Días de Crecimiento}}{\text{Días de Re-cosecha}} \right\rfloor$$
  $$\text{Ganancia Diaria} = \frac{(\text{Cosechas Totales} \times \text{Precio de Venta}) - \text{Costo de Semilla}}{28}$$

---

## Decisiones Técnicas y Estructuras de Datos

* **Merge Sort (`mergeSort.h`):** Elegido para ordenar los cultivos por rentabilidad diaria porque garantiza una complejidad de $O(n \log n)$ en todos los casos y es un algoritmo estable (mantiene el orden relativo en empates).
* **Árbol Binario de Búsqueda (`BST.h`):** Elegido para indexar los nombres de los cultivos, permitiendo búsquedas rápidas sin recorrer todo el arreglo y obteniendo la lista ordenada alfabéticamente mediante un recorrido *Inorder*.

---

## Análisis de Complejidad

| Componente / Operación | Mejor Caso | Caso Promedio | Peor Caso | Notas |
| :--- | :---: | :---: | :---: | :--- |
| **Merge Sort** (`mergeSort`) | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | Divide y mezcla los $n$ cultivos; espacio auxiliar $O(n)$. |
| **BST: Inserción / Búsqueda** (`add`, `find`) | $O(1)$ | $O(\log n)$ | $O(n)$ | Depende del balanceo del árbol ($O(n)$ si está sesgado). |
| **BST: Recorrido / Limpieza** (`printInorder`, `removeAll`) | $O(n)$ | $O(n)$ | $O(n)$ | Visita cada nodo exactamente una vez. |
| **Carga de archivo** (`crops.txt`) | $O(n)$ | $O(n \log n)$ | $O(n^2)$ | Lee $n$ líneas e inserta cada nombre en el BST. |
| **Filtros e impresión** (Opciones 1, 3, 4, 6) | $O(n)$ | $O(n)$ / $O(n \log n)$ | $O(n)$ / $O(n \log n)$ | Recorren el vector en $O(n)$ y ordenan subconjuntos con Merge Sort. |

**Complejidad Final del Programa:** **$O(n \log n)$** en el caso promedio (y **$O(n^2)$** en el peor caso si el árbol queda completamente desbalanceado al cargar los datos), con una complejidad espacial de **$O(n)$**.

---

## Estructura del Proyecto

* `JunimosCropAssistant.cpp`: Programa principal, lectura de archivo y menú interactivo.
* `crop.h`: Definición de la clase `Crop`, cálculo de rentabilidad y sobrecarga del operador `<`.
* `mergeSort.h`: Implementación genérica de *Merge Sort* mediante plantillas (`template`).
* `BST.h`: Implementación genérica de un Árbol Binario de Búsqueda.
* `crops.txt`: Archivo de entrada con los datos de los cultivos en formato CSV.

---

## Compilación y Ejecución

Asegúrate de que `crops.txt` se encuentre en el mismo directorio que el ejecutable.

```bash
g++ JunimosCropAssistant.cpp -o JunimosCropAssistant
./JunimosCropAssistant

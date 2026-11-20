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

### Algoritmo de Ordenamiento: Merge Sort
Se seleccionó **Merge Sort** para ordenar los cultivos por rentabilidad diaria debido a las siguientes ventajas:
* **Complejidad garantizada:** Mantiene un tiempo de ejecución de $O(n \log n)$ incluso en el peor de los casos, a diferencia de *Quick Sort* que puede degradarse a $O(n^2)$.
* **Estabilidad:** Conserva el orden relativo original entre cultivos que tienen exactamente la misma ganancia diaria.

### Estructura de Datos No Lineal: Árbol Binario de Búsqueda (BST)
Se implementó un **BST** para indexar los nombres de los cultivos:
* **Búsqueda rápida:** Permite verificar la existencia de un cultivo específico sin recorrer secuencialmente todo el arreglo de datos.
* **Ordenamiento alfabético natural:** Al realizar un recorrido *Inorder* (izquierda, raíz, derecha), se obtienen todos los nombres ordenados alfabéticamente en tiempo lineal $O(n)$ sin necesidad de ejecutar un algoritmo de ordenamiento adicional.

---

## Análisis de Complejidad

### 1. Algoritmo de Ordenamiento (`mergeSort.h`)

| Operación / Caso | Mejor Caso | Caso Promedio | Peor Caso | Complejidad Espacial |
| :--- | :---: | :---: | :---: | :---: |
| `mergeSort` | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ |
| `mergeSplit` | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ (pila) |
| `mergeArray` / `copyArray` | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |

### 2. Estructura de Datos: BST (`BST.h`)

| Método | Mejor Caso | Caso Promedio | Peor Caso (Árbol sesgado) | Descripción |
| :--- | :---: | :---: | :---: | :--- |
| `add(val)` | $O(1)$ | $O(\log n)$ | $O(n)$ | Inserción recursiva manteniendo la propiedad del BST. |
| `find(val)` | $O(1)$ | $O(\log n)$ | $O(n)$ | Búsqueda binaria descartando la mitad del subárbol en cada paso. |
| `printInorder()` | $O(n)$ | $O(n)$ | $O(n)$ | Visita cada nodo exactamente una vez para imprimir en orden. |
| `removeAll()` | $O(n)$ | $O(n)$ | $O(n)$ | Liberación de memoria en postorden de todos los nodos. |

### 3. Componentes del Programa (`JunimosCropAssistant.cpp`)

| Componente / Opción del Menú | Complejidad Temporal | Explicación |
| :--- | :---: | :--- |
| Carga de archivo (`crops.txt`) | $O(n \log n)$ promedio / $O(n^2)$ peor caso | Leer $n$ líneas es $O(n)$, e insertar cada elemento en el BST toma $O(\log n)$ promedio ($O(n)$ peor caso). |
| **1.** Ver lista sin ordenar | $O(n)$ | Recorre el `std::vector` secuencialmente para imprimir la tabla. |
| **2.** Ordenar por rentabilidad | $O(n \log n)$ | Ejecuta `mergeSort` sobre el vector de $n$ cultivos. |
| **3.** Filtrar por temporada | $O(n \log n)$ | Filtra en $O(n)$ y ordena el subconjunto resultante en $O(k \log k)$, donde $k \le n$. |
| **4.** Buscar cultivo por nombre | $O(n)$ | Realiza la búsqueda en el BST en $O(\log n)$ promedio y recupera los atributos del vector en $O(n)$. |
| **5.** Orden alfabético | $O(n)$ | Ejecuta el recorrido `printInorder()` sobre el BST. |
| **6.** Cultivos multi-cosecha | $O(n \log n)$ | Filtra mediante `canRegrow()` en $O(n)$ y ordena con `mergeSort` en $O(k \log k)$. |

### Complejidad Final del Programa
Considerando la carga inicial de datos y la ejecución de las operaciones principales del menú interactivo, la complejidad temporal dominante del sistema es **$O(n \log n)$** en el caso promedio (y **$O(n^2)$** en el peor caso si las inserciones en el BST ocurren en orden estrictamente ascendente o descendente), con una complejidad espacial de **$O(n)$**.

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
g++ -std=c++17 JunimosCropAssistant.cpp -o JunimosCropAssistant
./JunimosCropAssistant

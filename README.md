# Junimo Crop Assistant - Planificador de Cultivos y Rentabilidad por Temporada

Este proyecto es una herramienta en C++ diseñada para optimizar la toma de decisiones agrícolas en el videojuego *Stardew Valley*. El asistente procesa una base de datos de cultivos, calcula su rentabilidad neta por día considerando si son de cosecha única o recurrente, y organiza la información mediante algoritmos de ordenamiento eficientes e interacción por consola para ofrecer recomendaciones al jugador.

---

## Estructura de Datos Utilizada (`std::vector`)

Para el almacenamiento y gestión de los cultivos en memoria se utilizó la estructura de datos dinámica **`std::vector<Crop>`**.

### Justificación de Elección
1. **Memoria Dinámica:** El número de cultivos en `crops.txt` puede variar si se agregan nuevos registros; `std::vector` gestiona el redimensionamiento dinámico sin requerir definir un tamaño fijo en tiempo de compilación.
2. **Acceso Aleatorio** A diferencia de una lista simplemente o doblemente enlazada (`std::list`), el vector almacena los elementos en un bloque contiguo de memoria. Esto permite:
   * Acceso aleatorio directo a cualquier elemento mediante índice en tiempo constante $O(1)$.

### Complejidad de Operaciones en el Vector
* **Lectura / Acceso por índice (`operator[]`):** $O(1)$ temporal.
* **Inserción al final (`push_back`):** $O(1)$ amortizado temporal.
* **Recorrido secuencial (impresión y filtrado):** $O(n)$ temporal, donde $n$ es la cantidad de cultivos almacenados.
* **Espacio en memoria:** $O(n)$ para almacenar los $n$ objetos `Crop`.

---

## Descripción del Proyecto y Diseño POO

El sistema carga los datos desde un archivo delimitado por comas (`crops.txt`) y modela cada registro mediante la clase `Crop` implementada bajo una arquitectura basada en encabezados (*header-only*):

- **Atributos de `Crop`:**
  * `name` (`string`): Nombre del cultivo.
  * `season` (`string`): Temporada en la que crece (`Spring`, `Summer`, `Fall`).
  * `growDays` (`int`): Días requeridos para la primera cosecha.
  * `regrowDays` (`int`): Días que tarda en volver a producir (0 si no re-produce).
  * `sellPrice` (`int`): Precio de venta por unidad producida.
  * `seedCost` (`int`): Costo de compra de la semilla.

- **Lógica Financiera y Complejidad de Métodos:**
  * **Getters y `canRegrow()`:** $O(1)$ temporal. Operaciones de lectura y evaluación condicional directa.
  * **Cosecha única (`regrowDays == 0`):**
    $$\text{dailyCropsProfit} = \frac{\text{sellPrice} - \text{seedCost}}{\text{growDays}}$$
    *Complejidad:* $O(1)$ temporal (operaciones aritméticas elementales).
  * **Cosecha múltiple (`regrowDays > 0`) a lo largo de una temporada (28 días):**
    $$\text{totalHarvests} = 1 + \left\lfloor \frac{28 - \text{growDays}}{\text{regrowDays}} \right\rfloor$$
    $$\text{netProfit} = (\text{totalHarvests} \times \text{sellPrice}) - \text{seedCost}$$
    $$\text{dailyCropsProfit} = \frac{\text{netProfit}}{28}$$
    *Complejidad:* $O(1)$ temporal.
  * **Sobrecarga de operador `<`:** Compara directamente dos instancias de `Crop` con base en el valor de retorno de `dailyCropsProfit()`.
    *Complejidad:* $O(1)$ temporal.

---

## Análisis de Complejidad y Algoritmos

Para la organización de los cultivos según su rentabilidad se implementó el algoritmo **Merge Sort** dentro de una clase genérica con plantillas (`Sorts<T>`).

### 1. Merge Sort

- **Complejidad Temporal:**
  * **Todos los Casos:** $O(n \log n)$
    
  * **Justificación:** Primero, la función mergeSplit parte el arreglo a la mitad una y otra vez hasta que quedan elementos individuales, lo que forma un árbol de llamadas con una profundidad de $\log_2(n)$ niveles. Después, mergeArray va juntando y comparando esos pedazos en orden; recorrer y mezclar todos los elementos en cada nivel toma tiempo lineal, es decir, $O(n)$. Si multiplicas los $n$ pasos que toma mezclar por los $\log_2(n)$ niveles que tiene el árbol, el tiempo total siempre da $O(n \log n)$.

### 2. Justificación de Elección

Se seleccionó **Merge Sort** frente a otras alternativas por las siguientes razones:
1. **Rendimiento acotado en el peor caso:** Merge Sort garantiza un límite estricto de $O(n \log n)$ en cualquier escenario de entrada.
2. **Estabilidad:** Al ordenar colecciones de objetos, Merge Sort preserva el orden relativo original de aquellos cultivos que poseen la misma rentabilidad diaria (`dailyCropsProfit`).

---

## Interacción con el Usuario

El programa cuenta con un menú interactivo por consola que permite:
1. **Consultar todos los cultivos:** Aplica Merge Sort sobre la colección completa para presentar el orden de rentabilidad diaria general.
2. **Filtrar por temporada:** Permite al usuario seleccionar una estación específica (`Spring`, `Summer`, `Fall`), extrayendo los cultivos en $O(n)$ y ordenándolos en $O(n \log n)$.
3. **Salir:** Finaliza la ejecución del asistente de manera limpia.

---

## Instrucciones de Compilación y Ejecución

Debido al diseño modular basado en archivos de cabecera (`crop.h` y `mergeSort.h`), la compilación se realiza de manera directa sin requerir el enlazado manual de unidades de traducción adicionales:

```bash
g++ JunimosCropAssistant.cpp -o JunimosCropAssistant

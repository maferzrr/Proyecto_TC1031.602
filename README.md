# Junimo Crop Assistant - Planificador de Cultivos y Rentabilidad por Temporada

Este proyecto es una herramienta en C++ diseñada para optimizar la toma de decisiones agrícolas en el juego *Stardew Valley*. El asistente procesa una base de datos de cultivos, calcula su rentabilidad neta por día considerando si son de cosecha única o recurrente, y organiza la información mediante algoritmos de ordenamiento eficientes para ofrecer recomendaciones al jugador.

---

## Descripción del Proyecto y Diseño POO

El sistema carga los datos desde un archivo delimitado por comas (`crops.txt`) y modela cada registro mediante la clase `Crop`:

* **Atributos de `Crop`:**
  * `name` (`string`): Nombre del cultivo.
  * `season` (`string`): Temporada en la que crece (`Spring`, `Summer`, `Fall`).
  * `growDays` (`int`): Días requeridos para la primera cosecha.
  * `regrowDays` (`int`): Días que tarda en volver a producir (0 si no re-produce).
  * `sellPrice` (`int`): Precio de venta del producto.
  * `seedCost` (`int`): Costo de compra de la semilla.

* **Lógica Financiera Implementada:**
  * **Cosecha única (`regrowDays == 0`):**
    $$\text{dailyCropsProfit} = \frac{\text{sellPrice} - \text{seedCost}}{\text{growDays}}$$

  * **Cosecha múltiple (`regrowDays > 0`) a lo largo de una temporada (28 días):**
    $$\text{totalHarvests} = 1 + \left\lfloor \frac{28 - \text{growDays}}{\text{regrowDays}} \right\rfloor$$

    $$\text{netProfit} = (\text{totalHarvests} \times \text{sellPrice}) - \text{seedCost}$$

    $$\text{dailyCropsProfit} = \frac{\text{netProfit}}{28}$$

  * **Sobrecarga de operador `<`:** Compara directamente dos instancias de `Crop` con base en el valor de retorno de `dailyCropsProfit()`.

---

## Análisis de Complejidad y Algoritmos 
Para este primer avance se implementó el algoritmo de ordenamiento **Merge Sort** dentro de una clase genérica con plantillas (`Sorts<T>`).

### 1. Merge Sort

* **Complejidad Temporal:**
  * **Peor caso: $O(n \log n)$**
  * **Mejor caso: $O(n \log n)$**
  * **Caso promedio: $O(n \log n)$**
  * **Justificación:** En cada nivel de recursión, divide el vector a la mitad (`mergeSplit`), lo que genera una profundidad de árbol de llamadas de orden $O(\log n). Posteriormente, el procedimiento de unión (`mergeArray`) recorre todos los elementos de los subarreglos para compararlos y copiarlos linealmente, requiriendo $O(n)$ operaciones por nivel. En cada nivel se realizan comparaciones proporcionales a $n$, el costo temporal es estrictamente $O(n \log n)$ sin importar el orden inicial de los datos.

### 2. Justificación de Elección 

Se seleccionó **Merge Sort** frente a otras alternativas (como QuickSort o Bubble Sort) debido a dos factores determinantes:
1. **Garantía en el peor de los casos:** A diferencia de QuickSort, cuyo rendimiento puede degradarse a $O(n^2)$ con particiones desbalanceadas, Merge Sort garantiza un tiempo acotado a $O(n \log n)$ incluso en los peores escenarios de entrada.
   
2. **Estabilidad:** Es un algoritmo estable, lo que garantiza que dos cultivos con idéntica ganancia diaria mantendrán su orden relativo de aparición original.

---

## Instrucciones de Compilación y Ejecución

Para compilar el programa utilizando `g++` asegurando el enlazado de todos los módulos fuente:

```bash
g++ JunimosCropAssistant.cpp crop.cpp -o JunimosCropAssistant

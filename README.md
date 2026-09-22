# Junimo Crop Assistant - Planificador de Cultivos y Rentabilidad por Temporada

Este proyecto es una herramienta en C++ diseñada para optimizar la toma de decisiones agrícolas en el juego *Stardew Valley*[cite: 5]. El asistente procesa una base de datos de cultivos, calcula su rentabilidad neta por día considerando si son de cosecha única o recurrente, y organiza la información mediante algoritmos de ordenamiento eficientes para ofrecer recomendaciones al jugador[cite: 5].

---

## Descripción del Proyecto y Diseño POO

El sistema carga los datos desde un archivo delimitado por comas (`crops.txt`) y modela cada registro mediante la clase `Crop`[cite: 5]:

* **Atributos de `Crop`[cite: 5]:**
  * `name` (`std::string`): Nombre del cultivo[cite: 5].
  * `season` (`std::string`): Temporada en la que crece (`Spring`, `Summer`, `Fall`)[cite: 5].
  * `growDays` (`int`): Días requeridos para la primera cosecha[cite: 5].
  * `regrowDays` (`int`): Días que tarda en volver a producir (0 si no re-produce)[cite: 5].
  * `sellPrice` (`int`): Precio de venta del producto[cite: 5].
  * `seedCost` (`int`): Costo de compra de la semilla[cite: 5].

* **Lógica Financiera Implementada:**
  * **Cosecha única (`regrowDays == 0`)[cite: 5]:**
    $$\text{dailyCropsProfit} = \frac{\text{sellPrice} - \text{seedCost}}{\text{growDays}}$$
[cite: 5]
  * **Cosecha múltiple (`regrowDays > 0`) a lo largo de una temporada (28 días)[cite: 5]:**
    $$\text{totalHarvests} = 1 + \left\lfloor \frac{28 - \text{growDays}}{\text{regrowDays}} \right\rfloor$$
[cite: 5]
    $$\text{netProfit} = (\text{totalHarvests} \times \text{sellPrice}) - \text{seedCost}$$
[cite: 5]
    $$\text{dailyCropsProfit} = \frac{\text{netProfit}}{28}$$
[cite: 5]
  * **Sobrecarga de operador `<`:** Compara directamente dos instancias de `Crop` con base en el valor de retorno de `dailyCropsProfit()`[cite: 5].

---

## Análisis de Complejidad y Algoritmos (SICT0301 & SICT0302)

Para este primer avance se implementó el algoritmo de ordenamiento **Merge Sort** dentro de una clase genérica con plantillas (`Sorts<T>`)[cite: 2, 4, 5].

### 1. Merge Sort

* **Complejidad Temporal:**
  * **Peor caso: $O(n \log n)$**
  * **Mejor caso: $O(n \log n)$**
  * **Caso promedio: $O(n \log n)$**
  * **Justificación:** El algoritmo aplica la técnica de divide y vencerás[cite: 2]. En cada nivel de recursión, divide el vector a la mitad (`mergeSplit`), lo que genera una profundidad de árbol de llamadas de orden $O(\log n)$[cite: 2]. Posteriormente, el procedimiento de unión (`mergeArray`) recorre todos los elementos de los subarreglos para compararlos y copiarlos linealmente, requiriendo $O(n)$ operaciones por nivel[cite: 2]. Dado que el árbol siempre tiene $\log n$ niveles y en cada nivel se realizan comparaciones proporcionales a $n$, el costo temporal es estrictamente $O(n \log n)$ sin importar el orden inicial de los datos[cite: 2].

* **Complejidad Espacial:**
  * **Memoria auxiliar: $O(n)$**
  * **Justificación:** A diferencia de algoritmos en sitio como QuickSort o Insertion Sort, Merge Sort requiere espacio adicional de memoria temporal (vector auxiliar `tmp`) de tamaño proporcional a $n$ para almacenar los elementos mezclados antes de transferirlos de vuelta al vector principal[cite: 2].

### 2. Justificación de Elección (SICT0302)

Se seleccionó **Merge Sort** frente a otras alternativas (como QuickSort o Bubble Sort) debido a dos factores determinantes[cite: 4, 5]:
1. **Garantía en el peor de los casos:** A diferencia de QuickSort, cuyo rendimiento puede degradarse a $O(n^2)$ con particiones desbalanceadas, Merge Sort garantiza un tiempo acotado a $O(n \log n)$ incluso en los peores escenarios de entrada[cite: 5].
2. **Estabilidad:** Es un algoritmo estable, lo que garantiza que dos cultivos con idéntica ganancia diaria mantendrán su orden relativo de aparición original[cite: 5].

---

## Competencias y Estándares Desarrollados

* **SICT0301 (Evalúa los componentes):** Se realizó el análisis formal de complejidad temporal ($O(n \log n)$) y espacial ($O(n)$) para Merge Sort detallando las etapas de división y mezcla recursiva[cite: 2, 4].
* **SICT0302 (Toma decisiones):** Se justificó la selección del algoritmo de ordenamiento demostrando por qué su garantía $O(n \log n)$ y su estabilidad benefician la organización de los cultivos[cite: 4, 5].
* **SICT0303 (Implementa acciones científicas):** Se implementó una solución modular en C++ aplicando programación orientada a objetos, lectura robusta de flujos de archivos (`ifstream`, `stringstream`), sobrecarga de operadores y programación genérica con plantillas (`template <class T>`)[cite: 2, 4].
* **SEG0701 (Cultura digital):** El código se organiza bajo control de versiones con Git/GitHub, promoviendo el desarrollo de software estructurado, reproducible y documentado[cite: 4].

---

## Instrucciones de Compilación y Ejecución

Para compilar el programa utilizando `g++` asegurando el enlazado de todos los módulos fuente:

```bash
g++ JunimosCropAssistant.cpp crop.cpp -o JunimosCropAssistant

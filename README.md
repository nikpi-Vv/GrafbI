
# GrafbI

Проект для генерации, анализа, чтения и сохранения неориентированных графов без петель и кратных рёбер.

## Возможности

- собственный класс `Graph`
- обход графа с помощью DFS
- метрики:
  - количество компонент связности
  - плотность
  - проверка на двудольность
  - количество мостов
  - количество точек сочленения
- генераторы:
  - complete
  - path
  - cycle
  - star
  - wheel
  - tree
  - cubic
  - random
  - complete_bipartite
  - components
  - bridges
  - articulation
- парсеры:
  - edges
  - matrix
  - dimacs
- сериализаторы:
  - edges
  - adj
  - dot
- консольное приложение
- автоматические тесты

## Ограничения

- графы неориентированные
- петли не допускаются
- кратные рёбра не допускаются

Дополнительные ограничения:
- `cubic` — число вершин должно быть чётным и не меньше 4
- `components` — число компонент не должно превышать число вершин
- `random` — вероятность должна быть от 0 до 1

## Структура проекта

- `include/graph` — граф и storage
- `include/algorithms` — DFS
- `include/metrics` — метрики
- `include/generators` — генераторы
- `include/parsers` — парсеры
- `include/serializers` — сериализаторы
- `src/` — реализации
- `tests/` — тесты
- `app/main.cpp` — CLI
- `external/catch2` — Catch2
- `Makefile` — сборка

## Сборка

```bash
mingw32-make
````

## Запуск тестов

```bash
mingw32-make run-tests
```

## Очистка

```bash
mingw32-make clean
```

## Команды CLI

### Генерация графа

Формат:

```bash
.\bin\app.exe generate <type> <size> <serializer> <output>
```

Примеры:

```bash
.\bin\app.exe generate path 5 edges out.edges
.\bin\app.exe generate cycle 6 adj out.txt
.\bin\app.exe generate tree 7 dot tree.dot
.\bin\app.exe generate cubic 6 adj cubic.txt
```

### Генерация случайного графа

```bash
.\bin\app.exe generate random <size> <probability> <serializer> <output>
```

Пример:

```bash
.\bin\app.exe generate random 6 0.3 edges random.edges
```

### Генерация графа с двумя параметрами

Подходит для:

* `complete_bipartite`
* `components`
* `bridges`
* `articulation`

Формат:

```bash
.\bin\app.exe generate <type> <first> <second> <serializer> <output>
```

Примеры:

```bash
.\bin\app.exe generate complete_bipartite 2 4 adj bip.txt
.\bin\app.exe generate components 10 3 adj comp.txt
.\bin\app.exe generate bridges 8 4 adj br.txt
.\bin\app.exe generate articulation 8 3 adj art.txt
```

### Вычисление метрик

Формат:

```bash
.\bin\app.exe metric <metric_name> <parser_type> <input>
```

Где:

* `metric_name`:

  * components
  * density
  * bipartite
  * bridges
  * articulation

* `parser_type`:

  * edges
  * matrix
  * dimacs

Примеры:

```bash
.\bin\app.exe metric components edges out.edges
.\bin\app.exe metric density edges out.edges
.\bin\app.exe metric bridges edges out.edges
```

## Форматы файлов

### `.edges`

Список рёбер:

```text
1 2
2 3
3 4
```

### `.adj` / `.txt`

Список смежности:

```text
1: 2 5
2: 1 3
3: 2 4
```

### `.dot`

Формат GraphViz:

```text
graph G {
    1;
    2;
    1 -- 2;
}
```

## Тесты

В проекте есть тесты на:

* граф
* метрики
* генераторы
* парсеры
* сериализаторы

Во время тестов могут создаваться временные файлы в корне проекта, например:

* `test_graph.edges`
* `test_empty.dot`
* `test_adj.txt`
* `test_matrix.txt`

Это нормально.

## Кратко про архитектуру

* `Graph` — внешний класс графа
* `AdjacencyListStorage` — хранение графа
* `Dfs` — отдельный обход
* `Metrics` — отдельные метрики
* `BasicGenerators` — генераторы
* `Parsers` — чтение из файлов
* `Serializers` — сохранение в файлы
* `main.cpp` — консольный интерфейс


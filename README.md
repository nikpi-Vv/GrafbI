# GrafbI

Проект по работе с неориентированными графами без петель и кратных рёбер.

Программа умеет:

- хранить граф в собственной структуре данных
- обходить граф с помощью DFS
- вычислять основные метрики графа
- генерировать разные типы графов
- читать графы из файлов в нескольких форматах
- сохранять графы в нескольких форматах
- работать через консольное приложение
- проверяться автоматическими тестами

---

## 1. Идея проекта

В проекте реализован собственный класс `Graph`, который представляет неориентированный граф без петель и кратных рёбер.

Внутри граф хранится через отдельный backend хранения. Сейчас используется список смежности.

Также в проекте есть:

- отдельный обход DFS
- отдельные классы для метрик
- отдельные генераторы графов
- отдельные парсеры форматов входных файлов
- отдельные сериализаторы форматов выходных файлов
- консольное приложение для работы с проектом
- тесты

---

## 2. Основные ограничения

Проект работает со следующими ограничениями:

- графы **неориентированные**
- **петли запрещены**
- **кратные рёбра запрещены**
- вершины нумеруются целыми положительными числами, начиная с `1`

Некоторые генераторы имеют дополнительные ограничения, они описаны ниже.

---

## 3. Структура проекта

```text
GrafbI/
  include/
    algorithms/
      Dfs.h

    generators/
      BasicGenerators.h
      IGraphGenerator.h

    graph/
      AdjacencyListStorage.h
      Graph.h
      IGraphStorage.h

    metrics/
      Metrics.h

    parsers/
      IGraphParser.h
      Parsers.h

    serializers/
      IGraphSerializer.h
      Serializers.h

  src/
    algorithms/
      Dfs.cpp

    generators/
      BasicGenerators.cpp

    graph/
      AdjacencyListStorage.cpp
      Graph.cpp

    metrics/
      Metrics.cpp

    parsers/
      Parsers.cpp

    serializers/
      Serializers.cpp

  tests/
    test_main.cpp
    test_graph.cpp
    test_metrics.cpp
    test_generators.cpp
    test_parsers.cpp
    test_serializers.cpp

  app/
    main.cpp

  external/
    catch2/
      catch_amalgamated.hpp
      catch_amalgamated.cpp

  bin/
    tests.exe
    app.exe

  Makefile
  README.md# 
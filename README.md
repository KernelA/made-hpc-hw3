# HW 3 OpenMP

## Требования для запуска

1. CMake 3.17 или выше.
2. Компилятор с поддержкой C++17.
3. Установленный OpenMP.

## Задания

### Демонстрационные файлы

[CMake для сборки всех примеров](openmp/CMakeLists.txt)

### Программа с багами и их исправление

[Сравнение изменений в файлах после исправления ошибок](https://github.com/KernelA/made-hpc-hw3/compare/code-with-bugs...code-fixed?diff=split)

Можно было бы не использовать `printf`, но это оставлено с добавлением `critical` для целей отладки.

[Тесты запускаются автоматически через GitHub Actions в стадии Run tests](https://github.com/KernelA/made-hpc-hw3/compare/code-with-bugs...code-fixed?diff=split)

[![autobuild](https://github.com/KernelA/made-hpc-hw3/actions/workflows/build.yaml/badge.svg?branch=master)](https://github.com/KernelA/made-hpc-hw3/actions/workflows/build.yaml)

## Как запустить

Создать директорию: `build`.
```
mkdir build
cmake -S . -B ./build
```

Выполнить CMake:
```bash
cmake --build ./build --config Release --parallel $(nproc) --target all
```

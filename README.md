# 🔍 MegaByte Finder

Утилита под Windows для быстрого поиска крупных файлов на диске и очистки память накопителя.

---

## ✨ Основные возможности

* **Асинхронное сканирование:** Фоновый поиск файлов без подвисания интерфейса.
* **Фильтрация по размеру:** Мгновенный просмотр объектов от определённого порога (10 MB, 100 MB, 1 GB и т.д.).
* **Сортировка по убыванию:** Автоматическое ранжирование найденных файлов от самых крупных к меньшим.
* **Тёмный интерфейс:** Удобный кастомный GUI в стиле тёмной темы с встроенным логом.
* **Системные уведомления:** Оповещение в трее Windows по завершении глубокого сканирования.

---

## 🛠 Технологический стек

* **Язык:** C++20
* **Фреймворк:** Qt 6 (Qt Quick / QML, QtConcurrent)
* **Система сборки:** CMake

---

## 📥 Установка и запуск

Готовые бинарные сборки доступны в разделе **[Releases](../../releases)**:

1. **Installer (`MegaByteFinder_Setup_v1.0.exe`):** Запустите мастер установки для развертывания приложения в систему.
2. **Portable ZIP (`MegaByte_Finder_Release.zip`):** Распакуйте архив в любую папку и запустите `appMegaByte_Finder.exe`.

---

## 🔧 Сборка из исходников

Для самостоятельной сборки потребуется **Qt 6.x** и компилятор **MSVC 2022** или **MinGW**:

```bash
# Клонирование репозитория
git clone [https://github.com/qxlydo/MacroMicro.git](https://github.com/qxlydo/MacroMicro.git)
cd MacroMicro

# Конфигурация и сборка через CMake
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Credits

Application icon by [Aficons studio](https://www.flaticon.com/authors/aficons-studio) from [Flaticon](https://www.flaticon.com/).

[Search file icon](https://www.flaticon.com/ru/free-icon/search-file_16700618)

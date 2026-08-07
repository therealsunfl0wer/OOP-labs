# 🧑‍💻 OOP (Об'єктно-орієнтоване програмування) — Lab Checklist

Use this checklist to track
progress on the six hands-on labs.

> **Toolchain note:** the source manual targets Microsoft Visual Studio +
> raw Win32 API. This repo instead uses **CMake + Qt** (Widgets/Core/Network)
> so the labs build and run on any OS. Qt's `QMainWindow` /
> `QWidget` / signal-slot system stands in for raw `WndProc` message
> handlers, and Qt Creator's "New Class" wizard is replaced by writing
> headers/sources directly. Where the brief says "Win32 project" or
> "Windows Desktop Application", read that as "a Qt Widgets executable
> target" below.

- **`[ ]` Not Started**
- **`[➖]` In Progress**
- **`[✅]` Completed**

| Status | Folder                    | Assignment Topic                                                 | Deadline |
| :----: | :------------------------ | :--------------------------------------------------------------- | :------: |
|  [✅]   | `1-vs-setup`              | **Dev Environment & Modular C++ Project Setup**                  |    —     |
|  [ ]   | `2-shape-editor`          | **OOP Graphics Editor (Encapsulation/Inheritance/Polymorphism)** |    —     |
|  [ ]   | `3-ui-widgets`            | **User Interface Controls & Elements**                           |    —     |
|  [ ]   | `4-editor-refactor`       | **Editor Architecture Refactor (Decoupling)**                    |    —     |
|  [ ]   | `5-multiwindow-editor`    | **Multi-Window UI & Singleton Pattern**                          |    —     |
|  [ ]   | `6-message-driven-system` | **Message-Driven Multi-Component System**                        |    —     |

_(Deadlines are not yet specified)_

---

## 📝 Task Quick-Reference

1. **Setup:** Create a modular C++/Qt project (`Lab1`). Windows is a
   "message-driven application" in the original brief - replicate that with
   a `QApplication`/`QMainWindow` event loop instead of a raw `WndProc`.
   Compile, run, debug, and write up the result.
2. **Shape Editor:** Build a simple graphical object editor demonstrating
   encapsulation, type abstraction, inheritance, and polymorphism - a base
   shape class with derived shapes (line, rectangle, ellipse, etc.) drawn
   and manipulated on a canvas (`QPainter`/`QWidget::paintEvent`).
3. **UI Widgets:** Build a user-interface layer with standard controls
   (buttons, text fields, radio buttons, list boxes). Original brief uses
   raw Win32 child-window controls; use `QPushButton`, `QLineEdit`,
   `QRadioButton`, `QListWidget`, etc., wired up with Qt's signals/slots.
4. **Editor Refactor:** Redesign Lab 2's editor to fix tight coupling -
   the brief specifically calls out the anti-pattern of one class having a
   dedicated method per concrete shape type. Refactor toward a **Factory**
   (or similar creational pattern) so new shape types can be added without
   modifying the editor class.
5. **Multi-Window UI:** Extend the editor to a multi-window interface and
   implement the **Singleton** pattern (e.g. one shared document/state
   manager instance across windows). Use `QMainWindow`/`QDialog` instances
   for the extra windows.
6. **Message-Driven System:** Build a small system of **independent
   programs** (separate executables) that communicate via messages -
   e.g. two Qt processes exchanging data over `QLocalSocket`/`QUdpSocket`
   or named pipes, echoing the "object" (Alan Kay-style, cell-like,
   message-passing) view of OOP from the theory section.

---

## 🛠 Building

Each lab is its own CMake target so you can build/debug labs independently.

```bash
# Configure once (generates compile_commands.json for clangd)
cmake -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x/gcc_64

# Build a single lab
cmake --build build --target lab1

# Run it
./build/1-vs-setup/lab1
```

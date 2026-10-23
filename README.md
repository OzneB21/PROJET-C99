# SVG Shape Manager

A lightweight C99 command-line application designed to create, modify, and export 2D vector shapes into standard SVG format.

---

## Features

- **Interactive CLI Menu:** Easily navigate through shape management actions.
- **Supported Shapes:** Create, edit, and delete Lines, Ovals, and Rectangles.
- **Fixed Canvas Slots:** Manage up to 50 active shape slots (indices `0` to `49`).
- **Custom Styling & Transformations:** Customize shape attributes including:
  - Fill and border (stroke) colors
  - 2D Translations
  - Rotations
- **Export to SVG:** Render and save your complete drawing directly to `output.svg`.

---

## Requirements

- A **C compiler** supporting C99 standard (e.g., `gcc` or `clang`)
- **GNU Make**

---

## Building and Running

### Build the Project
Compile the source code into the `main` executable:

```bash
make
```

### Run the Application
Execute the compiled program:

```bash
./main
```

### Build and Run in One Step
Conveniently compile and launch the program immediately:

```bash
make run
```

---

## How to Use

When launched, the program displays an interactive menu with the following choices:

1. **Create a Shape:** Select shape type (Line, Oval, Rectangle) and assign it to an index (`0–49`). You will be prompted to enter geometry specifications (dimensions or coordinates) and styling properties.
2. **Modify a Shape:** Update the geometry, colors, translation, or rotation of an existing shape by its index.
3. **Delete a Shape:** Remove a shape at a specified index.
4. **Display Shapes:** Review all active shapes currently stored in memory.
5. **Export to SVG:** Write the current canvas configuration out to `output.svg`.
6. **Quit:** Exit the program.

---

## Cleaning Up

To remove generated binaries and object files:

```bash
make clean
```

***


[ My Linkedin](www.linkedin.com/in/enzo-baroni-71a03b21b)
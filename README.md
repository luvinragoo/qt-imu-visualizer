# qt-imu-visualizer

**Author:** Luvin Ragoo  
**Date:** 23 February 2026

A real-time IMU data visualization desktop application built with **Qt 6 (C++)**.  
Receives live sensor data from an **ESP32 + MPU6050** over **UDP**, and plots it on a scrolling live chart using **Qt Charts**.

Built as a portfolio project demonstrating embedded-to-desktop communication using the full UDP stack.

---

## Features

-  **Live UDP receiver** — listens on port `5005` for incoming IMU packets from an ESP32
-  **Scrolling QChart** — displays the last 100 samples of accelerometer X-axis data in real time
-  **IMUSensor abstraction class** — a reusable C++ class for managing multi-axis sensor calibration
-  **Qt Signals & Slots** — event-driven architecture; UI updates only when data arrives
-  **CMake build system** — clean, modern CMake configuration for Qt projects

---

## System Architecture

```
ESP32 (Core 0 - WiFi Task)
        │
        │  UDP packets over WiFi
        │  Format: IMU,<timestamp>,<ax>,<ay>,<az>,<gx>,<gy>,<gz>
        ▼
Qt Desktop App (port 5005)
        │
        ├── QUdpSocket  →  onDataReceived() slot
        ├── Parses CSV payload
        └── Appends ax to QLineSeries → scrolling QChart
```

---

## Packet Format

The ESP32 transmits packets as CSV strings over UDP:

```
IMU,<timestamp_ms>,<ax>,<ay>,<az>,<gx>,<gy>,<gz>
```

| Field | Description | Unit |
|---|---|---|
| `IMU` | Packet type identifier | — |
| `timestamp_ms` | Milliseconds since boot | ms |
| `ax`, `ay`, `az` | Accelerometer readings | g |
| `gx`, `gy`, `gz` | Gyroscope readings | °/s |

---

## Project Structure

```
qt-imu-visualizer/
├── CMakeLists.txt       # Build configuration
├── main.cpp             # App entry point; IMUSensor smoke test
├── mainwindow.h/.cpp    # Main window: chart, UDP socket, signal handling
├── mainwindow.ui        # Qt Designer UI file
├── IMUSensor.h/.cpp     # Sensor abstraction class (calibration, multi-axis)
└── test_udp.py          # Python script to simulate ESP32 UDP packets
```

---

## Getting Started

### Prerequisites

- Qt 6.x with `Qt Charts` module
- CMake ≥ 3.16
- A C++17-compatible compiler (MSVC / GCC / Clang)

### Build

```bash
git clone https://github.com/luvinragoo/qt-imu-visualizer.git
cd qt-imu-visualizer
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt6
cmake --build .
```

### Run

1. Launch the application — it immediately begins listening on **UDP port 5005**
2. Either connect a live ESP32 streaming IMU data, or run the test script:

```bash
python test_udp.py
```

The test script simulates the ESP32 by sending UDP packets formatted as `IMU,<timestamp>,<ax>,...` to `localhost:5005`.

---

## IMUSensor Class

A lightweight C++ class for representing a named, multi-axis sensor with per-axis calibration offsets.

```cpp
IMUSensor mpu("MPU6050", 3);
mpu.setCalibration(0, 0.02f);   // X offset
mpu.setCalibration(1, -0.01f);  // Y offset
mpu.setCalibration(2, 0.00f);   // Z offset
```

Manages its own memory via constructor/destructor — no smart pointers, intentionally demonstrating manual RAII.

---

## Roadmap

- [ ] Plot all 6 axes (3× accelerometer + 3× gyroscope) simultaneously
- [ ] Configurable UDP port via UI
- [ ] Export data to CSV
- [ ] 3D orientation rendering (quaternion / Euler angles)
- [ ] ESP32 firmware source code linked as submodule

---

## Tech Stack

| Component | Technology |
|---|---|
| Desktop App | Qt 6 / C++17 |
| Charting | Qt Charts (`QLineSeries`, `QChart`) |
| Networking | `QUdpSocket` |
| Embedded Sender | ESP32 (FreeRTOS WiFi task) |
| Sensor | MPU6050 (6-DOF IMU) |
| Build System | CMake |
| Test Simulator | Python 3 (`socket` module) |

---

## About

This project was built in February 2026 as part of interview preparation, demonstrating:
- Full-stack embedded systems development (firmware → network → desktop)
- Modern C++ practices with Qt framework
- Real-time data visualization techniques
- Network protocol design and implementation

---

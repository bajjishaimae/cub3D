# 🕹️ cub3D

**cub3D** is a simple 3D game engine inspired by early raycasting games like Wolfenstein 3D, built as part of the 42 curriculum. It uses raycasting to render a 3D world from a 2D map.

## 📁 Project Structure

- `mandatory/` — Core implementation of the game
- `bonus/` — Enhanced version with extra features (e.g. minimap, animations, mouse handling, sound, etc.)
- `MLX42/` — The graphics library used (needs to be cloned from GitHub)

## ⚙️ Dependencies

This project uses the **MLX42** graphics library, which depends on **GLFW** and **CMake**.

1. Clone the MLX42 Library

Before compiling, you must clone the `MLX42` repo inside your project directory:

```bash
git clone https://github.com/codam-coding-college/MLX42.git
```
2. Install Required Packages
If you don’t have cmake and glfw installed on your machine, you can install them using Homebrew (macOS):
```bash
brew install glfw
brew install cmake
```
⚠️ If you're not using macOS or not using Homebrew, please refer to your system’s package manager or the [MLX42 repo](https://github.com/codam-coding-college/MLX42.git) for proper installation.

3. Build Instructions
To build the project, run:
```bash
make
```
4. To build the bonus version, run:
```bash
make bonus
```
5. Running the Game
Once compiled, launch the game with:

```bash
./cub3D [map_file.cub]
```
Make sure to provide a valid `.cub` map file!

Bonus Features
The bonus version includes:

A dynamic minimap

Mouse movement support

Basic animations

Sound effects

## Screenshots: 

<img width="1800" height="998" alt="Screen Shot 2025-08-15 at 4 55 58 PM" src="https://github.com/user-attachments/assets/3814e7c1-fbc3-4b93-889c-403bf7c9ab35" />


<img width="1800" height="998" alt="Screen Shot 2025-08-15 at 4 57 32 PM" src="https://github.com/user-attachments/assets/3b84180a-9c36-4ead-9f17-3f067351ba40" />


<img width="1494" height="998" alt="Screen Shot 2025-08-15 at 4 42 30 PM" src="https://github.com/user-attachments/assets/82e94a32-1fcd-4163-8870-9c3c738770d1" />



https://github.com/user-attachments/assets/7af60a8c-eaf6-4c15-a96f-0194f47d4b02





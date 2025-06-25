# 🕹️ cub3D: My First 3D Game Engine Adventure 🚪  
Welcome to **Cub3D**, a raycasting-based 3D game where I built a first-person perspective engine from scratch—just like in Wolfenstein 3D!  
✨ This project brought together math, graphics, input handling, and game logic. It’s where C meets creativity and code becomes immersive! 🎮🧠

---

## 🌄 The Goal

Using a simple `.cub` map file and the **MiniLibX** graphics library, I created:

- A 3D environment with walls, player movement, and textures  
- A working minimap 🧭  
- A functional raycasting engine using DDA (Digital Differential Analysis)  
- Smooth controls: move, rotate, explore!  

---

## 🌟 Features

🎯 **Raycasting Engine**  
<li>Draws vertical slices of walls based on distance from player  
<li>Uses DDA to find wall hits efficiently  
<li>Supports textures for walls (N, S, E, W)

🧍‍♂️ **Player Movement**  
<li>WASD to move  
<li>← → to rotate  
<li>Collision detection (no walking through walls!)

🗺️ **Map Parsing**  
<li>Reads `.cub` config files  
<li>Checks for valid format and closed walls  
<li>Handles player spawn, textures, RGB colors

🖼️ **MiniLibX Integration**  
<li>Window creation, pixel rendering, and image handling  
<li>Cross-platform graphics (macOS/Linux depending on setup)

---

## 💡 What I Learned

Cub3D was a HUGE learning leap:

- 🎲 Raycasting and 3D simulation on a 2D grid  
- 🧮 Geometry, trigonometry, and math in game development  
- 🎨 Texture mapping and pixel-by-pixel drawing  
- 🛠️ Parsing complex input formats safely  
- 🧠 Structuring large C projects with multiple modules  

---

## Controls:

W / A / S / D to move

← / → arrows to rotate

ESC to quit

## Map:

1111111111  
1000000001  
1000000001  
100P000001  
1111111111

# **Industrialism**

_3D Game made in C++ using Vulkan_

---
**Industrialism** is an in-dev game (mostly the engine), focused on _technical_ and _logical_ aspects[^1]

This is something like changelog:

19.04.24 (or earlier)

- finds and loads defined vulkan validation layers and extensions
- creates a vulkan instance
- creates a configurable vulkan debug messenger
- finds all available GPUs, checks if they support needed functions and statistics, and sorts them based on their stats, then it picks the best one
- creates a logical device for GPU communication with the software
- loading a precompiled shader files (but it doesn't use them)\

20.04.24

- it creates a window surface that can be configured for specific support (X.org, Win32, Wayland, Metal, ...), and checks for its support on the GPU
- support for more queue families (`std::vector` system), currently just two queues: graphics and present queue 

21.04.24

- engine rewrite, `vk-bootrstrap` library now do all the vulkan boilerplate you must do to even see something in the window...
- currently, all the earlier changelog things should be okay (it's a few hundred lines of code less)
- the `vk-bootrstrap` will be removed when I want to jog and change this boilerplate stuff etc., but it's not fun for me + it's very time-consuming to write this boilerplate code, and you get really nothing from it (on start, later I'll want to change things...)

11.05.24

_yeah little break_
- displaying something to the window (blue to black flashing)
- fences and semaphores for waiting for the gpu rendering (draw) loop
- some optimization and stuff

16.05.24

- I'm feeling stupid, but redoing the project for the third time. I hope it's the last time :D
- the `vk-bootstrap` library is removed now
- window creation, instance creation, and vk extension listing are >"rewritten"

Please be aware that this is a very early version, it really does nothing now, but it'll grow to a larger game engine!\
I'm typing all these things that are mandatory for a game engine, but I want to express myself here, because of the time I take to write the actual code.

_I know that this changelog will grow, so maybe I'll store all these things in some .txt file and add a link to it ;)_

### What I want it to be

---

- rapid engine, capable of rendering complex things
- good gameplay
- at least some story
- effortless modding system (with custom 'scripting' language or something like lua)

### Contribution

---

I'd really be happy if anyone would contribute to this lil project 'o mine, so if you have anything to say or want to change, edit or add to the code, just create a pull request, and I'm going to look at it asap!\
But if you create a pull request, please describe what are you changing and what it does. And keep the code in good shape and maybe add a little documentation (few comments) to it.\
The same is with the readme, if you want to change something, make a pull request.

### Nerd Info

---

- it runs on vulkan 1.3
- c++ standard is 2023 version
- it is built on (for now, maybe forever) cmake build system with a main app and engine 'library' that is compiled with the needed libraries, classes and files
- libraries the engine is using:
    - [GLFW](https://github.com/glfw/glfw) (for window and input handling)
    - [glm](https://github.com/g-truc/glm) (for math)
    - [vk-bootstrap](https://github.com/charles-lunarg/vk-bootstrap) (for vulkan boilerplate code)

### Contact

---

My Discord name is kikismine

[^1]: Survival or something similar is considered too.

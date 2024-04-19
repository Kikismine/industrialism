# **Industrialism**

_3D Game made in C++ using Vulkan_

---
**Industrialism** is an in-dev game (mostly the engine), focused on _technical_ and _logical_ aspects[^1]

Currently, it does this:

- finds and loads defined vulkan validation layers and extensions
- creates a vulkan instance
- creates a configurable vulkan debug messenger
- finds all available GPUs, checks if they support needed functions and statistics, and sorts them based on their stats, then it picks the best one
- creates a logical device for GPU communication with the software
- loading a precompiled shader files (but it doesn't use them)

Please be aware that this is a very early version, it really does nothing now, but it'll grow to a larger game engine!\
I'm typing all these things that are mandatory for a game engine, but I want to express myself here, because of the time I take to write the actual code.

_I know that this list will grow, so maybe I'll store all these things in some .txt file and add a link to it ;)_

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

### Contact

---

My Discord name is kikismine

[^1]: Survival or something similar is considered too.
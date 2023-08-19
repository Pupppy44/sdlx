<p align="center"> <img width="default" height="250"
        src="https://cdn.discordapp.com/attachments/736359303744585821/1142576969708474399/image.png">
</p>

# **sdlx** - A C++ SDL2 Extension and Toolkit

`sdlx` is a library that makes it easier to create applications with SDL2. The library provides classes such as window, text, image, and audio classes to easily create advanced games and programs.

## Features

- Simple interface for creating and running a window
- Images, textboxes, rectangles, and audio
- Lambda event callbacks for SDL2 events and mouse clicks
- Customizable, lightweight, and easy-to-use

## Installation

To use `sdlx`, include all the files in the library to your project. You'll need **SDL2** and [**miniaudio**](https://github.com/mackron/miniaudio) (for audio).

## Example

Here's an ultimate example for this toolkit:
```cpp
App app;

app.Create("SDLX Example", 1216, 768); // Create a window with a title, width, and height (in pixels)
app.SetBackground({255, 255, 255, 255});
app.SetMusic("./example.mp3"); // Set the background music

app.Event([&](SDL_Event event) {
    switch (event.type) {
      // Handle SDL2 events
    }
    return true; // Return true to keep the loop callback, false to delete it from the application's list
});

// An example of adding a rectangle from this toolkit to the application
TkRect Banner;
Banner.x = 0;
Banner.y = 0;
Banner.w = 4.8 * 96;
Banner.h = .3 * 96;
Banner.color = { 114,137,218 }; // SDL2_Color
app.AddItem(Banner);

// ...Add more items here (like images, textboxes, and audio)

app.Start(); // This starts the application window. Use a thread if you want to reach code after this
```

## That's All
If you have any issues, feel free to create an issue or contact me. I plan on improving the code example, but this library will probably not be updated. Thanks!

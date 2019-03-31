# SMK (Simple multimedia kit)

The story of this library is simple, I wanted port a few SFML games to the web
by using WebAssembly. SFML wasn't supporting WebAssembly yet, so I had to
reimplement it myself. If you know the SFML, then SMK must be very familiar to
you.

## Opening a new Window:
~~~bash
  auto screen = smk::Screen(640, 480, "Title");
~~~

## The main loop:
~~~cpp
  void loop() {
    auto background_color = glm::vec4(0.0, 0.0, 0.0, 1.0);
    screen.Clear(background_color);

    [...] // Draw stuff

    screen.Display();
  }
~~~

## Images

### Loading textures
~~~cpp
  auto ball_texture = Texture("./ball.png");
~~~

### Displaying images (sprite)
~~~cpp
  Sprite ball_sprite;
  ball_sprite.SetTexture(ball_texture);
  auto position = glm::vec2(200,200);
  ball_sprite.SetPosition(position);
  screen.Draw(ball_sprite);
~~~


## Text
### Loading font
~~~
  auto font_arial = Font("./arial.ttf", 32);
~~~

### Displaying text
~~~cpp
  Text text;
  text.SetFont(font_arial);
  auto position = glm::vec2(200,200);
  text.SetPosition(position);
  screen.Draw(text);
~~~

## Transforming the view
~~~
  View view;
  view.SetCenter({200, 200});
  view.SetSize(320,240);
  screen.SetView(view);
~~~

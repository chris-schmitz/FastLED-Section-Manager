# Strip Section Manager

## Overview

The Strip Section Manager is a set of tools used to augment "sections" of an LED strip so that rows of a given "section" are treated like a single row of a normal LED strip.

![demo](./readme_attachments/level_by_level_demo.gif)
&nbsp;
![demo](./readme_attachments/gradient_demo.gif)

## E.g.

<!-- TODO: replace with picture of actual wiring -->

If a normal led strip had 20 leds in it and you considered 5 leds a section:

```
----- ----- ----- -----
```

The Section Manager could allow you to do something like make the middle "section" two rows:

```
----- ----- -----
      -----
```

And the two rows would be treated as one regular section.

You could then send a single red led animation across the strip like so:

TODO: add demo code once the classes are fully fleshed out

```c++
#define TOTAL_LEDS 20
CRGB leds[TOTAL_LEDS]

SectionManager sectionManager = SectionManager(leds);

sectionManager.addSections(3);

sectionManager.getSection(0).addPixelRange(0, 4);
sectionManager.getSection(1).addPixelRange(5, 9);
sectionManager.getSection(1).addPixelRange(10, 14);
sectionManager.getSection(2).addPixelRange(15, 19);

sectionManager.getSection(0).fillWithColor(0xFF0000, FillStyle(ALL_AT_ONCE));
//  Note that when we fill section 1, it fills all of the ranges at the same time
sectionManager.getSection(1).fillWithColor(0x00FF00, FillStyle(ALL_AT_ONCE));
sectionManager.getSection(2).fillWithColor(0x0000FF, FillStyle(ALL_AT_ONCE));
```

The leds in the middle section would light up, column by column, as if the color was being set for a single pixel.

<!-- TODO: fill in details including animated gifs -->

## Fill Styles

### All at once

### One at a time

### By "level"

## Assumptions and restrictions

Note that I'm developing this for a very specific light that has constraints that a more elaborate light wouldn't have. Also note that I'm not thinking of this light as a custom shaped matrix, this is specifically thinking of the strip still as a strip, just one that can get wider than a single line at points.

Because of that and because I'm trying to keep it simple so I can finish the actual project there are some assumptions and restrictions:

- Each row in a section starts at the same point
  - i.e. the starting point of a row can't be offset from another. That's possible, but it's outside of the scope of my current needs
- Each row in a given section has the exact same number of LEDs
  - Again, this is per the scope of my current project, the manager could be augmented to account for this as well, but keeping things simple and in scope

## Future considerations

- If throwing exceptions in arduino land jacks stuff up:
  - How do we handle "ok" out of bounds access? (right now we pass back a -1 index, but is that the best way of handling it?!)
  - How do we message back to the dev when an exceptional situation happens?
    - For this we could write a logger class that uses `Serial` to report back and inject that as a dependency so that the classes don't need to be tied to arduino just for logging

## To Dos

- Figure out a better name for the concept of "levels"
- Add in index offsetting per range
- Add in a way of iterating over all leds for all sections in a single loop

  - Like if you wanted to set each level one by one regardless of sections (but still applying section logic)

  ```c++
    // something like this

    for (int i = 0; i < sectionManager.totalLevels; i++){
      sectionManager.setGlobalLevel(i, 0xFF00FF);
      sectionManager.show();
      delay(100);
    }
  ```

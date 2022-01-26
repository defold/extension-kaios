# KaiOS extension
Defold native extension for use with KaiOS. See also [extension-kaiads](https://github.com/defold/extension-kaios) for KaiAds integration.

## KaiOS HTML template
The extension provides a [modified version](/kaios/engine_template.html) of the default `engine_template.html` from builtins. The modifications are:

* Removed "Made with Defold" and Fullscreen" `<div>`
* Hardcoded `Module['isWASMSupported']` to false (WASM is not supported on current KaiOS devices)
* Load `Defold.js` (see below)
* Canvas always resized to `fit`.

## KaiOS key support
The extension adds support for KaiOS specific keys:

* Left Softkey - Mapped to KEY_F1
* Right Softkey - Mapped to KEY_F2
* Call - Mapped to KEY_MENU


## API functions
The extension adds the following API functions:

### kaios.exit()
Close a KaiOS application (will call window.close()).

TODO: Should we instead use sys.exit() and hook into the application lifecycle somehow through the extension and do a `window.close()`?

### kaios.play_sound(sound, options)
Play a sound using JavaScript AudioContext. Sounds must be bundled using the "bundle resources" setting in game.project. Functionality for setting up an AudioContext and keeping track of audio buffers can be found in [`Defold.js`](https://github.com/refold/extension-kaios/blob/main/kaios/res/web/Defold.js) which is included with the extension.

```
-- play and loop sound
kaios.play_sound("sound.wav", { loop = true })
```


### kaios.stop_sound(sound)
Stop a sound played using `kaios.play_sound()`. Note: Sounds are of a "fire and forget" nature. If the same sound is played multiple times this function will only ever stop the most recently played instance of the sound.

```
kaios.stop_sound("sound.wav")
```

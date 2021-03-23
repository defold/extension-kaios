# extension-kaios
Defold native extension for use with KaiOS. See also [extension-kaiads](https://github.com/refold/extension-kaios) for KaiAds integration.

## Disclaimer
Experimental code for KaiOS. No support is provided! Code can change at any time.

### engine_template.html
Modified version of the default engine_template.html from builtins. This version changes a few things:

* Removed "Made with Defold" and Fullscreen" `<div>`
* Hardcoded `Module['isWASMSupported']` to false
* Load `Defold.js` (see below)
* Canvas always resized to `fit`.

## API functions
TODO: How many of the [KaiOS API functions](https://developer.kaiostech.com/api) are actually needed?

Additional API functions provided by this extension:

### kaios.exit()
Close a KaiOS application (will call window.close()).

TODO: Should we instead use sys.exit() and hook into the application lifecycle somehow through the extension and do a `window.close()`?

### kaios.play_sound(sound)
Play a sound using JavaScript AudioContext. Sounds must be bundled using the "bundle resources" setting in game.project. Functionality for setting up an AudioContext and keeping track of audio buffers can be found in [`Defold.js`](https://github.com/refold/extension-kaios/blob/main/kaios/res/web/Defold.js) which is included with the extension.

TODO: Can we use manifest merging to include `Defold.js` in the engine template in game.project?

```
kaios.play_sound("sound.wav")
```


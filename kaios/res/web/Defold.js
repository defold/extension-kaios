const AudioContext = window.AudioContext || window.webkitAudioContext;

var defold = {
	audioCtx: new AudioContext(),
	audioBuffers: {},
	audioSources: {},

	loadSoundFile: function(url) {
		return fetch(url).then(function(response) {
			return response.arrayBuffer();
		}).then(function(arrayBuffer) {
			return defold.audioCtx.decodeAudioData(arrayBuffer);
		}).then(function(audioBuffer) {
			defold.audioBuffers[url] = audioBuffer;
			return;
		}).catch(function(reason) {
			console.log(reason);
		});
	},

	hasAudioBuffer: function(url) {
		return defold.audioBuffers[url] != null;
	},

	// play a sound stored in an audio buffer
	playAudioBuffer: function(url, loop) {
		const audioBuffer = defold.audioBuffers[url];
		if (!audioBuffer) {
			console.err("No audio buffer loaded for " + url);
			return;
		}

		// check if context is in suspended state (autoplay policy)
		if (defold.audioCtx.state === 'suspended') {
			defold.audioCtx.resume();
		}
		// create audio buffer source and assign the buffer to it
		const bufferSource = defold.audioCtx.createBufferSource();
		bufferSource.buffer = audioBuffer;
		bufferSource.connect(defold.audioCtx.destination)
		bufferSource.loop = loop;
		bufferSource.start();

		// save audio buffer source for later (in case we need to stop it)
		defold.audioSources[url] = bufferSource;
	},

	// play a sound from a URL
	playAudioFromURL: function(url, loop) {
		if (defold.hasAudioBuffer(url)) {
			defold.playAudioBuffer(url, loop);
		}
		else {
			defold.loadSoundFile(url).then(function() {
				defold.playAudioBuffer(url, loop);
			}).catch(function(reason) {
				console.log(reason);
			});
		}
	},

	// stop the most recently played audio source for a give sound
	stopAudioFromURL: function(url) {
		if (defold.audioSources[url]) {
			defold.audioSources[url].stop();
			defold.audioSources[url] = null;
		}
	}
};

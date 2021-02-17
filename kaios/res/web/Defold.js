const AudioContext = window.AudioContext || window.webkitAudioContext;

var defold = {
	audioCtx: new AudioContext(),
	audioBuffers: {},

	fetchFile: async function(filepath) {
		const response = await fetch(filepath);
		const arrayBuffer = await response.arrayBuffer();
		const audioBuffer = await defold.audioCtx.decodeAudioData(arrayBuffer);
		return audioBuffer;
	},

	loadFile: function(filePath) {
		const audioBuffer = await defold.fetchFile(filePath);
		return audioBuffer;
	},

	playAudioBuffer: function(audioBuffer) {
		// check if context is in suspended state (autoplay policy)
		if (defold.audioCtx.state === 'suspended') {
			defold.audioCtx.resume();
		}
		const bufferSource = defold.audioCtx.createBufferSource();
		bufferSource.buffer = audioBuffer;
		bufferSource.connect(defold.audioCtx.destination)
		bufferSource.start();
		return bufferSource;
	},
	playAudioFromURL: function(url) {
		if (defold.audioBuffers[url]) {
			defold.playAudioBuffer(defold.audioBuffers[url]);
		}
		else {
			defold.loadFile(url).then((audioBuffer) => {
				defold.audioBuffers[url] = audioBuffer;
				defold.playAudioBuffer(audioBuffers[url]);
			});
		}
	}
};

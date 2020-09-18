(function () {
    var __aplay = Audio.prototype.play;
    Audio.prototype.play = function() {
        this.setAttribute('crossorigin', 'anonymous');
        document.body.appendChild(this);
        __aplay.call(this);
    };
    var __vplay = HTMLVideoElement.prototype.play;
    HTMLVideoElement.prototype.play = function() {
        var src = this.src;
        if (src && src.indexOf('cdn.videofarm.daum.net') == -1) {
            this.setAttribute('crossorigin', 'anonymous');
            if (src.indexOf('https://') === -1 && window && window.location
                && window.location.href && window.location.href.indexOf('https://') === 0) {
                src = src.replace('http://', 'https://');
            }
            if (src.substring(0, 5) !== "blob:") {
                this.src = src + '';
            }
        }

        __vplay.call(this);
    };
})();
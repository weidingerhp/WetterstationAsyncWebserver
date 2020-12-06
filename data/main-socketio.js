$(function () {
    // Hilfsvariablen für HTML-Elemente werden mit Hilfe von JQuery gesetzt.
    var $tempfield = $('#tempfield');
    var $hygfield = $('#hygfield');
    var gateway = `ws://${window.location.hostname}/ws`;
    var websocket;

    function initWebSocket() {
      console.log('Trying to open a WebSocket connection...');
      websocket = new WebSocket(gateway);
      websocket.onopen    = onOpen;
      websocket.onclose   = onClose;
      websocket.onmessage = onMessage; // <-- add this line
    }

    function onOpen(event) {
      console.log('Connection opened');
    }

    function onClose(event) {
      console.log('Connection closed');
      setTimeout(initWebSocket, 2000);
    }

    function onMessage(event) {
     console.log('Event received');
     var measurement = JSON.parse(event.data);

      $tempfield.text(measurement.temp);
      $hygfield.text(measurement.hyg);
    }

    initWebSocket();
});

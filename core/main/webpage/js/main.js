
//var ws = require("../../../../../ws/index.js")


let socket = new WebSocket("ws://localhost:9002");

// send message from the form
document.forms.publish.onsubmit = function() {
    let outgoingMessage = this.message.value;

    socket.send(outgoingMessage);
    return false;
};

// message received - show the message in div#messages
socket.onmessage = function(event) {
    let message = event.data;

    let messageElem = document.createElement('div');
    messageElem.textContent = message;
    document.getElementById('messages').prepend(messageElem);
}




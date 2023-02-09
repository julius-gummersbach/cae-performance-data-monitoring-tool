
//var ws = require("../../../../../ws/index.js")


let socket = new WebSocket("ws://localhost:9002");

// send message from the form
document.forms.publish.onsubmit = function() {
    let outgoingMessage = "G";
    //if(this.rhsThread.value !== ""){
    //    outgoingMessage +=
    //        ("2" + this.operation.textContent + "|" + this.rhsThread.textContent + "|" + this.threadName.value);
    //} else {
        outgoingMessage += "1" //+ this.lhsThread.selected().value;
    //}
    socket.send(outgoingMessage);
    return false;
};

// message received - show the message in div#messages
socket.onmessage = function(event) {
    let message = event.data.substring(1);

    // Is this is one of the first messages from the server that informs the tool of the given Threads
    //TODO make sure that in no other case a message from the server starts with "ST", or use a different identification method
    if(message.startsWith("T")){
        let lhsOptionElement = document.createElement('option');
        lhsOptionElement.value = message.substring(1);
        lhsOptionElement.textContent = "Thread " + message.substring(1);
        let rhsOptionElement = document.createElement('option');
        rhsOptionElement.value = message.substring(1);
        rhsOptionElement.textContent = "Thread " + message.substring(1);
        document.getElementById('lhsThread').prepend(lhsOptionElement);
        document.getElementById('rhsThread').prepend(rhsOptionElement);
        // If not:
    } else {
        //let splitMessage = message.split("|");
        //let test = document.createElement('div');
        //test.textContent = splitMessage[0];
        //document.getElementById('lhsThread').prepend(test);
        document.getElementById('graph_svg').src = message; //splitMessage[0];
    }
}




//WebSockets
var wsUri = "ws://" + location.host + "/index.html?command=true";
var output;

function init() {
	output = document.getElementById("output");
	testWebSocket();
}

function testWebSocket() {
	websocket = new WebSocket(wsUri);
	websocket.onopen = function(evt) {
		onOpen(evt)
	};
	websocket.onclose = function(evt) {
		onClose(evt)
	};
	websocket.onmessage = function(evt) {
		onMessage(evt)
	};
	websocket.onerror = function(evt) {
		onError(evt)
	};
}

function onOpen(evt) {
	// addCommandReply("CONNECTED");
	addCommandReply('<span style="color: red;">CONNECTED </span>');
	doSend("help");
}

function onClose(evt) {
	// addCommandReply("DISCONNECTED");
	addCommandReply('<span style="color: red;">DISCONNECTED </span>');
}

function onMessage(evt) {
	// addCommandReply('<span style="color: blue;">RESP: ' +
	// evt.data+'</span>');
	// websocket.close();
	// document.getElementById("commandReply").innerHTML += "<br>"+evt.data;
	addCommandReply('<span style="color: blue;">' + evt.data + '</span>');

}

function onError(evt) {
	addCommandReply('<span style="color: red;">ERROR:</span> ' + evt.data);
}

function doSend(message) {
	addCommandReply("SENT: " + message);
	websocket.send(message);
}

function writeToScreen(message) {
	var pre = document.createElement("p");
	pre.style.wordWrap = "break-word";
	pre.innerHTML = message;
	output.appendChild(pre);
}

window.addEventListener("load", init, false);

function addCommandReply(addString) {
	console.log(addString);
}

function connectBtn() {
	testWebSocket();
}

function disConnectBtn() {
	websocket.close();
}

function saveConfig() {
	doSend("ASd");
}

var intervalId; // keep the ret val from setTimeout()
function mousedownfunc(cmd) {
	
    intervalId = setInterval(runme, 200, cmd);
}

function mouseupfunc() {
    clearInterval(intervalId);
}

function runme(cmd) {
	doSend('Move ' + cmd);
}


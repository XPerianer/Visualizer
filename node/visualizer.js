// Beispiel für die Erstellung einen TCP-Empfängers
var tcp_client = 0;
var WebSocketServer = require('ws').Server
var DataGetter = new WebSocketServer({host: '0.0.0.0',port:8000});
DataGetter.on('connection',function(ws){


	console.log("Client(Control) connected to websocket");

	ws.on('message',function(message){ //(empfängt nachrichten)
		//console.log('Von Websocket-Client empfangen: ' + message);
		if(tcp_client != 0 && message.charAt(0) == '['){ //Very dirty way of checking if it's actually a fine message from the Painter(this is because it would sende a Client connected message if this wasn't checked)
		tcp_client.write(message);
		//console.log(message);
		};
	});

	ws.on('close',function(){
		ws.close();
	});


});

var net = require('net');

var DataSender = net.createServer(function (socket){
		tcp_client = socket;
		console.log("Client(DataSender) connected")
		socket.on('error',function(data){
			tcp_client = 0;
			console.log("Socket has thrown an error: " + data);
		});
		socket.on('close',function(data){
			tcp_client = 0;
			console.log("Client(DataSender) disconnected")
		});
});
DataSender.listen(1337,'0.0.0.0');


//Auslieferung der Webfiles
var connect = require('connect'),
    serveStatic = require('serve-static');

var app = connect();

app.use(serveStatic("webfiles/"));
app.listen(80);

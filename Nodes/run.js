//Sending BPM data
var keypress = require('keypress');
var SerialPort = require('serialport')
var Readline = SerialPort.parsers.Readline
var express = require('express');
var socket = require('socket.io');
var data1 = 0;
var data2 = 0;
let net = require('net');

const PORT = 8080;
const HOST='192.168.43.208';

var app = express();

let server = net.createServer(function(socket) {
    console.log("Connected");
    let timer = setInterval(function() {
        sendBPM(socket);
    }, 500);

    // Display error message
    socket.on('error', function(err) {

        clearInterval(timer);
        console.error(err);

    });

    // Detect a closed socket
    socket.on('close', function(err) {

        clearInterval(timer);
        console.log("Close");

    });

    // Set the Keep Alive so we can get an ACK from the device. Not sure how it works
    socket.setKeepAlive(true, 1000);

});

app.use(express.static('public'));

var io = socket(server);

io.on('connection', function(socket){

    console.log(socket.id);

});

var serialPort = new SerialPort('/dev/tty.usbmodem69', {
  baudRate: 9600
})

var parser = new Readline()
serialPort.pipe(parser)



parser.on('data', function (data) {
  //console.log('data received: ' + data)

  //console the BPM

  data1 = data;
  console.log(data);
})

/*serialPort.on('open', function () {
  console.log('Communication is on!')
})*/


// Start listening on a specific port and address
server.listen(PORT, HOST, function() {

	console.log("I'm listening at %s, on port %s", HOST, PORT);

});


function sendBPM(socket) {

    // Generate random number
    let bpm1 = data1;
    let bpm2 = data2;

    // Send random number with a separator character at the end.
    //socket.write(data1.toString()+",");
    socket.write(bpm1.toString() + ",");

    // Display what we sent.
    console.log("BPM: SEND");
    //console.log(data1);
    console.log(bpm1);


}


keypress(process.stdin);
process.stdin.on('keypress', function(ch, key){
  data1 = Math.floor(Math.random() * 100)+1;
  console.log(data1);


});
process.stdin.setRawMode(true);

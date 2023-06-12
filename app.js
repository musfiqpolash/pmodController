const express = require("express");
const http = require("http");
const { Server } = require("socket.io");
const { autoDetect } = require('@serialport/bindings-cpp');
const { SerialPort, ReadlineParser } = require('serialport');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

var device_path='/dev/ttyArduino';
var opsys = process.platform;
var serialPortError = false;
var errorMessage;

if (opsys == "win32" || opsys == "win64") {
    device_path="COM3";
} else if (opsys == "linux") {
    device_path='/dev/ttyArduino';
}

const Binding = autoDetect();
Binding.list().then(ports => {
    if (opsys == "win32" || opsys == "win64") {
        const port = ports.find(port => /2341/i.test(port.vendorId));
        if (port) device_path=port.path;
    } 
});

const port = new SerialPort({
    path: device_path,
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
});
const parser = port.pipe(new ReadlineParser());

app.use(express.static('public'));

app.get("/", (req, res)=>{
    // res.sendFile('/public/index.html' , { root: '.' });
});

io.on('connection', (socket) => {
    socket.on('toArduino', function (data) {
        if (serialPortError){
            console.log(errorMessage);
            io.emit('serialporterror',errorMessage);
        }
        console.log(data);
        port.write( data.command );
    });
});


parser.on('data', function(data){
    var received_data=JSON.parse(data);
    console.log("received from arduino "+data);
    if (received_data.sensor_data) {
        io.emit('sensor_data',received_data);
    } else {
        io.emit('data',received_data);
    }
});

// setInterval(()=>{
//     io.emit('webcam','some data');
// }, 1000);

server.listen(3000,()=>{
    console.log("listening on *.3000");
});
console.log("Web Server Started go to `http://localhost:3000` in your  Browser.");

port.on('error',(err)=>{
    console.log(err.message);
    serialPortError = true;
    errorMessage = err.message;
});
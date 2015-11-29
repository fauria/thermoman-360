var express = require('express');
var app = express();
var ejs = require('ejs');

app.engine('html', ejs.renderFile);
app.set('view engine', 'ejs');
app.use(express.static('public'));

var exec = require('child_process').exec;
var gm = require('gm');
var serialport = require('serialport'); 
var SerialPort = serialport.SerialPort; 

var repl = require('repl');

var arduino = new SerialPort('/dev/ttyACM0', {
	baudrate: 9600,
	parser: serialport.parsers.readline('\n')
});

arduino.on('open', function() {	

	console.log('Serial communication started...');
	
	var thermoman = function(socket){		
		var isHeatmap = false;

		arduino.on('data', function(data) {
			if(isHeatmap) {	
				console.log('HEATMAP:');
				console.log(JSON.parse(data.trim()));
				isHeatmap = false;
			}

			switch(data.trim()) {
				case 'ok-snap':
					process.emit('ok-snap');
					break;
				case 'begin-scan':
					isHeatmap = true;
				case 'end-scan':		
					socket.emit('end-scan');
					arduino.write('neutral\n');
					
					break;
				default: 
					process.emit('unknown-data', data);
					break;
			}
		});

		process.on('ok-snap', function(){
			exec('raspistill -vf -hf -o cam.jpg', function(err, stdout, stderr) {
				exec('convert -resize 640 cam.jpg hack.jpg', function(err, stdout, stderr) {
				//gm('./cam.jpg').resize(640, 480).write('./room.jpg', function (err) {
					arduino.write('scan\n');
				});
				//}):
			});
		});

		process.on('snap', function(){
			arduino.write('snap\n');
		});
					
		process.on('unknown-data', function(data) {		
			// console.log('Unknown data: '+data);		
		});
	}

	app.get('/', function (req, res) {
		res.render('index.html');
	});

	var server = app.listen(8080, function () {
		var io = require('socket.io')(server);
		io.sockets.setMaxListeners(1);		
		io.on('connection', thermoman);		
	});
});

/*
repl.start({
  prompt: 'Node.js via stdin> ',
  input: process.stdin,
  output: process.stdout
});
*/
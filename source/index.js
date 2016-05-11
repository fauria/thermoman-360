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
				arduino.write('neutral\n');
				break;
			default: 
				process.emit('unknown-data', data);
				break;
		}
	});

	process.on('ok-snap', function(){
		exec('raspistill -vf -hf -o cam.jpg', function(err, stdout, stderr) {
			//gm('./cam.jpg').resize(640, 480).write('./room.jpg', function (err) {
				arduino.write('scan\n');
			//}):
		});
	});

	process.on('snap', function(){
		arduino.write('snap\n');
	});
				
	process.on('unknown-data', function(data) {		
		// console.log('Unknown data: '+data);		
	});

});

repl.start({
  prompt: 'Node.js via stdin> ',
  input: process.stdin,
  output: process.stdout
});


/*

- Click boton snap
- Enviar ambient a arduino
- Arduino envía 'begin-ambient', despues la temperatura ambiente, y luego 'end-ambient'.
- Enviar snap a arduino
- Arduino coloca el cabezal en su sitio y devielve 'ok-snap'
- Si recibe 'ok-snap', hacer foto
- Guardar y escalar foto
- Enviar 'scan' a arduino
- Arduino envía 'begin-scan' 
- Al recibir 'begin-scan', se inicializa el objeto de temperaturas.
- Arduino mueve los servos y envía cadenas json con los datos de temperatura.
- Cada evento data se pasa por JSON decode y se guarda en el  objeto.
- Arduino al acabar envía 'end-scan'
- Se muestran los datos en el canvas

. Habrá que crear bloqueos para que no pueda darse varias veces al botón, etc.

*/
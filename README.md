Thermoman 360 - Smart home thermal imaging solution for effecient use of energy.
------

# The event

![Endesa Energy Challenge](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/hackathon-banner.jpg)

This project was developed during the first [Endesa Energy Challenges Hackathon](http://www.endesaenergychallenges.com/hackathon/), held in the Official College of Madrid Architects ([COAM](http://www.coam.org/), in Madrid, Spain between October 9th and 11th 2015.

The event was sponsored by [Endesa](http://www.endesaenergychallenges.com/) and runned by [Opinno](http://www.opinno.com/). Mentors from both organizations were present during the whole event, helping teams to structure and develop their ideas.

# The idea

![Idea draft](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/idea.jpg)

Our project was defined as *"An application that locates inefficiencies and energy loss within the home through the use of a thermographic sensor that detects differences in temperature"*

The goal was to develop a low cost thermographic camera that allowed the monitoring of rooms, learning about its users habits and detecting waste. 

This data, cross-referenced with external inputs, would generate recommendations to achive the most efficient use of energy.

# The team

![Thermoman 360 team members](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/winners.jpg)

Meet the team:

- Fernando Álvarez-Uría, Software Engineer. <fauria@gmail.com>. Twitter: [@fauria](https://twitter.com/fauria)
- Nuño Valencia, Industrial Engineer. <info@nunovalencia.info> Twitter: [@NuoValencia](https://twitter.com/NuoValencia)
- Andrea Jiménez, Business Analyst <andreaj.567@gmail.com>. Twitter: [@eatgreekspeakfr](https://twitter.com /eatgreekspeakfr)
- Diego Lasaosa, Architect. <diegolasaosa@certicalia.com> Twitter: [@diegolasaosa](https://twitter.com/diegolasaosa)

The teams were already pre-assigned before the event, although we hadn't met before.

At the entrance, the organisation handed each participant a hackathon kit, containing among other goodies one piece from a puzzle. 

The hackathon members teamed up by matching their puzzle pieces during a networking session. 

Each one had a superhero assigned, and ours was Ironman, thus the name of the project.

# Hardware

![Thermoman Rig](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/hardware.jpg)

For this project, we relied on the following parts:

- [Raspberry Pi](https://www.raspberrypi.org/) model B, with GPIO header break out.
- [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module/).
- [Arduino Uno board](https://www.arduino.cc/en/main/arduinoBoardUno).
- [Grove Base Shield](http://www.seeedstudio.com/depot/Base-Shield-V2-p-1378.html)
- Melexis MLX 90614 digital thermopile with 10° Field of View (FOV). Based on this project, an [infrared thermometer Grove module](http://www.seeed.cc/project_detail.html?id=1157) was later produced.
- Pan-tilt head, composed by two servos.
- Protoboards

The thermographic camera consisted on a piece of foam with both the camera and the sensor attached in a 90° angle arrangement.

This way, alternating the vertical servo between 0° and 90° allowd the usage of both the camera and the sensor.

# Software

![Thermoman actual picture](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/thermoman-action.gif)

We developed an Arduino sketch that performed a scan using the pan-tilt head. 

Knowing the field of view of the sensor was 10° on both axis, and the camera FOV 53.50° and 41.41° on X and Y respectively, we coud estimate a matrix of sensor readings. 

This approach was not very pricese, but enough for a proof of concept.

The Raspberry Pi runned a Node.js application, communicating with Arduino via USB serial terminal. Events were used to coordinate the different actions.

A web interface displayed the results, using an HTML5 canvas for the readings.

# Future improvements

The prototype was just a proof of concept. 

A potential commercial application should be efficient, able to perform readings in 360° and easly integrable in a home among many others.

# The prototype

![Fully functional prototype](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/prototype.gif)

For the assembly of the prototype we used a protoboard as a base, with the pant-tilt head, sensor foam setup and Raspberry Pi attached.

To perform a thermal image, the following steps were taken from the Node.js application on the Raspberry Pi:

1. Send a ```snap```command to Arduino to move the vertical servo to 90° and the horizontal servo to 180°. The camera should be looking forward.
2. [Take a picture](https://www.raspberrypi.org/documentation/usage/camera/raspicam/raspistill.md)
3. Send a ```reset``` command to Arduino to put both servos on ```0,0``` coordinates.
4. Send a ```scan``` command to Arduino. Now the servos start moving in increments, performing a sendor reading on each step. A JSON encoded string is sent back to the Raspberry Pi.
5. Send a ``neutral``` command to Arduino. This sets both servos on 90°.
6. Parse the JSON string sent from Arduino and display the image taken with a canvas overly showing the temperatures.


# The pitch

![Thermoman 360 team in front of the jury](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/pitch.jpg)

The jury was formed by:

**Juan Garrigosa** (Head of Innovation at Endesa), **Sandra Alfonso** (Head of Digital Market Transformation at Endesa), **Jorge Sánchez-Mayoral** (Digital Channel Director & Customer Experience at Endesa), **Enrique Dans** (Professor at IE Business School), **Antonio Fontanini** (Cex Advisor and Chief Optimistic Officer at Opinno), **Alberto Levy** (Innovation Evangelist) and **Javier Noguerol** (Senior researcher at Future Doers).

The pitch consisted on a five minutes talk, and altought the prototype could not be used live, the results were shown on the presentation.

# Awards

![Endesa Hackathon Winners](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/winners-all.jpg)

We won the first prize, awarded with 6.000€ for the team and four wooden table lamps, one for each member.

# Afterwork

![Endesa Hackathon Winners](https://raw.githubusercontent.com/fauria/thermoman-360/master/assets/exit-madrid.jpg)

After the prize-giving, the hackathon participants were taken to a special afterwork, held in [Exit Madrid](http://exit-game.es/?lang=en). It consisted on a *escape room* game, were we had to solver serveral puzzles inside a locked room before a certain deadline.

We had a great time there, working again together, but this time on a very different problem.

# Coverage

> November 30th, 2015

### Video: [Endesa Hackathon: Así se desarrolló el primer Hackathon de los #Energychallenges](https://www.youtube.com/watch?v=NXju4aeZCJc)

> November 25th, 2015

### Article: [Jóvenes competirán en un concurso para diseñar soluciones energéticas](http://www.elconfidencial.com/empresas/2015-11-25/jovenes-competiran-en-un-proyecto-para-disenar-soluciones-energeticas_1106238/)

> November 30th, 2015

### Article: [Una aplicación para saber por dónde se escapa el calor en casa gana el primer Hackathon Endesa](http://www.eleconomista.es/economia/noticias/7185653/11/15/Una-aplicacion-para-saber-por-donde-se-escapa-el-calor-en-casa-gana-el-primer-Hackathon-Endesa.html)


> November 30th, 2015

### TV: [Una aplicación para saber por dónde se escapa el calor en casa gana el primer Hackathon Endesa](http://www.telecinco.es/informativos/aplicacion-escapa-primer-Hackathon-Endesa_0_2092125256.html)


> November 30th, 2015

### Article: [Una app para saber por dónde se escapa el calor en casa gana el primer Hackathon Endesa](http://www.republica.com/2015/11/30/una-app-para-saber-por-donde-se-escapa-el-calor-en-casa-gana-el-primer-hackathon-endesa/)

> November 30th, 2015

### Article: [Una aplicación para saber por dónde se escapa el calor en casa gana el primer Hackathon Endesa](http://www.expansion.com/agencia/europa_press/2015/11/30/20151130142608.html)

> November 30th, 2015

### Article: [Una app para saber por dónde se escapa el calor en casa gana el primer Hackathon Endesa](http://www.endesa.com/es/saladeprensa/noticias/Entrega-premios-primer-Hackathon-Endesa)

> December 1st, 2015

### Article: [¿Por dónde se escapa el calor en casa? Endesa entrega los premios de su primer Hackathon](http://www.innovaspain.com/detalle_noticia.php?id=7559)

---


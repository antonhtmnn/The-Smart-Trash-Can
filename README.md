
## The Smart Trash Can

The Smart Trash Can is an innovative project aimed at addressing the environmental challenge of proper waste segregation. The project involves a robot capable of automatically identifying and sorting waste into appropriate categories.

### Table of Contents

- [Project Description](#project-description)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

### Project Description

Overfilled trash cans are a significant environmental issue. In Germany, only 68% of households practice waste separation, according to a [statistic](https://de.statista.com/statistik/daten/studie/1225/umfrage/praktizierte-muelltrennung-in-den-eu-laendern/). The Smart Trash Can aims to provide a solution by reliably analyzing and automatically sorting waste into designated bins.

<p align="center">
  <a href="https://www.youtube.com/watch?v=o4RRQOSKF5w" title="The Smart Trash Can">
    <img src="https://res.cloudinary.com/marcomontalbano/image/upload/v1649780668/video_to_markdown/images/youtube--o4RRQOSKF5w-c05b58ac6eb4c4700831b2b3070cd403.jpg" alt="The Smart Trash Can — demo video thumbnail" width="640" />
  </a>
  <br/>
  <sub>▶ click image to watch demo video</sub>
</p>

### Installation

To set up The Smart Trash Can on your local machine, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/antonhtmnn/The-Smart-Trash-Can.git
    ```
2. Navigate to the project directory:
    ```bash
    cd The-Smart-Trash-Can
    ```
3. Open the project in your preferred Arduino IDE.

### Usage

To run the application:

1. Connect your Arduino Nano and other components as per the pin configuration in `documentation.md`.
2. Upload the `TheSmartTrashCan.ino` sketch from the `TheSmartTrashCan` directory to your Arduino board.

The Smart Trash Can will start sorting waste based on the predefined parameters and sensors.

### Features

- **Waste Identification:** Identifies waste using metal sensors and color sensors.
- **Automated Sorting:** Automatically sorts waste into different bins based on the material type and weight.
- **Real-time Monitoring:** Continuously monitors and processes waste inputs.

### Project Structure

The project is structured as follows:

```
The-Smart-Trash-Can/
├── Bilder/
│   ├── Eingangsbereich.png
│   ├── Pinbelegung.png
│   ├── Programmablaufplan.png
│   ├── Roboter.png
│   └── Verteilungssystem.png
├── FarbsensorKalibrierung/
│   └── FarbsensorKalibrierung.ino
├── TheSmartTrashCan/
│   └── TheSmartTrashCan.ino
├── documentation.md
├── LICENSE
└── README.md
```

- **TheSmartTrashCan.ino:** Main program file for the smart trash can logic.
- **FarbsensorKalibrierung.ino:** Program for calibrating the color sensor.
- **Bilder Directory:** Contains images for various components and diagrams.
- **documentation.md:** A more complete description of the project (in German).

### Contributing

Contributions are welcome! Please fork the repository and create a pull request with your changes. Ensure you follow the coding conventions and include appropriate tests.

### License

This project is licensed under the MIT License.

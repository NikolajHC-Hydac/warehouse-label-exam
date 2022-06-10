<div id="top"></div>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4">
    <img src="images/logo.png" alt="Logo" width="291" height="110">
  </a>

<h3 align="center">Hydac DK Digital 1.0</h3>

  <p align="center">
    Box divided storage system controlled with buttons 
    <br />
    <a href="https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4">View Demo</a>
    ·
    <a href="https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4/issues">Report Bug</a>
    ·
    <a href="https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](http://localhost:1880/ui)

A simple box divided storage system, where two similar boxes with goods are placed on shelves. Buttons are placed on the front and back of the shelves, 2 push buttons for each pair of boxes. When a box is empty, the user presses the "order" on the front of the shelf, and the system notes on the reorder list that the box needs to be refilled. Once a week, the purchasing department will get a list of what c-items (bolts, washers and nuts) that needs to be ordered

Part goal:
C-items (bolts, washers and nuts) are ordered semi automatically by the user, system notes on the reorder list and sends it to the purchasing department weekly. Goods are stocked directly on the shelf.

Goal:
C-items (bolts, washers and nuts) ordered semi automatically by the user, and is sent directly to the distributor of said item. Items stocked directly on the shelf, and ready to use, without the purchasing department using resources on the process. Every month, the purchasing department will receive an invoice, while responsibility for the stock is outsourced to the user.

Gain:
It provides gain on all shelves: Purchasing, finance and user have fewer hours of administration in connection with ordering, invoicing, status, etc. Warehouse spends less time on transport to and from the warehouse and less time on searching for the goods. In addition, the standard program always contains the relevant items in appropriate quantities, and we can therefore cut back on both purchasing and stock binding.

<p align="right">(<a href="#top">back to top</a>)</p>



### Built With

* [Node-red](https://nodered.org/)
* [C++](https://isocpp.org/)
* [SQLite](https://www.sqlite.org/index.html)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

#### Debian and ubuntu based linux distributions  

* Node.js / npm
  ```sh
  # Using Ubuntu  
  curl -fsSL https://deb.nodesource.com/setup_14.x | sudo -E bash -
  sudo apt-get install -y nodejs

  # Using Debian, as root
  curl -fsSL https://deb.nodesource.com/setup_14.x | bash -
  apt-get install -y nodejs
  ```

* Node-red
  ```sh
  sudo npm install -g --unsafe-perm node-red
  ```  

#### Windows

* Node.js
  ```markdown
  Download a 64 or 32 bit version of node.js at [https://nodejs.org](https://nodejs.org/download/release/v14.19.1/)  
  Run the downloaded MSI file.  
    
  Once installed, open a command prompt and run the following command to ensure Node.js and npm are installed correctly.

  Using Powershell: node --version; npm --version

  Using cmd: node --version && npm --version
  ```  

* Node-red
  ```sh
  npm install -g --unsafe-perm node-red
  ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4.git
   ```
2. Build and upload esp32 code to control board 
3. Start node-red
    ```sh
    node-red
    ```
4. Import the "Flows.json" file using the node-red GUI
5. Install missing node-red modules
6. Set up mqtt server in the "MQTT" flow
7. In the "Database" flow, point the sqlite and watch nodes to the location of warehouselabels.db
8. Go to http://localhost:1880/ui, or wherever your node-red instance is hosted, enter the setup page, and add the email you want to receive updates on.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

![TestStand][test-stand]

Buttons are placed in the front of every box pair on shelves, as well as behind them.  
Product numbers are then added to the database, and paired with their respective buttons, either by manually adding them using the setup page in the UI, or by importing them using a CSV file.  
When a box has been emptied, the user presses the matching front button once, and puts the box back in the back of the shelf.  
When the boxes are refilled, the user that is refilling the box, presses the matching button on the back of the shelf, to indicate to the system that the box has been filled again.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [x] LED's on front buttons, showing the inventory status to the user
- [x] Automated opening of the UI after a system reset
- [x] Control board revision 4 PCB
    - [x] Design
    - [x] Order
    - [ ] Test
- [x] Buttons PCB
    - [x] Design
    - [x] Order
    - [x] Test

See the [open issues](https://github.com/HydacDK/New-Warehouse-Lables/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Linkedin: Nikolaj Hult-Christensen - [/in/nikolajhult](https://linkedin.com/in/nikolajhult)  
Email: Nikolaj.Hult-Christensen@hydac.dk  
Element: @hultn:hydac.com

Project Link: [https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4](https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/HydacDK/New-WarehouseLabels.svg?style=for-the-badge
[contributors-url]: https://github.com/HydacDK/New-WarehouseLabels/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/HydacDK/New-Warehouse-Lables/tree/Prototype4.svg?style=for-the-badge
[forks-url]: https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4/network/members
[stars-shield]: https://img.shields.io/github/stars/HydacDK/New-Warehouse-Lables/tree/Prototype4.svg?style=for-the-badge
[stars-url]: https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4/stargazers
[issues-shield]: https://img.shields.io/github/issues/HydacDK/New-Warehouse-Lables/tree/Prototype4.svg?style=for-the-badge
[issues-url]: https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4/issues
[license-shield]: https://img.shields.io/github/license/HydacDK/New-Warehouse-Lables/tree/Prototype4.svg?style=for-the-badge
[license-url]: https://github.com/HydacDK/New-Warehouse-Lables/tree/Prototype4/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
[test-stand]: images/teststand.jpg

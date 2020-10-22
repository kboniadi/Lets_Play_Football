# Let's Play NFL Football
Your agile team is to write an application that stores the given National Football League (NFL) information into an ordered or unordered map (not using the map or unordered map STL or the QT map). The underlying data structure of the map is the choice of the team. The map should store either the stadiums and/or the souvenirs. The application will allow football fans to plan their dream vacation. 

---

## Table of Contents
- [Installation](#installation)
- [Features](#features)
- [Team](#team)
- [FAQ](#faq)
- [Support](#support)
- [License](#license)

---

## Installation

### Clone

- Clone this repo to your local machine using `https://github.com/kboniadi/European-Vacation-App.git`

### Setup

- Download Qt from https://www.qt.io/download

> while in the project root directory, make a build directory within qt/ and then cd into it

```shell
$ mkdir qt/_build
$ cd qt/_build
```

> generate a Makefile using qmake  and then run make

```shell
$ path/to/Qt/5.xx.x/compiler_name/bin/qmake ../app/
$ make
```

> run the executable

```shell
$ ./app
```
- See the [Support](#support) section if you run into any problems
---

## Features
1. Display all the information related to only one particular football team (team name, stadium name, seating capacity, location, conference, division, surface type, stadium roof type, date opened). Do not display information related to the other NFL teams.

2. Display the list of the NFL teams sorted by team name.

3. Display the list of NFL stadiums and their corresponding team name sorted by stadium name.
  
4. Display the list of only the American Football Conference teams sorted by team name. The National Football Conference teams should not be displayed.
  
5. Display the list of only the National Football Conference teams sorted by team name. The American Football Conference teams should not be displayed.

6. Display the list of only the NFC North teams sorted by team name.  No other teams should be displayed.

7. Display the list of NFL stadiums sorted by date opened (oldest to newest).  Display the team name and date opened.
  
8. Display the list of only the stadiums that have an “open” stadium roof type and their corresponding team name sorted by stadium name. Display the number of stadiums have an “open” roof. If two teams use the same stadium, count the “open” roof just once.

9. Display the list of NFL stadiums and their corresponding team names sorted by seating capacity (smallest to largest).  Be sure to display seating capacity.  Display the total capacity of all NFL teams. If two teams use the same stadium, count the capacity of the stadium only once.

10. Display the list of NFL teams, their stadium names, their conference, and their corresponding location sorted by conference name.

11. Display the list of NFL teams whose surface type is Bermuda Grass. Display the number of NFL teams whose surface type is Bermuda Grass.

12. Display all the souvenir list related to only one particular football team.

13. Provide the capability for a football fan to visit any other team of their choice starting at the Green Bay Packers traveling the shortest distance.  Your Agile team should implement Dijkstra’s or the A* algorithm. Display the total distance travelled.

14. Provide the capability for a football fan to plan his/her dream vacation by allowing a football fan to choose their starting team and all the other teams they would like to visit using the order specified (determine the shortest distance).  Display the total distance travelled.

15. Provide the capability to visit the all the teams starting at New England Patriots traveling the shortest distance. Chose the team closest to the New England Patriots and then chose the team closes to that team, etc.
  - Display the total distance traveled
  
16. Provide the capability for a football fan to plan his/her dream vacation by allowing a football fan to choose their starting team
  - Then allow a football fan to select other teams they wish to visit
  - Plan the trip starting with the selected team then visit each of the other teams in the most efficient order (recursively choose the team closest to the previous team)    
  - Display the total distance traveled

17. Determine the minimum spanning tree (MST) connecting all the NFL stadiums using Prim’s or Kruskal’s algorithm. Display the associated mileage.

18. Perform a DFS starting at the Minnesota Vikings.  If there is a choice, always choose the shortest distance.  Display the associated mileage.
  
19. Perform a BFS starting at Los Angeles Rams.  If there is a choice, always choose the shortest distance. Display the associated mileage.

20. When taking any trip:
  - A football fan can purchase multiple souvenirs  
  - Your Agile team must keep track of the number of souvenirs purchased at each stadium.
  - Display the total amount spent at each stadium and a grand total for all stadiums visited

21. Maintenance (administrator only - requires a password to gain access)
  - Provide the capability to add a new team and its corresponding information by having your program read from an input file given to the class (assume the team has the default souvenirs)
  - Provide the capability to change the prices of the traditional souvenirs
  - Provide the capability to add new traditional souvenirs
  - Provide the capability to delete traditional souvenirs

22. Provide the ability to modify stadium information including capacity if a team moves into a new stadium. (administrator only) (The Buffalo Bills are planning to move to a new stadium in 2022).


---
  
## Team
- **Noah Vaks** - Product Owner - [noahvaks](https://github.com/noahvaks)
- **Muzammil Allie** - Scrum Master - [muzzy230](https://github.com/muzzy230)
- **Kord Boniadi** - Developer - [kboniadi](https://github.com/kboniadi)
- **Hieu Nguyen** - Developer - [yusei2910](https://github.com/yusei2910)

---

## FAQ

---

## Support

---

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)
- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright 2020 © Brogrammers

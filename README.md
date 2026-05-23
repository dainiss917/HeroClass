This program demonstrates important object-oriented programming concepts like inheritance, composition, dependency, etc through the interaction of different gamerelated classes.

The Hero class inherits from GameObject, while Stats and SoulMark are implemented through composition because they belong exclusively to the Hero and are destroyed together with it. Guild and Weapon are modeled using aggregation since they exist independently from the Hero. The Potion class represents a dependency relationship because it is temporarily used by the Hero during execution.

The project also includes a basic weapon inheritance hierarchy where Sword derives from the Weapon base class and overrides the attack() method using polymorphism.

To compile you need to use
g++ -std=c++11 main.cpp -o game

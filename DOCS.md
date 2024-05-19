# Documantations
<br>

## Setup
Just add The folder to your Source Files and do in your main/game file
```
#include "ECS/Components.h"
```
To use the features use
```
Manager manager;
```
in your file where you included it

## Entitys
Create an Entity with
```
auto& myEntity = manager.addEntity();
```
### Add Components
in your start function with 
```
myEntity.addComponent<TransformComponent>();
```
### Collison
to make collision you first need to add the component
```
myEntity.addComponent<MovingObjectComponent>();
```
to use it your just need to add the velocity, and your need to asign a group of your collidable wall and add your Manager
```
myEntity.getComponent<MovingObjectComponent>().MovePosition(Vector2 {velocity.x, velocity.y}, your_group, manager);
```
### Groups
to add groups you need to make an enum of the type of std::size_t
```
enum groupLabels : std::size_t {
	groupCollider,
	groupMap,
	groupPlayer
};
```

# Components
``` 
Transform Component
Sprite Component
Animated Sprite Component
Moving Object Component
```
